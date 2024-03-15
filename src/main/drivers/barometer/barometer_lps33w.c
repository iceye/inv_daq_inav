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

 ******************************************************************************
 * @brief   contains definitions from the ST MEMS team
 * @author  MEMS Application Team
 * @version V1.0.0
 * @date    11-February-2015
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
 * */

#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#ifdef STM32IDE
	#include "stm32h7xx_hal.h"
#endif

#include <platform.h>
#include "build/build_config.h"
#include "build/debug.h"
#include "common/utils.h"

#include "drivers/time.h"
#include "drivers/io.h"
#include "drivers/bus.h"
#include "drivers/barometer/barometer.h"

#if defined(USE_BARO_LPS33W)

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include <math.h>

/** @addtogroup LPS33W
  * @{
  *
  */

/** @defgroup  Endianness definitions
  * @{
  *
  */

#ifndef DRV_BYTE_ORDER
#ifndef __BYTE_ORDER__

#define DRV_LITTLE_ENDIAN 1234
#define DRV_BIG_ENDIAN    4321

/** if _BYTE_ORDER is not defined, choose the endianness of your architecture
  * by uncommenting the define which fits your platform endianness
  */
//#define DRV_BYTE_ORDER    DRV_BIG_ENDIAN
#define DRV_BYTE_ORDER    DRV_LITTLE_ENDIAN

#else /* defined __BYTE_ORDER__ */

#define DRV_LITTLE_ENDIAN  __ORDER_LITTLE_ENDIAN__
#define DRV_BIG_ENDIAN     __ORDER_BIG_ENDIAN__
#define DRV_BYTE_ORDER     __BYTE_ORDER__

#endif /* __BYTE_ORDER__*/
#endif /* DRV_BYTE_ORDER */

/**
  * @}
  *
  */

/** @defgroup STMicroelectronics sensors common types
  * @{
  *
  */

#ifndef MEMS_SHARED_TYPES
#define MEMS_SHARED_TYPES

typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t bit0       : 1;
  uint8_t bit1       : 1;
  uint8_t bit2       : 1;
  uint8_t bit3       : 1;
  uint8_t bit4       : 1;
  uint8_t bit5       : 1;
  uint8_t bit6       : 1;
  uint8_t bit7       : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t bit7       : 1;
  uint8_t bit6       : 1;
  uint8_t bit5       : 1;
  uint8_t bit4       : 1;
  uint8_t bit3       : 1;
  uint8_t bit2       : 1;
  uint8_t bit1       : 1;
  uint8_t bit0       : 1;
#endif /* DRV_BYTE_ORDER */
} bitwise_t;

#define PROPERTY_DISABLE                (0U)
#define PROPERTY_ENABLE                 (1U)

/** @addtogroup  Interfaces_Functions
  * @brief       This section provide a set of functions used to read and
  *              write a generic register of the device.
  *              MANDATORY: return 0 -> no Error.
  * @{
  *
  */

typedef int32_t (*stmdev_write_ptr)(void *, uint8_t, const uint8_t *, uint16_t);
typedef int32_t (*stmdev_read_ptr)(void *, uint8_t, uint8_t *, uint16_t);
typedef void (*stmdev_mdelay_ptr)(uint32_t millisec);

typedef struct
{
  /** Component mandatory fields **/
  stmdev_write_ptr  write_reg;
  stmdev_read_ptr   read_reg;
  /** Component optional fields **/
  stmdev_mdelay_ptr   mdelay;
  /** Customizable optional pointer **/
  void *handle;
} stmdev_ctx_t;

/**
  * @}
  *
  */

#endif /* MEMS_SHARED_TYPES */

#ifndef MEMS_UCF_SHARED_TYPES
#define MEMS_UCF_SHARED_TYPES

/** @defgroup    Generic address-data structure definition
  * @brief       This structure is useful to load a predefined configuration
  *              of a sensor.
  *              You can create a sensor configuration by your own or using
  *              Unico / Unicleo tools available on STMicroelectronics
  *              web site.
  *
  * @{
  *
  */

typedef struct
{
  uint8_t address;
  uint8_t data;
} ucf_line_t;

/**
  * @}
  *
  */

#endif /* MEMS_UCF_SHARED_TYPES */

/**
  * @}
  *
  */


/** @defgroup LSM9DS1_Infos
  * @{
  *
  */

/** I2C Device Address 8 bit format: if SA0=0 -> 0x5C if SA0=1 -> 0x5D **/
#define LPS33W_I2C_ADD_H   0x5DU
#define LPS33W_I2C_ADD_L   0x5CU

/** Device Identification (Who am I) **/
#define LPS33W_ID            0xB1U

/**
  * @}
  *
  */

#define LPS33W_INTERRUPT_CFG  0x0BU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t pe               : 2; /* ple + phe -> pe */
  uint8_t lir              : 1;
  uint8_t diff_en          : 1;
  uint8_t reset_az         : 1;
  uint8_t autozero         : 1;
  uint8_t reset_arp        : 1;
  uint8_t autorifp         : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t autorifp         : 1;
  uint8_t reset_arp        : 1;
  uint8_t autozero         : 1;
  uint8_t reset_az         : 1;
  uint8_t diff_en          : 1;
  uint8_t lir              : 1;
  uint8_t pe               : 2; /* ple + phe -> pe */
#endif /* DRV_BYTE_ORDER */
} lps33w_interrupt_cfg_t;

#define LPS33W_THS_P_L        0x0CU
#define LPS33W_THS_P_H        0x0DU
#define LPS33W_WHO_AM_I       0x0FU
#define LPS33W_CTRL_REG1      0x10U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t sim              : 1;
  uint8_t bdu              : 1;
  uint8_t lpfp             : 2; /* en_lpfp + lpfp_cfg -> lpfp */
  uint8_t odr              : 3;
  uint8_t not_used_01      : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01      : 1;
  uint8_t odr              : 3;
  uint8_t lpfp             : 2; /* en_lpfp + lpfp_cfg -> lpfp */
  uint8_t bdu              : 1;
  uint8_t sim              : 1;
#endif /* DRV_BYTE_ORDER */
} lps33w_ctrl_reg1_t;

#define LPS33W_CTRL_REG2      0x11U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t one_shot         : 1;
  uint8_t not_used_01      : 1;
  uint8_t swreset          : 1;
  uint8_t i2c_dis          : 1;
  uint8_t if_add_inc       : 1;
  uint8_t stop_on_fth      : 1;
  uint8_t fifo_en          : 1;
  uint8_t boot             : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t boot             : 1;
  uint8_t fifo_en          : 1;
  uint8_t stop_on_fth      : 1;
  uint8_t if_add_inc       : 1;
  uint8_t i2c_dis          : 1;
  uint8_t swreset          : 1;
  uint8_t not_used_01      : 1;
  uint8_t one_shot         : 1;
#endif /* DRV_BYTE_ORDER */
} lps33w_ctrl_reg2_t;

#define LPS33W_CTRL_REG3      0x12U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t int_s            : 2;
  uint8_t drdy             : 1;
  uint8_t f_ovr            : 1;
  uint8_t f_fth            : 1;
  uint8_t f_fss5           : 1;
  uint8_t pp_od            : 1;
  uint8_t int_h_l          : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t int_h_l          : 1;
  uint8_t pp_od            : 1;
  uint8_t f_fss5           : 1;
  uint8_t f_fth            : 1;
  uint8_t f_ovr            : 1;
  uint8_t drdy             : 1;
  uint8_t int_s            : 2;
#endif /* DRV_BYTE_ORDER */
} lps33w_ctrl_reg3_t;


#define LPS33W_FIFO_CTRL      0x14U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t wtm              : 5;
  uint8_t f_mode           : 3;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t f_mode           : 3;
  uint8_t wtm              : 5;
