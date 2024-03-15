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

#include <stdbool.h>
#include <stdint.h>

#include <platform.h>
#include <build/debug.h>

#include "common/log.h"
#include "common/utils.h"
#include "common/maths.h"
#include "drivers/bus_i2c.h"
#include "drivers/time.h"
#include "drivers/pitotmeter/pitotmeter.h"

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

#define RANGE_INCH_H2O      30
#define DLHR30G_OFFSET         0.0f
#define DLHR30G_SCALE          262144.0f
// NOTE :: DLHR30G_OFFSET_CORR can be used for offset correction. Now firmware relies on zero calibration
#define DLHR30G_OFFSET_CORR    0.0f   //MUST BE TESTED IN LAB

typedef struct __attribute__ ((__packed__)) dlhrl30gCtx_s {
    bool     dataValid;
    uint32_t dlhrl30g_ut;
    uint32_t dlhrl30g_up;
} dlhrl30gCtx_t;

STATIC_ASSERT(sizeof(dlhrl30gCtx_t) < BUS_SCRATCHPAD_MEMORY_SIZE, busDevice_scratchpad_memory_too_small);

static bool dlhrl30g_start(pitotDev_t * pitot)
{
    UNUSED(pitot);
    return true;
}

static bool dlhrl30g_read(pitotDev_t * pitot)
{
    uint8_t rxbuf1[4];

    dlhrl30gCtx_t * ctx = busDeviceGetScratchpadMemory(pitot->busDev);
    ctx->dataValid = false;

    if (!busReadBuf(pitot->busDev, 0xFF, rxbuf1, 4)) {
        return false;
    }

    // status = 00 -> ok, new data
	// status = 01 -> reserved
    // status = 10 -> ok, data stale
    // status = 11 -> error
    const uint8_t status = ((rxbuf1[0] & 0xC0) >> 6);

    if (status) {
        // anything other then 00 in the status bits is an error
        LOG_DEBUG( PITOT, "DLHR30G: Bad status read. status = %u", (unsigned int)(status) );
        return false;
    }

    int16_t dP_raw1, dT_raw1;

    dP_raw1 = 0x3FFF & ((rxbuf1[0] << 8) + rxbuf1[1]);
    dT_raw1 = (0xFFE0 & ((rxbuf1[2] << 8) + rxbuf1[3])) >> 5;

    // Data valid, update ut/up values
    ctx->dataValid = true;
    ctx->dlhrl30g_up = dP_raw1;
    ctx->dlhrl30g_ut = dT_raw1;

    return true;
}

static void dlhrl30g_calculate(pitotDev_t * pitot, float *pressure, float *temperature)
{
    dlhrl30gCtx_t * ctx = busDeviceGetScratchpadMemory(pitot->busDev);

  
    // pressure in inchH2O
    float dP_inchH2O = 1.25f *  2.0f * RANGE_INCH_H2O  * (((float)ctx->dlhrl30g_up - (DLHR30G_OFFSET + DLHR30G_OFFSET_CORR) ) / DLHR30G_SCALE); 

    // temperature in deg C
    float T_C = (float)ctx->dlhrl30g_ut * (200.0f / 2047.0f) - 50.0f;     

    // result must fit inside the max pressure range
    if ((dP_inchH2O > RANGE_INCH_H2O) || (dP_inchH2O < 0)) {
        LOG_DEBUG( PITOT,"DLHR30G: Out of range. pressure = %f", (double)(dP_inchH2O) );
        return;
    }

    if (pressure) {
        *pressure = INCH_H2O_TO_PASCAL( dP_inchH2O);   // Pa
    }

    if (temperature) {
        *temperature = C_TO_KELVIN( T_C); // K
    }
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
