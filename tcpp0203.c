/**
  ******************************************************************************
  * @file    tcpp0203.c
  * @modify  MCD Application Team
  * @brief   TCPP0203 driver file
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
#include "tcpp0203.h"


static tcpp0203_status_t tcpp0203_modify_reg0(tcpp0203_obj_t *pobj, uint8_t Value, uint8_t Mask);


/**
  * @brief  Initialize the TCPP0203 component and configure the needed hardware resources.
  * @param  pobj     : Part object pointer.
  * @param  dev_id   : Instance ID
  * @retval error status
  */
tcpp0203_status_t tcpp0203_init(tcpp0203_obj_t *pobj, uint32_t id)
{
  pobj->pio.id = id;
  /* Initialize the IO BUS layer */
  if (pobj->is_initialized == 0U)
  {
    if (tcpp0203_io_init(&pobj->pio) != 0)
    {
      return TCPP0203_ERROR;
    }

    /* Read the TCPP device type (TCPP02 or TCPP03) and store it in the part object */
    if (tcpp0203_read_tcpp_type(pobj, &pobj->tcpp_type) != TCPP0203_OK)
    {
      return TCPP0203_ERROR;
    }

    tcpp0203_io_power_on(&pobj->pio);
    pobj->is_initialized = 1U;
  }

  return TCPP0203_OK;
}


/**
  * @brief  Deinitialize the TCPP0203 component.
  * @param  pobj     : Part object pointer.
  * @retval error status
  */
tcpp0203_status_t tcpp0203_deinit(tcpp0203_obj_t *pobj)
{
  /* Initialize default part status */
  tcpp0203_status_t ret = TCPP0203_ERROR;

  if (pobj->is_initialized != 0U)
  {
    /* Power Off */
    tcpp0203_io_power_off(&(pobj->pio));

    /* Update State */
    pobj->is_initialized = 0U;
    /* Update part status */
    ret = TCPP0203_OK;
  }

  /* Return part status */
  return ret;
}

/**
  * @brief Clear, Enable and Start interrupt request on type C cable plugged event.
  * @param  pobj       : Part object pointer.
  * @retval error status
  */
tcpp0203_status_t tcpp0203_enable_it(tcpp0203_obj_t *pobj)
{
  /* Initialize default part status */
  tcpp0203_status_t ret = TCPP0203_ERROR;

  /* Check param */
  if (pobj == NULL)
  {
    ret = TCPP0203_INVALID_PARAM;
  }
  else
  {
    /* Check part if is initialized */
    if (pobj->is_initialized == 1U)
    {
      /* Clear interrupt pending bit of the selected EXTI line */
      tcpp0203_io_clear_irq(&(pobj->pio));
      /* Enable external interrupt pin */
      tcpp0203_io_enable_irq(&(pobj->pio));
      /* Start interrupt request */
      if (tcpp0203_io_start_it(&(pobj->pio)) == 0)
      {
        /* Update part status */
        ret = TCPP0203_OK;
      }
    }
  }

  /* Return part status */
  return ret;
}

/**
  * @brief Clear, Disable and Stop the interrupt for type C cable plugged event.
  * @param  pobj       : Part object pointer.
  * @retval error status
  */
tcpp0203_status_t tcpp0203_disable_it(tcpp0203_obj_t *pobj)
{
  /* Initialize default part status */
  tcpp0203_status_t ret = TCPP0203_ERROR;

  /* Check param */
  if (pobj == NULL)
  {
    ret = TCPP0203_INVALID_PARAM;
  }
  else
  {
    /* Check part if is initialized */
    if (pobj->is_initialized == 1U)
    {
      /* Clear interrupt pending bit of the selected EXTI line */
      tcpp0203_io_clear_irq(&(pobj->pio));
      /* Disable external interrupt pin */
      tcpp0203_io_disable_irq(&(pobj->pio));
      /* Stop interrupt request */
      if (tcpp0203_io_stop_it(&(pobj->pio)) == 0)
      {
        /* Update part status */
        ret = TCPP0203_OK;
      }
    }
  }


  /* Return part status */
  return ret;
}

/**
  * @brief Clear interrupt request on type C cable detected event.
  * @param  pobj       : Part object pointer.
  */
void tcpp0203_clear_it(tcpp0203_obj_t *pobj)
{
  tcpp0203_io_clear_irq(&(pobj->pio));
}

#if defined (TCPP0203_CALLBACKS) && (TCPP0203_CALLBACKS == 1)

static void tcpp0203_io_rising_callback(tcpp0203_io_t *pio, uint8_t io_trigger, void *parg)
{
  (void)(pio);
  tcpp0203_obj_t *pobj = parg;

  /* io_trigger = 0 means rising edge */
  if (io_trigger == 0U)
  {
    pobj->cb_rising_ctx.callback(pobj, pobj->cb_rising_ctx.parg);
  }
  tcpp0203_clear_it(pobj);
}

static void tcpp0203_io_falling_callback(tcpp0203_io_t *pio, uint8_t io_trigger, void *parg)
{
  (void)(pio);
  tcpp0203_obj_t *pobj = parg;

  /* io_trigger = 1 means falling edge */
  if (io_trigger == 1U)
  {
    pobj->cb_falling_ctx.callback(pobj, pobj->cb_falling_ctx.parg);
  }
  tcpp0203_clear_it(pobj);
}

/**
  * @brief This function registers a callback function for the tcpp0203.
  * In hibernate and low power modes it signifies VBUS detection
  * @param pobj  : Part object pointer.
  * @param pcb   : Callback function
  * @param arg   : Optional argument given to the callback
  * @retval      error status
  */

