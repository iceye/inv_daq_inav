/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "pitotmeter_dlhr_l30g.h"


#include <platform.h>
#include <build/debug.h>

#include "common/log.h"
#include "common/utils.h"
#include "common/maths.h"
#include "drivers/bus_i2c.h"
#include "drivers/time.h"
#include "drivers/pitotmeter/pitotmeter.h"

#ifndef DLHRL30G_RESOLUTION
#define DLHRL30G_RESOLUTION DLHRL30G_RESOLUTION_18_BITS
#endif

#ifndef DLHRL30G_MEASURAMENT_TYPE
#define DLHRL30G_MEASURAMENT_TYPE DLHRL30G_AVERAGE8
#endif

//ONLY SPI BUS IS SUPPORTED

// //---------------------------------------------------
// // Gas Constant is from Aerodynamics for Engineering Students, Third Edition, E.L.Houghton and N.B.Carruthers
// #define ISA_GAS_CONSTANT 287.26f
// #define ISA_LAPSE_RATE 0.0065f

// // Standard Sea Level values
// // Ref: https://en.wikipedia.org/wiki/Standard_sea_level
// #define SSL_AIR_DENSITY         1.225f // kg/m^3
// #define SSL_AIR_PRESSURE 101325.01576f // Pascal
// #define SSL_AIR_TEMPERATURE    288.15f // K
// //---------------------------------------------------

#define INCH_OF_H2O_TO_PASCAL   248.84f

#define INCH_H2O_TO_PASCAL(press) (INCH_OF_H2O_TO_PASCAL * (press))

#define DLHR30G_OFFSET_CORR    0x19EA40   //MUST BE TESTED IN LAB

uint8_t dlhrl30g_status;
bool dlhrl30g_init = false;
uint32_t dlhrl30g_pressure_resolution_mask = 0;
uint32_t dlhrl30g_temperature_resolution_mask = 0;
float dlhrl30g_pressure_zero_ref = 0.0f;



static float dlhrl30g_transferPressure(uint32_t raw_value) {
	// Based on the following formula in the datasheet:
	//     Pressure(inH2O) = 1.25 x ((P_out_dig - OS_dig) / 2^24) x FSS(inH2O)
	if(raw_value<DLHR30G_OFFSET_CORR){
		return 0.0f;
	}
	return 1.25f * (( (float) raw_value - DLHR30G_OFFSET_CORR) / DLHRL30G_FULL_SCALE_REF) * DLHRL30G_PRESSURE_RANGE;
}

// Convert a raw digital temperature read from the sensor to a floating point value in Celcius.
float dlhrl30g_transferTemperature(uint32_t raw_value) {
	// Based on the following formula in the datasheet:
	//     Temperature(degC) = ((T_out_dig * 125) / 2^24) - 40
	return (((float) raw_value * 125.0f) / DLHRL30G_FULL_SCALE_REF) - 40.0f;
}

// Convert the input in inH2O to the configured pressure output unit.
static  float dlhrl30g_convertPressure(float in_h2o, dlhrl30g_PressureUnit_t pressure_unit) {
	switch(pressure_unit) {
	  case  DLHRL30G_PASCAL:
		return 249.08 * (in_h2o);
	  case  DLHRL30G_IN_H2O:
	  default:
		return in_h2o;
	}
}

// Convert the input in Celcius to the configured temperature output unit.
static float dlhrl30g_convertTemperature(float degree_c, dlhrl30g_TemperatureUnit_t temperature_unit) {
	switch(temperature_unit) {
	  case  DLHRL30G_FAHRENHEIT:
		return degree_c * 1.8 + 32.0;
	  case  DLHRL30G_KELVIN:
		return degree_c + 273.15;
	  case  DLHRL30G_CELCIUS:
	  default:
		return degree_c;
	}
}


typedef struct __attribute__ ((__packed__)) dlhrl30gCtx_s {
    bool     dataValid;
    uint32_t dlhrl30g_ut;
    uint32_t dlhrl30g_up;
} dlhrl30gCtx_t;

STATIC_ASSERT(sizeof(dlhrl30gCtx_t) < BUS_SCRATCHPAD_MEMORY_SIZE, busDevice_scratchpad_memory_too_small);


static bool dlhr30g_startNewMeasurament(pitotDev_t * pitot){

	uint8_t i2cMeasurementType = DLHRL30G_MEASURAMENT_TYPE;
	if (!busWriteBuf(pitot->busDev, 0xFF, (uint8_t*)&i2cMeasurementType, 1)) {
		return false;
	}
	return true;
}