#endif /* DRV_BYTE_ORDER */
} lps33w_fifo_ctrl_t;

#define LPS33W_REF_P_XL       0x15U
#define LPS33W_REF_P_L        0x16U
#define LPS33W_REF_P_H        0x17U
#define LPS33W_RPDS_L         0x18U
#define LPS33W_RPDS_H         0x19U

#define LPS33W_RES_CONF       0x1AU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t lc_en            : 1;
  uint8_t not_used_01      : 7;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01      : 7;
  uint8_t lc_en            : 1;
#endif /* DRV_BYTE_ORDER */
} lps33w_res_conf_t;

#define LPS33W_INT_SOURCE     0x25U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t ph               : 1;
  uint8_t pl               : 1;
  uint8_t ia               : 1;
  uint8_t not_used_01      : 4;
  uint8_t boot_status      : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t boot_status      : 1;
  uint8_t not_used_01      : 4;
  uint8_t ia               : 1;
  uint8_t pl               : 1;
  uint8_t ph               : 1;
#endif /* DRV_BYTE_ORDER */
} lps33w_int_source_t;

#define LPS33W_FIFO_STATUS    0x26U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t fss              : 6;
  uint8_t ovr              : 1;
  uint8_t fth_fifo         : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t fth_fifo         : 1;
  uint8_t ovr              : 1;
  uint8_t fss              : 6;
#endif /* DRV_BYTE_ORDER */
} lps33w_fifo_status_t;

#define LPS33W_STATUS         0x27U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t p_da             : 1;
  uint8_t t_da             : 1;
  uint8_t not_used_02      : 2;
  uint8_t p_or             : 1;
  uint8_t t_or             : 1;
  uint8_t not_used_01      : 2;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01      : 2;
  uint8_t t_or             : 1;
  uint8_t p_or             : 1;
  uint8_t not_used_02      : 2;
  uint8_t t_da             : 1;
  uint8_t p_da             : 1;
#endif /* DRV_BYTE_ORDER */
} lps33w_status_t;

#define LPS33W_PRESS_OUT_XL   0x28U
#define LPS33W_PRESS_OUT_L    0x29U
#define LPS33W_PRESS_OUT_H    0x2AU
#define LPS33W_TEMP_OUT_L     0x2BU
#define LPS33W_TEMP_OUT_H     0x2CU
#define LPS33W_LPFP_RES       0x33U

/**
  * @defgroup LPS33W_Register_Union
  * @brief    This union group all the registers having a bit-field
  *           description.
  *           This union is useful but it's not needed by the driver.
  *
  *           REMOVING this union you are compliant with:
  *           MISRA-C 2012 [Rule 19.2] -> " Union are not allowed "
  *
  * @{
  *
  */

typedef union
{
  lps33w_interrupt_cfg_t      interrupt_cfg;
  lps33w_ctrl_reg1_t          ctrl_reg1;
  lps33w_ctrl_reg2_t          ctrl_reg2;
  lps33w_ctrl_reg3_t          ctrl_reg3;
  lps33w_fifo_ctrl_t          fifo_ctrl;
  lps33w_res_conf_t           res_conf;
  lps33w_int_source_t         int_source;
  lps33w_fifo_status_t        fifo_status;
  lps33w_status_t             status;
  bitwise_t                    bitwise;
  uint8_t                      byte;
} lps33w_reg_t;

/**
  * @}
  *
  */

#ifndef __weak
#define __weak __attribute__((weak))
#endif /* __weak */

/*
 * These are the basic platform dependent I/O routines to read
 * and write device registers connected on a standard bus.
 * The driver keeps offering a default implementation based on function
 * pointers to read/write routines for backward compatibility.
 * The __weak directive allows the final application to overwrite
 * them with a custom implementation.
 */


typedef enum
{
  LPS33W_LPF_ODR_DIV_2  = 0,
  LPS33W_LPF_ODR_DIV_9  = 2,
  LPS33W_LPF_ODR_DIV_20 = 3,
} lps33w_lpfp_t;


typedef enum
{
  LPS33W_POWER_DOWN  = 0,
  LPS33W_ODR_1_Hz    = 1,
  LPS33W_ODR_10_Hz   = 2,
  LPS33W_ODR_25_Hz   = 3,
  LPS33W_ODR_50_Hz   = 4,
  LPS33W_ODR_75_Hz   = 5,
} lps33w_odr_t;


typedef struct
{
  lps33w_fifo_status_t  fifo_status;
  lps33w_status_t       status;
} lps33w_dev_stat_t;

typedef enum
{
  LPS33W_NO_THRESHOLD = 0,
  LPS33W_POSITIVE     = 1,
  LPS33W_NEGATIVE     = 2,
  LPS33W_BOTH         = 3,
} lps33w_pe_t;

typedef enum
{
  LPS33W_INT_PULSED  = 0,
  LPS33W_INT_LATCHED = 1,
} lps33w_lir_t;

typedef enum
{
  LPS33W_DRDY_OR_FIFO_FLAGS = 0,
  LPS33W_HIGH_PRES_INT      = 1,
  LPS33W_LOW_PRES_INT       = 2,
  LPS33W_EVERY_PRES_INT     = 3,
} lps33w_int_s_t;

typedef enum
{
  LPS33W_PUSH_PULL  = 0,
  LPS33W_OPEN_DRAIN = 1,
} lps33w_pp_od_t;

typedef enum
{
  LPS33W_ACTIVE_HIGH = 0,
  LPS33W_ACTIVE_LOW = 1,
} lps33w_int_h_l_t;

typedef enum
{
  LPS33W_BYPASS_MODE           = 0,
  LPS33W_FIFO_MODE             = 1,
  LPS33W_STREAM_MODE           = 2,
  LPS33W_STREAM_TO_FIFO_MODE   = 3,
  LPS33W_BYPASS_TO_STREAM_MODE = 4,
  LPS33W_DYNAMIC_STREAM_MODE   = 6,
  LPS33W_BYPASS_TO_FIFO_MODE   = 7,
} lps33w_f_mode_t;



typedef enum
{
  LPS33W_SPI_4_WIRE = 0,
  LPS33W_SPI_3_WIRE = 1,
} lps33w_sim_t;

typedef enum
{
  LPS33W_I2C_ENABLE = 0,
  LPS33W_I2C_DISABLE = 1,
} lps33w_i2c_dis_t;


/**
  * @defgroup    LPS33W
  * @brief       This file provides a set of functions needed to drive the
  *              ultra-compact piezoresistive absolute pressure sensor.
  * @{
  *
  */

/**
  * @defgroup    LPS33W_Interfaces_functions
  * @brief       This section provide a set of functions used to read and
  *              write a generic register of the device.
  * @{
  *
  */

/**
  * @defgroup    LPS33W_Sensitivity
  * @brief       These functions convert raw-data into engineering units.
  * @{
  *
  */

float_t lps33w_from_lsb_to_pa(uint32_t lsb)
{
  return (((float_t)(lsb)) / 40.96f);
}

float_t lps33w_from_lsb_to_cdegc(int16_t lsb)
{
  return (lsb);
}

/**
  * @}
  *
  */

/**
  * @defgroup    LPS33W_data_generation_c
  * @brief       This section group all the functions concerning data
  *              generation
  * @{
  *
  */


