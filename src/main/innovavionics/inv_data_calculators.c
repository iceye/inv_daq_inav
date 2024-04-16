/*
 * inv_data_calculators.c
 *
 *  Created on: Mar 13, 2024
 *      Author: sandro.bottoni
 */

#include "inv_data_calculators.h"
#include "stm32h7xx_hal.h"
#include "inv_data.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "pitotmeter.h"
#include "time.h"

#define _OFFSET_TEMP_MILLIDEG_CHT 0.0f
#define _OFFSET_TEMP_MILLIDEG_OIL 0.0f


float invVref_mV = 3300.0f;
float invVan_mV = 3300.0f;
float mcuTemp_mdegC = 0.0f;

uint32_t invVref_uV = 0;
uint32_t invVan_uV = 0;
pt1Filter_t cht1LpfState;
pt1Filter_t cht2LpfState;
pt1Filter_t oiltLpfState;

void initInvDataCalculators() {
	uint32_t now = micros();
	for (int i = 0; i < INV_DATA_COUNT; i++) {
		_invData[i]._lastUpdate = now;
		if (invDataHasLpfMid(i)) {
			pt1FilterInit((pt1Filter_t *)&invData(i)._pt1FilterState,2, MS2S(100));
		}
		else
		if (invDataHasLpfFast(i)) {
			pt1FilterInit((pt1Filter_t *)&invData(i)._pt1FilterState,10, MS2S(100));
		}
		else
		if (invDataHasLpfSlow(i)) {
			pt1FilterInit((pt1Filter_t *)&invData(i)._pt1FilterState,0.5f, MS2S(100));
		}
	}
}





uint32_t to12VInMicroVolt(uint32_t analog_uV) {
  return ((analog_uV / 10000.0f ) * 8500.0f);
}

uint32_t to5VInMicroVolt(uint32_t analog_uV) {
  return ((analog_uV / 3300.0f) * 5500.0f);
}

uint32_t toRLowMilliohm(uint32_t analog_uV) {

   if(analog_uV >= invVan_uV-1024){
	  return 1000000000;
   }
   float analog_mV = (float)analog_uV / 1000.0f;
   float rLow = (220.0f * analog_mV) / (invVan_mV-analog_mV);
   return (uint32_t)(rLow*1000.0f);
}

uint32_t toRHighMilliohm(uint32_t analog_uV) {

  if(analog_uV >= invVan_uV-1024){
	  return 1000000000;
  }
  float analog_mV = (float)analog_uV / 1000.0f;

  float rHigh = (10000.0f * analog_mV) / (invVan_mV-analog_mV);

  return (uint32_t)(rHigh*1000.0f);
}



/*SENSOR CONVERSIONS*/



/*ROTAX CHT SENSOR*/
/**
 * @brief  Convert resistance to temperature for Rotax 912 CHT sensor
 * @param  r: resistance in milliOhms
 * @retval temperature in milliCelcius
 */
float r2tempRotaxCht(float r) { // culculate temperature from thermistor resistance using Steinhart-Hart equation
  if (r == 0) return 180000.0f;
  //Over 100k it's disconnected
  if(r>100000000) return -100000.0f;

  float logR = log(r/1000.0f);
  float logR3 = logR*logR*logR;

  return 1000.0f * ((1.0f /(0.0018032097440841197f + 0.00017511726125370215f * logR + 0.0000021767578413371076f * logR3) ) - 273.15f + _OFFSET_TEMP_MILLIDEG_CHT); // return temperature in milliCelcius
}


/*ROTAX OIL-T SENSOR*/
/**
 * @brief  Convert resistance to temperature for Rotax 912 Oil-T sensor
 * @param  r: resistance in milliOhms
 * @retval temperature in milliCelcius
 */