tcpp0203_status_t tcpp0203_register_cable_plugged_callback(tcpp0203_obj_t *pobj, tcpp0203_callback_t pcb, void *p_arg)
{
  /* Initialize default part status */
  tcpp0203_status_t ret = TCPP0203_ERROR;

  /* Check param */
  if (pobj == NULL)
  {
    ret = TCPP0203_INVALID_PARAM;
  }
  else
  {
    /* Check part if is initialized */
    if (pobj->is_initialized == 1U)
    {
      pobj->cb_falling_ctx.callback = pcb;
      pobj->cb_falling_ctx.parg = p_arg;

      /* Register falling callback */
      if (tcpp0203_io_register_callback(&(pobj->pio), tcpp0203_io_falling_callback, pobj) == 0)
      {
        /* Update part status */
        ret = TCPP0203_OK;
      }
    }
  }

  /* Return error status */
  return ret;
}

/**
  * @brief This function registers a callback function for the tcpp0203.
  * In hibernate and low power modes, it signifies VBUS undetection.
  * @param pobj     : Part object pointer.
  * @param pcb      : Callback function
  * @param arg      : Optional argument given to the callback
  * @retval         error status
  */

tcpp0203_status_t tcpp0203_register_cable_unplugged_callback(tcpp0203_obj_t *pobj, tcpp0203_callback_t pcb, void *p_arg)
{
  /* Initialize default part status */
  tcpp0203_status_t ret = TCPP0203_ERROR;

  /* Check param */
  if (pobj == NULL)
  {
    ret = TCPP0203_INVALID_PARAM;
  }
  else
  {
    pobj->cb_rising_ctx.callback = pcb;
    pobj->cb_rising_ctx.parg = p_arg;

    /* Check part if is initialized */
    if (pobj->is_initialized == 1U)
    {
      /* Register rising callback */
      if (tcpp0203_io_register_callback(&(pobj->pio), tcpp0203_io_rising_callback, pobj) == 0)
      {
        /* Update part status */
        ret = TCPP0203_OK;
      }
    }
  }

  /* Return part status */
  return ret;
}
#endif /* USE_TCPP0203_CALLBACKS */

/**
  * @brief  Resets TCPP0203 register (Reg0).
  * @param  pobj : Part object pointer.
  * @retval error status
  */
tcpp0203_status_t tcpp0203_reset(tcpp0203_obj_t *pobj)
{
  tcpp0203_status_t status = TCPP0203_OK;
  uint8_t tmp = (uint8_t)TCPP0203_REG0_RST_VALUE;

  /* Write reset values in Reg0 register */
  if (tcpp0203_io_write_reg(&pobj->pio, TCPP0203_PROG_CTRL, &tmp) != 0)
  {
    status = TCPP0203_ERROR;
  }

  return status;
}

/**
  * @brief  Configure TCPP0203 VConn Switch.
  * @param  pobj        : Part object pointer.
  * @param  vconn_switch : VConn Switch requested setting
  *         This parameter can be one of the following values:
  *          @arg TCPP0203_VCONN_SWITCH_OPEN VConn switch open
  *          @arg TCP03_VCONN_SWITCH_CC1  VConn closed on CC1
  *          @arg TCPP0203_VCONN_SWITCH_CC2  VConn closed on CC2
  * @retval error status
  */
tcpp0203_status_t tcpp0203_set_vconn_switch(tcpp0203_obj_t *pobj, tcpp0203_vconn_switch_t vconn_switch)
{
  tcpp0203_status_t status;

  if ((vconn_switch != TCPP0203_VCONN_SWITCH_OPEN)
      && (vconn_switch != TCPP0203_VCONN_SWITCH_CC1)
      && (vconn_switch != TCPP0203_VCONN_SWITCH_CC2))
  {
    status = TCPP0203_ERROR;
  }
  else
  {
    /* Update VConn switch setting in Writing register Reg0 */
    status = tcpp0203_modify_reg0(pobj, (uint8_t)vconn_switch, TCPP0203_VCONN_SWITCH_MSK);
  }

  return status;
}

/**
  * @brief  Configure TCPP0203 Gate Driver for Provider path.
  * @param  pobj                : Part object pointer.
  * @param  gate_driver_povider : GDP switch load requested setting
  *         This parameter can be one of the following values:
  *          @arg TCPP0203_GD_PROVIDER_SWITCH_OPEN    GDP Switch Load Open
  *          @arg TCPP0203_GD_PROVIDER_SWITCH_CLOSED  GDP Switch Load closed
  * @retval error status
  */
tcpp0203_status_t tcpp0203_set_gate_driver_provider(tcpp0203_obj_t *pobj,
                                                    tcpp0203_gate_driver_provider_t gate_driver_povider)
{
  tcpp0203_status_t status;

  if ((gate_driver_povider != TCPP0203_GD_PROVIDER_SWITCH_OPEN)
      && (gate_driver_povider != TCPP0203_GD_PROVIDER_SWITCH_CLOSED))
  {
    status = TCPP0203_ERROR;
  }
  else
  {
    /* Update GDP Switch Load setting in Writing register Reg0 */
    if (gate_driver_povider == TCPP0203_GD_PROVIDER_SWITCH_CLOSED)
    {
      /* If Gate Driver Provider is to be closed, Gate Driver Consumer must be open */
      status = tcpp0203_modify_reg0(pobj, ((uint8_t)gate_driver_povider | (uint8_t)TCPP0203_GD_CONSUMER_SWITCH_OPEN),
                                    ((uint8_t)TCPP0203_GD_PROVIDER_SWITCH_MSK |
                                     (uint8_t)TCPP0203_GD_CONSUMER_SWITCH_MSK));
    }
    else
    {
      status = tcpp0203_modify_reg0(pobj, (uint8_t)gate_driver_povider, TCPP0203_GD_PROVIDER_SWITCH_MSK);
    }
  }

  return status;
}

