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
 
};

const int timerHardwareCount = 0;
