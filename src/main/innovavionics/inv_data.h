/*
 * inv_data.h
 *
 *  Created on: Mar 13, 2024
 *      Author: sandro.bottoni
 */

#ifndef SRC_INNOVAVIONICS_INV_DATA_H_
#define SRC_INNOVAVIONICS_INV_DATA_H_
#include <innovavionics/inv_data_calculators.h>
#include <innovavionics/inv_params.h>
#include <stdint.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif

extern volatile invElement_t _invData [];


#define INV_DAQ_MCU_STATUS_FLAG 		0x01
#define INV_DAQ_ACC_STATUS_FLAG 		0x02
#define INV_DAQ_GYRO_STATUS_FLAG 		0x04
#define INV_DAQ_MAG_STATUS_FLAG 		0x08
#define INV_DAQ_GPS_STATUS_FLAG			0x10
#define INV_DAQ_PITOT_STATUS_FLAG 		0x20
#define INV_DAQ_BARO_STATUS_FLAG 		0x40
#define INV_DAQ_PITOT_ALT_STATUS_FLAG 	0x80



#define invData(_data) (_invData[_data])

void invDataStoreValByConf(invElementDataType_t _data, void* _val) ;


//#define invDataStoreValFromAdc_uV(_data, _val) {uint8_t __invValTmp = (uint8_t)_val; (*_invData[_data]._calcAdc)(&_invData[_data], &(__invValTmp));}
#define invDataIsEnabled(_data) _isInvElementEnabled(&(_invData[_data]))
#define invDataIsTimeout(_data) _isInvElementTimeout(&(_invData[_data]))
#define invDataIsReadable(_data) _isInvElementReadable(&(_invData[_data]))
#define invDataIsWritable(_data) _isInvElementWritable(&(_invData[_data]))
#define invDataIsInt(_data) _isInvElementInt(&(_invData[_data]))
#define invDataIsLong(_data) _isInvElementLong(&(_invData[_data]))
#define invDataIsByte(_data) _isInvElementByte(&(_invData[_data]))
#define invDataIsFloat(_data) _isInvElementFloat(&(_invData[_data]))
#define invDataIsBool(_data) _isInvElementBool(&(_invData[_data]))
#define invDataIsString(_data) _isInvElementString(&(_invData[_data]))
#define invDataHasFilter(_data) (_invData[_data])._filter != NO_FILTER
#define invDataHasLpfSlow(_data) (_invData[_data])._filter == LPF_PT1_SLOW
#define invDataHasLpfMid(_data) (_invData[_data])._filter == LPF_PT1_MID
#define invDataHasLpfFast(_data) (_invData[_data])._filter == LPF_PT1_FAST
#define invDataIsUnsigned(_data) _isInvElementUnsigned(&(_invData[_data]))
#define invDataLabel(_data) (_invData[_data]).label


#define invDataGetInt(_data) ((_invData[_data])._valueI)
#define invDataGetUInt(_data) ((_invData[_data])._valueUI)
#define invDataGetByte(_data) ((_invData[_data])._valueBy)
#define invDataGetBool(_data) ((_invData[_data])._valueB)


#define invGetDaqStatus() (_invData[INV_DAQ_STATUS]._valueBy)


#define invSetMcuSensorError() { \
		uint8_t newDaqStatus = invGetDaqStatus() & ~INV_DAQ_MCU_STATUS_FLAG ;	\
		invDataStoreValByConf(INV_DAQ_STATUS, &newDaqStatus); 					\
	}
#define invSetMcuSensorHealty() { \
		uint8_t newDaqStatus = invGetDaqStatus() | INV_DAQ_MCU_STATUS_FLAG ;	\
		invDataStoreValByConf(INV_DAQ_STATUS, &newDaqStatus); 					\
	}


#define invSetAccSensorError() { \
		uint8_t newDaqStatus = invGetDaqStatus() & ~INV_DAQ_ACC_STATUS_FLAG ;	\
		invDataStoreValByConf(INV_DAQ_STATUS, &newDaqStatus); 					\
	}
