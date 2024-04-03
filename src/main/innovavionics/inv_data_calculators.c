/*
 * inv_data_calculators.c
 *
 *  Created on: Mar 13, 2024
 *      Author: sandro.bottoni
 */

#include <innovavionics/inv_data_calculators.h>
#include "stm32h7xx_hal.h"
#include "inv_data.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define _OFFSET_TEMP_MILLIDEG_CHT 0
#define _OFFSET_TEMP_MILLIDEG_OIL 0


float invVref_mV = 3300.0f;
float invVan_mV = 3300.0f;
float mcuTemp_mdegC = 0.0f;

uint32_t invVref_uV = 0;
uint32_t invVan_uV = 0;
pt1Filter_t cht1LpfState;
pt1Filter_t cht2LpfState;
pt1Filter_t oiltLpfState;

void initInvDataCalculators() {

	for (int i = 0; i < INV_DATA_COUNT; i++) {

		if (invDataHasLpfMid(i)) {
			pt1FilterInit(&invData(i)._pt1FilterState,1, MS2S(100));
		}
		else
		if (invDataHasLpfFast(i)) {
			pt1FilterInit(&invData(i)._pt1FilterState,5, MS2S(100));
		}
		else
		if (invDataHasLpfSlow(i)) {
			pt1FilterInit(&invData(i)._pt1FilterState,0.2, MS2S(100));
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
 * @param  r: resistance in Ohms
 * @retval temperature in milliCelcius
 */
float r2tempRotaxCht(float r) { // culculate temperature from thermistor resistance using Steinhart-Hart equation
  if (r == 0) return 1000.0f;
  return 1000.0f * (1 / (1.588479837f + 2.677440431f * log(r) + -2.062028844 * pow(log(r), 3)) - 273.15 + _OFFSET_TEMP_MILLIDEG_CHT); // return temperature in milliCelcius
}


/*ROTAX OIL-T SENSOR*/
/**
 * @brief  Convert resistance to temperature for Rotax 912 Oil-T sensor
 * @param  r: resistance in Ohms
 * @retval temperature in milliCelcius
 */
float r2tempRotaxOilt(float r) { // culculate temperature from thermistor resistance using Steinhart-Hart equation
	if (r == 0) return 1000.0f;
	  return 1000.0f *(1 / (1.588479837f + 2.677440431f * log(r) + -2.062028844 * pow(log(r), 3)) - 273.15 + _OFFSET_TEMP_MILLIDEG_OIL); // return temperature in milliCelcius
}


/*ROTAX OIL-P SENSOR*/
/**
 * @brief  Convert resistance to pressure for Rotax 912 Oil-P sensor pre 2008
 * @param  r: resistance in Ohms
 * @retval pressure in milliBAR
 */
float r2pressRotaxPressure(float r) { // culculate temperature from thermistor resistance using Steinhart-Hart equation
	if (r == 0)
		return -1.0f;
	return (0.034471f * r * r) + (46.443574f * r) - 491.302965; // return pressure in milliBAR
}

/*AFTERMARKET OIL-P5V LINEAR SENSOR*/
/**
 * @brief  Convert voltage to pressure for Aftermarket Rotax 912 Oil-P sensor 0-5V (0.5v-4.5v) 0-10bar
 * @param  r: resistance in Ohms
 * @retval pressure in milliBAR
 */
float mV2press5VPressure(float r) {
	if (r == 0)
		return -1.0f;
	return 2500 * r - 1250; // return pressure in milliBAR
}





/* END OF SENSOR CONVERSIONS*/



uint32_t plain(uint32_t analog_uV) {
  return analog_uV;
}

uint32_t adc_uV(uint32_t adcRaw){

	return (uint32_t)(__HAL_ADC_CALC_DATA_TO_VOLTAGE(invVref_mV, adcRaw, ADC_RESOLUTION_16B) * 1000.0f);
}


bool invCalculatorIntPlain(invElement_t *el, void *val){
	if (el->_filter != NO_FILTER)
		el->_valueI = pt1FilterApply(&el->_pt1FilterState, (float)(*((int32_t*) val)));
	else if (el->_filter == NO_FILTER)
		el->_valueI = *((int32_t*) val);
	return true;
}

bool invCalculatorUIntPlain(invElement_t *el, void *val){
	if (el->_filter != NO_FILTER)
		el->_valueUI = pt1FilterApply(&el->_pt1FilterState, (float)(*((uint32_t*) val)));
	else if (el->_filter == NO_FILTER)
		el->_valueUI = *((uint32_t*) val);
	return true;
}

bool invCalculatorBytePlain(invElement_t *el, void *val) {
	el->_valueBy = *((uint8_t*)val);
	return true;
}

bool invCalculatorBoolPlain(invElement_t *el, void *val) {
	el->_valueB = *((bool*)val);
	return true;
}


bool invVrefCalculator(invElement_t *el, void *val) {
	invVref_mV = __HAL_ADC_CALC_VREFANALOG_VOLTAGE(*((uint32_t*) val),ADC_RESOLUTION_16B);
	invVref_uV = (uint32_t) (invVref_mV * 1000);
	el->_valueUI = (invVref_uV);
	return true;
}

bool invVanCalculator(invElement_t *el, void *val) {
	invVan_mV = __HAL_ADC_CALC_DATA_TO_VOLTAGE(invVref_mV,*((uint32_t*) val), ADC_RESOLUTION_16B);
	invVan_uV = (uint32_t) (invVan_mV * 1000);
	el->_valueUI =invVan_uV;
	return true;
}


bool invMcuTempCalculator(invElement_t *el, void *val) {
	mcuTemp_mdegC =  __LL_ADC_CALC_TEMPERATURE_FLOAT(invVref_mV, *((uint32_t*) val), ADC_RESOLUTION_16B);
	if (el->_filter != NO_FILTER)
		el->_valueI = pt1FilterApply(&el->_pt1FilterState,(float) (mcuTemp_mdegC * 1000.0f));
	else
		el->_valueI = (uint32_t)(mcuTemp_mdegC*1000.0f);
	return true;
}


bool invMicroVoltCalculator(invElement_t *el, void *val) {
	el->_valueUI = (uint32_t)(__HAL_ADC_CALC_DATA_TO_VOLTAGE(invVref_mV, *((uint32_t*) val), ADC_RESOLUTION_16B) * 1000.0f);
	return true;
}



bool general12VSensorCalculator(invElement_t *el, void *val) {
	if (el->_filter != NO_FILTER)
		el->_valueUI = pt1FilterApply(&el->_pt1FilterState,(float)to12VInMicroVolt(adc_uV(*((uint32_t*) val))));
	else
		el->_valueUI = to12VInMicroVolt(adc_uV(*((uint32_t*) val)));
	return true;
}

bool general5VSensorCalculator(invElement_t *el, void *val) {
	if (el->_filter != NO_FILTER)
		el->_valueUI = pt1FilterApply(&el->_pt1FilterState,(float)to5VInMicroVolt(adc_uV(*((uint32_t*) val))));
	else
		el->_valueUI = to5VInMicroVolt(adc_uV(*((uint32_t*) val)));
	return true;
}


bool generalRLowSensorCalculator(invElement_t *el, void *val) {
	if (el->_filter != NO_FILTER)
		el->_valueI = pt1FilterApply(&el->_pt1FilterState,(float)toRLowMilliohm(adc_uV(*((uint32_t*) val))));
	else
		el->_valueI = toRLowMilliohm(adc_uV(*((uint32_t*) val)));
	return true;
}


bool generalRHighSensorCalculator(invElement_t *el, void *val) {
	if (el->_filter != NO_FILTER)
		el->_valueI = pt1FilterApply(&el->_pt1FilterState,(float)toRHighMilliohm(adc_uV(*((uint32_t*) val))));
	else
		el->_valueI = toRHighMilliohm(adc_uV(*((uint32_t*) val)));
	return true;
}



bool rotaxChtRSensorCalculator(invElement_t *el, void *val) {
	if (el->_filter != NO_FILTER)
		el->_valueI = pt1FilterApply(&el->_pt1FilterState,(float)toRLowMilliohm(adc_uV(*((uint32_t*) val))));
	else
		el->_valueI = toRLowMilliohm(adc_uV(*((uint32_t*) val)));
	return true;
}



bool rotaxOiltRSensorCalculator(invElement_t *el, void *val) {
	if (el->_filter != NO_FILTER)
		el->_valueI = pt1FilterApply(&el->_pt1FilterState,(float)toRLowMilliohm(adc_uV(*((uint32_t*) val))));
	else
		el->_valueI = toRLowMilliohm(adc_uV(*((uint32_t*) val)));

	return true;
}



bool rotaxOilpRSensorCalculator(invElement_t *el, void *val) {
	if (el->_filter != NO_FILTER)
		el->_valueI = pt1FilterApply(&el->_pt1FilterState,(float)toRLowMilliohm(adc_uV(*((uint32_t*) val))));
	else
		el->_valueI = toRLowMilliohm(adc_uV(*((uint32_t*) val)));
	return true;
}



bool rotaxOilp5VSensorCalculator(invElement_t *el, void *val) {
	if (el->_filter != NO_FILTER)
		el->_valueI = pt1FilterApply(&el->_pt1FilterState,(float)to5VInMicroVolt(adc_uV(*((uint32_t*) val))));
	else
		el->_valueI = to5VInMicroVolt(adc_uV(*((uint32_t*) val)));
	return true;
}


bool rotaxFuelp5VSensorCalculator(invElement_t *el, void *val) {
	if (el->_filter != NO_FILTER)
		el->_valueI = pt1FilterApply(&el->_pt1FilterState,(float)to5VInMicroVolt(adc_uV(*((uint32_t*) val))));
	else
		el->_valueI = to5VInMicroVolt(adc_uV(*((uint32_t*) val)));
	return true;
}


bool rotaxVin12VSensorCalculator(invElement_t *el, void *val) {
	if (el->_filter != NO_FILTER)
		el->_valueI = pt1FilterApply(&el->_pt1FilterState,(float)to12VInMicroVolt(adc_uV(*((uint32_t*) val))));
	else
		el->_valueI = to5VInMicroVolt(adc_uV(*((uint32_t*) val)));
	return true;
}


