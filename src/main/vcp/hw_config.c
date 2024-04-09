/**
 ******************************************************************************
 * @file    hw_config.c
 * @author  MCD Application Team
 * @version V4.0.0
 * @date    21-January-2013
 * @brief   Hardware Configuration & Setup
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
 *
 * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *        http://www.st.com/software_license_agreement_liberty_v2
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include "stm32_it.h"
#include "platform.h"
#include "usb_lib.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "hw_config.h"
#include "usb_pwr.h"

#include <stdbool.h>
#include "drivers/time.h"
#include "drivers/nvic.h"

#include "common/utils.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_ll_exti.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ErrorStatus HSEStartUpStatus;
LL_EXTI_InitTypeDef EXTI_InitStructure;
__IO uint32_t packetSent;                                     // HJI
extern __IO uint32_t receiveLength;                          // HJI

uint8_t receiveBuffer[64];                                   // HJI
uint32_t sendLength;                                          // HJI
static void IntToUnicode(uint32_t value, uint8_t *pbuf, uint8_t len);
/* Extern variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
 * Function Name  : Set_System
 * Description    : Configures Main system clocks & power
 * Input          : None.
 * Return         : None.
 *******************************************************************************/
void Set_System(void)
{
#if !defined(STM32L1XX_MD) && !defined(STM32L1XX_HD) && !defined(STM32L1XX_MD_PLUS)
    GPIO_InitTypeDef GPIO_InitStructure;
#endif /* STM32L1XX_MD && STM32L1XX_XD */

#if defined(USB_USE_EXTERNAL_PULLUP)
    GPIO_InitTypeDef GPIO_InitStructure;
#endif /* USB_USE_EXTERNAL_PULLUP */

    /*!< At this stage the microcontroller clock setting is already configured,
     this is done through SystemInit() function which is called from startup
     file (startup_stm32f10x_xx.s) before to branch to application main.
     To reconfigure the default setting of SystemInit() function, refer to
     system_stm32f10x.c file
     */
#if defined(STM32L1XX_MD) || defined(STM32L1XX_HD)|| defined(STM32L1XX_MD_PLUS)
    /* Enable the SYSCFG module clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
#endif /* STM32L1XX_XD */


    /*Pull down PA12 to create USB Disconnect Pulse*/     // HJI
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /**USB_OTG_FS GPIO Configuration
	PA9     ------> USB_OTG_FS_VBUS
	PA11     ------> USB_OTG_FS_DM
	PA12     ------> USB_OTG_FS_DP
	*/

    GPIO_InitStructure.Pin = GPIO_PIN_9;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = GPIO_PIN_11|GPIO_PIN_12;
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStructure.Alternate = GPIO_AF10_OTG1_FS;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, RESET);                   // HJI

    delay(200);                                           // HJI

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, SET);                     // HJI

    /* Configure the EXTI line 18 connected internally to the USB IP */
    EXTI_HandleTypeDef line18;
    line18.Line = EXTI_LINE_18;
    line18.PendingCallback = NULL;
    HAL_EXTI_ClearPending(&line18, EXTI_TRIGGER_RISING_FALLING);
    EXTI_InitStructure.Line_0_31 = EXTI_LINE_18;
    EXTI_InitStructure.Trigger = EXTI_TRIGGER_RISING;
    EXTI_InitStructure.Mode = LL_EXTI_MODE_IT_EVENT;
    LL_EXTI_Init(&EXTI_InitStructure);
}

/*******************************************************************************
 * Function Name  : Set_USBClock
 * Description    : Configures USB Clock input (48MHz)
 * Input          : None.
 * Return         : None.
 *******************************************************************************/
void Set_USBClock(void)
{
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USB;
	PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
	HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

	__HAL_RCC_USB_OTG_FS_CLK_ENABLE();
}

/*******************************************************************************
 * Function Name  : Enter_LowPowerMode
 * Description    : Power-off system clocks and power while entering suspend mode
 * Input          : None.
 * Return         : None.
 *******************************************************************************/
void Enter_LowPowerMode(void)
{
    /* Set the device state to suspend */
    bDeviceState = SUSPENDED;
}

/*******************************************************************************
 * Function Name  : Leave_LowPowerMode
 * Description    : Restores system clocks and power while exiting suspend mode
 * Input          : None.
 * Return         : None.
 *******************************************************************************/
void Leave_LowPowerMode(void)
{
    DEVICE_INFO *pInfo = &Device_Info;

    /* Set the device state to the correct state */
    if (pInfo->Current_Configuration != 0) {
        /* Device configured */
        bDeviceState = CONFIGURED;
    } else {
        bDeviceState = ATTACHED;
    }
    /*Enable SystemCoreClock*/
    SystemInit();
}

/*******************************************************************************
 * Function Name  : USB_Interrupts_Config
 * Description    : Configures the USB interrupts
 * Input          : None.
 * Return         : None.
 *******************************************************************************/
void USB_Interrupts_Config(void)
{
	HAL_NVIC_SetPriority(OTG_FS_EP1_OUT_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(OTG_FS_EP1_OUT_IRQn);
	HAL_NVIC_SetPriority(OTG_FS_EP1_IN_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(OTG_FS_EP1_IN_IRQn);
	HAL_NVIC_SetPriority(OTG_FS_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(OTG_FS_IRQn);
}

/*******************************************************************************
 * Function Name  : USB_Cable_Config
 * Description    : Software Connection/Disconnection of USB Cable
 * Input          : None.
 * Return         : Status
 *******************************************************************************/
void USB_Cable_Config(FunctionalState NewState)
{
    UNUSED(NewState);
}

/*******************************************************************************
 * Function Name  : Get_SerialNum.
 * Description    : Create the serial number string descriptor.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
void Get_SerialNum(void)
{
    uint32_t Device_Serial0, Device_Serial1, Device_Serial2;

    Device_Serial0 = *(uint32_t*)ID1;
    Device_Serial1 = *(uint32_t*)ID2;
    Device_Serial2 = *(uint32_t*)ID3;

    Device_Serial0 += Device_Serial2;

    if (Device_Serial0 != 0) {
        IntToUnicode(Device_Serial0, &Virtual_Com_Port_StringSerial[2], 8);
        IntToUnicode(Device_Serial1, &Virtual_Com_Port_StringSerial[18], 4);
    }
}

/*******************************************************************************
 * Function Name  : HexToChar.
 * Description    : Convert Hex 32Bits value into char.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
static void IntToUnicode(uint32_t value, uint8_t *pbuf, uint8_t len)
{
    uint8_t idx = 0;

    for (idx = 0; idx < len; idx++) {
        if (((value >> 28)) < 0xA) {
            pbuf[2 * idx] = (value >> 28) + '0';
        } else {
            pbuf[2 * idx] = (value >> 28) + 'A' - 10;
        }

        value = value << 4;

        pbuf[2 * idx + 1] = 0;
    }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
