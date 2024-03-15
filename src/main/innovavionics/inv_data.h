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
#define invDataStoreValString(_data, _val)  (*_invData[_data]._calc)(&_invData[_data], _val))
#define invDataStoreValBool(_data, _val)  {bool __invValTmp = (bool)_val; (*_invData[_data]._calc)(&_invData[_data], &(__invValTmp));}
#define invDataStoreValULong(_data, _val)  {uint64_t __invValTmp = (uint64_t)_val; (*_invData[_data]._calc)(&_invData[_data], &(__invValTmp));}
#define invDataStoreValLong(_data, _val)  {int64_t __invValTmp = (int64_t)_val; (*_invData[_data]._calc)(&_invData[_data], &(__invValTmp));}
#define invDataStoreValUInt(_data, _val)  {uint32_t __invValTmp = (uint32_t)_val; (*_invData[_data]._calc)(&_invData[_data], &(__invValTmp));}
#define invDataStoreValInt(_data, _val)  {int32_t __invValTmp = (int32_t)_val; (*_invData[_data]._calc)(&_invData[_data], &(__invValTmp));}
#define invDataStoreValByte(_data, _val) {uint8_t __invValTmp = (uint8_t)_val; (*_invData[_data]._calc)(&_invData[_data], &(__invValTmp));}
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
#define invDataIsUnsigned(_data) _isInvElementUnsigned(&(_invData[_data]))
#define invDataLabel(_data) (_invData[_data]).label


#define invDataGetInt(_data) ((_invData[_data])._valueI)
#define invDataGetLong(_data) ((_invData[_data])._valueL)

#define invDataGetUInt(_data) ((uint32_t)(_invData[_data])._valueI)
#define invDataGetULong(_data) ((uint64_t)(_invData[_data])._valueL)
#define invDataGetByte(_data) ((_invData[_data])._valueBy)
#define invDataGetFloat(_data) ((_invData[_data])._valueF)
#define invDataGetBool(_data) ((_invData[_data])._valueB)
#define invDataGetString(_data) ((_invData[_data])._valueS)


#define invGetDaqStatus() (_invData[INV_DAQ_STATUS]._valueBy)

#define invSetMcuSensorError() invDataStoreValByte(INV_DAQ_STATUS, invGetDaqStatus() & ~INV_DAQ_MCU_STATUS_FLAG )
#define invSetMcuSensorHealty() invDataStoreValByte(INV_DAQ_STATUS, invGetDaqStatus() | INV_DAQ_MCU_STATUS_FLAG )

#define invSetAccSensorError() invDataStoreValByte(INV_DAQ_STATUS, invGetDaqStatus() & ~INV_DAQ_ACC_STATUS_FLAG )
#define invSetAccSensorHealty() invDataStoreValByte(INV_DAQ_STATUS, invGetDaqStatus() | INV_DAQ_ACC_STATUS_FLAG )

#define invSetGyroSensorError() invDataStoreValByte(INV_DAQ_STATUS, invGetDaqStatus() & ~INV_DAQ_GYRO_STATUS_FLAG )
#define invSetGyroSensorHealty() invDataStoreValByte(INV_DAQ_STATUS, invGetDaqStatus() | INV_DAQ_GYRO_STATUS_FLAG )

#define invSetMagSensorError() invDataStoreValByte(INV_DAQ_STATUS, invGetDaqStatus() & ~INV_DAQ_MAG_STATUS_FLAG )
#define invSetMagSensorHealty() invDataStoreValByte(INV_DAQ_STATUS, invGetDaqStatus() | INV_DAQ_MAG_STATUS_FLAG )

#define invSetGpsSensorError() invDataStoreValByte(INV_DAQ_STATUS, invGetDaqStatus() & ~INV_DAQ_GPS_STATUS_FLAG )
#define invSetGpsSensorHealty() invDataStoreValByte(INV_DAQ_STATUS, invGetDaqStatus() | INV_DAQ_GPS_STATUS_FLAG )

#define invSetPitotSensorError() invDataStoreValByte(INV_DAQ_STATUS, invGetDaqStatus() & ~INV_DAQ_PITOT_STATUS_FLAG )
#define invSetPitotSensorHealty() invDataStoreValByte(INV_DAQ_STATUS, invGetDaqStatus() | INV_DAQ_PITOT_STATUS_FLAG )

#define invSetBaroSensorError() invDataStoreValByte(INV_DAQ_STATUS, invGetDaqStatus() & ~INV_DAQ_BARO_STATUS_FLAG )
#define invSetBaroSensorHealty() invDataStoreValByte(INV_DAQ_STATUS, invGetDaqStatus() | INV_DAQ_BARO_STATUS_FLAG )

#define invSetPitotAltSensorError() invDataStoreValByte(INV_DAQ_STATUS, invGetDaqStatus() & ~INV_DAQ_PITOT_ALT_STATUS_FLAG )
#define invSetPitoAlttSensorHealty() invDataStoreValByte(INV_DAQ_STATUS, invGetDaqStatus() | INV_DAQ_PITOT_ALT_STATUS_FLAG )




#ifdef __cplusplus
}
#endif


#endif /* SRC_INNOVAVIONICS_INV_DATA_H_ */