/**
  * @brief  Reset Autozero function.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of reset_az in reg INTERRUPT_CFG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_autozero_rst_set(baroDev_t *baro, uint8_t val)
{
  lps33w_interrupt_cfg_t interrupt_cfg;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_INTERRUPT_CFG,
                        (uint8_t *)&interrupt_cfg);

  if (ret == 1)
  {
    interrupt_cfg.reset_az = val;
    ret = busWriteBuf(baro->busDev, LPS33W_INTERRUPT_CFG, (uint8_t *)&interrupt_cfg, 1);
  }

  return ret;
}

/**
  * @brief  Reset Autozero function.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of reset_az in reg INTERRUPT_CFG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_autozero_rst_get(baroDev_t *baro, uint8_t *val)
{
  lps33w_interrupt_cfg_t interrupt_cfg;
  int32_t ret;

  ret = busRead(baro->busDev,LPS33W_INTERRUPT_CFG, (uint8_t *)&interrupt_cfg);
  *val = interrupt_cfg.reset_az;

  return ret;
}

/**
  * @brief  Enable Autozero function.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of autozero in reg INTERRUPT_CFG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_autozero_set(baroDev_t *baro, uint8_t val)
{
  lps33w_interrupt_cfg_t interrupt_cfg;
  int32_t ret;

  ret = busRead(baro->busDev,LPS33W_INTERRUPT_CFG, (uint8_t *)&interrupt_cfg);

  if (ret == 1)
  {
    interrupt_cfg.autozero = val;
    ret = busWriteBuf(baro->busDev, LPS33W_INTERRUPT_CFG, (uint8_t *)&interrupt_cfg, 1);
  }

  return ret;
}

/**
  * @brief  Enable Autozero function.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of autozero in reg INTERRUPT_CFG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_autozero_get(baroDev_t *baro, uint8_t *val)
{
  lps33w_interrupt_cfg_t interrupt_cfg;
  int32_t ret;

  ret = busRead(baro->busDev,LPS33W_INTERRUPT_CFG, (uint8_t *)&interrupt_cfg);
  *val = interrupt_cfg.autozero;

  return ret;
}

/**
  * @brief  Reset AutoRifP function.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of reset_arp in reg INTERRUPT_CFG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_pressure_snap_rst_set(baroDev_t *baro, uint8_t val)
{
  lps33w_interrupt_cfg_t interrupt_cfg;
  int32_t ret;

  ret = busRead(baro->busDev,LPS33W_INTERRUPT_CFG, (uint8_t *)&interrupt_cfg);

  if (ret == 1)
  {
    interrupt_cfg.reset_arp = val;
    ret = busWriteBuf(baro->busDev, LPS33W_INTERRUPT_CFG, (uint8_t *)&interrupt_cfg, 1);
  }

  return ret;
}

/**
  * @brief  Reset AutoRifP function.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of reset_arp in reg INTERRUPT_CFG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_pressure_snap_rst_get(baroDev_t *baro, uint8_t *val)
{
  lps33w_interrupt_cfg_t interrupt_cfg;
  int32_t ret;

  ret = busRead(baro->busDev,LPS33W_INTERRUPT_CFG, (uint8_t *)&interrupt_cfg);
  *val = interrupt_cfg.reset_arp;

  return ret;
}

/**
  * @brief  Enable AutoRifP function.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of autorifp in reg INTERRUPT_CFG.
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_pressure_snap_set(baroDev_t *baro, uint8_t val)
{
  lps33w_interrupt_cfg_t interrupt_cfg;
  int32_t ret;

  ret = busRead(baro->busDev,LPS33W_INTERRUPT_CFG, (uint8_t *)&interrupt_cfg);

  if (ret == 1)
  {
    interrupt_cfg.autorifp = val;
    ret = busWriteBuf(baro->busDev, LPS33W_INTERRUPT_CFG, (uint8_t *)&interrupt_cfg, 1);
  }

  return ret;
}

/**
  * @brief  Enable AutoRifP function.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of autorifp in reg INTERRUPT_CFG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_pressure_snap_get(baroDev_t *baro, uint8_t *val)
{
  lps33w_interrupt_cfg_t interrupt_cfg;
  int32_t ret;

  ret = busRead(baro->busDev,LPS33W_INTERRUPT_CFG, (uint8_t *)&interrupt_cfg);
  *val = interrupt_cfg.autorifp;

  return ret;
}

/**
  * @brief  Block data update.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of bdu in reg CTRL_REG1
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_block_data_update_set(baroDev_t *baro, uint8_t val)
{
  lps33w_ctrl_reg1_t ctrl_reg1;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG1, (uint8_t *)&ctrl_reg1);

  if (ret == 1)
  {
    ctrl_reg1.bdu = val;
    ret = busWriteBuf(baro->busDev, LPS33W_CTRL_REG1, (uint8_t *)&ctrl_reg1, 1);
  }

  return ret;
}

/**
  * @brief  Block data update.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of bdu in reg CTRL_REG1
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_block_data_update_get(baroDev_t *baro, uint8_t *val)
{
  lps33w_ctrl_reg1_t ctrl_reg1;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG1, (uint8_t *)&ctrl_reg1);
  *val = ctrl_reg1.bdu;

  return ret;
}

/**
  * @brief  Low-pass bandwidth selection.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of lpfp in reg CTRL_REG1
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_low_pass_filter_mode_set(baroDev_t *baro,
                                        lps33w_lpfp_t val)
{
  lps33w_ctrl_reg1_t ctrl_reg1;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG1, (uint8_t *)&ctrl_reg1);

  if (ret == 1)
  {
    ctrl_reg1.lpfp = (uint8_t)val;
    ret = busWriteBuf(baro->busDev, LPS33W_CTRL_REG1, (uint8_t *)&ctrl_reg1, 1);
  }

  return ret;
}

/**
  * @brief   Low-pass bandwidth selection.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Get the values of lpfp in reg CTRL_REG1
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_low_pass_filter_mode_get(baroDev_t *baro,
                                        lps33w_lpfp_t *val)
{
  lps33w_ctrl_reg1_t ctrl_reg1;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG1, (uint8_t *)&ctrl_reg1);

  switch (ctrl_reg1.lpfp)
  {
    case LPS33W_LPF_ODR_DIV_2:
      *val = LPS33W_LPF_ODR_DIV_2;
      break;

    case LPS33W_LPF_ODR_DIV_9:
      *val = LPS33W_LPF_ODR_DIV_9;
      break;

    case LPS33W_LPF_ODR_DIV_20:
      *val = LPS33W_LPF_ODR_DIV_20;
      break;

    default:
      *val = LPS33W_LPF_ODR_DIV_2;
      break;
  }

  return ret;
}

/**
  * @brief  Output data rate selection.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of odr in reg CTRL_REG1
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_data_rate_set(baroDev_t *baro, lps33w_odr_t val)
{
  lps33w_ctrl_reg1_t ctrl_reg1;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG1, (uint8_t *)&ctrl_reg1);

  if (ret == 1)
  {
    ctrl_reg1.odr = (uint8_t)val;
    ret = busWriteBuf(baro->busDev, LPS33W_CTRL_REG1, (uint8_t *)&ctrl_reg1, 1);
  }

  return ret;
}

/**
  * @brief  Output data rate selection.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Get the values of odr in reg CTRL_REG1
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_data_rate_get(baroDev_t *baro, lps33w_odr_t *val)
{
  lps33w_ctrl_reg1_t ctrl_reg1;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG1, (uint8_t *)&ctrl_reg1);

  switch (ctrl_reg1.odr)
  {
    case LPS33W_POWER_DOWN:
      *val = LPS33W_POWER_DOWN;
      break;

    case LPS33W_ODR_1_Hz:
      *val = LPS33W_ODR_1_Hz;
      break;

    case LPS33W_ODR_10_Hz:
      *val = LPS33W_ODR_10_Hz;
      break;

    case LPS33W_ODR_25_Hz:
      *val = LPS33W_ODR_25_Hz;
      break;

    case LPS33W_ODR_50_Hz:
      *val = LPS33W_ODR_50_Hz;
      break;

    case LPS33W_ODR_75_Hz:
      *val = LPS33W_ODR_75_Hz;
      break;

    default:
      *val = LPS33W_ODR_1_Hz;
      break;
  }

  return ret;
}

/**
  * @brief  One-shot mode. Device perform a single measure.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of one_shot in reg CTRL_REG2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_one_shoot_trigger_set(baroDev_t *baro, uint8_t val)
{
  lps33w_ctrl_reg2_t ctrl_reg2;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG2, (uint8_t *)&ctrl_reg2);

  if (ret == 1)
  {
    ctrl_reg2.one_shot = val;
    ret = busWriteBuf(baro->busDev, LPS33W_CTRL_REG2, (uint8_t *)&ctrl_reg2, 1);
  }

  return ret;
}

/**
  * @brief  One-shot mode. Device perform a single measure.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of one_shot in reg CTRL_REG2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_one_shoot_trigger_get(baroDev_t *baro, uint8_t *val)
{
  lps33w_ctrl_reg2_t ctrl_reg2;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG2, (uint8_t *)&ctrl_reg2);
  *val = ctrl_reg2.one_shot;

  return ret;
}

/**
  * @brief  pressure_ref:   The Reference pressure value is a 24-bit data
  *         expressed as 2’s complement. The value is used when AUTOZERO
  *         or AUTORIFP function is enabled.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  buff   Buffer that contains data to write
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_pressure_ref_set(baroDev_t *baro, int32_t val)
{
  uint8_t buff[3];
  int32_t ret;

  buff[2] = (uint8_t)((uint32_t)val / 65536U);
  buff[1] = (uint8_t)((uint32_t)val - (buff[2] * 65536U)) / 256U;
  buff[0] = (uint8_t)((uint32_t)val - (buff[2] * 65536U) -
                      (buff[1] * 256U));
  ret =  busWriteBuf(baro->busDev, LPS33W_REF_P_XL, buff, 3);

  return ret;
}

/**
  * @brief  pressure_ref:   The Reference pressure value is a 24-bit data
  *         expressed as 2’s complement. The value is used when AUTOZERO
  *         or AUTORIFP function is enabled.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_pressure_ref_get(baroDev_t *baro, int32_t *val)
{
  uint8_t buff[3];
  int32_t ret;

  ret =  busReadBuf(baro->busDev,  LPS33W_REF_P_XL, buff, 3);
  *val = (int32_t)buff[2];
  *val = (*val * 256) + (int32_t)buff[1];
  *val = (*val * 256) + (int32_t)buff[0];

  return ret;
}

/**
  * @brief  The pressure offset value is 16-bit data that can be used to
  *         implement one-point calibration (OPC) after soldering.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  buff   Buffer that contains data to write
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_pressure_offset_set(baroDev_t *baro, int16_t val)
{
  uint8_t buff[2];
  int32_t ret;

  buff[1] = (uint8_t)((uint16_t)val / 256U);
  buff[0] = (uint8_t)((uint16_t)val - (buff[1] * 256U));
  ret =  busWriteBuf(baro->busDev, LPS33W_RPDS_L, buff, 2);

  return ret;
}

/**
  * @brief  The pressure offset value is 16-bit data that can be used to
  *         implement one-point calibration (OPC) after soldering.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_pressure_offset_get(baroDev_t *baro, int16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret =  busReadBuf(baro->busDev,  LPS33W_RPDS_L, buff, 2);
  *val = (int16_t)buff[1];
  *val = (*val * 256) + (int16_t)buff[0];

  return ret;
}

/**
  * @brief  Pressure data available.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of p_da in reg STATUS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_press_data_ready_get(baroDev_t *baro, uint8_t *val)
{
  lps33w_status_t status;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_STATUS, (uint8_t *)&status);
  *val = status.p_da;

  return ret;
}

/**
  * @brief  Temperature data available.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of t_da in reg STATUS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_temp_data_ready_get(baroDev_t *baro, uint8_t *val)
{
  lps33w_status_t status;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_STATUS, (uint8_t *)&status);
  *val = status.t_da;

  return ret;
}

/**
  * @brief  Pressure data overrun.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of p_or in reg STATUS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_press_data_ovr_get(baroDev_t *baro, uint8_t *val)
{
  lps33w_status_t status;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_STATUS, (uint8_t *)&status);
  *val = status.p_or;

  return ret;
}

/**
  * @brief  Temperature data overrun.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of t_or in reg STATUS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_temp_data_ovr_get(baroDev_t *baro, uint8_t *val)
{
  lps33w_status_t status;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_STATUS, (uint8_t *)&status);
  *val = status.t_or;

  return ret;
}

/**
  * @brief  Pressure output value[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_pressure_raw_get(baroDev_t *baro, uint32_t *buff)
{
  uint8_t reg[3];
  int32_t ret;

  ret =  busReadBuf(baro->busDev,  LPS33W_PRESS_OUT_XL, reg, 3);
  *buff = reg[0];
  *buff |= (reg[1]<<8);
  *buff |= (reg[2]<<16);

  return ret;
}

/**
  * @brief  temperature_raw:   Temperature output value[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  buff   Buffer that stores data read.
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_temperature_raw_get(baroDev_t *baro, int16_t *buff)
{
  uint8_t reg[2];
  int32_t ret;

  ret =  busReadBuf(baro->busDev,  LPS33W_TEMP_OUT_L, (uint8_t *) reg, 2);
  *buff = reg[0];
  *buff |= (reg[1]<<8);

  return ret;
}

/**
  * @brief  Low-pass filter reset register. If the LPFP is active, in
  *         order to avoid the transitory phase, the filter can be
  *         reset by reading this register before generating pressure
  *         measurements.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_low_pass_rst_get(baroDev_t *baro, uint8_t *buff)
{
  int32_t ret;

  ret =  busRead(baro->busDev, LPS33W_LPFP_RES, (uint8_t *) buff);

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup    LPS33W_common
  * @brief       This section group common useful functions
  * @{
  *
  */

