/*
 * inv_adc.c
 *
 *  Created on: Mar 14, 2024
 *      Author: sandro.bottoni
 */

#include "inv_adc.h"

#include "platform.h"
#include "build/debug.h"
#include "drivers/time.h"
#include "drivers/io.h"

#include "rcc.h"
#include "dma.h"


#include "drivers/time.h"
#include <stdlib.h>
#include <stdbool.h>

#ifdef STM32IDE
	#include "stm32h7xx_hal.h"
	#include "target.h"
#endif
#ifdef USE_INNOVAVIONICS_ADC

/*Private variables*/

#define INNOVAVIONICS_DEBUG_MODE 101

#define INV_ADC1_BUFFER_START 0
#define INV_ADC2_BUFFER_START INV_ADC1_CHANNELS
#define INV_ADC3_BUFFER_START INV_ADC3_CHANNELS
#define INV_ADC_ALL_CHANNELS INV_ADC1_CHANNELS + INV_ADC2_CHANNELS + INV_ADC3_CHANNELS


volatile DMA_RAM uint32_t invAdc1ValuesDMA[INV_ADC1_CHANNELS];
volatile DMA_RAM uint32_t invAdc2ValuesDMA[INV_ADC2_CHANNELS];
volatile DMA_RAM uint32_t invAdc3ValuesDMA[INV_ADC3_CHANNELS];
volatile uint32_t invAdcValues[INV_ADC_ALL_CHANNELS];

volatile bool invAdc1ValuesReady, invAdc2ValuesReady, invAdc3ValuesReady;
volatile bool invAdc1Timeout, invAdc2Timeout, invAdc3Timeout;
volatile bool invAdc1Error, invAdc2Error, invAdc3Error;
bool invAdcInitSuccess = false, invAdcStarted = false, invAdcRunning = false;
timeMs_t invAdc1LastSeen = 0, invAdc2LastSeen = 0, invAdc3LastSeen = 0;
volatile bool cleanCache = false;

invElementDataType_t invAdc1ValueMap[INV_ADC1_CHANNELS] = {
		INV_OILP,
		INV_DATA_NONE,
		INV_DATA_NONE,
		INV_AUMPUMP_VOLTAGE,
		INV_DATA_NONE,
		INV_OAT,
		INV_OILT,
		INV_TANK_2
};

invElementDataType_t invAdc2ValueMap[INV_ADC2_CHANNELS] = {
		INV_DATA_NONE,
		INV_DATA_NONE,
		INV_DATA_NONE,
		INV_DATA_NONE,
		INV_DAQ_MCU_GND,
		INV_GENAMP,
		INV_TANK_1,
		INV_IAT,
		INV_DATA_NONE
};

invElementDataType_t invAdc3ValueMap[INV_ADC3_CHANNELS] = {
		INV_MAINAMP,
		INV_DATA_NONE,
		INV_CHT2,
		INV_IAS_AUX,
		INV_CHT1,
		INV_DAQ_VIN,
		INV_DAQ_MCU_VAN,
		INV_BATT_V,
		INV_TRIM_POS,
		INV_FLAP_POS,
		INV_DATA_NONE, //internal vbatt
		INV_DAQ_MCU_TEMP,
		INV_DAQ_MCU_VVREF
};



ADC_HandleTypeDef invHadc1;
ADC_HandleTypeDef invHadc2;
ADC_HandleTypeDef invHadc3;
DMA_HandleTypeDef invHdmaAdc1;
DMA_HandleTypeDef invHdmaAdc2;
DMA_HandleTypeDef invHdmaAdc3;
dmaTag_t invHdmaAdc1DmaTag;
dmaTag_t invHdmaAdc2DmaTag;
dmaTag_t invHdmaAdc3DmaTag;


/*Private functions*/
static void invAdcCalibrate();
static void invAdcStop();
static bool invAdcCheckTimeout();
static void INV_DMA_INIT();
static void INV_ADC1_Init(void);
static void INV_ADC2_Init(void);
static void INV_ADC3_Init(void);
static volatile void *memcpy_v(volatile void *restrict dest, const volatile void *restrict src, size_t n);


