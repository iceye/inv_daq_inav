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

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "pitotmeter.h"

typedef enum {
	DLHRL30G_GAGE         = 'G',
	DLHRL30G_DIFFERENTIAL = 'D',
  } dlhrl30g_SensorType_t;

  // The sensor's resolution for pressure readings, where part numbers:
  //   * DLHR-*-6 are 16-bit resolution.
  //   * DLHR-*-7 are 17-bit resolution.
  //   * DLHR-*-8 are 18-bit resolution.
  typedef enum  {
    DLHRL30G_RESOLUTION_16_BITS = 16,
	DLHRL30G_RESOLUTION_17_BITS = 17,
	DLHRL30G_RESOLUTION_18_BITS = 18,
  } dlhrl30g_SensorResolution_t;

  typedef enum  {
	  DLHRL30G_SINGLE    = 0xAA,
	  DLHRL30G_AVERAGE2  = 0xAC,
	  DLHRL30G_AVERAGE4  = 0xAD,
	  DLHRL30G_AVERAGE8  = 0xAE,
	  DLHRL30G_AVERAGE16 = 0xAF,
  }dlhrl30g_MeasurementType_t;

  typedef enum {
	  DLHRL30G_RESERVED_7    = 1<<7,
	  DLHRL30G_POWER_ON      = 1<<6,
	  DLHRL30G_BUSY          = 1<<5,
	  DLHRL30G_MODE          = 1<<4 | 1<<3,
	  DLHRL30G_ERROR_MEMORY  = 1<<2,
	  DLHRL30G_CONFIGURATION = 1<<1,
	  DLHRL30G_ERROR_ALU     = 1<<0,
  }dlhrl30g_StatusFlags_t;

  typedef enum  {
	  DLHRL30G_IN_H2O = 'H',
	  DLHRL30G_PASCAL = 'P',
  }dlhrl30g_PressureUnit_t;

  typedef enum  {
	  DLHRL30G_CELCIUS    = 'C',
	  DLHRL30G_FAHRENHEIT = 'F',
	  DLHRL30G_KELVIN     = 'K',
  }dlhrl30g_TemperatureUnit_t;


// The length of the status information in the I2C response.
#define DLHRL30G_READ_STATUS_LENGTH 1

// The length of the pressure data in the I2C response.
#define DLHRL30G_READ_PRESSURE_LENGTH 3

// The length of the temperature data in the I2C response.
#define DLHRL30G_READ_TEMPERATURE_LENGTH 3

// The "full scale" resolution of the pressure and temperature data, which is fixed
// at 24 bits.
#define DLHRL30G_FULL_SCALE_RESOLUTION 24

// The actual temperature resolution, which is fixed at 16 bits.
#define DLHRL30G_TEMPERATURE_RESOLUTION 16

//Inch of water sensor range
#define DLHRL30G_PRESSURE_RANGE 30.0f


// The value of a full scale temperature or pressure, 2^24.
#define DLHRL30G_FULL_SCALE_REF ((uint32_t) 1 << DLHRL30G_FULL_SCALE_RESOLUTION)

bool dlhrl30gDetect(pitotDev_t *pitot);
