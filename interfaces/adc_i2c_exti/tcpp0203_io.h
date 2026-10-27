/**
  ******************************************************************************
  * @file    tcpp0203_io.h
  * @brief   tcpp0203 header IO driver file for I2C
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
#include "stm32_hal.h"

/* Macros definitions */

#define TCPP0203_ADC_CONVERSION_TIMEOUT  10U   /*!< ADC conversion time out value (10 ms) */

#if defined (USE_HAL_EXTI_REGISTER_CALLBACKS) && (USE_HAL_EXTI_REGISTER_CALLBACKS == 1)
#if defined (USE_HAL_EXTI_USER_DATA) && (USE_HAL_EXTI_USER_DATA == 1)
#define TCPP0203_CALLBACKS 1
#endif /* USE_HAL_EXTI_USER_DATA */
#endif /* USE_HAL_EXTI_REGISTER_CALLBACKS */

#define TCPP0203_POLLING_TIMEOUT         2000U   /*!< Default I2C timeout in polling mode (2s) */
#define TCPP0203_IANA_ISENSE_GA          42U     /* Current measure gain In V/V */

/* Exported types ------------------------------------------------------------*/

typedef struct tcpp0203_io_s tcpp0203_io_t;   /*!< IO structure type */

#if defined (TCPP0203_CALLBACKS) && (TCPP0203_CALLBACKS == 1)
/* io_trigger: 0=RISING, 1=FALLING */

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
  hal_i2c_handle_t   *phi2c;        /*!< I2C HAL handle for communication           */
  hal_exti_handle_t  *phexti;       /*!< EXTI HAL handle for Flgn pin               */
  hal_adc_handle_t   *phadc;        /*!< ADC HAL handle for VBUS sensing            */
  uint8_t            addr;          /*!< I2C address of TCPP0203 device               */
  uint32_t           id;            /*!< Instance ID                                */
  uint32_t           Ra;            /*!< VBUS voltage divider RA                    */
  uint32_t           Rb;            /*!< VBUS voltage divider RA                    */
  uint32_t           Rs;            /*!< Current measure shunt resistor in milliohm */
  uint32_t           Vdd;           /*!< Value of VDD in mv                         */
  uint8_t            active_state;  /*!< Hardware active enable pin state           */
  hal_gpio_t         enb_port;      /*!< Hardware enable port                       */
  uint32_t           enb_pin;       /*!< Hardware enable pin                        */
  IRQn_Type          irq_line;      /*!< TCPP0203 interrupt request line              */
#if defined (TCPP0203_CALLBACKS) && (TCPP0203_CALLBACKS == 1)
  tcpp0203_io_cb_ctx_t     exti_cb_ctx;      /*!< EXTI callback */
#endif /* TCPP0203_CALLBACKS */
};


int32_t tcpp0203_io_init(tcpp0203_io_t *pio);
void tcpp0203_io_power_on(tcpp0203_io_t *pio);
void tcpp0203_io_power_off(tcpp0203_io_t *pio);
int32_t tcpp0203_io_write_reg(tcpp0203_io_t *pio, const uint16_t reg, uint8_t *pdata);
int32_t tcpp0203_io_read_reg(tcpp0203_io_t *pio, const uint16_t reg, uint8_t *pdata);
int32_t tcpp0203_io_get_adc_value(tcpp0203_io_t *pio, uint32_t *p_adc_value);
uint32_t tcpp0203_io_get_vbus_voltage(tcpp0203_io_t *pio, uint32_t adc_value);
uint32_t tcpp0203_io_get_vbus_current(tcpp0203_io_t *pio, uint32_t adc_value);
int32_t tcpp0203_io_start_it(tcpp0203_io_t *pio);
int32_t tcpp0203_io_stop_it(tcpp0203_io_t *pio);
void tcpp0203_io_enable_irq(tcpp0203_io_t *pio);
void tcpp0203_io_disable_irq(tcpp0203_io_t *pio);
void tcpp0203_io_clear_irq(tcpp0203_io_t *pio);
int32_t tcpp0203_io_stop(tcpp0203_io_t *pio);
int32_t tcpp0203_io_start(tcpp0203_io_t *pio);
#if defined (TCPP0203_CALLBACKS) && (TCPP0203_CALLBACKS == 1)
int32_t tcpp0203_io_register_callback(tcpp0203_io_t *pio, tcpp0203_io_callback_t io_cb, void *p_arg);
#endif /* USE_TCPP0203_CALLBACKS */


#ifdef __cplusplus
}
#endif

#endif /* TCPP0203_IO_H */