/*Public functions*/

void invAdcInit(){
	if(invAdcInitSuccess){
		HAL_ADC_DeInit(&invHadc1);
		HAL_ADC_DeInit(&invHadc2);
		HAL_ADC_DeInit(&invHadc3);
	}
	//invHdmaAdc1DmaTag = DMA_TAG(1,4,0);
	INV_DMA_INIT();
	//invHdmaAdc1 = dmaGetByTag(invHdmaAdc1DmaTag); // Use DMA1 Stream 4

	// For H7 the DMA periphRequest is encoded in the DMA tag
	//init.PeriphRequest = DMATAG_GET_CHANNEL(invHdmaAdc1DmaTag);

	//dmaInit(invHdmaAdc1, OWNER_ADC, 0);
	//dmaSetHandler(invHdmaAdc1, invAdc1DMAHandler, 0, 0);

	/*
	RCC_ClockCmd(RCC_AHB1(ADC12), ENABLE);
	RCC_ClockCmd(RCC_AHB4(ADC3), ENABLE);
	RCC_ClockCmd(RCC_AHB1(DMA2), ENABLE);
	*/
	INV_ADC1_Init();
	INV_ADC2_Init();
	INV_ADC3_Init();
	invAdcInitSuccess = true;
}

bool invAdcStart(){
	if(!invAdcInitSuccess){
		invAdcInit();
	}

	invAdcCalibrate();

	invAdc1ValuesReady = false;
	invAdc2ValuesReady = false;
	invAdc3ValuesReady = false;
	invAdc1Timeout = false;
	invAdc2Timeout = false;
	invAdc3Timeout = false;
	invAdc1Error = false;
	invAdc2Error = false;
	invAdc3Error = false;

	HAL_ADC_Start_DMA(&invHadc1, (uint32_t*)invAdc1ValuesDMA, INV_ADC1_CHANNELS);
	HAL_ADC_Start_DMA(&invHadc2, (uint32_t*)invAdc2ValuesDMA, INV_ADC2_CHANNELS);
	HAL_ADC_Start_DMA(&invHadc3, (uint32_t*)invAdc3ValuesDMA, INV_ADC3_CHANNELS);

	if(!invAdc1Error && !invAdc2Error && !invAdc3Error){
		invAdcStarted = true;
		invAdcRunning = true;
	}
	else{
		invDeAdcInit();
		return false;
	}
	debugMode = INNOVAVIONICS_DEBUG_MODE;
	TIME_SECTION_BEGIN(1);
	TIME_SECTION_BEGIN(2);
	TIME_SECTION_BEGIN(3);
	return true;
}


static void invAdcCalibrate(){

		/* Run the ADC calibration in single-ended mode */
		if (HAL_ADCEx_Calibration_Start(&invHadc1, ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED) != HAL_OK)
		{
		  /* Calibration Error */
			invAdc1Error = true;
			invDeAdcInit();
			return;
		}
		/* Run the ADC calibration in single-ended mode */
		if (HAL_ADCEx_Calibration_Start(&invHadc2, ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED) != HAL_OK)
		{
		/* Calibration Error */
			invAdc2Error = true;
			invDeAdcInit();
			return;
		}

		/* Run the ADC calibration in single-ended mode */
		if (HAL_ADCEx_Calibration_Start(&invHadc3, ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED) != HAL_OK)
		{
		/* Calibration Error */
			invAdc3Error = true;
			invDeAdcInit();
			return;
		}

		while (LL_ADC_IsCalibrationOnGoing(invHadc1.Instance)) {
		}

		while (LL_ADC_IsCalibrationOnGoing(invHadc2.Instance)) {
		}

		while (LL_ADC_IsCalibrationOnGoing(invHadc3.Instance)) {
		}

}