static bool dlhrl30g_start(pitotDev_t * pitot)
{
    UNUSED(pitot);
    if(!dlhrl30g_init){
    	dlhrl30g_init = true;
		// Produce bitmasks to mask out undefined bits of both sensors. The pressure sensor's resolution
		  // depends on the purchased option (-6, -7, -8 for 16-, 17-, and 18-bit resolution respectively),
		  // and the temperature sensor is always 16-bit resolution. Note that the *lower* bits are the unused
		  // bits, so that it is the *UPPER* bits that should be kept and the lower ones discarded.
		dlhrl30g_pressure_resolution_mask    = ~(((uint32_t) 1 << (DLHRL30G_FULL_SCALE_RESOLUTION - DLHRL30G_RESOLUTION)) - 1);
		dlhrl30g_temperature_resolution_mask = ~(((uint32_t) 1 << (DLHRL30G_FULL_SCALE_RESOLUTION - DLHRL30G_TEMPERATURE_RESOLUTION)) - 1);
		dlhrl30g_pressure_zero_ref = 0.1f * DLHRL30G_FULL_SCALE_REF;

    }

    dlhr30g_startNewMeasurament(pitot);

    return true;
}

static bool dlhrl30g_read(pitotDev_t * pitot)
{

	dlhrl30gCtx_t * ctx = busDeviceGetScratchpadMemory(pitot->busDev);
	ctx->dataValid = false;

	uint8_t rxbuf1[7];
	// Read the 8-bit status data.
	if (!busReadBuf(pitot->busDev, 0xFF, (uint8_t*)&rxbuf1, 7)) {
		return false;
	}
	dlhrl30g_status = rxbuf1[0];

	if ((dlhrl30g_status & (DLHRL30G_ERROR_MEMORY | DLHRL30G_ERROR_ALU | DLHRL30G_RESERVED_7)) != 0) {
	  // An ALU or memory error occurred.
	  return false;
	}

	if ((dlhrl30g_status & DLHRL30G_BUSY) != 0) {
	  // The sensor is still busy; retry on next loop.
	  return false;
	}


	ctx->dataValid = true;
	ctx->dlhrl30g_up = (rxbuf1[1]<<16 | rxbuf1[2]<<8 | rxbuf1[3]);
	ctx->dlhrl30g_ut = (rxbuf1[4]<<16 | rxbuf1[5]<<8 | rxbuf1[6]);


	//Asking for a new measurement
	dlhr30g_startNewMeasurament(pitot);

    return true;
}

static void dlhrl30g_calculate(pitotDev_t * pitot, float *pressure, float *temperature)
{
    dlhrl30gCtx_t * ctx = busDeviceGetScratchpadMemory(pitot->busDev);
    float pInch = dlhrl30g_transferPressure(ctx->dlhrl30g_up & dlhrl30g_pressure_resolution_mask);
    *pressure = dlhrl30g_convertPressure(pInch, DLHRL30G_PASCAL);
   	*temperature = dlhrl30g_convertTemperature(dlhrl30g_transferTemperature(ctx->dlhrl30g_ut & dlhrl30g_temperature_resolution_mask), DLHRL30G_CELCIUS);


}

bool dlhrl30gDetect(pitotDev_t * pitot)
{
    uint8_t rxbuf[4];
    bool ack = false;

    pitot->busDev = busDeviceInit(BUSTYPE_I2C, DEVHW_DLHR30G, 0, OWNER_AIRSPEED);
    if (pitot->busDev == NULL) {
        return false;
    }

    // Read twice to fix:
    // Sending a start-stop condition without any transitions on the SCL line (no clock pulses in between) creates a
    // communication error for the next communication, even if the next start condition is correct and the clock pulse is applied.
    // An additional start condition must be sent, which results in restoration of proper communication.
    ack = busReadBuf(pitot->busDev, 0xFF, rxbuf, 4);
    ack = busReadBuf(pitot->busDev, 0xFF, rxbuf, 4);
    if (!ack) {
        return false;
    }

    // Initialize busDev data
    dlhrl30gCtx_t * ctx = busDeviceGetScratchpadMemory(pitot->busDev);
    ctx->dataValid = false;
    ctx->dlhrl30g_ut = 0;
    ctx->dlhrl30g_up = 0;

    // Initialize pitotDev object
    pitot->delay = 10000;
    pitot->calibThreshold = 0.00001f;   // low noise sensor
    pitot->start = dlhrl30g_start;
    pitot->get = dlhrl30g_read;
    pitot->calculate = dlhrl30g_calculate;
    return true;
}
