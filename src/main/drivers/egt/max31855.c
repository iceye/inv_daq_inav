/*
 * Olivier Van den Eede (4ilo) 2019
 */
#include "max31855.h"
#include <math.h>


//#########################################################################################################################

uint32_t readEgt(egtDevice_t *dev) {

	//The device sends the 4 bytes of data after 100ns after the CS is pulled low. No need to ask for a specific register
	SPI_TypeDef * spiInstance = spiInstanceByDevice(dev->bus->busdev.spi.spiBus);

	spiBusSelectDevice(dev->bus);

	//Delay at least 100ns (note the spiBusSelectDevice waits 8ns)
	delayNanos(110);
	uint8_t localBuffer[4] = {0};
	//Read the data (4 bytes)

	spiTransfer(spiInstance, localBuffer, NULL, 4);


	//Deselect the device
	spiBusDeselectDevice(dev->bus);

	return localBuffer[0] << 24 | localBuffer[1] << 16 | localBuffer[2] << 8 | localBuffer[3];
}

//#########################################################################################################################

egtFault_t getLastReatFault(egtDevice_t *dev){
	return dev->lastReadFault;
}

//#########################################################################################################################

egtFault_t readTempCThermoTypeK(egtDevice_t *dev){

	uint32_t dataBuffer = 0;
	uint8_t loopTimeout = 0;
	uint8_t _errorCode = 0;
	bool error = true;
	do{
		dataBuffer = readEgt(dev);
		_errorCode = dataBuffer & 0x07;
		if(_errorCode){
			loopTimeout++;
			error = true;
		}
		else{
			error = false;
			break;
		}
	}while(loopTimeout<2);

	//Store last read time
	dev->lastReadTime = millis();

	uint32_t dataBufferInternal = (((uint32_t)dataBuffer)&0xFFFF)>>4;                   // remove unused ambient values
	if(dataBufferInternal & 0x2000) dataBufferInternal |= 0xFFFE000; 		// 2s complement bits if negative
	dev->milliCelsiusInternal = (((int32_t)dataBufferInternal)*(int32_t)625/(int32_t)10);     // Sensitivity is 0.25C



	if(error){
		dev->milliCelsiusProbe = -100000;
		//dev->milliCelsiusInternal = -100000;
		if(_errorCode & MAX31855_2WIRE_FAULT_OPEN_MASK){
			dev->lastReadFault = MAX31855_2WIRE_FAULT_OPEN;
		}
		else
		if(_errorCode & MAX31855_2WIRE_FAULT_SHORTEDGND_MASK){
			dev->lastReadFault = MAX31855_2WIRE_FAULT_SHORTEDGND;
		}
		else
		if(_errorCode & MAX31855_2WIRE_FAULT_SHORTEDVCC_MASK){
			dev->lastReadFault = MAX31855_2WIRE_FAULT_SHORTEDVCC;
		}
		return dev->lastReadFault;
	}
	else{
		dev->lastReadFault = MAX31855_2WIRE_NO_FAULT;
		uint32_t dataBufferProbe = ((uint32_t)dataBuffer) >> 18;                   			// remove unused ambient values
		if(dataBufferProbe & 0x2000) dataBufferProbe |= 0xFFFE000; 				// 2s complement bits if negative
		dev->milliCelsiusProbe = ((int32_t)dataBufferProbe) * (int32_t)250;                      // Sensitivity is 0.25C

	}
	return MAX31855_2WIRE_NO_FAULT;
}
//#########################################################################################################################

int32_t getMilliCelsiusProbe(egtDevice_t *dev){
	return dev->milliCelsiusProbe;
}

int32_t getMilliCelsiusInternal(egtDevice_t *dev){
	return dev->milliCelsiusInternal;
}

//#########################################################################################################################
//#########################################################################################################################
//#########################################################################################################################
egtDevice_t egtDevice[4];

bool initEgts(){
	egtDevice[0].deviceID = EGT_DEVICE_1;
	egtDevice[0].bus = busDeviceInit(BUSTYPE_SPI, DEVHW_MAX31855_1, 0, OWNER_EGT);
	egtDevice[0].lastReadFault = MAX31855_2WIRE_NO_FAULT;
	egtDevice[0].milliCelsiusProbe = 0;
	egtDevice[0].milliCelsiusInternal = 0;
	readTempCThermoTypeK(&egtDevice[0]);

	egtDevice[1].deviceID = EGT_DEVICE_2;
	egtDevice[1].bus = busDeviceInit(BUSTYPE_SPI, DEVHW_MAX31855_2, 0, OWNER_EGT);
	egtDevice[1].lastReadFault = MAX31855_2WIRE_NO_FAULT;
	egtDevice[1].milliCelsiusProbe = 0;
	egtDevice[1].milliCelsiusInternal = 0;
	readTempCThermoTypeK(&egtDevice[1]);

	egtDevice[2].deviceID = EGT_DEVICE_3;
	egtDevice[2].bus = busDeviceInit(BUSTYPE_SPI, DEVHW_MAX31855_3, 0, OWNER_EGT);
	egtDevice[2].lastReadFault = MAX31855_2WIRE_NO_FAULT;
	egtDevice[2].milliCelsiusProbe = 0;
	egtDevice[2].milliCelsiusInternal = 0;
	readTempCThermoTypeK(&egtDevice[2]);

	egtDevice[3].deviceID = EGT_DEVICE_4;
	egtDevice[3].bus = busDeviceInit(BUSTYPE_SPI, DEVHW_MAX31855_4, 0, OWNER_EGT);
	egtDevice[3].lastReadFault = MAX31855_2WIRE_NO_FAULT;
	egtDevice[3].milliCelsiusProbe = 0;
	egtDevice[3].milliCelsiusInternal = 0;
	readTempCThermoTypeK(&egtDevice[3]);

    return true;
}


bool readEgts(){

	int32_t now = millis();
	for (uint8_t i = 0; i < 4; i++) {
		//if (egtDevice[i].lastReadFault==MAX31855_2WIRE_NO_FAULT ||  now - egtDevice[i].lastReadTime > 30000) {
			readTempCThermoTypeK(&egtDevice[i]);
			invDataStoreValInt(egtDevice[i].deviceID, egtDevice[i].milliCelsiusProbe);
		//}
	}

	return true;
}
