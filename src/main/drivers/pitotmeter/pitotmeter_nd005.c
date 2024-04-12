/*
 * pitotmeter_nd005.c
 *
 *  Created on: Apr 7, 2024
 *      Author: sandro.bottoni
 */


#include "pitotmeter_nd005.h"

#include <platform.h>
#include <build/debug.h>

#include "common/log.h"
#include "common/utils.h"
#include "common/maths.h"
#include "drivers/bus_i2c.h"
#include "drivers/time.h"
#include "drivers/pitotmeter/pitotmeter.h"

#include "innovavionics/inv_data.h"


#define ND005_OFFSET_CORR  28    //MUST BE TESTED IN LAB
#define ND005_SWITCHUP_VALUE 23600 //~80% of the range
#define ND005_SWITCHDOWN_VALUE 5900 //~20% of the range
#define ND005_MINSWITCH_MS 2000 //~30% of the range
#define ND005_ADJ_TIMESET_MS 200 //~30% of the range

nd005moderegs_t nd005_modeControl = {
		.notch = ND005_NOTCH_ON,
		.bwlimit = ND005_BW_50HZ,
		.watchdog = ND005_WATCHDOG_OFF,
		.range = ND005_PSI05,
};
uint8_t nd005_rateControl = ND005_RATE_CONTROL_AUTO;


typedef struct __attribute__ ((__packed__)) nd005Ctx_s {
    bool     dataValid;
    int16_t nd005_ut;
    int16_t nd005_up;
} nd005Ctx_t;


float nd005_pressureRange = 3447.3786465f;
float nd005_pressure;
float nd005_temperature;
uint32_t ajustLastMs = 0;

STATIC_ASSERT(sizeof(nd005Ctx_t) < BUS_SCRATCHPAD_MEMORY_SIZE, busDevice_scratchpad_memory_too_small);

static uint8_t nd005_modeControlReg(){
	return nd005_modeControl.notch<<7 | nd005_modeControl.bwlimit<<4 | nd005_modeControl.watchdog<<3 | nd005_modeControl.range;
}



static void nd005_adjustRange(pitotDev_t *pitot, bool higherRange) {

	if (higherRange) {
		if (nd005_modeControl.range == ND005_PSI05) {
			nd005_modeControl.range = ND005_PSI08;
			nd005_pressureRange = 5515.8058344f;
		} else if (nd005_modeControl.range == ND005_PSI08) {
			nd005_modeControl.range = ND005_PSI10;
			nd005_pressureRange = 6894.757293f;
		} else if (nd005_modeControl.range == ND005_PSI10) {
			nd005_modeControl.range = ND005_PSI20;
			nd005_pressureRange = 13789.514586f;
		} else if (nd005_modeControl.range == ND005_PSI20) {
			nd005_modeControl.range = ND005_PSI40;
			nd005_pressureRange = 27579.029172f;
		} else if (nd005_modeControl.range == ND005_PSI40) {
			nd005_modeControl.range = ND005_PSI50;
			nd005_pressureRange = 34473.786465f;
		} else {
			return;
		}
	} else {
		if (nd005_modeControl.range == ND005_PSI50) {
			nd005_modeControl.range = ND005_PSI40;
			nd005_pressureRange = 27579.029172f;
		} else if (nd005_modeControl.range == ND005_PSI40) {
			nd005_modeControl.range = ND005_PSI20;
			nd005_pressureRange = 13789.514586f;
		} else if (nd005_modeControl.range == ND005_PSI20) {
			nd005_modeControl.range = ND005_PSI10;
			nd005_pressureRange = 6894.757293;
		} else if (nd005_modeControl.range == ND005_PSI10) {
			nd005_modeControl.range = ND005_PSI08;
			nd005_pressureRange = 5515.8058344f;
		} else if (nd005_modeControl.range == ND005_PSI08) {
			nd005_modeControl.range = ND005_PSI05;
			nd005_pressureRange = 3447.3786465f;
		} else {
			return;
		}
	}



}