/**
  * @brief  Configure TCPP0203 Gate Driver for Consumer path.
  * @param  pobj                 : Part object pointer.
  * @param  gate_driver_consumer : GDC switch load requested setting
  *         This parameter can be one of the following values:
  *          @arg TCPP0203_GD_CONSUMER_SWITCH_OPEN    GDC Switch Load Open
  *          @arg TCPP0203_GD_CONSUMER_SWITCH_CLOSED  GDC Switch Load closed
  * @note   This feature is only supported by TCPP03. When the device is a TCPP02,
  *         this function returns TCPP0203_NOT_SUPPORTED.
  * @retval error status
  */
tcpp0203_status_t tcpp0203_set_gate_driver_consumer(tcpp0203_obj_t *pobj,
                                                    tcpp0203_gate_driver_consumer_t gate_driver_consumer)
{
  tcpp0203_status_t status;

  /* Check if TCPP type is TCPP03. Otherwise, return error */
  if (pobj->tcpp_type != TCPP0203_DEVICE_TYPE_03)
  {
    return TCPP0203_NOT_SUPPORTED;
  }

  if ((gate_driver_consumer != TCPP0203_GD_CONSUMER_SWITCH_OPEN)
      && (gate_driver_consumer != TCPP0203_GD_CONSUMER_SWITCH_CLOSED))
  {
    status = TCPP0203_ERROR;
  }
  else
  {
    /* Update GDC Switch Load setting in Writing register Reg0 */
    if (gate_driver_consumer == TCPP0203_GD_CONSUMER_SWITCH_CLOSED)
    {
      /* If Gate Driver Consumer is to be closed, Gate Driver Provider must be open */
      status = tcpp0203_modify_reg0(pobj, ((uint8_t)gate_driver_consumer | (uint8_t)TCPP0203_GD_PROVIDER_SWITCH_OPEN),
                                    ((uint8_t)TCPP0203_GD_PROVIDER_SWITCH_MSK |
                                     (uint8_t)TCPP0203_GD_CONSUMER_SWITCH_MSK));
    }
    else
    {
      status = tcpp0203_modify_reg0(pobj, (uint8_t)gate_driver_consumer, TCPP0203_GD_CONSUMER_SWITCH_MSK);
    }
  }

  return status;
}

/**
  * @brief  Configure TCPP0203 Power Mode.
  * @param  pobj       : Part object pointer.
  * @param  power_mode : Power mode requested setting
  *         This parameter can be one of the following values:
  *          @arg TCPP0203_POWER_MODE_HIBERNATE    Hibernate
  *          @arg TCPP0203_POWER_MODE_LOWPOWER     Low Power
  *          @arg TCPP0203_POWER_MODE_NORMAL       Normal
  * @retval error status
  */
tcpp0203_status_t tcpp0203_set_power_mode(tcpp0203_obj_t *pobj, tcpp0203_power_mode_t power_mode)
{
  tcpp0203_status_t status;

  if ((power_mode != TCPP0203_POWER_MODE_HIBERNATE)
      && (power_mode != TCPP0203_POWER_MODE_LOWPOWER)
      && (power_mode != TCPP0203_POWER_MODE_NORMAL))
  {
    status = TCPP0203_ERROR;
  }
  else
  {
    /* Update Power Mode setting in Writing register Reg0 */
    status = tcpp0203_modify_reg0(pobj, (uint8_t)power_mode, TCPP0203_POWER_MODE_MSK);
  }

  return status;
}

/**
  * @brief  Configure TCPP0203 VBUS discharge.
  * @param  pobj           : Part object pointer.
  * @param  vbus_discharge : VBUS Discharge requested setting
  *         This parameter can be one of the following values:
  *          @arg TCPP0203_VBUS_DISCHARGE_OFF    VBUS Discharge Off
  *          @arg TCPP0203_VBUS_DISCHARGE_ON     VBUS Discharge On
  * @retval error status
  */
tcpp0203_status_t tcpp0203_set_vbus_discharge(tcpp0203_obj_t *pobj, tcpp0203_vbus_discharge_t vbus_discharge)
{
  tcpp0203_status_t status;

  if ((vbus_discharge != TCPP0203_VBUS_DISCHARGE_OFF)
      && (vbus_discharge != TCPP0203_VBUS_DISCHARGE_ON))
  {
    status = TCPP0203_ERROR;
  }
  else
  {
    /* Update VBUS Discharge setting in Writing register Reg0 */
    status = tcpp0203_modify_reg0(pobj, (uint8_t)vbus_discharge, TCPP0203_VBUS_DISCHARGE_MSK);
  }

  return status;
}

/**
  * @brief  Configure TCPP0203 Vconn discharge.
  * @param  pobj            : Part object pointer.
  * @param  vconn_discharge : VCONN Discharge requested setting
  *         This parameter can be one of the following values:
  *          @arg TCPP0203_VCONN_DISCHARGE_OFF    VConn Discharge Off
  *          @arg TCPP0203_VCONN_DISCHARGE_ON     VConn Discharge On
  * @retval error status
  */
tcpp0203_status_t tcpp0203_set_vconn_discharge(tcpp0203_obj_t *pobj, tcpp0203_vconn_discharge_t vconn_discharge)
{
  tcpp0203_status_t status;

  if ((vconn_discharge != TCPP0203_VCONN_DISCHARGE_OFF)
      && (vconn_discharge != TCPP0203_VCONN_DISCHARGE_ON))
  {
    status = TCPP0203_ERROR;
  }
  else
  {
    /* Update VConn Discharge setting in Writing register Reg0 */
    status = tcpp0203_modify_reg0(pobj, (uint8_t)vconn_discharge, TCPP0203_VCONN_DISCHARGE_MSK);
  }

  return status;
}

