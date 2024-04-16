/*
 * inv_adc.h
 *
 *  Created on: Mar 14, 2024
 *      Author: sandro.bottoni
 */

#ifndef SRC_INNOVAVIONICS_INV_ADC_H_
#define SRC_INNOVAVIONICS_INV_ADC_H_
#include "stm32h7xx_hal.h"
#include "build_config.h"
#include "inv_data.h"
#include "dma.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define TASK_INV_ADC_HZ 20

#define INV_ADCD_COUNT 3

#define INV_ADC1_CHANNELS 8
#define INV_ADC2_CHANNELS 9
#define INV_ADC3_CHANNELS 13




#ifdef __cplusplus
extern "C" {
#endif


void invAdcInit(void);
bool invAdcStart(void);
void invDeAdcInit(void);
void invAdcCheckNewData(void);

void invAdc1DMAHandler(void);
void invAdc2DMAHandler(void);
void invAdc3DMAHandler(void);


extern ADC_HandleTypeDef invHadc1;
extern ADC_HandleTypeDef invHadc2;
extern ADC_HandleTypeDef invHadc3;
extern DMA_HandleTypeDef invHdmaAdc1;
extern DMA_HandleTypeDef invHdmaAdc2;
extern DMA_HandleTypeDef invHdmaAdc3;


#ifdef __cplusplus
}
#endif


#endif /* SRC_INNOVAVIONICS_INV_ADC_H_ */
