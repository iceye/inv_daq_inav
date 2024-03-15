/*
 * inv_data_calculators.c
 *
 *  Created on: Mar 13, 2024
 *      Author: sandro.bottoni
 */

#include <innovavionics/inv_data_calculators.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

bool invCalculatorFloatPlain(invElement_t *el, void *val){
	el->_valueF = *((float*)val);
	return true;
}

bool invCalculatorIntPlain(invElement_t *el, void *val){
	el->_valueI = *((int32_t*)val);
	return true;
}

bool invCalculatorUIntPlain(invElement_t *el, void *val){
	el->_valueI = *((uint32_t*)val);
	return true;
}

bool invCalculatorLongPlain(invElement_t *el, void *val){
	el->_valueL = *((int64_t*)val);
	return true;
}

bool invCalculatorULongPlain(invElement_t *el, void *val){
	el->_valueL = *((uint64_t*)val);
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

bool invCalculatorStringPlain(invElement_t *el, void *val) {
	if (el->_valueS != NULL){
		free(el->_valueS);
	}
	el->_valueS = (char *)malloc(strlen((char*)val) + 1);
	strcpy(el->_valueS, (char*)val);
	return true;
}


