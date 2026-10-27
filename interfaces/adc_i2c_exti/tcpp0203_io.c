/**
  ******************************************************************************
  * @file    tcpp0203_io.c
  * @brief   TCPP0203 IO driver file for I2C
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

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

#include "tcpp0203_io.h"

/*private functions */
static void tcpp0203_io_set_enb_pin(tcpp0203_io_t *pio, uint8_t state);


/**
  * @brief  Initialize the TCPP0203 IO I2C flavor.
  * @param  pio : the IO instance object
  * @retval error status
  */
__WEAK int32_t tcpp0203_io_init(tcpp0203_io_t *pio)
{
  (void)(pio);
  return  -1;
}


/**
  * @brief Enable Pin control.
  * @param  pio      : the IO instance object
  * @param  state    : the pin state
  */
static void tcpp0203_io_set_enb_pin(tcpp0203_io_t *pio, uint8_t state)
{
  /* pin state */
  hal_gpio_pin_state_t pin_state;

  /* Check Pin State */
  if (state == 1U)
  {
    pin_state = HAL_GPIO_PIN_SET;
  }
  else
  {
    /* reset pin in other case */
    pin_state = HAL_GPIO_PIN_RESET;
  }

  /* Update Pin State */
  HAL_GPIO_WritePin(pio->enb_port, pio->enb_pin, pin_state);
}

/**
  * @brief Power On Device.
  * @param  pio      : the IO instance object
  */
void tcpp0203_io_power_on(tcpp0203_io_t *pio)
{
  /* Power ON */
  tcpp0203_io_set_enb_pin(pio, pio->active_state);
}

/**
  * @brief Power Off Device.
  * @param  pio      : the IO instance object
  */
void tcpp0203_io_power_off(tcpp0203_io_t *pio)
{
  /* Power OFF */
  tcpp0203_io_set_enb_pin(pio, (pio->active_state == 0U) ? 1U : 0U);
}

/**
  * @brief  The read register function for TCPP0203 IO I2C flavor.
  * @param  pio     : the IO instance object
  * @param  reg     : the device register to read
  * @param  pdata   : the pointer where the read data are written
  * @retval 0 in case of success, -1 otherwise
  */
int32_t tcpp0203_io_read_reg(tcpp0203_io_t *pio, const uint16_t reg, uint8_t *pdata)
{
  int32_t ret = 0;

  if (HAL_I2C_MASTER_MemRead(pio->phi2c, pio->addr, reg, HAL_I2C_MEM_ADDR_8BIT, pdata,
                             1, TCPP0203_POLLING_TIMEOUT) != HAL_OK)
  {
    ret = -1;
  }
  return ret;
}

/**
  * @brief  The write register function for TCPP0203 IO I2C flavor.
  * @param  pio     : the IO instance object
  * @param  reg     : the device register to write
  * @param  pdata   : the write data
  * @retval 0 in case of success, -1 otherwise
  */
int32_t tcpp0203_io_write_reg(tcpp0203_io_t *pio, const uint16_t reg, uint8_t *pdata)
{
  int32_t ret = 0;

  if (HAL_I2C_MASTER_MemWrite(pio->phi2c, pio->addr, reg, HAL_I2C_MEM_ADDR_8BIT, pdata,
                              1, TCPP0203_POLLING_TIMEOUT) != HAL_OK)
  {
    ret = -1;
  }
  return ret;
}

/**
  * @brief  Get actual adc value measured on the VBUS line.
  * @param  pio  : the IO instance object
  * @retval measured adc value
  */
int32_t tcpp0203_io_get_adc_value(tcpp0203_io_t *pio, uint32_t *p_adc_value)
{
  hal_adc_config_t Config;
  uint32_t AdcFullScale;
  /* Initialize default part status */
  int32_t ret_val = -1;

  /* Retrieve the ADC conversion data */
  HAL_ADC_GetConfig(pio->phadc, &Config);
  AdcFullScale = (uint32_t)(HAL_ADC_DIGITAL_SCALE(Config.resolution));

  if (AdcFullScale != 0U)
  {
    /* Retrieve the ADC conversion data */
    *p_adc_value = (uint32_t)HAL_ADC_REG_ReadConversionData(pio->phadc);
    *p_adc_value = (uint32_t)((*p_adc_value * pio->Vdd) / AdcFullScale);
    /* Update part status */
    ret_val = 0;
  }

  /* Return part io status */
  return ret_val;
}

/**
  * @brief This function starts the ADC conversion.
  * @param  pio        : the IO instance object
  * @retval 0 in case of success, -1 otherwise
  */
int32_t tcpp0203_io_start(tcpp0203_io_t *pio)
{
  /* Initialize default part status */
  int32_t ret_val = -1;

  if (HAL_ADC_REG_StartConv(pio->phadc) == HAL_OK)
  {
    if (HAL_ADC_REG_PollForConv(pio->phadc, TCPP0203_ADC_CONVERSION_TIMEOUT) == HAL_OK)
    {
      /* Update part status */
      ret_val = 0;
    }
  }

  /* Return part io status */
  return ret_val;
}

/**
  * @brief This function stops the ADC conversion.
  * @param  pio         : the IO instance object
  * @retval 0 in case of success, -1 otherwise
  */
