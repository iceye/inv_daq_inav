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

void invDataStoreValByConf(invElementDataType_t _data, void* _val)  {
        if(_invData[_data]._boolvalue == 1){
            invDataStoreValBool(_data, _val);
        } else
		if(_invData[_data]
		._intvalue == 1){
            if(_invData[_data]
		._unsigned == 1) {
				invDataStoreValUInt(_data, _val);
            }else{
				invDataStoreValInt(_data, _val);
            }
        } else if(_invData[_data]._bytevalue == 1){
            invDataStoreValByte(_data, _val);
        }
}

//invElement_t _invData [INV_DATA_COUNT];
volatile invElement_t _invData [INV_DATA_COUNT] = {
	{
		.dataType = INV_IAS_STATUS,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 0, ._bytevalue = 0, ._boolvalue = 1,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBoolPlain,
		._valueB = false,

	},
	{
		.dataType = INV_IAS_AUX_STATUS,		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 0, ._bytevalue = 0, ._boolvalue = 1,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBoolPlain,
		._valueB = false,

	},
	{
		.dataType = INV_IAS,				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, //Filtered by the fc task
		._calc = invCalculatorIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_IAS_TURBOLENCE,				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, //Filtered by the fc task
		._calc = invCalculatorIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_IAS_TEMPERATURE,	._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = LPF_PT1_SLOW,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_IAS_PRESSURE,		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER, //Filtered by the fc task
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_IAS_AUX,			._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = LPF_PT1_MID,
		._calc = invCalculatorIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_IAS_AUX_TURBOLENCE,				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER, //Filtered by the fc task
		._calc = invCalculatorIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_IAS_AUX_PRESSURE,	._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorIasAdcPressure,
		._valueI = 0,

	},
	{
		.dataType = INV_IAS_MISMATCH,		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 0, ._bytevalue = 0, ._boolvalue = 1,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBoolPlain,
		._valueB = false,

	},
	{
		.dataType = INV_IAS_FORCE_ALT,		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 0, ._bytevalue = 0, ._boolvalue = 1,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBoolPlain,
		._valueB = false,

	},
	{
		.dataType = INV_OAT,				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = LPF_PT1_SLOW,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_IAT,				._enabled = 1,	._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = LPF_PT1_SLOW,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_TAS,				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = LPF_PT1_MID,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_ALTITUDE,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = LPF_PT1_MID,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_STATIC_PRESSURE,	._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_QNH,				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorUIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_DENSITYALT,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = LPF_PT1_SLOW,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_ROLL,				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_PITCH,				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_YAW,				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_HEADING,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_GYRO_NOISE,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_ACC_NOISE,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_MAG_NOISE,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_MAG_CAL_STATUS,		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 0, ._bytevalue = 0, ._boolvalue = 1,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBoolPlain,
		._valueB = false,

	},
	{
		.dataType = INV_GPS_STATUS,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 0, ._bytevalue = 0, ._boolvalue = 1,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBoolPlain,
		._valueB = false,

	},
	{
		.dataType = INV_GPS_FIX_STATUS,		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 0, ._bytevalue = 1, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBytePlain,
		._valueBy = 0x00,

	},
	{
		.dataType = INV_GPS_LAT,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_GPS_LON,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_GPS_ALT,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_GPS_COURSE,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorUIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_GPS_HDOP,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_GPS_VDOP,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_GPS_PDOP,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_GPS_FREQ,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 0, ._bytevalue = 1, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBytePlain,
		._valueBy = 0,

	},
	{
		.dataType = INV_GPS_SAT,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 0, ._bytevalue = 1, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBytePlain,
		._valueBy = 0,

	},
	{
		.dataType = INV_GPS_SAT_DETAIL, 	._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorUIntPlain,
		._valueBy = 0,

	},
	{
		.dataType = INV_GPS_GS,				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = LPF_PT1_MID,
		._calc = invCalculatorUIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_GPS_3DSPEED,		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorUIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_GPS_NSPEED,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_GPS_ESPEED,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_GPS_DSPEED,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_GPS_TIME,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorUIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_WIND_SPEED_STATUS,	._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 0, ._bytevalue = 0, ._boolvalue = 1,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBoolPlain,
		._valueB = false,

	},
	{
		.dataType = INV_WIND_SPEED,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorUIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_WIND_DIR,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorUIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_CHT1,				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = LPF_PT1_MID,
		._calc = rotaxChtRSensorCalculator,
		._valueI = 0,

	},
	{
		.dataType = INV_CHT2,				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = LPF_PT1_MID,
		._calc = rotaxChtRSensorCalculator,
		._valueI = 0,

	},
	{
		.dataType = INV_CHT3,				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = LPF_PT1_MID,
		._calc = rotaxChtRSensorCalculator,
		._valueI = 0,

	},
	{
		.dataType = INV_CHT4,				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = LPF_PT1_MID,
		._calc = rotaxChtRSensorCalculator,
		._valueI = 0,

	},
	{
		.dataType = INV_OILP,				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = LPF_PT1_MID,
		._calc = rotaxOilp5VSensorCalculator,
		._valueI = 0,

	},
	{
		.dataType = INV_OILT,				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = LPF_PT1_SLOW,
		._calc = rotaxOiltRSensorCalculator,
		._valueI = 0,

	},
	{
		.dataType = INV_FUELP,				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = LPF_PT1_MID,
		._calc = rotaxFuelp5VSensorCalculator,
		._valueI = 0,

	},
	{
		.dataType = INV_FUELFLOW,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = MOVING_AVG,
		._calc = invCalculatorIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_EGT1,				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_EGT2,				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_EGT3,				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_EGT4,				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_RPM_ENGINE,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = LPF_PT1_FAST,
		._calc = invCalculatorUIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_RPM_PROP,			._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = LPF_PT1_FAST,
		._calc = invCalculatorUIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_RPM_ROTOR,			._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = LPF_PT1_FAST,
		._calc = invCalculatorUIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_AUXPUMP_ACTIVE,		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 0, ._bytevalue = 0, ._boolvalue = 1,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBoolPlain,
		._valueB = false,

	},
	{
		.dataType = INV_AUXPUMP_AMP,		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_AUXPUMP_VOLTAGE,	._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = MOVING_AVG,
		._calc = general12VSensorCalculator,
		._valueUI = 0,

	},
	{
		.dataType = INV_MAP,				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_THROTTLE_POS,		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_LAMBDA,				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_VIBRATION_X,		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_VIBRATION_Y,		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_VIBRATION_Z,		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_VIBRATIONS,			._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_MAIN_V,				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = MOVING_AVG,
		._calc = invCalculatorUIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_BATT_V,				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = MOVING_AVG,
		._calc = general12VSensorCalculator,
		._valueUI = 0,

	},
	{
		.dataType = INV_BKBATT_V,			._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = MOVING_AVG,
		._calc = general12VSensorCalculator,
		._valueUI = 0,

	},
	{
		.dataType = INV_MAINAMP,			._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_GENAMP,				._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG,
		._calc = invCalculatorUIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_GEN_ALARM,			._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 0, ._bytevalue = 0, ._boolvalue = 1,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBoolPlain,
		._valueB = 0,

	},
	{
		.dataType = INV_FLAP_POS,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_TRIM_PITCH_POS,		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_TRIM_ROLL_POS,		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_TRIM_YAW_POS,		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_ROLL_POS,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_PITCH_POS,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_YAW_POS,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = MOVING_AVG,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_TANK_1,				._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = MOVING_AVG,
		._calc = invCalculatorUIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_TANK_2,				._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = MOVING_AVG,
		._calc = invCalculatorUIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_TANK_AUX,			._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = MOVING_AVG,
		._calc = invCalculatorUIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_VHF_STATUS,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 0, ._bytevalue = 0, ._boolvalue = 1,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBoolPlain,
		._valueB = false,

	},
	{
		.dataType = INV_VHF_MAIN_FREQ,		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorUIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_VHF_STBY_FREQ,		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorUIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_VHF_DUAL,			._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 0, ._bytevalue = 0, ._boolvalue = 1,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBoolPlain,
		._valueB = 0,

	},
	{
		.dataType = INV_VHF_SQ,				._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 0, ._bytevalue = 0, ._boolvalue = 1,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBytePlain,
		._valueBy = 0,

	},
	{
		.dataType = INV_VHF_VOL,			._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 0, ._bytevalue = 0, ._boolvalue = 1,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBytePlain,
		._valueBy = 0,

	},
	{
		.dataType = INV_VHF_VOX,			._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 0, ._bytevalue = 0, ._boolvalue = 1,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBytePlain,
		._valueBy = 0,

	},
	{
		.dataType = INV_VHF_AUX_VOL,		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 0, ._bytevalue = 0, ._boolvalue = 1,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBytePlain,
		._valueBy = 0,

	},
	{
		.dataType = INV_VHF_INTERCOM_VOL,	._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 0, ._bytevalue = 1, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBytePlain,
		._valueBy = 0,

	},
	{
		.dataType = INV_VHF_SIT_LEV,		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 0, ._bytevalue = 1, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBytePlain,
		._valueBy = 0,

	},
	{
		.dataType = INV_VHF_PIC_MIC_GAIN,	._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 0, ._bytevalue = 1, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBytePlain,
		._valueBy = 0,

	},
	{
		.dataType = INV_VHF_COP_MIC_GAIN,	._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 0, ._bytevalue = 1, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBytePlain,
		._valueBy = 0,

	},
	{
		.dataType = INV_VHF_CH_SP_833K,		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 0, ._bytevalue = 0, ._boolvalue = 1,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBoolPlain,
		._valueB = false,

	},
	{
		.dataType = INV_VHF_PTT_CONF,		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 0, ._bytevalue = 1, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBytePlain,
		._valueBy = 0,

	},
	{
		.dataType = INV_VHF_ERROR,			._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorUIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_XPDR_STATUS,		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 0, ._bytevalue = 0, ._boolvalue = 1,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBoolPlain,
		._valueB = false,

	},
	{
		.dataType = INV_XPDR_SQUAK,			._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorUIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_XPDR_ALT_FL,		._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorUIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_XPDR_MODE,			._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 0, ._bytevalue = 1, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBytePlain,
		._valueBy = 0,

	},
	{
		.dataType = INV_XPDR_IDENT,			._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 1,
		._intvalue = 0, ._bytevalue = 0, ._boolvalue = 1,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBoolPlain,
		._valueB = false,

	},
	{
		.dataType = INV_XPDR_ERROR,			._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorUIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_DAQ_VIN,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = LPF_PT1_MID,
		._calc = invMicroVoltCalculator,
		._valueUI = 0,

	},
	{
		.dataType = INV_DAQ_TEMP,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = LPF_PT1_MID,
		._calc = invCalculatorIntPlain,
		._valueI = 0,

	},
	{
		.dataType = INV_DAQ_HUMIDITY,		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = LPF_PT1_SLOW,
		._calc = invCalculatorUIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_DAQ_MCU_GND,		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = LPF_PT1_MID,
		._calc = invMicroVoltCalculator,
		._valueUI = 0,

	},
	{
		.dataType = INV_DAQ_MCU_GND_NOISE,	._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorUIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_DAQ_MCU_VAN,		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invVanCalculator,
		._valueUI = 0,

	},
	{
		.dataType = INV_DAQ_MCU_VAN_NOISE,	._enabled = 0, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorUIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_DAQ_MCU_VVREF,		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc = invVrefCalculator,
		._valueUI = 0,

	},
	{
		.dataType = INV_DAQ_MCU_TEMP,		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 0, ._flags = 0, ._filter = LPF_PT1_MID,
		._calc = invMcuTempCalculator,
		._valueI = 0,

	},
	{
		.dataType = INV_DAQ_MCU_WARNING,	._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 0, ._bytevalue = 0, ._boolvalue = 1,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBoolPlain,
		._valueB = false,

	},
	{
		.dataType = INV_DAQ_MCU_ALARM,		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 0, ._bytevalue = 0, ._boolvalue = 1,
		._unsigned = 0, ._flags = 0, ._filter = NO_FILTER,
		._calc = invCalculatorBoolPlain,
		._valueB = false,

	},
	{
		.dataType = INV_DAQ_STATUS,			._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc =  &invCalculatorUIntPlain,
		._valueUI = 0,

	},
	{
		.dataType = INV_DAQ_ERRORCODE,		._enabled = 1, ._timeout = 0, ._hasTimeout = 0, ._readable = 1, ._writable = 0,
		._intvalue = 1, ._bytevalue = 0, ._boolvalue = 0,
		._unsigned = 1, ._flags = 0, ._filter = NO_FILTER,
		._calc =  &invCalculatorUIntPlain,
		._valueUI = 0,

	},
};
