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


#pragma once
#ifndef INNOVAVIONICSH743_TARGET
#define INNOVAVIONICSH743_TARGET
#ifdef STM32IDE
    #define TARGET_BOARD_IDENTIFIER "H743"
    #define STM32H7


#define __TARGET__ "INNOVAVIONICSH743_3_1_1"
#define __REVISION__ 0
#endif

#if defined(INNOVAVIONICSH743_3_1_1HD)
  #define USBD_PRODUCT_STRING     "INNOVAVIONICSH743_3_1_1HD"
#else
  #define USBD_PRODUCT_STRING     "INNOVAVIONICSH743_3_1_1"
#endif


#define USE_TARGET_CONFIG

#define MAX_MPU_REGIONS 16


#define LED0                    PA15
#define LED1                    PH15

// *************** SDIO SD BLACKBOX*******************
#define USE_SDCARD
#define USE_SDCARD_SDIO
#define USE_SDCARD_SDIO_CACHE
#define SDCARD_SDIO_DEVICE      SDIODEV_1
#define SDCARD_SDIO_4BIT

#define ENABLE_BLACKBOX_LOGGING_ON_SDCARD_BY_DEFAULT

// *******************************************************
// *************** USING I2C AND SPI buses ***************
// *******************************************************
#define USE_SPI
#define USE_I2C

#define USE_SPI_DEVICE_1
#define SPI1_SCK_PIN            PG11
#define SPI1_MISO_PIN           PG9
#define SPI1_MOSI_PIN           PD7

#define USE_SPI_DEVICE_4
#define SPI4_SCK_PIN            PE12
#define SPI4_MISO_PIN           PE5
#define SPI4_MOSI_PIN           PE6

#define USE_I2C_DEVICE_1
// I2C1 can be used for external device (ie compass, accgyro, etc)
#define I2C1_SCL                PB8
#define I2C1_SDA                PB7

#define USE_I2C_DEVICE_2
#define I2C2_SCL                PF1
#define I2C2_SDA                PF0

#define USE_I2C_DEVICE_3
// I2C1 can be used for external device (ie compass, accgyro, etc)
#define I2C3_SCL                PH7
#define I2C3_SDA                PH8


#define USE_I2C_DEVICE_4
#define I2C4_SCL                PH11
#define I2C4_SDA                PF15

// *******************************************************
// *************** DIGITAL IN PINS ***********************
// *******************************************************
#define USE_COUNTER


#define USE_DIGITAL_IN


// *******************************************************
// ***************** IMU/AHRS DEVICES ********************
// *******************************************************

// *************** IMU0 LSM6DSRTR ON SPI 1 ****************

#define USE_IMU_LSM6DXX
#define LSM6DXX_SPI_BUS         BUS_SPI1
#define LSM6DXX_CS_PIN          PG10
#define LSM6DXX_INT1_PIN        PG2
#define IMU_LSM6DXX_ALIGN		CW0_DEG



// *************** MAG0 LIS3MDLTR ON I2C3 **************

#define USE_MAG
#define MAG_I2C_BUS             BUS_I2C3
#define USE_MAG_LIS3MDL
#define LIS3MDL_I2C_BUS         BUS_I2C3


// *************** PITOT0 DLHR_L30G_E1BD_C/I_NAV8 ON I2C2 **************
#define PITOT_I2C_BUS            BUS_I2C2
//#define USE_PITOT_DLHRL30G
#define PITOT_EOC_PIN            PG3
#define USE_PITOT_ND005
#define ND005_I2C_BUS            BUS_I2C2

// *************** BARO0 LPS33WTR ON I2C1 **************
#define USE_BARO
#define BARO_I2C_BUS            BUS_I2C1
#define LPS33W_I2C_BUS_ADDR     0x5C
#define USE_BARO_LPS33W