/**
  * @brief  Get VConn switch Ack value.
  * @param  pobj               : Part object pointer.
  * @param  p_vconn_switch_ack : Pointer on VConn switch Ack value
  *         This output parameter can be one of the following values:
  *          @arg TCPP0203_VCONN_SWITCH_OPEN VConn switch open Ack
  *          @arg TCPP0203_VCONN_SWITCH_CC1  VConn closed on CC1 Ack
  *          @arg TCPP0203_VCONN_SWITCH_CC2  VConn closed on CC2 Ack
  * @retval error status
  */
tcpp0203_status_t tcpp0203_get_vconn_switch_ack(tcpp0203_obj_t *pobj, tcpp0203_vconn_switch_ack_t *p_vconn_switch_ack)
{
  tcpp0203_status_t ret = TCPP0203_OK;
  uint8_t tmp;

  if (tcpp0203_io_read_reg(&pobj->pio, TCPP0203_ACK_REG, &tmp) != 0)
  {
    ret = TCPP0203_ERROR;
  }

  tmp = tmp & TCPP0203_VCONN_SWITCH_ACK_MSK;

  switch (tmp)
  {
    case TCPP0203_VCONN_SWITCH_ACK_OPEN:
      *p_vconn_switch_ack = TCPP0203_VCONN_SWITCH_ACK_OPEN;
      break;
    case TCPP0203_VCONN_SWITCH_ACK_CC1:
      *p_vconn_switch_ack = TCPP0203_VCONN_SWITCH_ACK_CC1;
      break;
    case TCPP0203_VCONN_SWITCH_ACK_CC2:
      *p_vconn_switch_ack = TCPP0203_VCONN_SWITCH_ACK_CC2;
      break;
    default:
      ret = TCPP0203_ERROR;
      break;
  }

  return ret;
}

/**
  * @brief  Get Gate Driver Provider Ack value.
  * @param  pobj                       : Part object pointer.
  * @param  p_gate_driver_provider_ack : Pointer on Gate Driver Provider Ack value
  *         This output parameter can be one of the following values:
  *          @arg TCPP0203_GD_PROVIDER_SWITCH_ACK_OPEN    Gate Driver Provider Open Ack
  *          @arg TCPP0203_GD_PROVIDER_SWITCH_ACK_CLOSED  Gate Driver Provider Closed Ack
  * @retval error status
  */
tcpp0203_status_t tcpp0203_get_gate_driver_provider_ack(tcpp0203_obj_t *pobj,
                                                        tcpp0203_gate_driver_provider_ack_t *p_gate_driver_provider_ack)
{
  tcpp0203_status_t ret = TCPP0203_OK;
  uint8_t tmp;

  if (tcpp0203_io_read_reg(&pobj->pio, TCPP0203_ACK_REG, &tmp) != 0)
  {
    ret = TCPP0203_ERROR;
  }

  tmp = (uint8_t)(tmp & (uint8_t)(TCPP0203_GD_PROVIDER_SWITCH_ACK_MSK));

  switch (tmp)
  {
    case TCPP0203_GD_PROVIDER_SWITCH_ACK_OPEN:
      *p_gate_driver_provider_ack = TCPP0203_GD_PROVIDER_SWITCH_ACK_OPEN;
      break;
    case TCPP0203_GD_PROVIDER_SWITCH_ACK_CLOSED:
      *p_gate_driver_provider_ack = TCPP0203_GD_PROVIDER_SWITCH_ACK_CLOSED;
      break;
    default:
      ret = TCPP0203_ERROR;
      break;
  }

  return ret;
}

/**
  * @brief  Get Gate Driver Consumer Ack value.
  * @param  pobj                       : Part object pointer.
  * @param  p_gate_driver_consumer_ack : Pointer on Gate Driver Consumer Ack value
  *         This output parameter can be one of the following values:
  *          @arg TCPP0203_GD_CONSUMER_SWITCH_ACK_OPEN    Gate Driver Consumer Open Ack
  *          @arg TCPP0203_GD_CONSUMER_SWITCH_ACK_CLOSED  Gate Driver Consumer Closed Ack
  * @note   This feature is only supported by TCPP03. When the device is a TCPP02,
  *         this function returns TCPP0203_NOT_SUPPORTED.
  * @retval error status
  */
tcpp0203_status_t tcpp0203_get_gate_driver_consumer_ack(tcpp0203_obj_t *pobj,
                                                        tcpp0203_gate_driver_consumer_ack_t *p_gate_driver_consumer_ack)
{
  tcpp0203_status_t ret = TCPP0203_OK;
  uint8_t tmp;

  /* Check if TCPP type is TCPP03. Otherwise, return error */
  if (pobj->tcpp_type != TCPP0203_DEVICE_TYPE_03)
  {
    ret = TCPP0203_NOT_SUPPORTED;
  }

  if (tcpp0203_io_read_reg(&pobj->pio, TCPP0203_ACK_REG, &tmp) != 0)
  {
    ret = TCPP0203_ERROR;
  }

  tmp = (uint8_t)(tmp & (uint8_t)(TCPP0203_GD_CONSUMER_SWITCH_ACK_MSK));

  switch (tmp)
  {
    case TCPP0203_GD_CONSUMER_SWITCH_ACK_OPEN:
      *p_gate_driver_consumer_ack = TCPP0203_GD_CONSUMER_SWITCH_ACK_OPEN;
      break;
    case TCPP0203_GD_CONSUMER_SWITCH_ACK_CLOSED:
      *p_gate_driver_consumer_ack = TCPP0203_GD_CONSUMER_SWITCH_ACK_CLOSED;
      break;
    default:
      ret = TCPP0203_ERROR;
      break;
  }

  return ret;
}