static void invAdcStop(){
	invAdcRunning = false;
}

void invDeAdcInit(){
	invAdcStop();
	invAdcInitSuccess = false;
	invAdcStarted = false;
}


static void invCleanCache(uint32_t* buffer, uint8_t size){
	SCB_InvalidateDCache_by_Addr((uint32_t*)(((uint32_t)buffer) & ~(uint32_t)0x1F), size*sizeof(uint32_t)+32);
}





void invAdcCheckNewData(){
	if (invAdc1Error) {
		invAdc1Error = true;
		invAdc1ValuesReady = false;
		invAdc1Timeout = false;
		invCleanCache((uint32_t*)invAdc1ValuesDMA, INV_ADC1_CHANNELS);
		HAL_ADC_Start_DMA(&invHadc1, (uint32_t*)invAdc1ValuesDMA, INV_ADC1_CHANNELS);
	}
	if (invAdc2Error) {
		invAdc2Error = true;
		invAdc2ValuesReady = false;
		invAdc2Timeout = false;
		invCleanCache((uint32_t*)invAdc2ValuesDMA, INV_ADC2_CHANNELS);
		HAL_ADC_Start_DMA(&invHadc2, (uint32_t*) invAdc2ValuesDMA, INV_ADC2_CHANNELS);
	}
	if (invAdc3Error) {
		invAdc3Error = true;
		invAdc3ValuesReady = false;
		invAdc3Timeout = false;
		invCleanCache((uint32_t*)invAdc3ValuesDMA, INV_ADC3_CHANNELS);
		HAL_ADC_Start_DMA(&invHadc3, (uint32_t*) invAdc3ValuesDMA, INV_ADC3_CHANNELS);
	}

	if (invAdc1ValuesReady) {
		for (uint8_t i; i < INV_ADC1_CHANNELS; i++) {
			if (invAdc1ValueMap[i] != INV_DATA_NONE) {
				invDataStoreValUInt(invAdc1ValueMap[i], invAdcValues[INV_ADC1_BUFFER_START + i]);
			}
		}
		invAdc1ValuesReady = false;
		invAdc1Timeout = false;
		invAdc1Error = false;
		invAdc1LastSeen = millis();
		invCleanCache((uint32_t*)invAdc1ValuesDMA, INV_ADC1_CHANNELS);
		TIME_SECTION_BEGIN(1);
		HAL_ADC_Start_DMA(&invHadc1, (uint32_t*)invAdc1ValuesDMA, INV_ADC1_CHANNELS);
	}
	else{
		invAdc1Timeout = (millis() - invAdc1LastSeen) > 1000;
	}
	if (invAdc2ValuesReady) {
		for (uint8_t i; i < INV_ADC2_CHANNELS; i++) {
			if (invAdc2ValueMap[i] != INV_DATA_NONE) {
				invDataStoreValUInt(invAdc2ValueMap[i],invAdcValues[INV_ADC2_BUFFER_START + i]);
			}
		}
		DEBUG_SET(INNOVAVIONICS_DEBUG_MODE, 7, invAdcValues[INV_ADC2_BUFFER_START + 4]); // GND
		invAdc2ValuesReady = false;
		invAdc2Timeout = false;
		invAdc2Error = false;
		invAdc2LastSeen = millis();
		invCleanCache((uint32_t*) invAdc2ValuesDMA, INV_ADC2_CHANNELS);
		TIME_SECTION_BEGIN(2);
		HAL_ADC_Start_DMA(&invHadc2, (uint32_t*) invAdc2ValuesDMA,
				INV_ADC2_CHANNELS);
	}
	else{
		invAdc2Timeout = (millis() - invAdc2LastSeen) > 1000;
	}
	if (invAdc3ValuesReady) {
		for (uint8_t i; i < INV_ADC3_CHANNELS; i++) {
			if (invAdc3ValueMap[i] != INV_DATA_NONE) {
				invDataStoreValUInt(invAdc3ValueMap[i],invAdcValues[INV_ADC3_BUFFER_START + i]);
			}
		}
		DEBUG_SET(INNOVAVIONICS_DEBUG_MODE, 0, invAdcValues[INV_ADC3_BUFFER_START + 5]); //VIN
		DEBUG_SET(INNOVAVIONICS_DEBUG_MODE, 6, 65535-invAdcValues[INV_ADC3_BUFFER_START + 6]); //VAN
		DEBUG_SET(INNOVAVIONICS_DEBUG_MODE, 4, invAdcValues[INV_ADC3_BUFFER_START + 11]); //TEMP
		DEBUG_SET(INNOVAVIONICS_DEBUG_MODE, 5, invAdcValues[INV_ADC3_BUFFER_START + 12]); //VREF



		invAdc3ValuesReady = false;
		invAdc3Timeout = false;
		invAdc3Error = false;
		invAdc3LastSeen = millis();
		invCleanCache((uint32_t*) invAdc3ValuesDMA, INV_ADC3_CHANNELS);
		TIME_SECTION_BEGIN(3);
		HAL_ADC_Start_DMA(&invHadc3, (uint32_t*) invAdc3ValuesDMA,
		INV_ADC3_CHANNELS);
	}
	else{
		invAdc3Timeout = (millis() - invAdc3LastSeen) > 1000;
	}

}