// *************** TEMP0 HDC1080D ON I2C1 **************
#define USE_TEMPHUM
#define TEMPERATURE_I2C_BUS     BUS_I2C1
#define HDC1080D_I2C_BUS_ADDR   0x40
#define USE_TEMPHUM_HDC1080D

// *************** EGTs MAX31855KASA+T ON SPI4 **************
#define USE_EGT
#define EGT_SPI_BUS            	BUS_SPI4
#define EGT1_CS_PIN             PE15
#define EGT2_CS_PIN             PE14
#define EGT3_CS_PIN             PE13
#define EGT4_CS_PIN             PE11
#define USE_EGT_MAX31855K


// *************** UART *****************************
#define USE_VCP

#define USE_UART1
#define UART1_TX_PIN            PB14
#define UART1_RX_PIN            PB15

#define USE_UART2
#define UART2_RS485
#define UART2_TX_PIN            PD5
#define UART2_RX_PIN            PD6
#define UART2_DE_PIN            PD4

#define USE_UART3
#define UART3_TX_PIN            PB10
#define UART3_RX_PIN            PB11

#define USE_UART4
#define UART4_TX_PIN            PH13
#define UART4_RX_PIN            PH14

#define USE_UART5
#define UART5_TX_PIN            PB6
#define UART5_RX_PIN            PB5

#define USE_UART6
#define UART6_TX_PIN            PC6
#define UART6_RX_PIN            PC7

#define USE_UART7
#define UART7_TX_PIN            PE8
#define UART7_RX_PIN            PE7

#define USE_UART8
#define UART8_TX_PIN            PE1
#define UART8_RX_PIN            PE0



#define SERIAL_PORT_COUNT       9

#define DEFAULT_RX_TYPE         RX_TYPE_SERIAL
#define SERIALRX_PROVIDER       SERIALRX_CRSF
#define SERIALRX_UART           SERIAL_PORT_USART1


// *************** ADC *****************************
#define USE_INNOVAVIONICS_ADC
//No configuration yet


// *************** COUNTERS/FREQ METERS ************************

#define RPMA_PIN                    PE9
#define RPMA_TIM                    TIM12    //TIM1, TIM2, TIM3, TIM4, TIM5, TIM8, TIM12, TIM13, TIM14, ...
#define RPMA_TIM_CH                 2       //1,2,3,4   
#define RPMA_TIM_PRSC               65535   //16bit
#define RPMA_TIM_COUNT              65535   //16bit
#define RPMA_TIM_CLK_DIV            1       //1,2,4
#define RPMA_TIM_MODE               DOWN    //UP, DOWN, CENTER
#define RPMA_TIM_POL                RISING  //RISING, FALLING, BOTH
#define RPMA_TIM_PRSC_IN_DIV        1      //1,2,4,8
#define RPMA_TIM_IN_FILTER          0     //4bits 0-15


#define FUELFLOWA_PIN               PF7
#define FUELFLOWA_TIM               TIM17    //TIM1, TIM2, TIM3, TIM4, TIM5, TIM8, TIM12, TIM13, TIM14, ...
#define FUELFLOWA_TIM_CH            1       //1,2,3,4   
#define FUELFLOWA_TIM_PRSC          65535   //16bit
#define FUELFLOWA_TIM_COUNT         65535   //16bit
#define FUELFLOWA_TIM_CLK_DIV       1       //1,2,4
#define FUELFLOWA_TIM_MODE          DOWN    //UP, DOWN, CENTER
#define FUELFLOWA_TIM_POL           RISING  //RISING, FALLING, BOTH
#define FUELFLOWA_TIM_PRSC_IN_DIV   1      //1,2,4,8
#define FUELFLOWA_TIM_IN_FILTER     0     //4bits 0-15