int32_t tcpp0203_io_stop(tcpp0203_io_t *pio)
{
  /* Initialize default part status */
  int32_t ret_val = -1;

  if (HAL_ADC_REG_StopConv(pio->phadc) == HAL_OK)
  {
    /* Update part status */
    ret_val = 0;
  }

  /* Return part io status */
  return ret_val;
}

/**
  * @brief  Get actual voltage level measured on the VBUS line.
  * @param  pio       : the IO instance object
  * @param  adc_value : measured ADC value
  * @note   Voltage level is measured though a voltage divider
  * @note   AdcValue = Voltage * Rb /(Ra + Rb)
  * @retval measured voltage value
  */
uint32_t tcpp0203_io_get_vbus_voltage(tcpp0203_io_t *pio, uint32_t adc_value)
{
  uint32_t Voltage;

  Voltage = (uint32_t)(adc_value * (pio->Ra + pio->Rb) / pio->Rb);

  return Voltage;
}

/**
  * @brief  Get actual current level measured on the VBUS line.
  * @param  pio       : the IO instance object
  * @param  adc_value : measured ADC value
  * @retval measured current value
  */
uint32_t tcpp0203_io_get_vbus_current(tcpp0203_io_t *pio, uint32_t adc_value)
{
  uint32_t Current;

  Current = (uint32_t)((adc_value * 1000U) / (TCPP0203_IANA_ISENSE_GA * pio->Rs));

  return Current;
}

/**
  * @brief This function starts interrupt request on type C Cable plug event.
  * @param  pio         : the IO instance object
  * @retval 0 in case of success, -1 otherwise
  */
int32_t tcpp0203_io_start_it(tcpp0203_io_t *pio)
{
  /* Initialize default part status */
  int32_t ret_val = -1;

  /* Start the selected EXTI line on Interrupt Mode. */
  if (HAL_EXTI_Enable(pio->phexti, HAL_EXTI_MODE_INTERRUPT) == HAL_OK)
  {
    /* Update part status */
    ret_val = 0;
  }
  /* Return part io status */
  return ret_val;
}

/**
  * @brief This function stops interrupt request on type C cable plug event.
  * @param  pio         : the IO instance object
  * @retval 0 in case of success, -1 otherwise
  */
int32_t tcpp0203_io_stop_it(tcpp0203_io_t *pio)
{
  /* Initialize default part status */
  int32_t ret_val = -1;

  /* Stop the selected EXTI line. */
  if (HAL_EXTI_Disable(pio->phexti) == HAL_OK)
  {
    /* Update part status */
    ret_val = 0;
  }

  /* Return part io status */
  return ret_val;
}

/**
  * @brief This function enables interrupt request on type C cable plug event.
  * @param  pio         : the IO instance object
  */
void tcpp0203_io_enable_irq(tcpp0203_io_t *pio)
{
  /* Enable NVIC interrupt request for the selected EXTI line.*/
  HAL_CORTEX_NVIC_EnableIRQ(pio->irq_line);
}

/**
  * @brief This function disable the interrupt for type C cable plug event.
  * @param  pio         : the IO instance object
  */
void tcpp0203_io_disable_irq(tcpp0203_io_t *pio)
{
  /* Disable NVIC interrupt request for the selected EXTI line.*/
  HAL_CORTEX_NVIC_DisableIRQ(pio->irq_line);
}

/**
  * @brief This function Clear interrupt pending bit of the selected EXTI line.
  * @param  pio         : the IO instance object
  */
void tcpp0203_io_clear_irq(tcpp0203_io_t *pio)
{
  /* Clear interrupt pending bit of the selected EXTI line. */
  HAL_EXTI_ClearPending(pio->phexti, HAL_EXTI_TRIGGER_RISING_FALLING);
}

#if defined (TCPP0203_CALLBACKS) && (TCPP0203_CALLBACKS == 1)

static void EXTI_Callback(hal_exti_handle_t *p_exti, hal_exti_trigger_t trigger)
{
  tcpp0203_io_t *pio = (tcpp0203_io_t *)HAL_EXTI_GetUserData(p_exti);
  pio->exti_cb_ctx.io_callback(pio, (trigger == HAL_EXTI_TRIGGER_FALLING), pio->exti_cb_ctx.parg);
}

/**
  * @brief Registration of exti callback.
  * @param  pio      : The IO instance object.
  * @param  io_cb    : Callback function to be registered.
  * @param  p_arg    : Optional argument given to the callback
  * @retval 0 in case of success, -1 otherwise
  */

int32_t tcpp0203_io_register_callback(tcpp0203_io_t *pio, tcpp0203_io_callback_t io_cb, void *p_arg)
{
  pio->exti_cb_ctx.io_callback = io_cb;
  pio->exti_cb_ctx.parg = p_arg;
  HAL_EXTI_SetUserData(pio->phexti, pio);
  /* Initialize default part status */
  int32_t ret_val = -1;

  /* Register callback*/
  if (HAL_EXTI_RegisterTriggerCallback(pio->phexti, EXTI_Callback) == HAL_OK)
  {
    /* Update part status */
    ret_val = 0;
  }
  /* Return part io status */
  return ret_val;
}


#endif /* USE_TCPP0203_CALLBACKS */