/**
  * @brief  Get Power Mode Ack value.
  * @param  pobj             : Part object pointer.
  * @param  p_power_mode_ack : Pointer on Power Mode Ack value
  *         This output parameter can be one of the following values:
  *          @arg TCPP0203_POWER_MODE_ACK_HIBERNATE  Power Mode Hibernate Ack
  *          @arg TCPP0203_POWER_MODE_ACK_LOWPOWER   Power Mode Low Power Ack
  *          @arg TCPP0203_POWER_MODE_ACK_NORMAL     Power Mode Normal Ack
  * @retval error status
  */
tcpp0203_status_t tcpp0203_get_power_mode_ack(tcpp0203_obj_t *pobj, tcpp0203_power_mode_ack_t *p_power_mode_ack)
{
  tcpp0203_status_t ret = TCPP0203_OK;
  uint8_t tmp;

  if (tcpp0203_io_read_reg(&pobj->pio, TCPP0203_ACK_REG, &tmp) != 0)
  {
    ret = TCPP0203_ERROR;
  }

  tmp = (uint8_t)(tmp & (uint8_t)(TCPP0203_POWER_MODE_ACK_MSK));

  switch (tmp)
  {
    case TCPP0203_POWER_MODE_ACK_HIBERNATE:
      *p_power_mode_ack = TCPP0203_POWER_MODE_ACK_HIBERNATE;
      break;
    case TCPP0203_POWER_MODE_ACK_LOWPOWER:
      *p_power_mode_ack = TCPP0203_POWER_MODE_ACK_LOWPOWER;
      break;
    case TCPP0203_POWER_MODE_ACK_NORMAL:
      *p_power_mode_ack = TCPP0203_POWER_MODE_ACK_NORMAL;
      break;
    default:
      ret = TCPP0203_ERROR;
      break;
  }

  return ret;
}

/**
  * @brief  Get VBUS Discharge Ack value.
  * @param  pobj                 : Part object pointer.
  * @param  p_vbus_discharge_ack : Pointer on VBUS Discharge Ack value
  *         This output parameter can be one of the following values:
  *          @arg TCPP0203_VBUS_DISCHARGE_ACK_OFF   VBUS Discharge Off Ack
  *          @arg TCPP0203_VBUS_DISCHARGE_ACK_ON    VBUS Discharge On Ack
  * @retval error status
  */
tcpp0203_status_t tcpp0203_get_vbus_discharge_ack(tcpp0203_obj_t *pobj,
                                                  tcpp0203_vbus_discharge_ack_t *p_vbus_discharge_ack)
{
  tcpp0203_status_t ret = TCPP0203_OK;
  uint8_t tmp;

  if (tcpp0203_io_read_reg(&pobj->pio, TCPP0203_ACK_REG, &tmp) != 0)
  {
    ret = TCPP0203_ERROR;
  }

  tmp = (uint8_t)(tmp & (uint8_t)(TCPP0203_VBUS_DISCHARGE_ACK_MSK));

  switch (tmp)
  {
    case TCPP0203_VBUS_DISCHARGE_ACK_OFF:
      *p_vbus_discharge_ack = TCPP0203_VBUS_DISCHARGE_ACK_OFF;
      break;
    case TCPP0203_VBUS_DISCHARGE_ACK_ON:
      *p_vbus_discharge_ack = TCPP0203_VBUS_DISCHARGE_ACK_ON;
      break;
    default:
      ret = TCPP0203_ERROR;
      break;
  }

  return ret;
}

/**
  * @brief  Get VConn Discharge Ack value.
  * @param  pobj                  : Part object pointer.
  * @param  p_vconn_discharge_ack : Pointer on VConn Discharge Ack value
  *         This output parameter can be one of the following values:
  *          @arg TCPP0203_VCONN_DISCHARGE_ACK_OFF   VConn Discharge Off Ack
  *          @arg TCPP0203_VCONN_DISCHARGE_ACK_ON    VConn Discharge On Ack
  * @retval error status
  */
tcpp0203_status_t tcpp0203_get_vconn_discharge_ack(tcpp0203_obj_t *pobj,
                                                   tcpp0203_vconn_discharge_ack_t *p_vconn_discharge_ack)
{
  tcpp0203_status_t ret = TCPP0203_OK;
  uint8_t tmp;

  if (tcpp0203_io_read_reg(&pobj->pio, TCPP0203_ACK_REG, &tmp) != 0)
  {
    ret = TCPP0203_ERROR;
  }

  tmp = (uint8_t)(tmp & (uint8_t)(TCPP0203_VCONN_DISCHARGE_ACK_MSK));

  switch (tmp)
  {
    case TCPP0203_VCONN_DISCHARGE_ACK_OFF:
      *p_vconn_discharge_ack = TCPP0203_VCONN_DISCHARGE_ACK_OFF;
      break;
    case TCPP0203_VCONN_DISCHARGE_ACK_ON:
      *p_vconn_discharge_ack = TCPP0203_VCONN_DISCHARGE_ACK_ON;
      break;
    default:
      ret = TCPP0203_ERROR;
      break;
  }

  return ret;
}

/**
  * @brief  Get OCP VConn Flag value.
  * @param  pobj             : Part object pointer.
  * @param  p_ocp_vconn_flag : Pointer on OCP VConn Flag value
  *         This output parameter can be one of the following values:
  *          @arg TCPP0203_FLAG_OCP_VCONN_RESET   OCP VConn flag not set
  *          @arg TCPP0203_FLAG_OCP_VCONN_SET     OCP VConn flag set
  * @retval error status
  */