/**
  * @brief  Device Who am I[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_device_id_get(baroDev_t *baro, uint8_t *buff)
{
  int32_t ret;

  ret =  busRead(baro->busDev, LPS33W_WHO_AM_I, (uint8_t *) buff);

  return ret;
}

/**
  * @brief  Software reset. Restore the default values in user registers[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of swreset in reg CTRL_REG2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_reset_set(baroDev_t *baro, uint8_t val)
{
  lps33w_ctrl_reg2_t ctrl_reg2;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG2, (uint8_t *)&ctrl_reg2);

  if (ret == 1)
  {
    ctrl_reg2.swreset = val;
    ret = busWriteBuf(baro->busDev, LPS33W_CTRL_REG2, (uint8_t *)&ctrl_reg2, 1);
  }

  return ret;
}

/**
  * @brief  Software reset. Restore the default values in user registers[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of swreset in reg CTRL_REG2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_reset_get(baroDev_t *baro, uint8_t *val)
{
  lps33w_ctrl_reg2_t ctrl_reg2;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG2, (uint8_t *)&ctrl_reg2);
  *val = ctrl_reg2.swreset;

  return ret;
}

/**
  * @brief  Reboot memory content. Reload the calibration parameters.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of boot in reg CTRL_REG2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_boot_set(baroDev_t *baro, uint8_t val)
{
  lps33w_ctrl_reg2_t ctrl_reg2;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG2, (uint8_t *)&ctrl_reg2);

  if (ret == 1)
  {
    ctrl_reg2.boot = val;
    ret = busWriteBuf(baro->busDev, LPS33W_CTRL_REG2, (uint8_t *)&ctrl_reg2, 1);
  }

  return ret;
}

/**
  * @brief  Reboot memory content. Reload the calibration parameters.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of boot in reg CTRL_REG2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_boot_get(baroDev_t *baro, uint8_t *val)
{
  lps33w_ctrl_reg2_t ctrl_reg2;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG2, (uint8_t *)&ctrl_reg2);
  *val = ctrl_reg2.boot;

  return ret;
}

/**
  * @brief  Low current mode.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of lc_en in reg RES_CONF
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_low_power_set(baroDev_t *baro, uint8_t val)
{
  lps33w_res_conf_t res_conf;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_RES_CONF, (uint8_t *)&res_conf);

  if (ret == 1)
  {
    res_conf.lc_en = val;
    ret = busWriteBuf(baro->busDev, LPS33W_RES_CONF, (uint8_t *)&res_conf, 1);
  }

  return ret;
}

/**
  * @brief  Low current mode.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of lc_en in reg RES_CONF
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_low_power_get(baroDev_t *baro, uint8_t *val)
{
  lps33w_res_conf_t res_conf;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_RES_CONF, (uint8_t *)&res_conf);
  *val = res_conf.lc_en;

  return ret;
}

/**
  * @brief  If ‘1’ indicates that the Boot (Reboot) phase is running.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of boot_status in reg INT_SOURCE
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_boot_status_get(baroDev_t *baro, uint8_t *val)
{
  lps33w_int_source_t int_source;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_INT_SOURCE, (uint8_t *)&int_source);
  *val = int_source.boot_status;

  return ret;
}

/**
  * @brief  All the status bit, FIFO and data generation[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Structure of registers from FIFO_STATUS to STATUS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_dev_status_get(baroDev_t *baro,
                              lps33w_dev_stat_t *val)
{
  int32_t ret;

  ret =  busReadBuf(baro->busDev,  LPS33W_FIFO_STATUS, (uint8_t *) val, 2);

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup    LPS33W_interrupts
  * @brief       This section group all the functions that manage interrupts
  * @{
  *
  */

