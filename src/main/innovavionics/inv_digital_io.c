/*
 * inv_digital.c
 *
 *  Created on: Apr 12, 2024
 *      Author: sandro.bottoni
 */

#include "inv_digital_io.h"
#include "drivers/time.h"
#include "scheduler/protothreads.h"

//TIM12 with this settings should span between ~109k rpm and ~27rpm,
#define CLOCK_PRESCALER 15
#define TIMER_COUNTER_MAX 65535
#define TIMER_MAX_OVERFLOWS 512
#define MAX_RPM		15000

#define TIMER_DETECT_FALLING_EDGE false
#define TIMER_DETECT_RISING_EDGE true
#define TIMER_SKIP_TIMER_CLOCK_CYCLES 0 //MAX IS 15

const uint16_t digitalio_minSignalDelay = 1000000/((MAX_RPM/60.0)*1.3);


digitalio_counter_t digitalio_counters[DIGITALIO_COUNTER_MAP_COUNT] = {
		{.enabled = true,  .pin = NULL, .timer = DEF_TIM(TIM12, CH2, PH9, TIM_USE_COUNTER, 0, 0) , .tch = NULL, .counterAccumulator = 0, .counterOverflowAccCounter = 0, .counterOverflowAccOverflow = false, .pinRisingCounter = 0, .pinRisingLast = 0, .resetCycle = true, .lastValue = 0},
		{.enabled = false,  .pin = NULL, .timer = DEF_TIM(TIM17, CH1, PB9, TIM_USE_COUNTER, 0, 0), .tch = NULL, .counterAccumulator = 0, .counterOverflowAccCounter = 0, .counterOverflowAccOverflow = false, .pinRisingCounter = 0, .pinRisingLast = 0, .resetCycle = true, .lastValue = 0},
		{.enabled = false, .pin = NULL, .timer = NULL, .tch = NULL, .counterAccumulator = 0, .counterOverflowAccCounter = 0, .counterOverflowAccOverflow = false, .pinRisingCounter = 0, .pinRisingLast = 0, .resetCycle = true, .lastValue = 0},
		{.enabled = false, .pin = NULL, .timer = NULL, .tch = NULL, .counterAccumulator = 0, .counterOverflowAccCounter = 0, .counterOverflowAccOverflow = false, .pinRisingCounter = 0, .pinRisingLast = 0, .resetCycle = true, .lastValue = 0}
};

uint8_t digitalio_invDataMap[DIGITALIO_COUNTER_MAP_COUNT] = { INV_RPM_ENGINE,
		INV_RPM_ROTOR, INV_FUELFLOW, 0 };


static inline uint8_t getDigitalIOCounterIndexByTch(TCH_t *tch) {
	for (uint8_t i = 0; i < DIGITALIO_COUNTER_MAP_COUNT; i++) {
		if (digitalio_counters[i].tch == tch) {
			return i;
		}
	}
	return 127;
}

static inline uint8_t getDigitalIOCounterIndexByExtiCallbackRec(extiCallbackRec_t *cb) {
	for (uint8_t i = 0; i < DIGITALIO_COUNTER_MAP_COUNT; i++) {
		if (&digitalio_counters[i].extiCallback == cb) {
			return i;
		}
	}
	return 127;
}

void onDigitalIOPinChange(TCH_t * tch, uint32_t capture)
{
	//__HAL_TIM_CLEAR_FLAG(tch->timCtx->timHandle, TIM_FLAG_UPDATE);
	__HAL_TIM_SET_COUNTER(tch->timCtx->timHandle, 0);
	uint8_t counterIndex = getDigitalIOCounterIndexByTch(tch);
	if(counterIndex>DIGITALIO_COUNTER_MAP_COUNT){
		return;
	}

	if(digitalio_counters[counterIndex].resetCycle){
		digitalio_counters[counterIndex].counterAccumulator = 0;
		digitalio_counters[counterIndex].pinRisingCounter = 0;
		digitalio_counters[counterIndex].counterOverflowAccCounter = 0;
		digitalio_counters[counterIndex].counterOverflowAccOverflow = false;
		digitalio_counters[counterIndex].resetCycle = false;
		digitalio_counters[counterIndex].pinRisingLast = micros();
		return;
	}
	if(digitalio_counters[counterIndex].counterOverflowAccOverflow || digitalio_counters[counterIndex].pinRisingLast+digitalio_minSignalDelay>micros()){
		//Seems a debounce, max ~60k rpm
		return;
	}
	digitalio_counters[counterIndex].pinRisingLast = micros();
	digitalio_counters[counterIndex].counterAccumulator += (digitalio_counters[counterIndex].counterOverflowAccCounter*TIMER_COUNTER_MAX) + capture;
	digitalio_counters[counterIndex].pinRisingCounter++;
	digitalio_counters[counterIndex].counterOverflowAccCounter = 0;
}

void extiDigitalIOCallback(extiCallbackRec_t *self){
	uint8_t counterIndex = getDigitalIOCounterIndexByExtiCallbackRec(self);
	if(counterIndex>DIGITALIO_COUNTER_MAP_COUNT){
		return;
	}
	onDigitalIOPinChange(digitalio_counters[counterIndex].tch, digitalio_counters[counterIndex].tch->timCtx->timHandle->Instance->CNT);
}

