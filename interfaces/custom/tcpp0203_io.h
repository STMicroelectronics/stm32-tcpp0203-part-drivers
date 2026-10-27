/**
  ******************************************************************************
  * @file    tcpp01_io.h
  * @author  MCD Application Team
  * @brief   This file contains all the functions prototypes for the
  *          tcpp0203_io.c .
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef TCPP0203_IO_H
#define TCPP0203_IO_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/*
 * Callback features are optional; the feature flag TCPP01_CALLBACKS signals their availability.
 * You can conditionally define this flag based on any preprocessor condition.
 * Examples using feature flags in mx_hal_def.h: USE_HAL_EXTI_REGISTER_CALLBACKS, USE_HAL_EXTI_USER_DATA...
 */
#define TCPP0203_CALLBACKS 1

/* Exported types ------------------------------------------------------------*/

typedef struct tcpp0203_io_s tcpp0203_io_t;   /*!< IO structure type */

#if defined (TCPP0203_CALLBACKS) && (TCPP0203_CALLBACKS == 1)
/** io_trigger: 0=RISING, 1=FALLING */

typedef void (*tcpp0203_io_callback_t)(tcpp0203_io_t *pio, uint8_t io_trigger, void *arg);  /*!< IO callback function pointer definition */


/**
  * @brief Callback context structure
  */
typedef struct
{
  tcpp0203_io_callback_t io_callback;    /*!< IO callback function to register        */
  void *parg;                          /*!< Optional argument given to the callback */
} tcpp0203_io_cb_ctx_t;
#endif /* TCPP0203_CALLBACKS */

/**
  * @brief I2C IO interface structure
  */

struct tcpp0203_io_s
{
  uint32_t           id;            /*!< Configuration ID                          */

  /* Add fields as needed to store HAL handles and other resources */
#if defined (TCPP0203_CALLBACKS) && (TCPP0203_CALLBACKS == 1)
  tcpp0203_io_cb_ctx_t     exti_cb_ctx;      /*!< EXTI callback */
#endif /* TCPP0203_CALLBACKS */
};


int32_t tcpp0203_io_init(tcpp0203_io_t *pio);
void tcpp0203_io_power_on(tcpp0203_io_t *pio);
void tcpp0203_io_power_off(tcpp0203_io_t *pio);
int32_t tcpp0203_io_write_reg(tcpp0203_io_t *pio, const uint16_t reg, uint8_t *pdata);
int32_t tcpp0203_io_read_reg(tcpp0203_io_t *pio, const uint16_t reg, uint8_t *pdata);
int32_t tcpp0203_io_start_it(tcpp0203_io_t *pio);
int32_t tcpp0203_io_stop_it(tcpp0203_io_t *pio);
void tcpp0203_io_enable_irq(tcpp0203_io_t *pio);
void tcpp0203_io_disable_irq(tcpp0203_io_t *pio);
void tcpp0203_io_clear_irq(tcpp0203_io_t *pio);
#if defined (TCPP0203_CALLBACKS) && (TCPP0203_CALLBACKS == 1)
int32_t tcpp0203_io_register_callback(tcpp0203_io_t *pio, tcpp0203_io_callback_t io_cb, void *p_arg);
#endif /* USE_TCPP0203_CALLBACKS */


#ifdef __cplusplus
}
#endif

#endif /* TCPP0203_IO_H */

