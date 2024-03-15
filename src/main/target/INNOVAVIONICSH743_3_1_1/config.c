/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>

#include "platform.h"

#include "fc/fc_msp_box.h"
#include "fc/config.h"
#include "io/piniobox.h"
#include "sensors/boardalignment.h"
#include "sensors/barometer.h"
#include "sensors/compass.h"
#include "sensors/acceleration.h"
#include "sensors/pitotmeter.h"
#include "io/serial.h"

void targetConfiguration(void)
{
#ifdef STM32IDE
    beeperConfigMutable()->pwmMode = false;

    boardAlignmentMutable()->pitchDeciDegrees   = 0;
    boardAlignmentMutable()->rollDeciDegrees    = 0;
    boardAlignmentMutable()->yawDeciDegrees = 900;

    accelerometerConfigMutable()->acc_hardware = ACC_LSM6DXX;
    
    compassConfigMutable()->mag_hardware = MAG_LIS3MDL;
    compassConfigMutable()->mag_align = CW180_DEG;
   
    barometerConfigMutable()->baro_hardware = BARO_LPS33W;

    pitotmeterConfigMutable()->pitot_hardware = PITOT_DLHR30G;

    // UART1 is in the plug for vtx
    serialConfigMutable()->portConfigs[findSerialPortIndexByIdentifier(SERIAL_PORT_USART1)].functionMask = FUNCTION_MSP;
    serialConfigMutable()->portConfigs[findSerialPortIndexByIdentifier(SERIAL_PORT_USART1)].msp_baudrateIndex = BAUD_115200;


    serialConfigMutable()->portConfigs[findSerialPortIndexByIdentifier(SERIAL_PORT_USART5)].functionMask = FUNCTION_GPS;
    serialConfigMutable()->portConfigs[findSerialPortIndexByIdentifier(SERIAL_PORT_USART5)].msp_baudrateIndex = BAUD_38400;


    serialConfigMutable()->portConfigs[findSerialPortIndexByIdentifier(SERIAL_PORT_USART2)].functionMask = FUNCTION_RS485; // IFDNET SERVO
#endif
    

}