void onDigitalIOOverflow(TCH_t * tch, uint32_t capture)
{
    UNUSED(capture);
	uint8_t counterIndex = getDigitalIOCounterIndexByTch(tch);
	if(counterIndex>DIGITALIO_COUNTER_MAP_COUNT){
		return;
	}
   // __HAL_TIM_CLEAR_FLAG(tch->timCtx->timHandle, TIM_FLAG_UPDATE);
    if(digitalio_counters[counterIndex].counterOverflowAccOverflow == true){
    	return;
    }

    if(digitalio_counters[counterIndex].counterOverflowAccCounter > TIMER_MAX_OVERFLOWS){
    	digitalio_counters[counterIndex].counterOverflowAccCounter = 0;
    	digitalio_counters[counterIndex].counterOverflowAccOverflow = true;
    }
    else{
    	digitalio_counters[counterIndex].counterOverflowAccCounter++;
    }

}




void invDigitalIOInit(){

	digitalio_counters[DIGITALIO_RPM_ENGINE].pin = IOGetByTag(DEFIO_TAG(RPMA_PIN));
	digitalio_counters[DIGITALIO_RPM_ENGINE].tch = timerGetTCH(&digitalio_counters[DIGITALIO_RPM_ENGINE].timer);

	IOInit(digitalio_counters[DIGITALIO_RPM_ENGINE].pin, OWNER_INVDIGITALIO, RESOURCE_INPUT, RESOURCE_INDEX(21));
	IOConfigGPIOAF(digitalio_counters[DIGITALIO_RPM_ENGINE].pin, IOCFG_AF_PP_UP, GPIO_AF2_TIM12);//digitalio_RpmATimer->alternateFunction);
}


bool invDigitalIOStart(){
	uint32_t clock = timerClock(digitalio_counters[DIGITALIO_RPM_ENGINE].timer.tim);
	digitalio_counters[DIGITALIO_RPM_ENGINE].timerClock =  clock / CLOCK_PRESCALER;

	timerConfigure(digitalio_counters[DIGITALIO_RPM_ENGINE].tch, TIMER_COUNTER_MAX, digitalio_counters[DIGITALIO_RPM_ENGINE].timerClock);
	HAL_TIM_Base_Stop(digitalio_counters[DIGITALIO_RPM_ENGINE].tch->timCtx->timHandle);




	timerChInitCallbacks(&digitalio_counters[DIGITALIO_RPM_ENGINE].timerCallbacks, &digitalio_counters[DIGITALIO_RPM_ENGINE].counterAccumulator, onDigitalIOPinChange, onDigitalIOOverflow);
	timerChConfigCallbacks(digitalio_counters[DIGITALIO_RPM_ENGINE].tch, &digitalio_counters[DIGITALIO_RPM_ENGINE].timerCallbacks);
	timerChConfigIC(digitalio_counters[DIGITALIO_RPM_ENGINE].tch, TIMER_DETECT_FALLING_EDGE, TIMER_SKIP_TIMER_CLOCK_CYCLES);
	timerChCaptureEnable(digitalio_counters[DIGITALIO_RPM_ENGINE].tch);
	timerEnable(digitalio_counters[DIGITALIO_RPM_ENGINE].tch);
	digitalio_counters[DIGITALIO_RPM_ENGINE].resetCycle = true;
	EXTIHandlerInit(&digitalio_counters[DIGITALIO_RPM_ENGINE].extiCallback,extiDigitalIOCallback);
	EXTIConfigDetail(digitalio_counters[DIGITALIO_RPM_ENGINE].pin, &digitalio_counters[DIGITALIO_RPM_ENGINE].extiCallback, NVIC_PRIO_TIMER, IOCFG_AF_PP_UP, GPIO_MODE_IT_RISING, GPIO_SPEED_FREQ_LOW, GPIO_PULLUP);

	return true;
}

void invDeDigitalIOInit(){
	timerChCaptureDisable(digitalio_counters[DIGITALIO_RPM_ENGINE].tch);
}

PROTOTHREAD(invDigitalIOCheck)
{
	//ptBegin(invDigitalIOCheck);

	for (uint8_t i = 0; i < DIGITALIO_COUNTER_MAP_COUNT; i++) {
		if (digitalio_counters[i].enabled) {
			if(digitalio_counters[i].counterOverflowAccOverflow == false && (digitalio_counters[i].resetCycle == true || digitalio_counters[i].pinRisingCounter==0)){
				//Nothing to do here, freq is lower than cheching...giving more time to IT to receive other pulses
			}
			else{
				if (digitalio_counters[i].counterOverflowAccOverflow == true || digitalio_counters[i].pinRisingCounter == 0 || digitalio_counters[i].counterAccumulator == 0) {
					digitalio_counters[i].lastValue = 0;
				}
				else{
					digitalio_counters[i].lastValue = 60.0f * ((float)digitalio_counters[i].timerClock/(float)( (float)digitalio_counters[i].counterAccumulator / (float)digitalio_counters[i].pinRisingCounter ));
				}
				if(digitalio_counters[i].counterOverflowAccOverflow == true || digitalio_counters[i].pinRisingCounter>0 || digitalio_counters[i].lastValue > 0.0f){
					uint32_t value =  digitalio_counters[i].lastValue*1000;
					invDataStoreValByConf(digitalio_invDataMap[i], &value);
					invDataStoreValByConf(INV_RPM_ROTOR, &value);
					//invDataStoreValUInt(INV_RPM_ROTOR, digitalio_counters[i].lastValue*1000);
					digitalio_counters[i].resetCycle = true;
				}
			}
		}
	}

	//ptEnd(0);
}

