/*
 * inv_params.c
 *
 *  Created on: Mar 14, 2024
 *      Author: sandro.bottoni
 */

#include "inv_params.h"


bool _isInvElementEnabled(invElement_t *el){
	return el->_enabled == 1;
}

bool _isInvElementTimeout(invElement_t *el){
	return el->_hasTimeout == 1 && el->_timeout == 1;
}

bool _isInvElementReadable(invElement_t *el){
	return el->_readable == 1;
}

bool _isInvElementWritable(invElement_t *el){
	return el->_writable == 1;
}

bool _isInvElementInt(invElement_t *el){
	return el->_intvalue == 1;
}

bool _isInvElementLong(invElement_t *el){
	return el->_longvalue == 1;
}

bool _isInvElementByte(invElement_t *el){
	return el->_bytevalue == 1;
}

bool _isInvElementFloat(invElement_t *el){
	return el->_floatvalue == 1;
}

bool _isInvElementBool(invElement_t *el){
	return el->_boolvalue == 1;
}

bool _isInvElementString(invElement_t *el){
	return el->_stringvalue == 1;
}

bool _isInvElementUnsigned(invElement_t *el) {
	return el->_unsigned == 1;
}