#define AUXCOUNTER1_PIN             PE9
#define AUXCOUNTER1_TIM             TIM1    //TIM1, TIM2, TIM3, TIM4, TIM5, TIM8, TIM12, TIM13, TIM14, ...
#define AUXCOUNTER1_TIM_CH          1       //1,2,3,4
#define AUXCOUNTER1_TIM_PRSC        65535   //16bit
#define AUXCOUNTER1_TIM_COUNT       65535   //16bit
#define AUXCOUNTER1_TIM_CLK_DIV     1       //1,2,4
#define AUXCOUNTER1_TIM_MODE        DOWN    //UP, DOWN, CENTER
#define AUXCOUNTER1_TIM_POL         RISING  //RISING, FALLING, BOTH
#define AUXCOUNTER1_TIM_PRSC_IN_DIV 1      //1,2,4,8
#define AUXCOUNTER1_TIM_IN_FILTER   0     //4bits 0-15

#define AUXCOUNTER3_PIN             PI7
#define AUXCOUNTER3_TIM             TIM8    //TIM1, TIM2, TIM3, TIM4, TIM5, TIM8, TIM12, TIM13, TIM14, ...
#define AUXCOUNTER3_TIM_CH          3       //1,2,3,4
#define AUXCOUNTER3_TIM_PRSC        65535   //16bit
#define AUXCOUNTER3_TIM_COUNT       65535   //16bit
#define AUXCOUNTER3_TIM_CLK_DIV     1       //1,2,4
#define AUXCOUNTER3_TIM_MODE        DOWN    //UP, DOWN, CENTER
#define AUXCOUNTER3_TIM_POL         RISING  //RISING, FALLING, BOTH
#define AUXCOUNTER3_TIM_PRSC_IN_DIV 1      //1,2,4,8
#define AUXCOUNTER3_TIM_IN_FILTER   0     //4bits 0-15

#define AUXCOUNTER4_PIN             PE9
#define AUXCOUNTER4_TIM             TIM5    //TIM1, TIM2, TIM3, TIM4, TIM5, TIM8, TIM12, TIM13, TIM14, ...
#define AUXCOUNTER4_TIM_CH          1       //1,2,3,4
#define AUXCOUNTER4_TIM_PRSC        65535   //16bit
#define AUXCOUNTER4_TIM_COUNT       65535   //16bit
#define AUXCOUNTER4_TIM_CLK_DIV     1       //1,2,4
#define AUXCOUNTER4_TIM_MODE        DOWN    //UP, DOWN, CENTER
#define AUXCOUNTER4_TIM_POL         RISING  //RISING, FALLING, BOTH
#define AUXCOUNTER4_TIM_PRSC_IN_DIV 1      //1,2,4,8
#define AUXCOUNTER4_TIM_IN_FILTER   0     //4bits 0-15


// *************** CAN *****************************

#define USE_CAN
#define USE_CAN1
#define CAN1_RX_PIN                 PD0
#define CAN1_TX_PIN                 PD1
#define CAN1_EN_PIN                 PD9


#define USE_CAN2
#define CAN2_RX_PIN                 PB12
#define CAN2_TX_PIN                 PB13
#define CAN2_EN_PIN                 PD8

// *************** PINIO ***************************
//#define USE_PINIO
//#define USE_PINIOBOX
//#define PINIO1_PIN                  PG12

#define GPS_RESET_PIN				DEFIO_TAG__PG12
// *************** PWM *****************************
//DISABLED

//

#define DEFAULT_FEATURES            (FEATURE_CURRENT_METER | FEATURE_VBAT | FEATURE_TX_PROF_SEL | FEATURE_BLACKBOX)
#define CURRENT_METER_SCALE         250

#define TARGET_IO_PORTA 0xffff
#define TARGET_IO_PORTB 0xffff
#define TARGET_IO_PORTC 0xffff
#define TARGET_IO_PORTD 0xffff
#define TARGET_IO_PORTE 0xffff
#define TARGET_IO_PORTF 0xffff
#define TARGET_IO_PORTG 0xffff
#define TARGET_IO_PORTH 0xffff
#define TARGET_IO_PORTI 0xffff

#define MAX_PWM_OUTPUT_PORTS        4

#endif
