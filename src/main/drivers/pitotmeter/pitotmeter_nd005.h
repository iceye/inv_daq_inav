/*
 * pitotmeter_nd005.h
 *
 *  Created on: Apr 7, 2024
 *      Author: sandro.bottoni
 */

#ifndef SRC_DRIVERS_PITOTMETER_PITOTMETER_ND005_H_
#define SRC_DRIVERS_PITOTMETER_PITOTMETER_ND005_H_
#include <stdint.h>
#include <stdbool.h>
#include "pitotmeter.h"

/* Pressure Enumerator

`PSI05` is 0.5 PSI, etc. Can't have punctuation in identifiers.

Enumerator are handy when dealing with values we only want to take certain
values and nothing else. In this case we are using an enumerator to store
the valid pressure settings for the sensor.

We don't have to assign a type for the enumerator data itself but I chose
to set this enumerator value to be stored as an eight bit unsigned integer.
Nor do we have to assign values for each option as I have, however it makes
sense for us in a lot of our application when using these to describe
registers to alight the options to their value, otherwise the compiler will
assign whatever it feels like.
*/
typedef enum {
    ND005_PSI05 = 0b010,
	ND005_PSI08 = 0b011,
	ND005_PSI10 = 0b100,
	ND005_PSI20 = 0b101,
	ND005_PSI40 = 0b110,
	ND005_PSI50 = 0b111
} nd005_PressureRangeSettings_t;


typedef enum{
	ND005_BW_1HZ = 0b000,
	ND005_BW_2HZ = 0b001,
	ND005_BW_5HZ = 0b010,
	ND005_BW_10HZ = 0b011,
	ND005_BW_20HZ = 0b100,
	ND005_BW_50HZ = 0b101,
	ND005_BW_100HZ = 0b110,
	ND005_BW_200HZ = 0b111,
} nd005_BandwidthSettings_t;

typedef enum {
	ND005_NOTCH_OFF = 0,
	ND005_NOTCH_ON = 1
} nd005_NotchFilterSettings_t;

typedef enum {
	ND005_WATCHDOG_OFF = 0,
	ND005_WATCHDOG_ON = 1
} nd005_WatchdogSettings_t;

typedef struct {
	uint8_t notch: 1;
	uint8_t bwlimit: 3;
	uint8_t watchdog: 1;
	uint8_t range: 3;

} nd005moderegs_t;


#define ND005_RATE_CONTROL_AUTO 0x00;
#define ND005_RATE_CONTROL_HZ 444;



bool nd005Detect(pitotDev_t *pitot);

#endif /* SRC_DRIVERS_PITOTMETER_PITOTMETER_ND005_H_ */
