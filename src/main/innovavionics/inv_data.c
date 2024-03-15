/*
 * inv_data.c
 *
 *  Created on: Mar 13, 2024
 *      Author: sandro.bottoni
 */

#include "inv_data.h"

#include <innovavionics/inv_data_calculators.h>
#include <innovavionics/inv_params.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


//invElement_t _invData [INV_DATA_COUNT];

volatile invElement_t _invData [INV_DATA_COUNT] = {
	{
		.dataType = INV_IAS_STATUS,			.label = "IAS STATUS",			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 0, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 1, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorBoolPlain,
		._valueB = false,
		._history = NULL,
	},
	{
		.dataType = INV_IAS_AUX_STATUS,		.label = "IAS AUX STATUS",		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 0, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 1, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorBoolPlain,
		._valueB = false,
		._history = NULL,
	},
	{
		.dataType = INV_IAS,				.label = "IAS",					._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorIntPlain,
		._valueF = 0.0f,
		._history = NULL,
	},
	{
		.dataType = INV_IAS_TEMPERATURE,	.label = "IAS TEMPERATURE",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorIntPlain,
		._valueF = 0.0f,
		._history = NULL,
	},
	{
		.dataType = INV_IAS_PRESSURE,		.label = "IAS PRESSURE",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorIntPlain,
		._valueF = 0.0f,
		._history = NULL,
	},
	{
		.dataType = INV_IAS_AUX,			.label = "IAS AUX",				._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorIntPlain,
		._valueF = 0.0f,
		._history = NULL,
	},
	{
		.dataType = INV_IAS_AUX_PRESSURE,	.label = "IAS AUX PRESSURE",	._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorIntPlain,
		._valueF = 0.0f,
		._history = NULL,
	},
	{
		.dataType = INV_IAS_MISMATCH,		.label = "IAS MISMATCH",		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 0, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 1, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorBoolPlain,
		._valueB = false,
		._history = NULL,
	},
	{
		.dataType = INV_IAS_FORCE_ALT,		.label = "IAS FORCE ALT",		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1, ._intvalue = 0, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 1, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorBoolPlain,
		._valueB = false,
		._history = NULL,
	},
	{
		.dataType = INV_OAT,				.label = "OAT",					._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueF = 0.0f,
		._history = NULL,
	},
	{
		.dataType = INV_IAT,				.label = "IAT",					._enabled = 1,	._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueF = 0.0f,
		._history = NULL,
	},
	{
		.dataType = INV_TAS,				.label = "TAS",					._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueF = 0.0f,
		._history = NULL,
	},
	{
		.dataType = INV_ALTITUDE,			.label = "ALTITUDE",			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorIntPlain,
		._valueF = 0.0f,
		._history = NULL,
	},
	{
		.dataType = INV_STATIC_PRESSURE,	.label = "STATIC PRESSURE",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorIntPlain,
		._valueF = 0.0f,
		._history = NULL,
	},
	{
		.dataType = INV_QNH,				.label = "QNH",					._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorUIntPlain,
		._valueF = 0.0f,
		._history = NULL,
	},
	{
		.dataType = INV_DENSITYALT,			.label = "DENSITY ALTITUDE",	._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueF = 0.0f,
		._history = NULL,
	},
	{
		.dataType = INV_ROLL,				.label = "ROLL",				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_PITCH,				.label = "PITCH",				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_YAW,				.label = "YAW",					._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_HEADING,			.label = "HEADING",				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_GYRO_NOISE,			.label = "GYRO NOISE",			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_ACC_NOISE,			.label = "ACC NOISE",			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_MAG_NOISE,			.label = "MAG NOISE",			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_MAG_CAL_STATUS,		.label = "MAG CAL STATUS",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1, ._intvalue = 0, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 1, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorBoolPlain,
		._valueB = false,
		._history = NULL,
	},
	{
		.dataType = INV_GPS_STATUS,			.label = "GPS STATUS",			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1, ._intvalue = 0, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 1, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorBoolPlain,
		._valueB = false,
		._history = NULL,
	},
	{
		.dataType = INV_GPS_FIX_STATUS,		.label = "GPS FIX",				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 0, ._longvalue = 0, ._bytevalue = 1, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorBytePlain,
		._valueBy = 0x00,
		._history = NULL,
	},
	{
		.dataType = INV_GPS_LAT,			.label = "GPS LAT",				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_GPS_LON,			.label = "GPS LON",				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_GPS_ALT,			.label = "GPS ALT",				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_GPS_HEADING,		.label = "GPS HEADING",			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_GPS_HDOP,			.label = "GPS HDOP",			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_GPS_VDOP,			.label = "GPS VDOP",			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_GPS_PDOP,			.label = "GPS PDOP",			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_GPS_FREQ,			.label = "GPS FREQ",			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 0, ._longvalue = 0, ._bytevalue = 1, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorBytePlain,
		._valueBy = 0,
		._history = NULL,
	},
	{
		.dataType = INV_GPS_SAT,			.label = "GPS SAT",				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 0, ._longvalue = 0, ._bytevalue = 1, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorBytePlain,
		._valueBy = 0,
		._history = NULL,
	},
	{
		.dataType = INV_GPS_SAT_DETAIL, 	.label = "GPS SAT DETAIL", 		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 0, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 1, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorStringPlain,
		._valueBy = 0,
		._history = NULL,
	},
	{
		.dataType = INV_GPS_GS,				.label = "GPS GROUND SPEED",	._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_GPS_3DSPEED,		.label = "GPS 3D SPEED",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_GPS_NSPEED,			.label = "GPS NORTH SPEED",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_GPS_ESPEED,			.label = "GPS EAST SPEED",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_GPS_DSPEED,			.label = "GPS DOWN SPEED",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_GPS_TIME,			.label = "GPS TIMESTAMP",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_WIND_SPEED_STATUS,	.label = "WIND SPEED STATUS",	._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1, ._intvalue = 0, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 1, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorBoolPlain,
		._valueB = false,
		._history = NULL,
	},
	{
		.dataType = INV_WIND_SPEED,			.label = "WIND SPEED",			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_WIND_DIR,			.label = "WIND DIR",			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_CHT1,				.label = "CHT1",				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_CHT2,				.label = "CHT2",				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_CHT3,				.label = "CHT3",				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_CHT4,				.label = "CHT4",				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_OILP,				.label = "OILP",				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_OILT,				.label = "OILT",				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_FUELP,				.label = "FUELP",				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_EGT1,				.label = "EGT1",				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_EGT2,				.label = "EGT2",				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_EGT3,				.label = "EGT3",				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_EGT4,				.label = "EGT4",				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_RPM_ENGINE,			.label = "RPM ENGINE",			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_RPM_PROP,			.label = "RPM PROPELLER",		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_RPM_ROTOR,			.label = "RPM ROTOR",			._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_AUXPUMP_ACTIVE,		.label = "AUX PUMP ACTIVE",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1, ._intvalue = 0, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 1, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorBoolPlain,
		._valueB = false,
		._history = NULL,
	},
	{
		.dataType = INV_AUMPUMP_AMP,		.label = "AUMPUMP AMPS",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_AUMPUMP_VOLTAGE,	.label = "AUMPUMP VOLTAGE",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_MAP,				.label = "MAP",					._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_THROTTLE_POS,		.label = "THROTTLE POSITION",	._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_LAMBDA,				.label = "LAMBDA",				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_VIBRATION_X,		.label = "VIBRATION X",			._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_VIBRATION_Y,		.label = "VIBRATION Y",			._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_VIBRATION_Z,		.label = "VIBRATION Z",			._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_VIBRATIONS,			.label = "VIBRATIONS 3D",		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_MAIN_V,				.label = "MAIN VOLTAGE",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_BATT_V,				.label = "BATT VOLTAGE",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_BKBATT_V,			.label = "BK BATT VOLTAGE",		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_MAINAMP,			.label = "MAIN CURRENT",		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_GENAMP,				.label = "GENERATOR CURRENT",	._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_FLAP_POS,			.label = "FLAP POSITION",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_TRIM_PITCH_POS,		.label = "TRIM PITCH POS",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_TRIM_ROLL_POS,		.label = "TRIM ROLL POS",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_TRIM_YAW_POS,		.label = "TRIM YAW POS",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_ROLL_POS,			.label = "ROLL POSITION",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_PITCH_POS,			.label = "PITCH POSITION",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_YAW_POS,			.label = "YAW POSITION",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_TANK_1,				.label = "TANK 1 LEVEL",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_TANK_2,				.label = "TANK 2 LEVEL",		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_TANK_AUX,			.label = "TANK AUX LEVEL",		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_VHF_STATUS,			.label = "VHF STATUS",			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 0, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 1, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorBoolPlain,
		._valueB = false,
		._history = NULL,
	},
	{
		.dataType = INV_VHF_MAIN_FREQ,		.label = "VHF MAIN FREQ",		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1, ._intvalue = 0, ._longvalue = 0, ._longvalue = 1, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorULongPlain,
		._valueL = 0,
		._history = NULL,
	},
	{
		.dataType = INV_VHF_STBY_FREQ,		.label = "VHF STBY FREQ",		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1, ._intvalue = 0, ._longvalue = 0, ._longvalue = 1, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorULongPlain,
		._valueL = 0,
		._history = NULL,
	},
	{
		.dataType = INV_VHF_DUAL,			.label = "VHF DUAL WATCH",		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1, ._intvalue = 0, ._longvalue = 0, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 1, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorBoolPlain,
		._valueB = 0,
		._history = NULL,
	},
	{
		.dataType = INV_VHF_SQ,				.label = "VHF SQUELCH",			._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1, ._intvalue = 0, ._longvalue = 0, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 1, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorBytePlain,
		._valueBy = 0,
		._history = NULL,
	},
	{
		.dataType = INV_VHF_VOL,			.label = "VHF VOL",				._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1, ._intvalue = 0, ._longvalue = 0, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 1, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorBytePlain,
		._valueBy = 0,
		._history = NULL,
	},
	{
		.dataType = INV_VHF_VOX,			.label = "VHF VOX",				._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1, ._intvalue = 0, ._longvalue = 0, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 1, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorBytePlain,
		._valueBy = 0,
		._history = NULL,
	},
	{
		.dataType = INV_VHF_AUX_VOL,		.label = "VHF AUX VOL",			._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1, ._intvalue = 0, ._longvalue = 0, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 1, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorBytePlain,
		._valueBy = 0,
		._history = NULL,
	},
	{
		.dataType = INV_VHF_INTERCOM_VOL,	.label = "VHF INTERCOM VOL",	._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1, ._intvalue = 0, ._longvalue = 0, ._longvalue = 0, ._bytevalue = 1, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorBytePlain,
		._valueBy = 0,
		._history = NULL,
	},
	{
		.dataType = INV_VHF_SIT_LEV,		.label = "VHF SIT LEVEL",		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1, ._intvalue = 0, ._longvalue = 0, ._longvalue = 0, ._bytevalue = 1, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorBytePlain,
		._valueBy = 0,
		._history = NULL,
	},
	{
		.dataType = INV_VHF_PIC_MIC_GAIN,	.label = "VHF PIC MIC GAIN",	._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1, ._intvalue = 0, ._longvalue = 0, ._longvalue = 0, ._bytevalue = 1, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorBytePlain,
		._valueBy = 0,
		._history = NULL,
	},
	{
		.dataType = INV_VHF_COP_MIC_GAIN,	.label = "VHF COPILOT MIC GAIN",._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1, ._intvalue = 0, ._longvalue = 0, ._longvalue = 0, ._bytevalue = 1, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorBytePlain,
		._valueBy = 0,
		._history = NULL,
	},
	{
		.dataType = INV_VHF_CH_SP_833K,		.label = "VHF 25KHZ-8.33KHZ",	._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1, ._intvalue = 0, ._longvalue = 0, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 1, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorBoolPlain,
		._valueB = false,
		._history = NULL,
	},
	{
		.dataType = INV_VHF_PTT_CONF,		.label = "VHF PTT CONF",		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1, ._intvalue = 0, ._longvalue = 0, ._longvalue = 0, ._bytevalue = 1, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorBytePlain,
		._valueBy = 0,
		._history = NULL,
	},
	{
		.dataType = INV_VHF_ERROR,			.label = "VHF ERROR CODE",		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_XPDR_STATUS,		.label = "XPDR STATUS",			._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 0, ._longvalue = 0, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 1, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorBoolPlain,
		._valueB = false,
		._history = NULL,
	},
	{
		.dataType = INV_XPDR_SQUAK,			.label = "XPDR SQUAK",			._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1, ._intvalue = 1, ._longvalue = 0, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_XPDR_MODE,			.label = "XPDR MODE",			._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1, ._intvalue = 0, ._longvalue = 0, ._longvalue = 0, ._bytevalue = 1, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorBytePlain,
		._valueBy = 0,
		._history = NULL,
	},
	{
		.dataType = INV_XPDR_IDENT,			.label = "XPDR IDENT",			._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1, ._intvalue = 0, ._longvalue = 0, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 1, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorBoolPlain,
		._valueB = false,
		._history = NULL,
	},
	{
		.dataType = INV_XPDR_ERROR,			.label = "XPDR ERROR CODE",		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_DAQ_VIN,			.label = "DAQ VIN VOLTAGE",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_DAQ_TEMP,			.label = "DAQ TEMPERATURE",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_DAQ_HUMIDITY,		.label = "DAQ HUMIDITY",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_DAQ_MCU_GND,		.label = "DAQ GND VOLTAGE",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = MOVING_AVG, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_DAQ_MCU_GND_NOISE,	.label = "DAQ GND NOISE",		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_DAQ_MCU_VAN,		.label = "DAQ VAN VOLTAGE",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_DAQ_MCU_VAN_NOISE,	.label = "DAQ VAN NOISE",		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_DAQ_MCU_VVREF,		.label = "DAQ VREF VOLTAGE",	._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_DAQ_MCU_TEMP,		.label = "DAQ MCU TEMP",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_DAQ_MCU_WARNING,	.label = "DAQ WARNING",			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 0, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 1, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorBoolPlain,
		._valueB = false,
		._history = NULL,
	},
	{
		.dataType = INV_DAQ_MCU_ALARM,		.label = "DAQ ALARM",			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 0, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 1, ._stringvalue = 0, ._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, ._calc = invCalculatorBoolPlain,
		._valueB = false,
		._history = NULL,
	},
	{
		.dataType = INV_DAQ_STATUS,			.label = "DAQ STATUS",			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc =  &invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
	{
		.dataType = INV_DAQ_ERRORCODE,		.label = "DAQ ERROR CODE",		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0, ._intvalue = 1, ._longvalue = 0, ._bytevalue = 0, ._floatvalue = 0, ._boolvalue = 0, ._stringvalue = 0, ._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, ._calc =  &invCalculatorUIntPlain,
		._valueI = 0,
		._history = NULL,
	},
};