/**
  * @brief  Enable interrupt generation on pressure low/high event.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of pe in reg INTERRUPT_CFG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_sign_of_int_threshold_set(baroDev_t *baro,
                                         lps33w_pe_t val)
{
  lps33w_interrupt_cfg_t interrupt_cfg;
  int32_t ret;

  ret = busRead(baro->busDev,LPS33W_INTERRUPT_CFG, (uint8_t *)&interrupt_cfg);

  if (ret == 1)
  {
    interrupt_cfg.pe = (uint8_t)val;
    ret = busWriteBuf(baro->busDev, LPS33W_INTERRUPT_CFG, (uint8_t *)&interrupt_cfg, 1);
  }

  return ret;
}

/**
  * @brief  Enable interrupt generation on pressure low/high event.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Get the values of pe in reg INTERRUPT_CFG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_sign_of_int_threshold_get(baroDev_t *baro,
                                         lps33w_pe_t *val)
{
  lps33w_interrupt_cfg_t interrupt_cfg;
  int32_t ret;

  ret = busRead(baro->busDev,LPS33W_INTERRUPT_CFG, (uint8_t *)&interrupt_cfg);

  switch (interrupt_cfg.pe)
  {
    case LPS33W_NO_THRESHOLD:
      *val = LPS33W_NO_THRESHOLD;
      break;

    case LPS33W_POSITIVE:
      *val = LPS33W_POSITIVE;
      break;

    case LPS33W_NEGATIVE:
      *val = LPS33W_NEGATIVE;
      break;

    case LPS33W_BOTH:
      *val = LPS33W_BOTH;
      break;

    default:
      *val = LPS33W_NO_THRESHOLD;
      break;
  }

  return ret;
}

/**
  * @brief  Interrupt request to the INT_SOURCE (25h) register
  *         mode (pulsed / latched) [set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of lir in reg INTERRUPT_CFG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_int_notification_mode_set(baroDev_t *baro,
                                         lps33w_lir_t val)
{
  lps33w_interrupt_cfg_t interrupt_cfg;
  int32_t ret;

  ret = busRead(baro->busDev,LPS33W_INTERRUPT_CFG, (uint8_t *)&interrupt_cfg);

  if (ret == 1)
  {
    interrupt_cfg.lir = (uint8_t)val;
    ret = busWriteBuf(baro->busDev, LPS33W_INTERRUPT_CFG, (uint8_t *)&interrupt_cfg, 1);
  }

  return ret;
}

/**
  * @brief   Interrupt request to the INT_SOURCE (25h) register
  *          mode (pulsed / latched) [get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Get the values of lir in reg INTERRUPT_CFG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_int_notification_mode_get(baroDev_t *baro,
                                         lps33w_lir_t *val)
{
  lps33w_interrupt_cfg_t interrupt_cfg;
  int32_t ret;

  ret = busRead(baro->busDev,LPS33W_INTERRUPT_CFG, (uint8_t *)&interrupt_cfg);

  switch (interrupt_cfg.lir)
  {
    case LPS33W_INT_PULSED:
      *val = LPS33W_INT_PULSED;
      break;

    case LPS33W_INT_LATCHED:
      *val = LPS33W_INT_LATCHED;
      break;

    default:
      *val = LPS33W_INT_PULSED;
      break;
  }

  return ret;
}

/**
  * @brief  Enable interrupt generation.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of diff_en in reg INTERRUPT_CFG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_int_generation_set(baroDev_t *baro, uint8_t val)
{
  lps33w_interrupt_cfg_t interrupt_cfg;
  int32_t ret;

  ret = busRead(baro->busDev,LPS33W_INTERRUPT_CFG,(uint8_t *)&interrupt_cfg);

  if (ret == 1)
  {
    interrupt_cfg.diff_en = val;
    ret = busWriteBuf(baro->busDev, LPS33W_INTERRUPT_CFG,(uint8_t *)&interrupt_cfg, 1);
  }

  return ret;
}

/**
  * @brief  Enable interrupt generation.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of diff_en in reg INTERRUPT_CFG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_int_generation_get(baroDev_t *baro, uint8_t *val)
{
  lps33w_interrupt_cfg_t interrupt_cfg;
  int32_t ret;

  ret = busRead(baro->busDev,LPS33W_INTERRUPT_CFG,(uint8_t *)&interrupt_cfg);
  *val = interrupt_cfg.diff_en;

  return ret;
}

/**
  * @brief  User-defined threshold value for pressure interrupt event[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  buff   Buffer that contains data to write
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_int_threshold_set(baroDev_t *baro, uint16_t val)
{
  uint8_t buff[2];
  int32_t ret;

  buff[1] = (uint8_t)(val / 256U);
  buff[0] = (uint8_t)(val - (buff[1] * 256U));
  ret =  busWriteBuf(baro->busDev, LPS33W_THS_P_L, (uint8_t *) buff, 2);

  return ret;
}

/**
  * @brief  User-defined threshold value for pressure interrupt event[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_int_threshold_get(baroDev_t *baro, uint16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret =  busReadBuf(baro->busDev,  LPS33W_THS_P_L, (uint8_t *) buff, 2);
  *val = buff[1];
  *val = (*val * 256) + buff[0];

  return ret;
}

/**
  * @brief  Data signal on INT_DRDY pin control bits.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of int_s in reg CTRL_REG3
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_int_pin_mode_set(baroDev_t *baro, lps33w_int_s_t val)
{
  lps33w_ctrl_reg3_t ctrl_reg3;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG3, (uint8_t *)&ctrl_reg3);

  if (ret == 1)
  {
    ctrl_reg3.int_s = (uint8_t)val;
    ret = busWriteBuf(baro->busDev, LPS33W_CTRL_REG3, (uint8_t *)&ctrl_reg3, 1);
  }

  return ret;
}

/**
  * @brief  Data signal on INT_DRDY pin control bits.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Get the values of int_s in reg CTRL_REG3
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_int_pin_mode_get(baroDev_t *baro,
                                lps33w_int_s_t *val)
{
  lps33w_ctrl_reg3_t ctrl_reg3;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG3, (uint8_t *)&ctrl_reg3);

  switch (ctrl_reg3.int_s)
  {
    case LPS33W_DRDY_OR_FIFO_FLAGS:
      *val = LPS33W_DRDY_OR_FIFO_FLAGS;
      break;

    case LPS33W_HIGH_PRES_INT:
      *val = LPS33W_HIGH_PRES_INT;
      break;

    case LPS33W_LOW_PRES_INT:
      *val = LPS33W_LOW_PRES_INT;
      break;

    case LPS33W_EVERY_PRES_INT:
      *val = LPS33W_EVERY_PRES_INT;
      break;

    default:
      *val = LPS33W_DRDY_OR_FIFO_FLAGS;
      break;
  }

  return ret;
}

/**
  * @brief  Data-ready signal on INT_DRDY pin.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of drdy in reg CTRL_REG3
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_drdy_on_int_set(baroDev_t *baro, uint8_t val)
{
  lps33w_ctrl_reg3_t ctrl_reg3;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG3, (uint8_t *)&ctrl_reg3);

  if (ret == 1)
  {
    ctrl_reg3.drdy = val;
    ret = busWriteBuf(baro->busDev, LPS33W_CTRL_REG3, (uint8_t *)&ctrl_reg3, 1);
  }

  return ret;
}

/**
  * @brief  Data-ready signal on INT_DRDY pin.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of drdy in reg CTRL_REG3
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_drdy_on_int_get(baroDev_t *baro, uint8_t *val)
{
  lps33w_ctrl_reg3_t ctrl_reg3;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG3, (uint8_t *)&ctrl_reg3);
  *val = ctrl_reg3.drdy;

  return ret;
}

/**
  * @brief  FIFO overrun interrupt on INT_DRDY pin.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of f_ovr in reg CTRL_REG3
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_fifo_ovr_on_int_set(baroDev_t *baro, uint8_t val)
{
  lps33w_ctrl_reg3_t ctrl_reg3;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG3, (uint8_t *)&ctrl_reg3);

  if (ret == 1)
  {
    ctrl_reg3.f_ovr = val;
    ret = busWriteBuf(baro->busDev, LPS33W_CTRL_REG3, (uint8_t *)&ctrl_reg3, 1);
  }

  return ret;
}

/**
  * @brief  FIFO overrun interrupt on INT_DRDY pin.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of f_ovr in reg CTRL_REG3
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_fifo_ovr_on_int_get(baroDev_t *baro, uint8_t *val)
{
  lps33w_ctrl_reg3_t ctrl_reg3;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG3, (uint8_t *)&ctrl_reg3);
  *val = ctrl_reg3.f_ovr;

  return ret;
}

/**
  * @brief  FIFO watermark status on INT_DRDY pin.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of f_fth in reg CTRL_REG3
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_fifo_threshold_on_int_set(baroDev_t *baro,
                                         uint8_t val)
{
  lps33w_ctrl_reg3_t ctrl_reg3;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG3, (uint8_t *)&ctrl_reg3);

  if (ret == 1)
  {
    ctrl_reg3.f_fth = val;
    ret = busWriteBuf(baro->busDev, LPS33W_CTRL_REG3, (uint8_t *)&ctrl_reg3, 1);
  }

  return ret;
}

/**
  * @brief   FIFO watermark status on INT_DRDY pin.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of f_fth in reg CTRL_REG3
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_fifo_threshold_on_int_get(baroDev_t *baro,
                                         uint8_t *val)
{
  lps33w_ctrl_reg3_t ctrl_reg3;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG3, (uint8_t *)&ctrl_reg3);
  *val = ctrl_reg3.f_fth;

  return ret;
}

/**
  * @brief  FIFO full flag on INT_DRDY pin.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of f_fss5 in reg CTRL_REG3
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_fifo_full_on_int_set(baroDev_t *baro, uint8_t val)
{
  lps33w_ctrl_reg3_t ctrl_reg3;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG3, (uint8_t *)&ctrl_reg3);

  if (ret == 1)
  {
    ctrl_reg3.f_fss5 = val;
    ret = busWriteBuf(baro->busDev, LPS33W_CTRL_REG3, (uint8_t *)&ctrl_reg3, 1);
  }

  return ret;
}

/**
  * @brief  FIFO full flag on INT_DRDY pin.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of f_fss5 in reg CTRL_REG3
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_fifo_full_on_int_get(baroDev_t *baro, uint8_t *val)
{
  lps33w_ctrl_reg3_t ctrl_reg3;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG3, (uint8_t *)&ctrl_reg3);
  *val = ctrl_reg3.f_fss5;

  return ret;
}

/**
  * @brief  Push-pull/open drain selection on interrupt pads.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of pp_od in reg CTRL_REG3
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_pin_mode_set(baroDev_t *baro, lps33w_pp_od_t val)
{
  lps33w_ctrl_reg3_t ctrl_reg3;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG3, (uint8_t *)&ctrl_reg3);

  if (ret == 1)
  {
    ctrl_reg3.pp_od = (uint8_t)val;
    ret = busWriteBuf(baro->busDev, LPS33W_CTRL_REG3, (uint8_t *)&ctrl_reg3, 1);
  }

  return ret;
}

/**
  * @brief  Push-pull/open drain selection on interrupt pads.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Get the values of pp_od in reg CTRL_REG3
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_pin_mode_get(baroDev_t *baro, lps33w_pp_od_t *val)
{
  lps33w_ctrl_reg3_t ctrl_reg3;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG3, (uint8_t *)&ctrl_reg3);

  switch (ctrl_reg3.pp_od)
  {
    case LPS33W_PUSH_PULL:
      *val = LPS33W_PUSH_PULL;
      break;

    case LPS33W_OPEN_DRAIN:
      *val = LPS33W_OPEN_DRAIN;
      break;

    default:
      *val = LPS33W_PUSH_PULL;
      break;
  }

  return ret;
}

/**
  * @brief  Interrupt active-high/low.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of int_h_l in reg CTRL_REG3
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_int_polarity_set(baroDev_t *baro,
                                lps33w_int_h_l_t val)
{
  lps33w_ctrl_reg3_t ctrl_reg3;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG3, (uint8_t *)&ctrl_reg3);

  if (ret == 1)
  {
    ctrl_reg3.int_h_l = (uint8_t)val;
    ret = busWriteBuf(baro->busDev, LPS33W_CTRL_REG3, (uint8_t *)&ctrl_reg3, 1);
  }

  return ret;
}

/**
  * @brief  Interrupt active-high/low.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Get the values of int_h_l in reg CTRL_REG3
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_int_polarity_get(baroDev_t *baro,
                                lps33w_int_h_l_t *val)
{
  lps33w_ctrl_reg3_t ctrl_reg3;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG3, (uint8_t *)&ctrl_reg3);

  switch (ctrl_reg3.int_h_l)
  {
    case LPS33W_ACTIVE_HIGH:
      *val = LPS33W_ACTIVE_HIGH;
      break;

    case LPS33W_ACTIVE_LOW:
      *val = LPS33W_ACTIVE_LOW;
      break;

    default:
      *val = LPS33W_ACTIVE_HIGH;
      break;
  }

  return ret;
}

/**
  * @brief  Interrupt source register[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Register INT_SOURCE
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_int_source_get(baroDev_t *baro,
                              lps33w_int_source_t *val)
{
  int32_t ret;

  ret =  busRead(baro->busDev, LPS33W_INT_SOURCE, (uint8_t *) val);

  return ret;
}

/**
  * @brief  Differential pressure high interrupt flag.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of ph in reg INT_SOURCE
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_int_on_press_high_get(baroDev_t *baro, uint8_t *val)
{
  lps33w_int_source_t int_source;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_INT_SOURCE, (uint8_t *)&int_source);
  *val = int_source.ph;

  return ret;
}

/**
  * @brief  Differential pressure low interrupt flag.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of pl in reg INT_SOURCE
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_int_on_press_low_get(baroDev_t *baro, uint8_t *val)
{
  lps33w_int_source_t int_source;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_INT_SOURCE, (uint8_t *)&int_source);
  *val = int_source.pl;

  return ret;
}

/**
  * @brief  Interrupt active flag.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of ia in reg INT_SOURCE
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_interrupt_event_get(baroDev_t *baro, uint8_t *val)
{
  lps33w_int_source_t int_source;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_INT_SOURCE, (uint8_t *)&int_source);
  *val = int_source.ia;

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup    LPS33W_fifo
  * @brief       This section group all the functions concerning the
  *              fifo usage
  * @{
  *
  */