float r2tempRotaxOilt(float r) { // culculate temperature from thermistor resistance using Steinhart-Hart equation
	if (r == 0) return 180000.0f;
	//Over 100k it's disconnected
	if(r>100000000) return -100000.0f;

	float logR = log(r/1000.0f);
	float logR3 = logR*logR*logR;
	return 1000.0f * ((1.0f /(0.0018032097440841197f + 0.00017511726125370215f * logR + 0.0000021767578413371076f * logR3) ) - 273.15f +_OFFSET_TEMP_MILLIDEG_CHT); // return temperature in milliCelcius
}


/*ROTAX OIL-P SENSOR*/
/**
 * @brief  Convert resistance to pressure for Rotax 912 Oil-P sensor pre 2008
 * @param  r: resistance in milliOhms
 * @retval pressure in milliBAR
 */
float r2pressRotaxPressure(float r) { // culculate temperature from thermistor resistance using Steinhart-Hart equation
	if (r == 0) return -1.0f;
	if(r>100000000) return -1.0f;

	r /=1000.0f;
	return (0.034471f * r * r) + (46.443574f * r) - 491.302965; // return pressure in milliBAR
}

/*AFTERMARKET OIL-P5V LINEAR SENSOR*/
/**
 * @brief  Convert voltage to pressure for Aftermarket Rotax 912 Oil-P sensor 0-5V (0.5v-4.5v) 0-10bar, the ADC will detect 300mV to 2700V
 * @param  microVolts: microVolts
 * @retval pressure in milliBAR
 */
float mV2press5VPressure(float microVolts) {
	if (microVolts < 450000 || microVolts > 4550000) return -1000.0f;
	if (microVolts <= 500000) return 0.0f;
	if (microVolts >= 4500000) return 10000.0f;

	return 2.500f *  ((microVolts/1000.0f) - 500.0f); // return pressure in milliBAR
}

/* END OF SENSOR CONVERSIONS*/



uint32_t plain(uint32_t analog_uV) {
  return analog_uV;
}

uint32_t adc_uV(uint32_t adcRaw){

	return (uint32_t)(__HAL_ADC_CALC_DATA_TO_VOLTAGE(invVref_mV, adcRaw, ADC_RESOLUTION_16B) * 1000.0f);
}



// PUBLIC CALCULATORS
bool invCalculatorIntPlain(invElement_t *el, void *val , float dtMicros) {
	if (el->_filter != NO_FILTER)
		el->_valueI = pt1FilterApply3(&el->_pt1FilterState, (float)(*((int32_t*) val)), dtMicros);
	else if (el->_filter == NO_FILTER)
		el->_valueI = *((int32_t*) val);
	return true;
}

bool invCalculatorUIntPlain(invElement_t *el, void *val , float dtMicros) {
	if (el->_filter != NO_FILTER)
		el->_valueUI = pt1FilterApply3(&el->_pt1FilterState, (float)(*((uint32_t*) val)), dtMicros);
	else if (el->_filter == NO_FILTER)
		el->_valueUI = *((uint32_t*) val);
	return true;
}

bool invCalculatorBytePlain(invElement_t *el, void *val , float dtMicros) {
	el->_valueBy = *((uint8_t*)val);
	return true;
}

bool invCalculatorBoolPlain(invElement_t *el, void *val , float dtMicros) {
	el->_valueB = *((bool*)val);
	return true;
}


bool invVrefCalculator(invElement_t *el, void *val , float dtMicros) {
	invVref_mV = __HAL_ADC_CALC_VREFANALOG_VOLTAGE(*((uint32_t*) val),ADC_RESOLUTION_16B);
	invVref_uV = (uint32_t) (invVref_mV * 1000);
	el->_valueUI = (invVref_uV);
	return true;
}

bool invVanCalculator(invElement_t *el, void *val , float dtMicros) {
	invVan_mV = __HAL_ADC_CALC_DATA_TO_VOLTAGE(invVref_mV,*((uint32_t*) val), ADC_RESOLUTION_16B);
	invVan_uV = (uint32_t) (invVan_mV * 1000);
	el->_valueUI =invVan_uV;
	return true;
}


