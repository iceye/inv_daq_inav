/*
 * inv_canbus.h
 *
 *  Created on: Apr 3, 2024
 *      Author: sandro.bottoni
 */

#ifndef SRC_INNOVAVIONICS_INV_CAN_H_
#define SRC_INNOVAVIONICS_INV_CAN_H_

#include "stm32h7xx_hal.h"
#include "build_config.h"
#include "inv_data.h"
#include "dma.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define TASK_INV_CAN_HZ 100

#ifdef __cplusplus
extern "C" {
#endif

void invCanInit();
bool invCanStart();
void invDeCanInit();
void invCanProcess();


#ifdef __cplusplus
}
#endif
#endif /* SRC_INNOVAVIONICS_INV_CAN_H_ */