/**
  * @brief   Stop on FIFO watermark. Enable FIFO watermark level use.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of stop_on_fth in reg CTRL_REG2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_stop_on_fifo_threshold_set(baroDev_t *baro,
                                          uint8_t val)
{
  lps33w_ctrl_reg2_t ctrl_reg2;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG2, (uint8_t *)&ctrl_reg2);

  if (ret == 1)
  {
    ctrl_reg2.stop_on_fth = val;
    ret = busWriteBuf(baro->busDev, LPS33W_CTRL_REG2, (uint8_t *)&ctrl_reg2, 1);
  }

  return ret;
}

/**
  * @brief   Stop on FIFO watermark. Enable FIFO watermark level use.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of stop_on_fth in reg CTRL_REG2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_stop_on_fifo_threshold_get(baroDev_t *baro,
                                          uint8_t *val)
{
  lps33w_ctrl_reg2_t ctrl_reg2;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG2, (uint8_t *)&ctrl_reg2);
  *val = ctrl_reg2.stop_on_fth;

  return ret;
}

/**
  * @brief  FIFO enable.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of fifo_en in reg CTRL_REG2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_fifo_set(baroDev_t *baro, uint8_t val)
{
  lps33w_ctrl_reg2_t ctrl_reg2;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG2, (uint8_t *)&ctrl_reg2);

  if (ret == 1)
  {
    ctrl_reg2.fifo_en = val;
    ret = busWriteBuf(baro->busDev, LPS33W_CTRL_REG2, (uint8_t *)&ctrl_reg2, 1);
  }

  return ret;
}

/**
  * @brief  FIFO enable.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of fifo_en in reg CTRL_REG2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_fifo_get(baroDev_t *baro, uint8_t *val)
{
  lps33w_ctrl_reg2_t ctrl_reg2;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG2, (uint8_t *)&ctrl_reg2);
  *val = ctrl_reg2.fifo_en;

  return ret;
}

/**
  * @brief  FIFO watermark level selection.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of wtm in reg FIFO_CTRL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_fifo_watermark_set(baroDev_t *baro, uint8_t val)
{
  lps33w_fifo_ctrl_t fifo_ctrl;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_FIFO_CTRL, (uint8_t *)&fifo_ctrl);

  if (ret == 1)
  {
    fifo_ctrl.wtm = val;
    ret = busWriteBuf(baro->busDev, LPS33W_FIFO_CTRL, (uint8_t *)&fifo_ctrl, 1);
  }

  return ret;
}

/**
  * @brief  FIFO watermark level selection.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of wtm in reg FIFO_CTRL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_fifo_watermark_get(baroDev_t *baro, uint8_t *val)
{
  lps33w_fifo_ctrl_t fifo_ctrl;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_FIFO_CTRL, (uint8_t *)&fifo_ctrl);
  *val = fifo_ctrl.wtm;

  return ret;
}

/**
  * @brief  FIFO mode selection.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of f_mode in reg FIFO_CTRL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_fifo_mode_set(baroDev_t *baro, lps33w_f_mode_t val)
{
  lps33w_fifo_ctrl_t fifo_ctrl;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_FIFO_CTRL, (uint8_t *)&fifo_ctrl);

  if (ret == 1)
  {
    fifo_ctrl.f_mode = (uint8_t)val;
    ret = busWriteBuf(baro->busDev, LPS33W_FIFO_CTRL, (uint8_t *)&fifo_ctrl, 1);
  }

  return ret;
}

/**
  * @brief  FIFO mode selection.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Get the values of f_mode in reg FIFO_CTRL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_fifo_mode_get(baroDev_t *baro, lps33w_f_mode_t *val)
{
  lps33w_fifo_ctrl_t fifo_ctrl;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_FIFO_CTRL, (uint8_t *)&fifo_ctrl);

  switch (fifo_ctrl.f_mode)
  {
    case LPS33W_BYPASS_MODE:
      *val = LPS33W_BYPASS_MODE;
      break;

    case LPS33W_FIFO_MODE:
      *val = LPS33W_FIFO_MODE;
      break;

    case LPS33W_STREAM_MODE:
      *val = LPS33W_STREAM_MODE;
      break;

    case LPS33W_STREAM_TO_FIFO_MODE:
      *val = LPS33W_STREAM_TO_FIFO_MODE;
      break;

    case LPS33W_BYPASS_TO_STREAM_MODE:
      *val = LPS33W_BYPASS_TO_STREAM_MODE;
      break;

    case LPS33W_DYNAMIC_STREAM_MODE:
      *val = LPS33W_DYNAMIC_STREAM_MODE;
      break;

    case LPS33W_BYPASS_TO_FIFO_MODE:
      *val = LPS33W_BYPASS_TO_FIFO_MODE;
      break;

    default:
      *val = LPS33W_BYPASS_MODE;
      break;
  }

  return ret;
}

/**
  * @brief  FIFO stored data level.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of fss in reg FIFO_STATUS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_fifo_data_level_get(baroDev_t *baro, uint8_t *val)
{
  lps33w_fifo_status_t fifo_status;
  int32_t ret;

  ret = busRead(baro->busDev,LPS33W_FIFO_STATUS, (uint8_t *)&fifo_status);
  *val = fifo_status.fss;

  return ret;
}

/**
  * @brief  FIFO overrun status.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of ovr in reg FIFO_STATUS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_fifo_ovr_flag_get(baroDev_t *baro, uint8_t *val)
{
  lps33w_fifo_status_t fifo_status;
  int32_t ret;

  ret = busRead(baro->busDev,LPS33W_FIFO_STATUS, (uint8_t *)&fifo_status);
  *val = fifo_status.ovr;

  return ret;
}

/**
  * @brief  FIFO watermark status.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of fth_fifo in reg FIFO_STATUS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_fifo_fth_flag_get(baroDev_t *baro, uint8_t *val)
{
  lps33w_fifo_status_t fifo_status;
  int32_t ret;

  ret = busRead(baro->busDev,LPS33W_FIFO_STATUS, (uint8_t *)&fifo_status);
  *val = fifo_status.fth_fifo;

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup    LPS33W_serial_interface
  * @brief       This section group all the functions concerning serial
  *              interface management
  * @{
  *
  */

