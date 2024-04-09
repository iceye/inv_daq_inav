/*
 * engine_params.h
 *
 *  Created on: Mar 13, 2024
 *      Author: sandro.bottoni
 */

#ifndef SRC_INNOVAVIONICS_INV_PARAMS_H_
#define SRC_INNOVAVIONICS_INV_PARAMS_H_
#include "common/filter.h"
#include "common/time.h"
#include <stdint.h>
#include <stdbool.h>

typedef enum {
	INV_IAS_STATUS,
	INV_IAS_AUX_STATUS,
	INV_IAS,
	INV_IAS_TURBOLENCE,
	INV_IAS_TEMPERATURE,
	INV_IAS_PRESSURE,
	INV_IAS_AUX,
	INV_IAS_AUX_TURBOLENCE,
	INV_IAS_AUX_PRESSURE,
	INV_IAS_MISMATCH,
	INV_IAS_FORCE_ALT,
	INV_OAT,
	INV_IAT,
	INV_TAS,
	INV_ALTITUDE,
	INV_STATIC_PRESSURE,
	INV_QNH,
	INV_DENSITYALT,
	INV_ROLL,
	INV_PITCH,
	INV_YAW,
	INV_HEADING,
	INV_GYRO_NOISE,
	INV_ACC_NOISE,
	INV_MAG_NOISE,
	INV_MAG_CAL_STATUS,
	INV_GPS_STATUS,
	INV_GPS_FIX_STATUS,
	INV_GPS_LAT,
	INV_GPS_LON,
	INV_GPS_ALT,
	INV_GPS_COURSE,
	INV_GPS_HDOP,
	INV_GPS_VDOP,
	INV_GPS_PDOP,
	INV_GPS_FREQ,
	INV_GPS_SAT,
	INV_GPS_SAT_DETAIL,
	INV_GPS_GS,
	INV_GPS_3DSPEED,
	INV_GPS_NSPEED,
	INV_GPS_ESPEED,
	INV_GPS_DSPEED,
	INV_GPS_TIME,
	INV_WIND_SPEED_STATUS,
	INV_WIND_SPEED,
	INV_WIND_DIR,
	INV_CHT1,
	INV_CHT2,
	INV_CHT3,
	INV_CHT4,
	INV_OILP,
	INV_OILT,
	INV_FUELP,
	INV_FUELFLOW,
	INV_EGT1,
	INV_EGT2,
	INV_EGT3,
	INV_EGT4,
	INV_RPM_ENGINE,
	INV_RPM_PROP,
	INV_RPM_ROTOR,
	INV_AUXPUMP_ACTIVE,
	INV_AUXPUMP_AMP,
	INV_AUXPUMP_VOLTAGE,
	INV_MAP,
	INV_THROTTLE_POS,
	INV_LAMBDA,
	INV_VIBRATION_X,
	INV_VIBRATION_Y,
	INV_VIBRATION_Z,
	INV_VIBRATIONS,
	INV_MAIN_V,
	INV_BATT_V,
	INV_BKBATT_V,
	INV_MAINAMP,
	INV_GENAMP,
	INV_GEN_ALARM,
	INV_FLAP_POS,
	INV_TRIM_PITCH_POS,
	INV_TRIM_ROLL_POS,
	INV_TRIM_YAW_POS,
	INV_ROLL_POS,
	INV_PITCH_POS,
	INV_YAW_POS,
	INV_TANK_1,
	INV_TANK_2,
	INV_TANK_AUX,
	INV_VHF_STATUS,
	INV_VHF_MAIN_FREQ,
	INV_VHF_STBY_FREQ,
	INV_VHF_DUAL,
	INV_VHF_SQ,
	INV_VHF_VOL,
	INV_VHF_VOX,
	INV_VHF_AUX_VOL,
	INV_VHF_INTERCOM_VOL,
	INV_VHF_SIT_LEV,
	INV_VHF_PIC_MIC_GAIN,
	INV_VHF_COP_MIC_GAIN,
	INV_VHF_CH_SP_833K,
	INV_VHF_PTT_CONF,
	INV_VHF_ERROR,
	INV_XPDR_STATUS,
	INV_XPDR_SQUAK,
	INV_XPDR_ALT_FL,
	INV_XPDR_MODE,
	INV_XPDR_IDENT,
	INV_XPDR_ERROR,
	INV_DAQ_VIN,
	INV_DAQ_TEMP,
	INV_DAQ_HUMIDITY,
	INV_DAQ_MCU_GND,
	INV_DAQ_MCU_GND_NOISE,
	INV_DAQ_MCU_VAN,
	INV_DAQ_MCU_VAN_NOISE,
	INV_DAQ_MCU_VVREF,
	INV_DAQ_MCU_TEMP,
	INV_DAQ_MCU_WARNING,
	INV_DAQ_MCU_ALARM,
	INV_DAQ_STATUS,
	INV_DAQ_ERRORCODE,
	INV_DATA_NONE,
	INV_DATA_COUNT
}invElementDataType_t;

typedef enum {
	PLAIN_VALUE,
	PLAIN_MV,
	RPART_5V,
	RPART_12V,
	R_OHM,
	NTC_BETA,
	MA_4_20,
	STRING
}invElementConverterType_t;


typedef enum {
	NO_FILTER,
	ROUND,
	MOVING_AVG,
	LPF_PT1_SLOW,
	LPF_PT1_FAST,
	LPF_PT1_MID,
} invElementFilter_t;

typedef struct invElement_t invElement_t;

typedef bool (*invElementCalculator_t)(invElement_t *el, void* value);

struct invElement_t{
	invElementDataType_t dataType;
	char label[16];
	uint8_t _enabled : 1;
	uint8_t _timeout : 1;
	uint8_t _hasTimeout : 1;
	uint8_t _readable : 1;
	uint8_t _writable : 1;
	uint8_t _intvalue : 1;
	uint8_t _bytevalue : 1;
	uint8_t _boolvalue : 1;
	uint8_t _unsigned : 1;
	uint8_t _flags : 7;			// used to align to 16bit or for future use


	invElementFilter_t _filter;

	invElementCalculator_t _calc;
	int32_t _valueI;
	uint32_t _valueUI;
	uint8_t _valueBy;
	bool _valueB;
	pt1Filter_t _pt1FilterState;
};

typedef struct invElement_t invElement_t;





bool _isInvElementEnabled(invElement_t *el);

bool _isInvElementTimeout(invElement_t *el);

bool _isInvElementReadable(invElement_t *el);

bool _isInvElementWritable(invElement_t *el);

bool _isInvElementInt(invElement_t *el);

bool _isInvElementUInt(invElement_t *el);

bool _isInvElementByte(invElement_t *el);

bool _isInvElementBool(invElement_t *el);

bool _isInvElementUnsigned(invElement_t *el);





#endif /* SRC_INNOVAVIONICS_INV_PARAMS_H_ */
