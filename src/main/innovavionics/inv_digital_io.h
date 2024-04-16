/*
 * inv_digital.h
 *
 *  Created on: Apr 12, 2024
 *      Author: sandro.bottoni
 */

#ifndef SRC_INNOVAVIONICS_INV_DIGITAL_H_
#define SRC_INNOVAVIONICS_INV_DIGITAL_H_

#define TASK_INV_DIGITALIO_HZ 10

#include "inv_params.h"
#include "inv_data.h"
#include "drivers/timer.h"
#include "drivers/pinio.h"
#include "drivers/io.h"
#include "drivers/exti.h"
#include "drivers/nvic.h"
#include "target.h"
#include <stdint.h>
#include <stdbool.h>


enum digitalio_counter_map{
	DIGITALIO_RPM_ENGINE,
	DIGITALIO_RPM_PROP_FUEL_FLOW,
	DIGITALIO_AUX3,
	DIGITALIO_AUX4,
	DIGITALIO_COUNTER_MAP_COUNT
};




typedef struct digitalio_counter_e{
	//TIMER
	bool enabled;
	IO_t *pin;
	const timerHardware_t timer;
	TCH_t *tch;

	timerCallbacks_t timerCallbacks;
	extiCallbackRec_t extiCallback;
	uint32_t timerClock;

	uint32_t counterAccumulator;
	uint16_t counterOverflowAccCounter;
	bool counterOverflowAccOverflow;
	uint32_t pinRisingCounter;
	uint32_t pinRisingLast;
	bool resetCycle;
	float lastValue;
} digitalio_counter_t;


void invDigitalIOInit(void);
bool invDigitalIOStart(void);
void invDeDigitalIOInit(void);
void invDigitalIOCheck(void);


#endif /* SRC_INNOVAVIONICS_INV_DIGITAL_H_ */