/**
  * @brief  SPI Serial Interface Mode selection.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of sim in reg CTRL_REG1
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_spi_mode_set(baroDev_t *baro, lps33w_sim_t val)
{
  lps33w_ctrl_reg1_t ctrl_reg1;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG1, (uint8_t *)&ctrl_reg1);

  if (ret == 1)
  {
    ctrl_reg1.sim = (uint8_t)val;
    ret = busWriteBuf(baro->busDev, LPS33W_CTRL_REG1, (uint8_t *)&ctrl_reg1, 1);
  }

  return ret;
}

/**
  * @brief  SPI Serial Interface Mode selection.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Get the values of sim in reg CTRL_REG1
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_spi_mode_get(baroDev_t *baro, lps33w_sim_t *val)
{
  lps33w_ctrl_reg1_t ctrl_reg1;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG1, (uint8_t *)&ctrl_reg1);

  switch (ctrl_reg1.sim)
  {
    case LPS33W_SPI_4_WIRE:
      *val = LPS33W_SPI_4_WIRE;
      break;

    case LPS33W_SPI_3_WIRE:
      *val = LPS33W_SPI_3_WIRE;
      break;

    default:
      *val = LPS33W_SPI_4_WIRE;
      break;
  }

  return ret;
}

/**
  * @brief  Disable I2C interface.[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of i2c_dis in reg CTRL_REG2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_i2c_interface_set(baroDev_t *baro,
                                 lps33w_i2c_dis_t val)
{
  lps33w_ctrl_reg2_t ctrl_reg2;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG2, (uint8_t *)&ctrl_reg2);

  if (ret == 1)
  {
    ctrl_reg2.i2c_dis = (uint8_t)val;
    ret = busWriteBuf(baro->busDev, LPS33W_CTRL_REG2, (uint8_t *)&ctrl_reg2, 1);
  }

  return ret;
}

/**
  * @brief  Disable I2C interface.[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Get the values of i2c_dis in reg CTRL_REG2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_i2c_interface_get(baroDev_t *baro,
                                 lps33w_i2c_dis_t *val)
{
  lps33w_ctrl_reg2_t ctrl_reg2;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG2, (uint8_t *)&ctrl_reg2);

  switch (ctrl_reg2.i2c_dis)
  {
    case LPS33W_I2C_ENABLE:
      *val = LPS33W_I2C_ENABLE;
      break;

    case LPS33W_I2C_DISABLE:
      *val = LPS33W_I2C_DISABLE;
      break;

    default:
      *val = LPS33W_I2C_ENABLE;
      break;
  }

  return ret;
}

/**
  * @brief  Register address automatically incremented during a
  *         multiple byte access with a serial interface (I2C or SPI).[set]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of if_add_inc in reg CTRL_REG2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_auto_add_inc_set(baroDev_t *baro, uint8_t val)
{
  lps33w_ctrl_reg2_t ctrl_reg2;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG2, (uint8_t *)&ctrl_reg2);

  if (ret == 1)
  {
    ctrl_reg2.if_add_inc = val;
    ret = busWriteBuf(baro->busDev, LPS33W_CTRL_REG2, (uint8_t *)&ctrl_reg2, 1);
  }

  return ret;
}

/**
  * @brief  Register address automatically incremented during a
  *         multiple byte access with a serial interface (I2C or SPI).[get]
  *
  * @param  ctx    Read / write interface definitions
  * @param  val    Change the values of if_add_inc in reg CTRL_REG2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lps33w_auto_add_inc_get(baroDev_t *baro, uint8_t *val)
{
  lps33w_ctrl_reg2_t ctrl_reg2;
  int32_t ret;

  ret = busRead(baro->busDev, LPS33W_CTRL_REG2, (uint8_t *)&ctrl_reg2);
  *val = ctrl_reg2.if_add_inc;

  return ret;
}

/**
  * @}
  *
  */

