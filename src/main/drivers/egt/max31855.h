/*
 Author:     Nima Askari
 WebSite:    http://www.github.com/NimaLTD
 Instagram:  http://instagram.com/github.NimaLTD
 Youtube:    https://www.youtube.com/channel/UCUhY7qY1klJm1d2kulr9ckw

 Version:    1.0.0


 Reversion History:

 (1.0.0)
 First Release.
 */
#pragma once
#ifndef _MAX31855_H
#define _MAX31855_H

#include "stm32h7xx_hal.h"
#include "innovavionics/inv_data.h"
#include "innovavionics/inv_params.h"
#include "drivers/io.h"
#include "drivers/bus_spi.h"
#include "drivers/bus.h"
#include "drivers/time.h"

#define TASK_EGT_HZ 2

#ifdef __cplusplus
extern "C" {
#endif

#define  MAX31855_2WIRE_FAULT_OPEN_MASK 		0x01
#define  MAX31855_2WIRE_FAULT_SHORTEDGND_MASK	0x02
#define  MAX31855_2WIRE_FAULT_SHORTEDVCC_MASK 	0x04

typedef enum {
	MAX31855_2WIRE_NO_FAULT,
	MAX31855_2WIRE_FAULT_OPEN, 			// 0x01
	MAX31855_2WIRE_FAULT_SHORTEDGND,	// 0x02
	MAX31855_2WIRE_FAULT_SHORTEDVCC		// 0x03
} egtFault_t;

typedef enum {
	EGT_DEVICE_1 = INV_EGT1,
	EGT_DEVICE_2 = INV_EGT2,
	EGT_DEVICE_3 = INV_EGT3,
	EGT_DEVICE_4 = INV_EGT4
} egtDeviceId_t;

typedef struct egtDevice_t {
	egtDeviceId_t deviceID;
	busDevice_t *bus;
	egtFault_t lastReadFault;
	int32_t milliCelsiusProbe;
	int32_t milliCelsiusInternal;
	int32_t lastReadTime;
} egtDevice_t;


uint32_t readEgt(egtDevice_t *dev);
egtFault_t readTempCThermoTypeK(egtDevice_t *dev);

egtFault_t getLastReatFault(egtDevice_t *dev);
int32_t getMilliCelsiusProbe(egtDevice_t *dev);
int32_t getMilliCelsiusInternal(egtDevice_t *dev);
bool initEgts();
bool readEgts();
#ifdef __cplusplus
}
#endif

#endif