tcpp0203_status_t tcpp0203_get_ocp_vconn_flag(tcpp0203_obj_t *pobj, tcpp0203_ocp_vconn_flag_t *p_ocp_vconn_flag)
{
  tcpp0203_status_t ret = TCPP0203_OK;
  uint8_t tmp;

  if (tcpp0203_io_read_reg(&pobj->pio, TCPP0203_FLAG_REG, &tmp) != 0)
  {
    ret = TCPP0203_ERROR;
  }

  tmp = (uint8_t)(tmp & (uint8_t)(TCPP0203_FLAG_OCP_VCONN_MSK));

  switch (tmp)
  {
    case TCPP0203_FLAG_OCP_VCONN_RESET:
      *p_ocp_vconn_flag = TCPP0203_FLAG_OCP_VCONN_RESET;
      break;
    case TCPP0203_FLAG_OCP_VCONN_SET:
      *p_ocp_vconn_flag = TCPP0203_FLAG_OCP_VCONN_SET;
      break;
    default:
      ret = TCPP0203_ERROR;
      break;
  }

  return ret;
}

/**
  * @brief  Get OCP VBUS Flag value.
  * @param  pobj            : Part object pointer.
  * @param  p_ocp_vbus_flag : Pointer on OCP VBUS Flag value
  *         This output parameter can be one of the following values:
  *          @arg TCPP0203_FLAG_OCP_VBUS_RESET   OCP VBUS flag not set
  *          @arg TCPP0203_FLAG_OCP_VBUS_SET     OCP VBUS flag set
  * @retval error status
  */
tcpp0203_status_t tcpp0203_get_ocp_vbus_flag(tcpp0203_obj_t *pobj, tcpp0203_ocp_vbus_flag_t *p_ocp_vbus_flag)
{
  tcpp0203_status_t ret = TCPP0203_OK;
  uint8_t tmp;

  if (tcpp0203_io_read_reg(&pobj->pio, TCPP0203_FLAG_REG, &tmp) != 0)
  {
    ret = TCPP0203_ERROR;
  }

  tmp = (uint8_t)(tmp & (uint8_t)(TCPP0203_FLAG_OCP_VBUS_MSK));

  switch (tmp)
  {
    case TCPP0203_FLAG_OCP_VBUS_RESET:
      *p_ocp_vbus_flag = TCPP0203_FLAG_OCP_VBUS_RESET;
      break;
    case TCPP0203_FLAG_OCP_VBUS_SET:
      *p_ocp_vbus_flag = TCPP0203_FLAG_OCP_VBUS_SET;
      break;
    default:
      ret = TCPP0203_ERROR;
      break;
  }

  return ret;
}

/**
  * @brief  Get OVP VBUS Flag value.
  * @param  pobj            : Part object pointer.
  * @param  p_ovp_vbus_flag : Pointer on OVP VBUS Flag value
  *         This output parameter can be one of the following values:
  *          @arg TCPP0203_FLAG_OVP_VBUS_RESET   OVP VBUS flag not set
  *          @arg TCPP0203_FLAG_OVP_VBUS_SET     OVP VBUS flag set
  * @retval error status
  */
tcpp0203_status_t tcpp0203_get_ovp_vbus_flag(tcpp0203_obj_t *pobj, tcpp0203_ovp_vbus_flag_t *p_ovp_vbus_flag)
{
  tcpp0203_status_t ret = TCPP0203_OK;
  uint8_t tmp;

  if (tcpp0203_io_read_reg(&pobj->pio, TCPP0203_FLAG_REG, &tmp) != 0)
  {
    ret = TCPP0203_ERROR;
  }

  tmp = (uint8_t)(tmp & (uint8_t)(TCPP0203_FLAG_OVP_VBUS_MSK));

  switch (tmp)
  {
    case TCPP0203_FLAG_OVP_VBUS_RESET:
      *p_ovp_vbus_flag = TCPP0203_FLAG_OVP_VBUS_RESET;
      break;
    case TCPP0203_FLAG_OVP_VBUS_SET:
      *p_ovp_vbus_flag = TCPP0203_FLAG_OVP_VBUS_SET;
      break;
    default:
      ret = TCPP0203_ERROR;
      break;
  }

  return ret;
}

/**
  * @brief  Get OVP CC Flag value.
  * @param  pobj          : Part object pointer.
  * @param  p_ovp_cc_flag : Pointer on OVP CC Flag value
  *         This output parameter can be one of the following values:
  *          @arg TCPP0203_FLAG_OVP_CC_RESET   OVP CC flag not set
  *          @arg TCPP0203_FLAG_OVP_CC_SET     OVP CC flag set
  * @retval error status
  */
tcpp0203_status_t tcpp0203_get_ovp_cc_flag(tcpp0203_obj_t *pobj, tcpp0203_ovp_cc_flag_t *p_ovp_cc_flag)
{
  tcpp0203_status_t ret = TCPP0203_OK;
  uint8_t tmp;

  if (tcpp0203_io_read_reg(&pobj->pio, TCPP0203_FLAG_REG, &tmp) != 0)
  {
    ret = TCPP0203_ERROR;
  }

  tmp = (uint8_t)(tmp & (uint8_t)(TCPP0203_FLAG_OVP_CC_MSK));

  switch (tmp)
  {
    case TCPP0203_FLAG_OVP_CC_RESET:
      *p_ovp_cc_flag = TCPP0203_FLAG_OVP_CC_RESET;
      break;
    case TCPP0203_FLAG_OVP_CC_SET:
      *p_ovp_cc_flag = TCPP0203_FLAG_OVP_CC_SET;
      break;
    default:
      ret = TCPP0203_ERROR;
      break;
  }

  return ret;
}

