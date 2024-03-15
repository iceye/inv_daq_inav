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

#include "target/INNOVAVIONICSH743_3_1_1/target.h"


#include <stdbool.h>
#include <stdint.h>

#include "platform.h"
#include "build/debug.h"
#include "drivers/serial.h"
#include "drivers/serial_softserial.h"

#include "fc/fc_init.h"

#include "scheduler/scheduler.h"
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
    pinioBoxConfigMutable()->permanentId[0] = BOX_PERMANENT_ID_USER1;
    pinioBoxConfigMutable()->permanentId[1] = BOX_PERMANENT_ID_USER2;
    beeperConfigMutable()->pwmMode = false;

    boardAlignmentMutable()->pitchDeciDegrees   = 0;
    boardAlignmentMutable()->rollDeciDegrees    = 0;

    accelerometerConfigMutable()->acc_hardware = ACC_LSM6DXX;

    compassConfigMutable()->mag_hardware = MAG_LIS3MDL;
    compassConfigMutable()->mag_align = CW0_DEG;

    barometerConfigMutable()->baro_hardware = BARO_LPS33W;

    pitotmeterConfigMutable()->pitot_hardware = PITOT_DLHR30G;

    // UART1 is in the plug for vtx
    serialConfigMutable()->portConfigs[findSerialPortIndexByIdentifier(SERIAL_PORT_USART1)].functionMask = FUNCTION_MSP_OSD;
    serialConfigMutable()->portConfigs[findSerialPortIndexByIdentifier(SERIAL_PORT_USART5)].functionMask = FUNCTION_GPS;
    serialConfigMutable()->portConfigs[findSerialPortIndexByIdentifier(SERIAL_PORT_USART2)].functionMask = FUNCTION_RS485; // IFDNET SERVO



}

#ifdef SOFTSERIAL_LOOPBACK
serialPort_t *loopbackPort;
#endif


static void loopbackInit(void)
{
#ifdef SOFTSERIAL_LOOPBACK
    loopbackPort = softSerialLoopbackPort();
    serialPrint(loopbackPort, "LOOPBACK\r\n");
#endif
}

static void processLoopback(void)
{
#ifdef SOFTSERIAL_LOOPBACK
    if (loopbackPort) {
        uint8_t bytesWaiting;
        while ((bytesWaiting = serialRxBytesWaiting(loopbackPort))) {
            uint8_t b = serialRead(loopbackPort);
            serialWrite(loopbackPort, b);
        };
    }
#endif
}

#if defined(SITL_BUILD)
int main(int argc, char *argv[])
{
    parseArguments(argc, argv);
#else
int main(void)
{
#endif
    init();
    loopbackInit();

    while (true) {
        scheduler();
        processLoopback();
    }
}


