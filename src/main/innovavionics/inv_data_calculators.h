/*
 * inv_data_calculators.h
 *
 *  Created on: Mar 13, 2024
 *      Author: sandro.bottoni
 */

#ifndef SRC_INNOVAVIONICS_INV_DATA_CALCULATORS_H_
#define SRC_INNOVAVIONICS_INV_DATA_CALCULATORS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <innovavionics/inv_params.h>
#include "common/filter.h"
#include "common/time.h"
#include <stdint.h>
#include <stdbool.h>

#define __LL_ADC_CALC_TEMPERATURE_FLOAT(__VREFANALOG_VOLTAGE__,					\
                                  __TEMPSENSOR_ADC_DATA__,						\
                                  __ADC_RESOLUTION__)                           \
 (																																								\
	(																																							\
	   (																																						\
		  ( 																																					\
			(																																					\
				(float)																																			\
				( 																																				\
					( 																																			\
							__LL_ADC_CONVERT_DATA_RESOLUTION((__TEMPSENSOR_ADC_DATA__), (__ADC_RESOLUTION__), LL_ADC_RESOLUTION_16B) * (__VREFANALOG_VOLTAGE__) \
					)																																			\
					/ TEMPSENSOR_CAL_VREFANALOG																													\
				)                                     																											\
				- (float)((int32_t) *TEMPSENSOR_CAL1_ADDR)																										\
			)                                         																											\
		  )																																						\
		  * (float)																																				\
          (																																						\
				(																																				\
				TEMPSENSOR_CAL2_TEMP - TEMPSENSOR_CAL1_TEMP																										\
				)											                    																				\
		  )																																						\
	   ) 																																						\
	   / (float) 																																				\
          (																																						\
			 (int32_t)*TEMPSENSOR_CAL2_ADDR - (int32_t)*TEMPSENSOR_CAL1_ADDR																					\
		  ) 																																					\
   ) + (float)TEMPSENSOR_CAL1_TEMP                                                        																		\
 )

void initInvDataCalculators();

bool invCalculatorIntPlain(invElement_t *el, void *val, float dtMicros);

bool invCalculatorUIntPlain(invElement_t *el, void *val, float dtMicros);

bool invCalculatorBytePlain(invElement_t *el, void *val, float dtMicros);

bool invCalculatorBoolPlain(invElement_t *el, void *val, float dtMicros);

bool invVrefCalculator(invElement_t *el, void *val, float dtMicros);

bool invVanCalculator(invElement_t *el, void *val, float dtMicros);

bool invMcuTempCalculator(invElement_t *el, void *val, float dtMicros);

bool invMicroVoltCalculator(invElement_t *el, void *val, float dtMicros);

bool general12VSensorCalculator(invElement_t *el, void *val, float dtMicros);
bool general5VSensorCalculator(invElement_t *el, void *val, float dtMicros) ;
bool generalRLowSensorCalculator(invElement_t *el, void *val, float dtMicros);
bool generalRHighSensorCalculator(invElement_t *el, void *val, float dtMicros);
bool rotaxChtRSensorCalculator(invElement_t *el, void *val, float dtMicros);

bool rotaxOiltRSensorCalculator(invElement_t *el, void *val, float dtMicros);
bool rotaxOilpRSensorCalculator(invElement_t *el, void *val, float dtMicros) ;
bool rotaxOilp5VSensorCalculator(invElement_t *el, void *val, float dtMicros) ;
bool rotaxFuelp5VSensorCalculator(invElement_t *el, void *val, float dtMicros);
bool rotaxVin12VSensorCalculator(invElement_t *el, void *val, float dtMicros) ;

bool invCalculatorIasAdcPressure(invElement_t *el, void *val, float dtMicros);


#ifdef __cplusplus
}
#endif

#endif /* SRC_INNOVAVIONICS_INV_DATA_CALCULATORS_H_ */