bool invMcuTempCalculator(invElement_t *el, void *val , float dtMicros) {
	mcuTemp_mdegC =  __LL_ADC_CALC_TEMPERATURE_FLOAT(invVref_mV, *((uint32_t*) val), ADC_RESOLUTION_16B);
	if (el->_filter != NO_FILTER)
		el->_valueI = pt1FilterApply3(&el->_pt1FilterState,(float) (mcuTemp_mdegC * 1000.0f), dtMicros);
	else
		el->_valueI = (uint32_t)(mcuTemp_mdegC*1000.0f);
	return true;
}


bool invMicroVoltCalculator(invElement_t *el, void *val , float dtMicros) {
	el->_valueUI = (uint32_t)(__HAL_ADC_CALC_DATA_TO_VOLTAGE(invVref_mV, *((uint32_t*) val), ADC_RESOLUTION_16B) * 1000.0f);
	return true;
}



bool general12VSensorCalculator(invElement_t *el, void *val , float dtMicros) {
	if (el->_filter != NO_FILTER)
		el->_valueUI = pt1FilterApply3(&el->_pt1FilterState,(float)to12VInMicroVolt(adc_uV(*((uint32_t*) val))), dtMicros);
	else
		el->_valueUI = to12VInMicroVolt(adc_uV(*((uint32_t*) val)));
	return true;
}

bool general5VSensorCalculator(invElement_t *el, void *val , float dtMicros) {
	if (el->_filter != NO_FILTER)
		el->_valueUI = pt1FilterApply3(&el->_pt1FilterState,(float)to5VInMicroVolt(adc_uV(*((uint32_t*) val))), dtMicros);
	else
		el->_valueUI = to5VInMicroVolt(adc_uV(*((uint32_t*) val)));
	return true;
}


bool generalRLowSensorCalculator(invElement_t *el, void *val , float dtMicros) {
	if (el->_filter != NO_FILTER)
		el->_valueI = pt1FilterApply3(&el->_pt1FilterState,(float)toRLowMilliohm(adc_uV(*((uint32_t*) val))), dtMicros);
	else
		el->_valueI = toRLowMilliohm(adc_uV(*((uint32_t*) val)));
	return true;
}


bool generalRHighSensorCalculator(invElement_t *el, void *val , float dtMicros) {
	if (el->_filter != NO_FILTER)
		el->_valueI = pt1FilterApply3(&el->_pt1FilterState,(float)toRHighMilliohm(adc_uV(*((uint32_t*) val))), dtMicros);
	else
		el->_valueI = toRHighMilliohm(adc_uV(*((uint32_t*) val)));
	return true;
}



bool rotaxChtRSensorCalculator(invElement_t *el, void *val , float dtMicros) {
	float milliCelsius = r2tempRotaxCht(toRLowMilliohm(adc_uV(*((uint32_t*) val))));
	if (el->_filter != NO_FILTER)
		el->_valueI = pt1FilterApply3(&el->_pt1FilterState,milliCelsius, dtMicros);
	else
		el->_valueI = milliCelsius;
	return true;
}



bool rotaxOiltRSensorCalculator(invElement_t *el, void *val , float dtMicros) {
	float milliCelsius = r2tempRotaxOilt(toRLowMilliohm(adc_uV(*((uint32_t*) val))));
	if (el->_filter != NO_FILTER)
		el->_valueI = pt1FilterApply3(&el->_pt1FilterState,milliCelsius, dtMicros);
	else
		el->_valueI = milliCelsius;
	return true;
}



bool rotaxOilpRSensorCalculator(invElement_t *el, void *val , float dtMicros) {
	float milliBar = r2pressRotaxPressure(toRLowMilliohm(adc_uV(*((uint32_t*) val))));
	if (el->_filter != NO_FILTER)
		el->_valueI = pt1FilterApply3(&el->_pt1FilterState,milliBar, dtMicros);
	else
		el->_valueI = milliBar;
	return true;
}



bool rotaxOilp5VSensorCalculator(invElement_t *el, void *val , float dtMicros) {
	float milliBar = mV2press5VPressure(to5VInMicroVolt(adc_uV(*((uint32_t*) val))));
	if (el->_filter != NO_FILTER)
		el->_valueI = pt1FilterApply3(&el->_pt1FilterState,milliBar, dtMicros);
	else
		el->_valueI = milliBar;
	return true;
}