/**
  * @}
  *
  */


static uint32_t lps33w_data_raw_pressure;
static int16_t lps33w_data_raw_temperature;
static uint32_t lps33w_pressure_Pa;
static int32_t lps33w_temperature_cdegC;
static uint8_t lps33w_whoamI, lps33w_rst;
static uint8_t lps33w_temp_reg,lps33w_press_reg;




/**
 * @brief  This function provides a delay (in microseconds)
 * @param  microseconds: delay in microseconds
 */
__STATIC_INLINE void DWT_Delay_us(volatile uint32_t microseconds)
{
  uint32_t clk_cycle_start = DWT->CYCCNT;

  /* Go to number of cycles for system */
  microseconds *= (HAL_RCC_GetHCLKFreq() / 1000000);

  /* Delay till end */
  while ((DWT->CYCCNT - clk_cycle_start) < microseconds);
}


static bool lps33w_start_up(baroDev_t * baro)
{
    UNUSED(baro);
    return true;
}

static bool lps33w_get_up(baroDev_t * baro)
{

	/* Wait data ready */
	lps33w_press_data_ready_get(baro, &lps33w_press_reg);
	if (lps33w_press_reg) {
	  memset(&lps33w_data_raw_pressure, 0x00, sizeof(int32_t));
	  lps33w_pressure_raw_get(baro, &lps33w_data_raw_pressure);
	  lps33w_pressure_Pa = lps33w_from_lsb_to_pa(lps33w_data_raw_pressure);

	  return true;
   	}

   	return false;
}

static bool lps33w_start_ut(baroDev_t * baro)
{
    UNUSED(baro);
    return true;
}

static bool lps33w_get_ut(baroDev_t * baro)
{

	lps33w_temp_data_ready_get(baro, &lps33w_temp_reg);

	if (lps33w_temp_reg) {
	  memset(&lps33w_data_raw_temperature, 0x00, sizeof(int32_t));
	  lps33w_temperature_raw_get(baro, &lps33w_data_raw_temperature);
	  lps33w_temperature_cdegC = lps33w_from_lsb_to_cdegc(lps33w_data_raw_temperature);

	  return true;
	}

	return false;

}



STATIC_UNIT_TESTED bool lps33w_calculate(baroDev_t * baro, int32_t * pressure, int32_t * temperature)
{
    UNUSED(baro);

    if (pressure) {
        //Pressure in Pa
        *pressure = lps33w_pressure_Pa;
    }

    if (temperature) {
        // Temp in centidegrees Celsius
        *temperature = lps33w_temperature_cdegC;
    }

    return true;
}

#define INIT_MAX_RETRY_COUNT   5
static bool lps33wInit(baroDev_t * baro){

	/* Restore default configuration */
	lps33w_reset_set(baro, PROPERTY_ENABLE);
	uint8_t resetCounter = 0;
	do {
		resetCounter++;
		if(lps33w_rst && resetCounter >= INIT_MAX_RETRY_COUNT){
			/* Reset failed, something is wrong with the device communication */
			return false;
		}
		lps33w_reset_get(baro, &lps33w_rst);

	} while (lps33w_rst && resetCounter < INIT_MAX_RETRY_COUNT);

	/* Enable Block Data Update */
	//lps33w_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);
	/* Can be enabled low pass filter on output */
	lps33w_low_pass_filter_mode_set(baro, LPS33W_LPF_ODR_DIV_9);
	/* Can be set Data-ready signal on INT_DRDY pin */
	//lps33w_drdy_on_int_set(&dev_ctx, PROPERTY_ENABLE);
	/* Set Output Data Rate */
	lps33w_data_rate_set(baro, LPS33W_ODR_10_Hz);

    /* Device is ready */
    return true;
}

#define DETECTION_MAX_RETRY_COUNT   5
static bool deviceDetect(baroDev_t *baro){
    for (int retry = 0; retry < DETECTION_MAX_RETRY_COUNT; retry++) {
        
        delay(100);
        /* Check device ID */
        lps33w_device_id_get(baro, &lps33w_whoamI);
        
        if (lps33w_whoamI == LPS33W_ID) {
            /* Device found */

            return true;
        }
    };
    /* Device not found */
    return false;
}

bool lps33wDetect(baroDev_t *baro)
{   


    baro->busDev = busDeviceInit(BUSTYPE_I2C, DEVHW_LPS33W, 0, OWNER_BARO);
    if (baro->busDev == NULL) {
        return false;
    }

    busSetSpeed(baro->busDev, BUS_SPEED_STANDARD);

    if (!deviceDetect(baro)) {
        busDeviceDeInit(baro->busDev);
        return false;
    }

    lps33wInit(baro);

    /* Trigger one shot data acquisition */
    lps33w_one_shoot_trigger_set(baro, PROPERTY_ENABLE);


    baro->ut_delay = 0;
    baro->get_ut = lps33w_get_ut;
    baro->start_ut = lps33w_start_ut;

    baro->up_delay = 1000;
    baro->start_up = lps33w_start_up;
    baro->get_up = lps33w_get_up;

    baro->calculate = lps33w_calculate;

    return true;
}


#endif
