/**
  ******************************************************************************
  * @file    tcpp01_io.c
  * @author  MCD Application Team
  * @brief   This file contains all the functions implementations for the
  *          tcpp0203.
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

#include "tcpp0203_io.h"


/**
  * @brief Initializes the IO layer by assigning resources to the IO object.
  * @retval 0 in case of success, -1 in case of error
  */
int32_t tcpp0203_io_init(mfxstm32l152_io_t *pio)
{
  switch (pio->id)
  {
    /* assign resources to the pio according to its ID */
    /* case TCPP0203_ID_0: ... */
    default:
      return -1; /* unrecognized object: return an error */
  }
  return 0;
}

/**
  * @brief Power On Device.
  * @param  pio      : the IO instance object
  */
void tcpp0203_io_power_on(tcpp0203_io_t *pio)
{

}

/**
  * @brief Power Off Device.
  * @param  pio      : the IO instance object
  */
void tcpp0203_io_power_off(tcpp0203_io_t *pio)
{

}

/**
  * @brief  The read register function for TCPP0203 IO flavor.
  * @param  pio     : the IO instance object
  * @param  reg     : the device register to read
  * @param  pdata   : the pointer where the read data are written
  * @retval 0 in case of success, -1 otherwise
  */
int32_t tcpp0203_io_read_reg(tcpp0203_io_t *pio, const uint16_t reg, uint8_t *pdata)
{
  return -1;
}

/**
  * @brief  The write register function for TCPP0203 IO flavor.
  * @param  pio     : the IO instance object
  * @param  reg     : the device register to write
  * @param  pdata   : the write data
  * @retval 0 in case of success, -1 otherwise
  */
int32_t tcpp0203_io_write_reg(tcpp0203_io_t *pio, const uint16_t reg, uint8_t *pdata)
{
  return -1;
}

/**
  * @brief This function starts interrupt request on type C Cable plug event.
  * @param  pio         : the IO instance object
  * @retval 0 in case of success, -1 otherwise
  */
int32_t tcpp0203_io_start_it(tcpp0203_io_t *pio)
{
  return -1;
}

/**
  * @brief This function stops interrupt request on type C cable plug event.
  * @param  pio         : the IO instance object
  * @retval 0 in case of success, -1 otherwise
  */
int32_t tcpp0203_io_stop_it(tcpp0203_io_t *pio)
{
  return -1;
}

/**
  * @brief This function enables interrupt request on type C cable plug event.
  * @param  pio         : the IO instance object
  */
void tcpp0203_io_enable_irq(tcpp0203_io_t *pio)
{

}

/**
  * @brief This function disable the interrupt for type C cable plug event.
  * @param  pio         : the IO instance object
  */
void tcpp0203_io_disable_irq(tcpp0203_io_t *pio)
{

}

/**
  * @brief This function Clear interrupt pending bit of the selected EXTI line.
  * @param  pio         : the IO instance object
  */
void tcpp0203_io_clear_irq(tcpp0203_io_t *pio)
{

}

#if defined (TCPP0203_CALLBACKS) && (TCPP0203_CALLBACKS == 1)

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

  /* Implement your own callback mechanism here. */

  return -1;
}


#endif /* USE_TCPP0203_CALLBACKS */