static bool invAdcCheckTimeout(){
	return invAdc1Timeout || invAdc2Timeout || invAdc3Timeout;
}



/*Private functions*/

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */

static void INV_DMA_INIT(){
 /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();


  /* DMA interrupt init */
  /* DMA1_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);
  /* DMA1_Stream1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
  /* DMA1_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);
}

void DMA1_Stream4_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream2_IRQn 0 */

  /* USER CODE END DMA1_Stream2_IRQn 0 */
  HAL_DMA_IRQHandler(&invHdmaAdc1);
  /* USER CODE BEGIN DMA1_Stream2_IRQn 1 */

  /* USER CODE END DMA1_Stream2_IRQn 1 */
}

void DMA1_Stream5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream2_IRQn 0 */

  /* USER CODE END DMA1_Stream2_IRQn 0 */
  HAL_DMA_IRQHandler(&invHdmaAdc2);
  /* USER CODE BEGIN DMA1_Stream2_IRQn 1 */

  /* USER CODE END DMA1_Stream2_IRQn 1 */
}


void DMA1_Stream6_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream2_IRQn 0 */

  /* USER CODE END DMA1_Stream2_IRQn 0 */
  HAL_DMA_IRQHandler(&invHdmaAdc3);
  /* USER CODE BEGIN DMA1_Stream2_IRQn 1 */

  /* USER CODE END DMA1_Stream2_IRQn 1 */
}



