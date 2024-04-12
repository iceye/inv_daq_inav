/*
 * This file is part of INAV.
 *
 * INAV is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * INAV is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with INAV.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>

#include "platform.h"

#include "drivers/bus.h"
#include "drivers/io.h"
#include "drivers/pwm_mapping.h"
#include "drivers/timer.h"
#include "drivers/pinio.h"
#include "drivers/sensor.h"

/*
BUSDEV_REGISTER_SPI_TAG(busdev_mpu6000,  DEVHW_MPU6000,  MPU6000_SPI_BUS,   MPU6000_CS_PIN,   NONE,   0,  DEVFLAGS_NONE,  IMU_MPU6000_ALIGN);
BUSDEV_REGISTER_SPI_TAG(busdev_icm42688, DEVHW_ICM42605, MPU6000_SPI_BUS,   MPU6000_CS_PIN,   NONE,   0,  DEVFLAGS_NONE,  IMU_MPU6000_ALIGN);
BUSDEV_REGISTER_SPI_TAG(busdev_icm20602, DEVHW_MPU6500,  MPU6500_SPI_BUS,   MPU6500_CS_PIN,   NONE,   1,  DEVFLAGS_NONE,  IMU_MPU6500_ALIGN);
BUSDEV_REGISTER_SPI_TAG(busdev_icm42605, DEVHW_ICM42605, ICM42605_SPI_BUS,  ICM42605_CS_PIN,  NONE,  2,  DEVFLAGS_NONE,  IMU_ICM42605_ALIGN);
*/

timerHardware_t timerHardware[] = {
		DEF_TIM(TIM4, CH1, PD12, TIM_USE_SERVO, 0, 0),   // UNCONNECTED BUT USEFUL TO HAVE THE SW WORKING WITH IT - MOTOR
		DEF_TIM(TIM4, CH2, PD13, TIM_USE_SERVO, 0, 0),   // UNCONNECTED BUT USEFUL TO HAVE THE SW WORKING WITH IT - PITCH
		DEF_TIM(TIM4, CH3, PD14, TIM_USE_SERVO, 0, 0),   // UNCONNECTED BUT USEFUL TO HAVE THE SW WORKING WITH IT - ROLL
		DEF_TIM(TIM4, CH4, PD15, TIM_USE_SERVO, 0, 0),   // UNCONNECTED BUT USEFUL TO HAVE THE SW WORKING WITH IT - YAW
		//DEF_TIM(TIM3, CH1, PB4,  TIM_USE_SERVO, 0, 0),   // UNCONNECTED BUT USEFUL TO HAVE THE SW WORKING WITH IT - YAW
	//	DEF_TIM(TIM1, CH3, PA10, TIM_USE_SERVO, 0, 0),   // UNCONNECTED BUT USEFUL TO HAVE THE SW WORKING WITH IT - YAW
		DEF_TIM(TIM2, CH2, PB3,  TIM_USE_MOTOR, 0, 0),   // UNCONNECTED BUT USEFUL TO HAVE THE SW WORKING WITH IT - YAW

};

/*
 *
 * AuxCounter are on:
 * RPM: TIM12 CH2 PE9
 * RPM_AUX/FUEL FLOW: TIM17 CH1 PF7
 * AUX 4: TIM8 CH3 PI7
 * AUX 4: TIM5 CH1 PH10
 *
 *
 * FREE TIMER PINS ARE
 * TIM16 ch 1 PF6
//TIM17 ch 1 PF7
TIM1 ch 1 PE9
//TIM12 CH 1 PH6
//TIM5 ch 3 PH12
TIM4 ch 1 PD12
TIM4 ch2 PD13
TIM4 ch3 PD14
TIM4 ch4 PD15
TIM1 ch1 PA8
TIM1 ch3 PA10
//TIM5 ch4 PI0
TIM2 CH2 PB3
TIM3 ch1 PB4
//TIM8 ch1 PI5
 */

const int timerHardwareCount = 5;