#define invSetAccSensorHealty() { \
		uint8_t newDaqStatus = invGetDaqStatus() | INV_DAQ_ACC_STATUS_FLAG ;	\
		invDataStoreValByConf(INV_DAQ_STATUS, &newDaqStatus); 					\
	}



#define invSetGyroSensorError() { \
		uint8_t newDaqStatus = invGetDaqStatus() & ~INV_DAQ_GYRO_STATUS_FLAG ;	\
		invDataStoreValByConf(INV_DAQ_STATUS, &newDaqStatus); 					\
	}

#define invSetGyroSensorHealty() { \
		uint8_t newDaqStatus = invGetDaqStatus() | INV_DAQ_GYRO_STATUS_FLAG ;	\
		invDataStoreValByConf(INV_DAQ_STATUS, &newDaqStatus); 					\
	}




#define invSetMagSensorError() { \
        uint8_t newDaqStatus = invGetDaqStatus() & ~INV_DAQ_MAG_STATUS_FLAG ;	\
        invDataStoreValByConf(INV_DAQ_STATUS, &newDaqStatus); 					\
    }
#define invSetMagSensorHealty() { \
        uint8_t newDaqStatus = invGetDaqStatus() | INV_DAQ_MAG_STATUS_FLAG ;	\
        invDataStoreValByConf(INV_DAQ_STATUS, &newDaqStatus); 					\
    }



#define invSetGpsSensorError() { \
        uint8_t newDaqStatus = invGetDaqStatus() & ~INV_DAQ_GPS_STATUS_FLAG ;	\
        invDataStoreValByConf(INV_DAQ_STATUS, &newDaqStatus); 					\
    }

#define invSetGpsSensorHealty() { \
        uint8_t newDaqStatus = invGetDaqStatus() | INV_DAQ_GPS_STATUS_FLAG ;	\
        invDataStoreValByConf(INV_DAQ_STATUS, &newDaqStatus); 					\
    }



#define invSetPitotSensorError() { \
        uint8_t newDaqStatus = invGetDaqStatus() & ~INV_DAQ_PITOT_STATUS_FLAG ;	\
        invDataStoreValByConf(INV_DAQ_STATUS, &newDaqStatus); 					\
    }

#define invSetPitotSensorHealty() { \
        uint8_t newDaqStatus = invGetDaqStatus() | INV_DAQ_PITOT_STATUS_FLAG ;	\
        invDataStoreValByConf(INV_DAQ_STATUS, &newDaqStatus); 					\
    }




#define invSetBaroSensorError() { \
        uint8_t newDaqStatus = invGetDaqStatus() & ~INV_DAQ_BARO_STATUS_FLAG ;	\
        invDataStoreValByConf(INV_DAQ_STATUS, &newDaqStatus); 					\
    }

#define invSetBaroSensorHealty() { \
        uint8_t newDaqStatus = invGetDaqStatus() | INV_DAQ_BARO_STATUS_FLAG ;	\
        invDataStoreValByConf(INV_DAQ_STATUS, &newDaqStatus); 					\
    }



#define invSetPitotAltSensorError() { \
        uint8_t newDaqStatus = invGetDaqStatus() & ~INV_DAQ_PITOT_ALT_STATUS_FLAG ;	\
        invDataStoreValByConf(INV_DAQ_STATUS, &newDaqStatus); 					\
    }

#define invSetPitotAltSensorHealty() { \
        uint8_t newDaqStatus = invGetDaqStatus() | INV_DAQ_PITOT_ALT_STATUS_FLAG ;	\
        invDataStoreValByConf(INV_DAQ_STATUS, &newDaqStatus); 					\
    }




#ifdef __cplusplus
}
#endif


#endif /* SRC_INNOVAVIONICS_INV_DATA_H_ */