static void INV_ADC1_Init(void)
{

  /* USER CODE END ADC1_Init 0 */

  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  invHadc1.Instance = ADC1;
  invHadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV8;
  invHadc1.Init.Resolution = ADC_RESOLUTION_16B;
  invHadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  invHadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  invHadc1.Init.LowPowerAutoWait = DISABLE;
  invHadc1.Init.ContinuousConvMode = DISABLE;
  invHadc1.Init.NbrOfConversion = 8;
  invHadc1.Init.DiscontinuousConvMode = DISABLE;
  invHadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  invHadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  invHadc1.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DMA_CIRCULAR;
  invHadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  invHadc1.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
  invHadc1.Init.OversamplingMode = ENABLE;
  invHadc1.Init.Oversampling.Ratio = 16;
  invHadc1.Init.Oversampling.RightBitShift = ADC_RIGHTBITSHIFT_4;
  invHadc1.Init.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;
  invHadc1.Init.Oversampling.OversamplingStopReset = ADC_REGOVERSAMPLING_CONTINUED_MODE;
  if (HAL_ADC_Init(&invHadc1) != HAL_OK)
  {
    invAdc1Error = true;
    return;
  }

  /** Configure the ADC multi-mode
  */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&invHadc1, &multimode) != HAL_OK)
  {
	invAdc1Error = true;
	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = LL_ADC_SAMPLINGTIME_387CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  sConfig.OffsetSignedSaturation = DISABLE;
  if (HAL_ADC_ConfigChannel(&invHadc1, &sConfig) != HAL_OK)
  {
	invAdc1Error = true;
	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&invHadc1, &sConfig) != HAL_OK)
  {
	invAdc1Error = true;
	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = ADC_REGULAR_RANK_3;
  if (HAL_ADC_ConfigChannel(&invHadc1, &sConfig) != HAL_OK)
  {
	invAdc1Error = true;
	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_5;
  sConfig.Rank = ADC_REGULAR_RANK_4;
  if (HAL_ADC_ConfigChannel(&invHadc1, &sConfig) != HAL_OK)
  {
	invAdc1Error = true;
	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_6;
  sConfig.Rank = ADC_REGULAR_RANK_5;
  if (HAL_ADC_ConfigChannel(&invHadc1, &sConfig) != HAL_OK)
  {
	invAdc1Error = true;
	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_15;
  sConfig.Rank = ADC_REGULAR_RANK_6;
  if (HAL_ADC_ConfigChannel(&invHadc1, &sConfig) != HAL_OK)
  {
	invAdc1Error = true;
	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_16;
  sConfig.Rank = ADC_REGULAR_RANK_7;
  if (HAL_ADC_ConfigChannel(&invHadc1, &sConfig) != HAL_OK)
  {
	invAdc1Error = true;
	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_17;
  sConfig.Rank = ADC_REGULAR_RANK_8;
  if (HAL_ADC_ConfigChannel(&invHadc1, &sConfig) != HAL_OK)
  {
	invAdc1Error = true;
	return;
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief ADC2 Initialization Function
  * @param None
  * @retval None
  */

static void INV_ADC2_Init(void)
{

  /* USER CODE BEGIN ADC2_Init 0 */

  /* USER CODE END ADC2_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC2_Init 1 */

  /* USER CODE END ADC2_Init 1 */

  /** Common config
  */
  invHadc2.Instance = ADC2;
  invHadc2.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV8;
  invHadc2.Init.Resolution = ADC_RESOLUTION_16B;
  invHadc2.Init.ScanConvMode = ADC_SCAN_ENABLE;
  invHadc2.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  invHadc2.Init.LowPowerAutoWait = DISABLE;
  invHadc2.Init.ContinuousConvMode = DISABLE;
  invHadc2.Init.NbrOfConversion = 9;
  invHadc2.Init.DiscontinuousConvMode = DISABLE;
  invHadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  invHadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  invHadc2.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DMA_CIRCULAR;
  invHadc2.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  invHadc2.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
  invHadc2.Init.OversamplingMode = ENABLE;
  invHadc2.Init.Oversampling.Ratio = 16;
  invHadc2.Init.Oversampling.RightBitShift = ADC_RIGHTBITSHIFT_4;
  invHadc2.Init.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;
  invHadc2.Init.Oversampling.OversamplingStopReset = ADC_REGOVERSAMPLING_CONTINUED_MODE;
  if (HAL_ADC_Init(&invHadc2) != HAL_OK)
  {
	  invAdc2Error = true;
	  	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_6;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = LL_ADC_SAMPLINGTIME_387CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  sConfig.OffsetSignedSaturation = DISABLE;
  if (HAL_ADC_ConfigChannel(&invHadc2, &sConfig) != HAL_OK)
  {
	  invAdc2Error = true;
	  	  	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_7;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&invHadc2, &sConfig) != HAL_OK)
  {
	  invAdc2Error = true;
	  	  	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_8;
  sConfig.Rank = ADC_REGULAR_RANK_3;
  if (HAL_ADC_ConfigChannel(&invHadc2, &sConfig) != HAL_OK)
  {
	  invAdc2Error = true;
	  	  	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_9;
  sConfig.Rank = ADC_REGULAR_RANK_4;
  if (HAL_ADC_ConfigChannel(&invHadc2, &sConfig) != HAL_OK)
  {
	  invAdc2Error = true;
	  	  	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_10;
  sConfig.Rank = ADC_REGULAR_RANK_5;
  if (HAL_ADC_ConfigChannel(&invHadc2, &sConfig) != HAL_OK)
  {
	  invAdc2Error = true;
	  	  	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_11;
  sConfig.Rank = ADC_REGULAR_RANK_6;
  if (HAL_ADC_ConfigChannel(&invHadc2, &sConfig) != HAL_OK)
  {
	  invAdc2Error = true;
	  	  	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_14;
  sConfig.Rank = ADC_REGULAR_RANK_7;
  if (HAL_ADC_ConfigChannel(&invHadc2, &sConfig) != HAL_OK)
  {
	  invAdc2Error = true;
	  	  	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_18;
  sConfig.Rank = ADC_REGULAR_RANK_8;
  if (HAL_ADC_ConfigChannel(&invHadc2, &sConfig) != HAL_OK)
  {
	  invAdc2Error = true;
	  	  	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_19;
  sConfig.Rank = ADC_REGULAR_RANK_9;
  if (HAL_ADC_ConfigChannel(&invHadc2, &sConfig) != HAL_OK)
  {
	  invAdc2Error = true;
	  	  	return;
  }
  /* USER CODE BEGIN ADC2_Init 2 */

  /* USER CODE END ADC2_Init 2 */

}

/**
  * @brief ADC3 Initialization Function
  * @param None
  * @retval None
  */

static void INV_ADC3_Init(void)
{

  /* USER CODE BEGIN ADC3_Init 0 */

  /* USER CODE END ADC3_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC3_Init 1 */

  /* USER CODE END ADC3_Init 1 */

  /** Common config
  */
  invHadc3.Instance = ADC3;
  invHadc3.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV8;
  invHadc3.Init.Resolution = ADC_RESOLUTION_16B;
  invHadc3.Init.ScanConvMode = ADC_SCAN_ENABLE;
  invHadc3.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  invHadc3.Init.LowPowerAutoWait = DISABLE;
  invHadc3.Init.ContinuousConvMode = DISABLE;
  invHadc3.Init.NbrOfConversion = 13;
  invHadc3.Init.DiscontinuousConvMode = DISABLE;
  invHadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  invHadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  invHadc3.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DMA_CIRCULAR;
  invHadc3.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  invHadc3.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
  invHadc3.Init.OversamplingMode = ENABLE;
  invHadc3.Init.Oversampling.Ratio = 16;
  invHadc3.Init.Oversampling.RightBitShift = ADC_RIGHTBITSHIFT_4;
  invHadc3.Init.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;
  invHadc3.Init.Oversampling.OversamplingStopReset = ADC_REGOVERSAMPLING_CONTINUED_MODE;
  if (HAL_ADC_Init(&invHadc3) != HAL_OK)
  {
	  invAdc3Error = true;
	  	  	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = LL_ADC_SAMPLINGTIME_387CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  sConfig.OffsetSignedSaturation = DISABLE;
  if (HAL_ADC_ConfigChannel(&invHadc3, &sConfig) != HAL_OK)
  {
	  invAdc3Error = true;
	  	  	  	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&invHadc3, &sConfig) != HAL_OK)
  {
	  invAdc3Error = true;
	  	  	  	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = ADC_REGULAR_RANK_3;
  if (HAL_ADC_ConfigChannel(&invHadc3, &sConfig) != HAL_OK)
  {
	  invAdc3Error = true;
	  	  	  	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_5;
  sConfig.Rank = ADC_REGULAR_RANK_4;
  if (HAL_ADC_ConfigChannel(&invHadc3, &sConfig) != HAL_OK)
  {
	  invAdc3Error = true;
	  	  	  	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_6;
  sConfig.Rank = ADC_REGULAR_RANK_5;
  if (HAL_ADC_ConfigChannel(&invHadc3, &sConfig) != HAL_OK)
  {
	  invAdc3Error = true;
	  	  	  	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_7;
  sConfig.Rank = ADC_REGULAR_RANK_6;
  if (HAL_ADC_ConfigChannel(&invHadc3, &sConfig) != HAL_OK)
  {
	  invAdc3Error = true;
	  	  	  	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_13;
  sConfig.Rank = ADC_REGULAR_RANK_7;
  if (HAL_ADC_ConfigChannel(&invHadc3, &sConfig) != HAL_OK)
  {
	  invAdc3Error = true;
	  	  	  	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_14;
  sConfig.Rank = ADC_REGULAR_RANK_8;
  if (HAL_ADC_ConfigChannel(&invHadc3, &sConfig) != HAL_OK)
  {
	  invAdc3Error = true;
	  	  	  	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_15;
  sConfig.Rank = ADC_REGULAR_RANK_9;
  if (HAL_ADC_ConfigChannel(&invHadc3, &sConfig) != HAL_OK)
  {
	  invAdc3Error = true;
	  	  	  	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_16;
  sConfig.Rank = ADC_REGULAR_RANK_10;
  if (HAL_ADC_ConfigChannel(&invHadc3, &sConfig) != HAL_OK)
  {
	  invAdc3Error = true;
	  	  	  	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_VBAT;
  sConfig.Rank = ADC_REGULAR_RANK_11;
  if (HAL_ADC_ConfigChannel(&invHadc3, &sConfig) != HAL_OK)
  {
	  invAdc3Error = true;
	  	  	  	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
  sConfig.Rank = ADC_REGULAR_RANK_12;
  if (HAL_ADC_ConfigChannel(&invHadc3, &sConfig) != HAL_OK)
  {
	  invAdc3Error = true;
	  	  	  	return;
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_VREFINT;
  sConfig.Rank = ADC_REGULAR_RANK_13;
  sConfig.SamplingTime = LL_ADC_SAMPLINGTIME_387CYCLES_5;
  if (HAL_ADC_ConfigChannel(&invHadc3, &sConfig) != HAL_OK)
  {
	  invAdc3Error = true;
	  	  	  	return;
  }
  /* USER CODE BEGIN ADC3_Init 2 */

  /* USER CODE END ADC3_Init 2 */

}




static volatile void *memcpy_v(volatile void *restrict dest, const volatile void *restrict src, size_t n) {
    const volatile unsigned char *src_c = src;
    volatile unsigned char *dest_c      = dest;

    while (n > 0) {
        n--;
        dest_c[n] = src_c[n];
    }
    return  dest;
}
/** ADC DMA Interrupt Handlers
 *
 * @param[in] ADC_HandleTypeDef* adc
 *
 * @return void
 */

/**
  * @brief This function handles DMA1 stream0 global interrupt.
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	if(hadc == &invHadc1){
		memcpy_v(&invAdcValues[INV_ADC1_BUFFER_START],invAdc1ValuesDMA,INV_ADC1_CHANNELS*sizeof(uint32_t));
		invAdc1ValuesReady = true;
		invAdc1Error = false;
		TIME_SECTION_END(1);
	}
	if(hadc == &invHadc2){
		memcpy_v(&invAdcValues[INV_ADC2_BUFFER_START],invAdc2ValuesDMA,INV_ADC2_CHANNELS*sizeof(uint32_t));
		invAdc2ValuesReady = true;
		invAdc2Error = false;
		TIME_SECTION_END(2);
	}
	if(hadc == &invHadc3){
		memcpy_v(&invAdcValues[INV_ADC3_BUFFER_START],invAdc3ValuesDMA,INV_ADC3_CHANNELS*sizeof(uint32_t));
		invAdc3ValuesReady = true;
		invAdc3Error = false;
		TIME_SECTION_END(3);
	}

}



#endif