/**
  * @brief  Get Over Temperature Flag value.
  * @param  pobj     : Part object pointer.
  * @param  p_otp_flag : Pointer on Over Temperature Flag value
  *         This output parameter can be one of the following values:
  *          @arg TCPP0203_FLAG_OTP_RESET   Over Temperature flag not set
  *          @arg TCPP0203_FLAG_OTP_SET     Over Temperature flag set
  * @retval error status
  */
tcpp0203_status_t tcpp0203_get_otp_flag(tcpp0203_obj_t *pobj, tcpp0203_otp_flag_t *p_otp_flag)
{
  tcpp0203_status_t ret = TCPP0203_OK;
  uint8_t tmp;

  if (tcpp0203_io_read_reg(&pobj->pio, TCPP0203_FLAG_REG, &tmp) != 0)
  {
    ret = TCPP0203_ERROR;
  }

  tmp = (uint8_t)(tmp & (uint8_t)(TCPP0203_FLAG_OTP_MSK));

  switch (tmp)
  {
    case TCPP0203_FLAG_OTP_RESET:
      *p_otp_flag = TCPP0203_FLAG_OTP_RESET;
      break;
    case TCPP0203_FLAG_OTP_SET:
      *p_otp_flag = TCPP0203_FLAG_OTP_SET;
      break;
    default:
      ret = TCPP0203_ERROR;
      break;
  }

  return ret;
}

/**
  * @brief  Get VBUS OK Flag value.
  * @param  pobj           : Part object pointer.
  * @param  p_vbus_ok_flag : Pointer on VBUS OK Flag value
  *         This output parameter can be one of the following values:
  *          @arg TCPP0203_FLAG_VBUS_OK_RESET   VBUS OK flag not set
  *          @arg TCPP0203_FLAG_VBUS_OK_SET     VBUS OK flag set
  * @retval error status
  */
tcpp0203_status_t tcpp0203_get_vbus_ok_flag(tcpp0203_obj_t *pobj, tcpp0203_vbus_ok_flag_t *p_vbus_ok_flag)
{
  tcpp0203_status_t ret = TCPP0203_OK;
  uint8_t tmp;

  if (tcpp0203_io_read_reg(&pobj->pio, TCPP0203_FLAG_REG, &tmp) != 0)
  {
    ret = TCPP0203_ERROR;
  }

  tmp = (uint8_t)(tmp & (uint8_t)(TCPP0203_FLAG_VBUS_OK_MSK));

  switch (tmp)
  {
    case TCPP0203_FLAG_VBUS_OK_RESET:
      *p_vbus_ok_flag = TCPP0203_FLAG_VBUS_OK_RESET;
      break;
    case TCPP0203_FLAG_VBUS_OK_SET:
      *p_vbus_ok_flag = TCPP0203_FLAG_VBUS_OK_SET;
      break;
    default:
      ret = TCPP0203_ERROR;
      break;
  }

  return ret;
}

/**
  * @brief  Get TCPP0203 Device Type value.
  * @param  pobj        : Part object pointer.
  * @param  p_tcpp_type : Pointer on TCPP0203 Device Type value
  *         This output parameter can be one of the following values:
  *          @arg TCPP0203_DEVICE_TYPE_02   TCPP02 Type
  *          @arg TCPP0203_DEVICE_TYPE_03   TCPP0203 Type
  * @retval error status
  */
tcpp0203_status_t tcpp0203_read_tcpp_type(tcpp0203_obj_t *pobj, tcpp0203_tcpp_type_t *p_tcpp_type)
{
  tcpp0203_status_t ret = TCPP0203_OK;
  uint8_t tmp;

  if (tcpp0203_io_read_reg(&pobj->pio, TCPP0203_FLAG_REG, &tmp) != 0)
  {
    ret = TCPP0203_ERROR;
  }

  tmp = (uint8_t)(tmp & (uint8_t)(TCPP0203_DEVICE_TYPE_MSK));

  switch (tmp)
  {
    case TCPP0203_DEVICE_TYPE_02:
      *p_tcpp_type = TCPP0203_DEVICE_TYPE_02;
      break;
    case TCPP0203_DEVICE_TYPE_03:
      *p_tcpp_type = TCPP0203_DEVICE_TYPE_03;
      break;
    default:
      ret = TCPP0203_ERROR;
      break;
  }

  return ret;
}

/**
  * @brief  Get VConn Power value.
  * @param  pobj          : Part object pointer.
  * @param  p_vconn_power : Pointer on VConn Power value
  *         This output parameter can be one of the following values:
  *          @arg TCPP0203_FLAG_VCONN_PWR_1W       OCP VConn flag not set
  *          @arg TCPP0203_FLAG_VCONN_PWR_0_1W     OCP VConn flag set
  * @retval error status
  */
tcpp0203_status_t tcpp0203_read_vconn_power(tcpp0203_obj_t *pobj, tcpp0203_vconn_power_t *p_vconn_power)
{
  tcpp0203_status_t ret = TCPP0203_OK;
  uint8_t tmp;

  if (tcpp0203_io_read_reg(&pobj->pio, TCPP0203_FLAG_REG, &tmp) != 0)
  {
    ret = TCPP0203_ERROR;
  }

  tmp = (uint8_t)(tmp & (uint8_t)(TCPP0203_FLAG_VCONN_PWR_MSK));

  switch (tmp)
  {
    case TCPP0203_FLAG_VCONN_PWR_1W:
      *p_vconn_power = TCPP0203_FLAG_VCONN_PWR_1W;
      break;
    case TCPP0203_FLAG_VCONN_PWR_0_1W:
      *p_vconn_power = TCPP0203_FLAG_VCONN_PWR_0_1W;
      break;
    default:
      ret = TCPP0203_ERROR;
      break;
  }

  return ret;
}