static bool nd005_start(pitotDev_t * pitot)
{
	uint8_t rxbuf1[4];
	pitot->busDev->flags |= DEVFLAGS_USE_RAW_REGISTERS;
	nd005Ctx_t * ctx = busDeviceGetScratchpadMemory(pitot->busDev);
	ctx->dataValid = false;

	for(uint8_t i = 0; i<10; i++){
		uint8_t modeControlData = nd005_modeControlReg();
		uint16_t combinedControl = (modeControlData << 8) | nd005_rateControl; // *BITWISE* OR to combine bytes
		if (!busWriteBuf(pitot->busDev, 0xFF, (uint8_t*)&modeControlData, 1)) {
			return false;
		}

		if (!busReadBuf(pitot->busDev, 0xFF, rxbuf1, 4)) {
			return false;
		}
		delay(5);
	}
	ctx->dataValid = false;
	ctx->nd005_up = (((rxbuf1[0] << 8) + rxbuf1[1]))-ND005_OFFSET_CORR;
	ctx->nd005_ut = ((rxbuf1[2] << 8) + rxbuf1[3]);
    return true;
}


static bool nd005_read(pitotDev_t * pitot){
	uint8_t rxbuf1[4];

	nd005Ctx_t * ctx = busDeviceGetScratchpadMemory(pitot->busDev);

	uint8_t modeControlData = nd005_modeControlReg();
	uint16_t combinedControl = (modeControlData << 8) | nd005_rateControl; // *BITWISE* OR to combine bytes
	if (!busWriteBuf(pitot->busDev, 0xFF, (uint8_t*)&modeControlData, 1)) {
		return false;
	}

	if (!busReadBuf(pitot->busDev, 0xFF, rxbuf1, 4)) {
		return false;
	}

	ctx->dataValid = true;
	ctx->nd005_up = (((rxbuf1[0] << 8) + rxbuf1[1]))-ND005_OFFSET_CORR;
	ctx->nd005_ut = ((rxbuf1[2] << 8) + rxbuf1[3]);
	if(nd005_modeControl.range != ND005_PSI50 && ctx->nd005_up>ND005_SWITCHUP_VALUE){

			nd005_adjustRange(pitot, true);

	}
	else
	if (nd005_modeControl.range != ND005_PSI05 && ctx->nd005_up < ND005_SWITCHDOWN_VALUE) {

			nd005_adjustRange(pitot, false);

	}
	return true;
}


static void nd005_calculate(pitotDev_t * pitot, float *pressure, float *temperature){
	nd005Ctx_t * ctx = busDeviceGetScratchpadMemory(pitot->busDev);

	if(ctx->nd005_up<0){
		ctx->nd005_up = 0;
	}

	if(ctx->nd005_up<0){
		ctx->nd005_up = 0;
	}
	*pressure = ((((int16_t)ctx->nd005_up) / 29491.2) * (nd005_pressureRange)); // divide by 90% of 2^15 and multiply by range value

	uint8_t tempDec = (ctx->nd005_ut & 0xFF00) >> 8;
	uint8_t tempInt = (ctx->nd005_ut & 0x00FF);
	*temperature = (float) ((float)(tempDec)  +  (tempInt/256.0f));;



}


bool nd005Detect(pitotDev_t * pitot)
{
    uint8_t rxbuf[4] = {0};
    bool ack = false;

    pitot->busDev = busDeviceInit(BUSTYPE_I2C, DEVHW_ND005, 0, OWNER_AIRSPEED);
    if (pitot->busDev == NULL) {
        return false;
    }

    // Read twice to fix:
	// Sending a start-stop condition without any transitions on the SCL line (no clock pulses in between) creates a
	// communication error for the next communication, even if the next start condition is correct and the clock pulse is applied.
	// An additional start condition must be sent, which results in restoration of proper communication.
    uint8_t modeControlData = nd005_modeControlReg();
    uint16_t combinedControl = (modeControlData << 8) | nd005_rateControl; // *BITWISE* OR to combine bytes
    if (!busWriteBuf(pitot->busDev, 0xFF, (uint8_t*)&modeControlData, 1)) {
    	return false;
    }
	ack = busReadBuf(pitot->busDev, 0xFF, rxbuf, 4);
	if (!rxbuf[0] && !rxbuf[1] && !rxbuf[2] && !rxbuf[3]) {
		return false;
	}

	// Initialize busDev data
	nd005Ctx_t * ctx = busDeviceGetScratchpadMemory(pitot->busDev);
	ctx->dataValid = false;
	ctx->nd005_ut = 0;
	ctx->nd005_up = 0;

	// Initialize pitotDev object
	pitot->delay = 10000;
	pitot->calibThreshold = 0.00001f;   // low noise sensor
	pitot->start = nd005_start;
	pitot->get = nd005_read;
	pitot->calculate = nd005_calculate;
	return true;

}



