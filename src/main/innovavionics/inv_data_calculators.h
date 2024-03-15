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
#include <stdint.h>
#include <stdbool.h>


bool invCalculatorFloatPlain(invElement_t *el, void *val);

bool invCalculatorIntPlain(invElement_t *el, void *val);

bool invCalculatorUIntPlain(invElement_t *el, void *val);

bool invCalculatorLongPlain(invElement_t *el, void *val);

bool invCalculatorULongPlain(invElement_t *el, void *val);

bool invCalculatorBytePlain(invElement_t *el, void *val);

bool invCalculatorBoolPlain(invElement_t *el, void *val);

bool invCalculatorStringPlain(invElement_t *el, void *val);


#ifdef __cplusplus
}
#endif

#endif /* SRC_INNOVAVIONICS_INV_DATA_CALCULATORS_H_ */