/**
  * @brief  Set complete Ctrl register value (Reg 0).
  * @param  pobj            : Part object pointer.
  * @param  p_ctrl_register : Pointer on Ctrl register value
  * @retval error status
  */
tcpp0203_status_t tcpp0203_write_ctrl_register(tcpp0203_obj_t *pobj, uint8_t *p_ctrl_register)
{
  /* Update value in writing register (reg0) */
  if (tcpp0203_io_write_reg(&pobj->pio, TCPP0203_PROG_CTRL, p_ctrl_register) != 0)
  {
    return TCPP0203_ERROR;
  }

  return TCPP0203_OK;
}

/**
  * @brief  Get complete Ack register value.
  * @param  pobj           : Part object pointer.
  * @param  p_ack_register : Pointer on Ack register value
  * @retval error status
  */
tcpp0203_status_t tcpp0203_read_ack_register(tcpp0203_obj_t *pobj, uint8_t *p_ack_register)
{
  if (tcpp0203_io_read_reg(&pobj->pio, TCPP0203_ACK_REG, p_ack_register) != 0)
  {
    return TCPP0203_ERROR;
  }
  return TCPP0203_OK;
}

/**
  * @brief  Get complete Flag register value.
  * @param  pobj            : Part object pointer.
  * @param  p_flag_register : Pointer on Flag register value
  * @retval error status
  */
tcpp0203_status_t tcpp0203_read_flag_register(tcpp0203_obj_t *pobj, uint8_t *p_flag_register)
{
  if (tcpp0203_io_read_reg(&pobj->pio, TCPP0203_FLAG_REG, p_flag_register) != 0)
  {
    return TCPP0203_ERROR;
  }

  return TCPP0203_OK;
}

/**
  * @brief  Get actual voltage level measured on the VBUS line.
  * @param  pobj         : Part object pointer.
  * @param  p_voltage_mv : Pointer on measured voltage level (in mV)
  * @retval error status
  */
tcpp0203_status_t tcpp0203_get_vbus_voltage(tcpp0203_obj_t *pobj, uint32_t *p_voltage_mv)
{
  uint32_t AdcValue;
  uint32_t Voltage;

  if (tcpp0203_io_get_adc_value(&pobj->pio, &AdcValue) != 0)
  {
    return TCPP0203_ERROR;
  }

  Voltage = tcpp0203_io_get_vbus_voltage(&pobj->pio, AdcValue);;

  *p_voltage_mv = Voltage;

  return TCPP0203_OK;
}

/**
  * @brief  Get actual current level measured on the VBUS line.
  * @param  pobj         : Part object pointer.
  * @param  p_current_ma : Pointer on measured current level (in mA)
  * @retval error status
  */
tcpp0203_status_t tcpp0203_get_vbus_current(tcpp0203_obj_t *pobj, uint32_t *p_current_ma)
{
  uint32_t AdcValue;
  uint32_t Current;

  if (tcpp0203_io_get_adc_value(&pobj->pio, &AdcValue) != 0)
  {
    return TCPP0203_ERROR;
  }

  Current = tcpp0203_io_get_vbus_current(&pobj->pio, AdcValue);

  *p_current_ma = Current;

  return TCPP0203_OK;
}

/**
  * @brief This function starts the ADC conversion.
  * @param  pobj       : Part object pointer.
  * @retval error status
  */
tcpp0203_status_t  tcpp0203_start(tcpp0203_obj_t *pobj)
{
  /* Initialize default part status */
  tcpp0203_status_t ret = TCPP0203_ERROR;

  if (tcpp0203_io_start(&pobj->pio) == 0)
  {
    ret = TCPP0203_OK;
  }

  /* Return error status */
  return ret;
}

/**
  * @brief This function stops the ADC conversion.
  * @param  pobj       : Part object pointer.
  * @retval error status
  */
tcpp0203_status_t  tcpp0203_stop(tcpp0203_obj_t *pobj)
{
  /* Initialize default part status */
  tcpp0203_status_t ret = TCPP0203_ERROR;

  if (tcpp0203_io_stop(&pobj->pio) == 0)
  {
    ret = TCPP0203_OK;
  }


  /* Return error status */
  return ret;
}


/******************** Static functions ****************************************/

/**
  * @brief  TCPP0203 register update function to Bus IO function.
  * @param  pobj       : Part object pointer.
  * @param  Value      : Target register value to be written
  * @param  Mask       : Target register mask to be applied
  * @retval error status
  */
static tcpp0203_status_t tcpp0203_modify_reg0(tcpp0203_obj_t *pobj, uint8_t Value, uint8_t Mask)
{
  tcpp0203_status_t status;
  uint8_t tmp;

  /* Read current content of ACK register (reflects content of bits set to 1 in Writing register Reg0) */
  if (tcpp0203_io_read_reg(&pobj->pio, TCPP0203_ACK_REG, &tmp) != 0)
  {
    status = TCPP0203_ERROR;
  }
  else
  {
    /* Update only the area dedicated to Mask */
    tmp &= ~(Mask);
    tmp |= (Value & Mask);

    /* Update value in writing register (reg0) */
    if (tcpp0203_io_write_reg(&pobj->pio, TCPP0203_PROG_CTRL, &tmp) == 0)
    {
      status = TCPP0203_OK;
    }
    else
    {
      status = TCPP0203_ERROR;
    }
  }

  return status;
}