bool rotaxFuelp5VSensorCalculator(invElement_t *el, void *val , float dtMicros) {
	float milliBar = mV2press5VPressure(to5VInMicroVolt(adc_uV(*((uint32_t*) val))));
	if (el->_filter != NO_FILTER)
		el->_valueI = pt1FilterApply3(&el->_pt1FilterState,milliBar, dtMicros);
	else
		el->_valueI = milliBar;
	return true;
}


bool rotaxVin12VSensorCalculator(invElement_t *el, void *val , float dtMicros) {
	float milliVolt = to12VInMicroVolt(adc_uV(*((uint32_t*) val)));
	if (el->_filter != NO_FILTER)
		el->_valueI = pt1FilterApply3(&el->_pt1FilterState,milliVolt, dtMicros);
	else
		el->_valueI = milliVolt;
	return true;
}


uint32_t invCalculatorIasAdcPressureCurrentTimeUs = 0;
uint32_t invCalculatorIasAdcPressureCurrentTimeUsLastMeasurementUs = 0;
#define ADC_IAS_AUX_MICROV_ZERO 735400
#define ADC_IAS_AUX_MICROV_PA 662.0f

bool invCalculatorIasAdcPressure(invElement_t *el, void *val , float dtMicros) {

#ifdef USE_PITOT_AUX

	uint32_t adcuV = (float)adc_uV(*((uint32_t*) val));
	float pitotPressureTmp = 0;
	if(adcuV > ADC_IAS_AUX_MICROV_ZERO){
		pitotPressureTmp = (float)(adcuV-ADC_IAS_AUX_MICROV_ZERO)/ADC_IAS_AUX_MICROV_PA;
	}

	pitot.pressureAux = pt1FilterApply3(&pitot.lpfStateAux, pitotPressureTmp, dtMicros);
	pitot.pressureSpeedAuxTurbolence = pt1FilterApply3(&pitot.lpfStateAuxTurbolence, fabsf(pitotPressureTmp - pitot.pressureAux), dtMicros);
	invCalculatorIasAdcPressureCurrentTimeUsLastMeasurementUs = invCalculatorIasAdcPressureCurrentTimeUs;
	el->_valueI = pitot.pressureAux*1000;

    pitot.airSpeedAux = pitotmeterConfig()->pitot_scale * fast_fsqrtf(2.0f * fabsf(pitot.pressureAux - pitot.pressureZero) / SSL_AIR_DENSITY) * 100;  // cm/s
    pitot.airSpeedAuxTurbolence = (pitotmeterConfig()->pitot_scale * fast_fsqrtf(2.0f * (pitot.pressureAux+pitot.pressureSpeedAuxTurbolence) / SSL_AIR_DENSITY) * 100) - pitotmeterConfig()->pitot_scale * fast_fsqrtf(2.0f * (pitot.pressureAux-pitot.pressureSpeedAuxTurbolence) / SSL_AIR_DENSITY) * 100;  // cm/s;

	invDataStoreValUInt(INV_IAS_AUX, (int32_t) pitot.airSpeedAux); // mm/s
	invDataStoreValUInt(INV_IAS_AUX_TURBOLENCE, (int32_t) pitot.airSpeedTurbolence); // mm/s
#else
	pitot.pressureAux = 0;
	pitot.pressureSpeedAuxTurbolence = 0;
	pitot.airSpeedAux = 0;
	pitot.airSpeedAuxTurbolence = 0;

	int32_t airSpeedAux = (int32_t) pitot.airSpeedAux;
	int32_t airSpeedAuxTurbolence = (int32_t) pitot.airSpeedTurbolence;

	invDataStoreValByConf(INV_IAS_AUX, &airSpeedAux); // mm/s
	invDataStoreValByConf(INV_IAS_AUX_TURBOLENCE, &airSpeedAuxTurbolence); // mm/s
#endif
    return true;
}
