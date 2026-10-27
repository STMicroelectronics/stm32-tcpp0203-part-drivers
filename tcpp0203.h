/**
  ******************************************************************************
  * @file    TCPP0203.h
  * @brief   This file contains all the functions prototypes for the
  *          TCPP0203.c driver.
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
#ifndef TCPP0203_H
#define TCPP0203_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "tcpp0203_io.h"
#include <stddef.h>

/* Exported types ------------------------------------------------------------*/

/**
  * @brief Enumeration defining the state of TCPP0203.
  */
typedef enum
{
  TCPP0203_OK = 0,          /*!< Success State     */
  TCPP0203_ERROR,           /*!< Error State       */
  TCPP0203_NOT_SUPPORTED,    /*!< Feature not supported by TCPP02 */
  TCPP0203_INVALID_PARAM,   /*!< Invalid Parameter */
} tcpp0203_status_t;

/* TCPP0203 possible I2C Addresses */
#define TCPP0203_I2C_ADDRESS_X68                (0x68U)     /*!< TCPP0203 I2C address : 0x68 */
#define TCPP0203_I2C_ADDRESS_X6A                (0x6AU)     /*!< TCPP0203 I2C address : 0x6A */

/* TCPP0203 Reg0 Reset Value */

#define TCPP0203_REG0_RST_VALUE         TCPP0203_GD_CONSUMER_SWITCH_CLOSED   /*!<TCPP0203 Reg0 Reset Value */

/* TCPP0203 VCONN Switch values*/
#define TCPP0203_VCONN_SWITCH_POS                 (0U)                                /*!< Vconn switch bit position */
#define TCPP0203_VCONN_SWITCH_MSK                 (0x03U << TCPP0203_VCONN_SWITCH_POS)  /*!< Vconn switch mask     */

/* TCPP0203 Gate Driver Provider switch */
#define TCPP0203_GD_PROVIDER_SWITCH_POS           (2U)                                     /*!< Gate Driver Provider switch bit position */
#define TCPP0203_GD_PROVIDER_SWITCH_MSK           (0x01U << TCPP0203_GD_PROVIDER_SWITCH_POS) /*!< Gate Driver Provider switch mask     */

/* TCPP0203 Gate Driver Consumer values */
#define TCPP0203_GD_CONSUMER_SWITCH_POS           (3U)                                     /*!< Gate Driver Consumer switch bit position */
#define TCPP0203_GD_CONSUMER_SWITCH_MSK           (0x01U << TCPP0203_GD_CONSUMER_SWITCH_POS) /*!< Gate Driver Consumer switch mask */

/* TCPP0203 Power Mode values */
#define TCPP0203_POWER_MODE_POS                   (4U)                              /*!< Power mode bit position */
#define TCPP0203_POWER_MODE_MSK                   (0x03U << TCPP0203_POWER_MODE_POS)  /*!< Power mode mask */

/*TCPP0203 VBUS Discharge management */
#define TCPP0203_VBUS_DISCHARGE_POS               (6U)                                  /*!< VBUS discharge bit position */
#define TCPP0203_VBUS_DISCHARGE_MSK               (0x01U << TCPP0203_VBUS_DISCHARGE_POS)  /*!< VBUS discharge mask */

/* TCPP0203 VCONN Discharge management */
#define TCPP0203_VCONN_DISCHARGE_POS              (7U)                                  /*!< VCONN discharge bit position */
#define TCPP0203_VCONN_DISCHARGE_MSK              (0x01U << TCPP0203_VCONN_DISCHARGE_POS) /*!< VCONN discharge mask */

/* TCPP0203 VCONN Switch Acknowledge */
#define TCPP0203_VCONN_SWITCH_ACK_POS             (0U)                                    /*!< VCONN switch acknowledge bit position */
#define TCPP0203_VCONN_SWITCH_ACK_MSK             (0x03U << TCPP0203_VCONN_SWITCH_ACK_POS)  /*!< VCONN switch acknowledge mask */

/* TCPP0203 Gate Driver Provider Acknowledge */
#define TCPP0203_GD_PROVIDER_SWITCH_ACK_POS       (2U)                                         /*!< Gate Driver Provider switch acknowledge bit position */
#define TCPP0203_GD_PROVIDER_SWITCH_ACK_MSK       (0x01U << TCPP0203_GD_PROVIDER_SWITCH_ACK_POS) /*!< Gate Driver Provider switch acknowledge mask */

/* TCPP0203 Gate Driver Consumer Acknowledge */
#define TCPP0203_GD_CONSUMER_SWITCH_ACK_POS       (3U)                                          /*!< Gate Driver Consumer switch acknowledge bit position */
#define TCPP0203_GD_CONSUMER_SWITCH_ACK_MSK       (0x01U << TCPP0203_GD_CONSUMER_SWITCH_ACK_POS)  /*!< Gate Driver Consumer switch acknowledge mask */

/* TCPP0203 Power Mode Acknowledge */
#define TCPP0203_POWER_MODE_ACK_POS               (4U)                                  /*!< Power Mode acknowledge bit position */
#define TCPP0203_POWER_MODE_ACK_MSK               (0x03U << TCPP0203_POWER_MODE_ACK_POS)  /*!< Power Mode acknowledge mask */

/* TCPP0203 VBUS Discharge Acknowledge */
#define TCPP0203_VBUS_DISCHARGE_ACK_POS           (6U)                                      /*!< VBUS discharge acknowledge bit position */
#define TCPP0203_VBUS_DISCHARGE_ACK_MSK           (0x01U << TCPP0203_VBUS_DISCHARGE_ACK_POS)  /*!< VBUS discharge acknowledge mask */

/* TCPP0203 VConn Discharge Acknowledge */
#define TCPP0203_VCONN_DISCHARGE_ACK_POS          (7U)                                       /*!< VCONN discharge acknowledge bit position */
#define TCPP0203_VCONN_DISCHARGE_ACK_MSK          (0x01U << TCPP0203_VCONN_DISCHARGE_ACK_POS)  /*!< VCONN discharge acknowledge mask */

/* TCPP0203 OCP Vconn Flag management */
#define TCPP0203_FLAG_OCP_VCONN_POS               (0U)                                    /*!< OCP VCONN Flag bit position */
#define TCPP0203_FLAG_OCP_VCONN_MSK               (0x01U << TCPP0203_FLAG_OCP_VCONN_POS)    /*!< OCP VCONN Flag mask */

/* TCPP0203 OCP VBUS Flag management */
#define TCPP0203_FLAG_OCP_VBUS_POS                (1U)                                  /*!< OCP VBUS Flag bit position */
#define TCPP0203_FLAG_OCP_VBUS_MSK                (0x01U << TCPP0203_FLAG_OCP_VBUS_POS)   /*!< OCP VBUS Flag mask */

/* TCPP0203 OVP VBUS Flag management */
#define TCPP0203_FLAG_OVP_VBUS_POS                (2U)                                 /*!< OVP VBUS Flag bit position */
#define TCPP0203_FLAG_OVP_VBUS_MSK                (0x01U << TCPP0203_FLAG_OVP_VBUS_POS)  /*!< OVP VBUS Flag mask */

/* TCPP0203 OTP Flag management */
#define TCPP0203_FLAG_OTP_POS                     (3U)                             /*!< OTP Flag bit position */
#define TCPP0203_FLAG_OTP_MSK                     (0x01U << TCPP0203_FLAG_OTP_POS)   /*!< OTP Flag mask */

/* TCPP0203 OVP CC Flag management */
#define TCPP0203_FLAG_OVP_CC_POS                  (4U)                                 /*!< OVP CC Flag bit position */
#define TCPP0203_FLAG_OVP_CC_MSK                  (0x01U << TCPP0203_FLAG_OVP_CC_POS)    /*!< OVP CC Flag mask */

/* TCPP0203 VBUS OK Flag management */
#define TCPP0203_FLAG_VBUS_OK_POS                 (5U)                               /*!< VBUS OK Flag bit position */
#define TCPP0203_FLAG_VBUS_OK_MSK                 (0x01U << TCPP0203_FLAG_VBUS_OK_POS) /*!< VBUS OK mask */

/* TCPP0203 VConn Power */
#define TCPP0203_FLAG_VCONN_PWR_POS               (6U)                                 /*!<  VConn Power bit position */
#define TCPP0203_FLAG_VCONN_PWR_MSK               (0x01U << TCPP0203_FLAG_VCONN_PWR_POS) /*!<  VConn Power mask */

/* TCPP0203 Device Type */
#define TCPP0203_DEVICE_TYPE_POS                  (7U)                                 /*!< Device type bit position */
#define TCPP0203_DEVICE_TYPE_MSK                  (0x01U << TCPP0203_DEVICE_TYPE_POS)    /*!< Device type mask */

/******************************************************************************/
/****************************** REGISTER MAPPING ******************************/
/******************************************************************************/
#define TCPP0203_WRITE_REG                   0x00U                 /*!< Write register */
#define TCPP0203_PROG_CTRL                   TCPP0203_WRITE_REG      /*!< Program control register */
#define TCPP0203_READ_REG1                   0x01U                 /*!< Read register 1 */
#define TCPP0203_ACK_REG                     TCPP0203_READ_REG1      /*!< Acknowledge register */
#define TCPP0203_READ_REG2                   0x02U                 /*!< Read register 2 */
#define TCPP0203_FLAG_REG                    TCPP0203_READ_REG2      /*!< Flag register  */


/**
  * @brief Enumeration defining VCONN Switch values.
  */
typedef enum
{
  TCPP0203_VCONN_SWITCH_OPEN   = (0x00U),                             /*!< Vconn switch open     */
  TCPP0203_VCONN_SWITCH_CC1    = (0x01U << TCPP0203_VCONN_SWITCH_POS),  /*!< Vconn switch CC1      */
  TCPP0203_VCONN_SWITCH_CC2    = (0x02U << TCPP0203_VCONN_SWITCH_POS)   /*!< Vconn switch CC2      */
} tcpp0203_vconn_switch_t;

/**
  * @brief Enumeration defining Gate Driver Provider switch values.
  */
typedef enum
{
  TCPP0203_GD_PROVIDER_SWITCH_OPEN    = (0x00U),                         /*!< Gate Driver Provider switch open */
  TCPP0203_GD_PROVIDER_SWITCH_CLOSED  = (TCPP0203_GD_PROVIDER_SWITCH_MSK)  /*!< Gate Driver Provider switch closed */
} tcpp0203_gate_driver_provider_t;


/**
  * @brief Enumeration defining Gate Driver Consumer switch values.
  */
typedef enum
{
  TCPP0203_GD_CONSUMER_SWITCH_CLOSED = (0x00U),                          /*!< Gate Driver Consumer switch closed*/
  TCPP0203_GD_CONSUMER_SWITCH_OPEN   = (TCPP0203_GD_CONSUMER_SWITCH_MSK)   /*!< Gate Driver Consumer switch open */
} tcpp0203_gate_driver_consumer_t;

/**
  * @brief Enumeration defining Power Mode values.
  */
typedef enum
{
  TCPP0203_POWER_MODE_HIBERNATE = (0x00U),                           /*!< Power mode hibernate */
  TCPP0203_POWER_MODE_NORMAL    = (0x01U << TCPP0203_POWER_MODE_POS),  /*!< Power mode normal */
  TCPP0203_POWER_MODE_LOWPOWER  = (0x02U << TCPP0203_POWER_MODE_POS),  /*!< Power mode low power */

} tcpp0203_power_mode_t;

/**
  * @brief Enumeration defining VBUS Discharge values.
  */
typedef enum
{
  TCPP0203_VBUS_DISCHARGE_OFF  = (0x00U),                               /*!< VBUS discharge OFF */
  TCPP0203_VBUS_DISCHARGE_ON   = (TCPP0203_VBUS_DISCHARGE_MSK)           /*!< VBUS discharge ON */
} tcpp0203_vbus_discharge_t;

/**
  * @brief Enumeration defining VCONN Discharge values.
  */
typedef enum
{
  TCPP0203_VCONN_DISCHARGE_OFF = (0x00U),                               /*!< VCONN discharge OFF */
  TCPP0203_VCONN_DISCHARGE_ON  = (TCPP0203_VCONN_DISCHARGE_MSK)          /*!< VCONN discharge ON */
} tcpp0203_vconn_discharge_t;

/**
  * @brief Enumeration defining VCONN Switch Acknowledge values.
  */
typedef enum
{
  TCPP0203_VCONN_SWITCH_ACK_OPEN = (0x00U),                                 /*!< VCONN switch acknowledge OPEN */
  TCPP0203_VCONN_SWITCH_ACK_CC1  = (0x01U << TCPP0203_VCONN_SWITCH_ACK_POS),  /*!< VCONN switch acknowledge CC1 */
  TCPP0203_VCONN_SWITCH_ACK_CC2  = (0x02U << TCPP0203_VCONN_SWITCH_ACK_POS)   /*!< VCONN switch acknowledge CC2 */
} tcpp0203_vconn_switch_ack_t;

/**
  * @brief Enumeration defining Gate Driver Provider Acknowledge values.
  */
typedef enum
{
  TCPP0203_GD_PROVIDER_SWITCH_ACK_OPEN   = (0x00U),                             /*!< Gate Driver Provider switch acknowledge open */
  TCPP0203_GD_PROVIDER_SWITCH_ACK_CLOSED = (TCPP0203_GD_PROVIDER_SWITCH_ACK_MSK)  /*!< Gate Driver Provider switch acknowledge closed */
} tcpp0203_gate_driver_provider_ack_t;

/**
  * @brief Enumeration defining Gate Driver Consumer Acknowledge values.
  */
typedef enum
{
  TCPP0203_GD_CONSUMER_SWITCH_ACK_CLOSED = (0x00U),                             /*!< Gate Driver Consumer switch acknowledge closed */
  TCPP0203_GD_CONSUMER_SWITCH_ACK_OPEN   = (TCPP0203_GD_CONSUMER_SWITCH_ACK_MSK)  /*!< Gate Driver Consumer switch acknowledge open */
} tcpp0203_gate_driver_consumer_ack_t;

/**
  * @brief Enumeration defining Power Mode Acknowledge values.
  */
typedef enum
{
  TCPP0203_POWER_MODE_ACK_HIBERNATE = (0x00U),                               /*!< Power Mode acknowledge hibernate */
  TCPP0203_POWER_MODE_ACK_NORMAL    = (0x01U << TCPP0203_POWER_MODE_ACK_POS),  /*!< Power Mode acknowledge normal */
  TCPP0203_POWER_MODE_ACK_LOWPOWER  = (0x02U << TCPP0203_POWER_MODE_ACK_POS)   /*!< Power Mode acknowledge low powerS */
} tcpp0203_power_mode_ack_t;

/**
  * @brief Enumeration defining VBUS Discharge Acknowledge values.
  */
typedef enum
{
  TCPP0203_VBUS_DISCHARGE_ACK_OFF = (0x00U),                         /*!< VBUS discharge acknowledge OFF */
  TCPP0203_VBUS_DISCHARGE_ACK_ON  = (TCPP0203_VBUS_DISCHARGE_ACK_MSK)  /*!< VBUS discharge acknowledge ON */
} tcpp0203_vbus_discharge_ack_t;

/**
  * @brief Enumeration defining VCONN Discharge Acknowledge values.
  */
typedef enum
{
  TCPP0203_VCONN_DISCHARGE_ACK_OFF = (0x00U),                         /*!< VCONN discharge acknowledge OFF */
  TCPP0203_VCONN_DISCHARGE_ACK_ON  = (TCPP0203_VCONN_DISCHARGE_ACK_MSK) /*!< VCONN discharge acknowledge ON */
} tcpp0203_vconn_discharge_ack_t;

/**
  * @brief Enumeration defining OCP Vconn Flag values.
  */
typedef enum
{
  TCPP0203_FLAG_OCP_VCONN_RESET = (0x00U),                      /*!< OCP VCONN Flag RESET */
  TCPP0203_FLAG_OCP_VCONN_SET   = (TCPP0203_FLAG_OCP_VCONN_MSK)   /*!< OCP VCONN Flag SET */
} tcpp0203_ocp_vconn_flag_t;

/**
  * @brief Enumeration defining OCP VBUS Flag values.
  */
typedef enum
{
  TCPP0203_FLAG_OCP_VBUS_RESET = (0x00U),                   /*!< OCP VBUS Flag RESET */
  TCPP0203_FLAG_OCP_VBUS_SET   = (TCPP0203_FLAG_OCP_VBUS_MSK) /*!< OCP VBUS Flag SET */
} tcpp0203_ocp_vbus_flag_t;

/**
  * @brief Enumeration defining OVP VBUS Flag values.
  */
typedef enum
{
  TCPP0203_FLAG_OVP_VBUS_RESET = (0x00U),                    /*!< OVP VBUS Flag RESET */
  TCPP0203_FLAG_OVP_VBUS_SET   = (TCPP0203_FLAG_OVP_VBUS_MSK)  /*!< OVP VBUS Flag SET */
} tcpp0203_ovp_vbus_flag_t;

/**
  * @brief Enumeration defining OVP CC Flag values.
  */
typedef enum
{
  TCPP0203_FLAG_OVP_CC_RESET = (0x00U),                  /*!< OVP CC Flag RESET */
  TCPP0203_FLAG_OVP_CC_SET   = (TCPP0203_FLAG_OVP_CC_MSK)  /*!< OVP CC Flag SET */
} tcpp0203_ovp_cc_flag_t;

/**
  * @brief Enumeration defining OTP Flag values.
  */
typedef enum
{
  TCPP0203_FLAG_OTP_RESET = (0x00U),               /*!< OTP Flag RESET */
  TCPP0203_FLAG_OTP_SET   = (TCPP0203_FLAG_OTP_MSK)  /*!< OTP Flag SET */
} tcpp0203_otp_flag_t;

/**
  * @brief Enumeration defining VBUS OK Flag values.
  */
typedef enum
{
  TCPP0203_FLAG_VBUS_OK_RESET = (0x00U),                   /*!< VBUS OK RESET */
  TCPP0203_FLAG_VBUS_OK_SET   = (TCPP0203_FLAG_VBUS_OK_MSK)  /*!< VBUS OK SET */
} tcpp0203_vbus_ok_flag_t;

/**
  * @brief Enumeration defining Device Type values.
  */
typedef enum
{
  TCPP0203_DEVICE_TYPE_03 = (0x00U),                 /*!< Device type TCPP0203 */
  TCPP0203_DEVICE_TYPE_02 = (TCPP0203_DEVICE_TYPE_MSK) /*!< Device type TCPP02 */
} tcpp0203_tcpp_type_t;

/**
  * @brief Enumeration defining VConn Power values.
  */
typedef enum
{
  TCPP0203_FLAG_VCONN_PWR_1W   = (TCPP0203_FLAG_VCONN_PWR_MSK),  /*!<  VConn Power 1W */
  TCPP0203_FLAG_VCONN_PWR_0_1W = (0x00U)                       /*!<  VConn Power 0_1W */
} tcpp0203_vconn_power_t;

typedef struct tcpp0203_obj_s tcpp0203_obj_t;   /*!< TCPP0203 object structure type */

#if defined (TCPP0203_CALLBACKS) && (TCPP0203_CALLBACKS == 1)
typedef void (*tcpp0203_callback_t)(tcpp0203_obj_t *pobj, void *arg);  /*!< callback function pointer definition */

/**
  * @brief Callback context structure
  */
typedef struct
{
  tcpp0203_callback_t callback;   /*!< Callback function to register           */
  void *parg;                   /*!< Optional argument given to the callback */
} tcpp0203_cb_ctx_t;
#endif /* TCPP0203_CALLBACKS */

/**
  * @brief Part object structure
  */
struct tcpp0203_obj_s
{
  tcpp0203_io_t           pio;               /*!< IO interface */
  uint8_t                 is_initialized;    /*!< Init state : 1 if the instance is initialized , 0 otherwise */
  tcpp0203_tcpp_type_t    tcpp_type;
#if defined (TCPP0203_CALLBACKS) && (TCPP0203_CALLBACKS == 1)
  tcpp0203_cb_ctx_t     cb_rising_ctx;      /*!< callback context for exti rising event  */
  tcpp0203_cb_ctx_t     cb_falling_ctx;     /*!< callback context for exti falling event */
#endif /* TCPP0203_CALLBACKS */
};

tcpp0203_status_t tcpp0203_init(tcpp0203_obj_t *pobj, uint32_t id);
tcpp0203_status_t tcpp0203_deinit(tcpp0203_obj_t *pobj);

tcpp0203_status_t tcpp0203_enable_it(tcpp0203_obj_t *pobj);
tcpp0203_status_t tcpp0203_disable_it(tcpp0203_obj_t *pobj);
void tcpp0203_clear_it(tcpp0203_obj_t *pobj);
#if defined (TCPP0203_CALLBACKS) && (TCPP0203_CALLBACKS == 1)
tcpp0203_status_t tcpp0203_register_cable_plugged_callback(tcpp0203_obj_t *pobj, tcpp0203_callback_t pcb, void *p_arg);
tcpp0203_status_t tcpp0203_register_cable_unplugged_callback(tcpp0203_obj_t *pobj, tcpp0203_callback_t pcb,
                                                             void *p_arg);
#endif /* TCPP0203_CALLBACKS */

tcpp0203_status_t tcpp0203_reset(tcpp0203_obj_t *pobj);
tcpp0203_status_t tcpp0203_set_vconn_switch(tcpp0203_obj_t *pobj, tcpp0203_vconn_switch_t vconn_switch);
tcpp0203_status_t tcpp0203_set_gate_driver_provider(tcpp0203_obj_t *pobj,
                                                    tcpp0203_gate_driver_provider_t gate_driver_provider);
tcpp0203_status_t tcpp0203_set_gate_driver_consumer(tcpp0203_obj_t *pobj,
                                                    tcpp0203_gate_driver_consumer_t gate_driver_consumer);
tcpp0203_status_t tcpp0203_set_power_mode(tcpp0203_obj_t *pobj, tcpp0203_power_mode_t power_mode);
tcpp0203_status_t tcpp0203_set_vbus_discharge(tcpp0203_obj_t *pobj, tcpp0203_vbus_discharge_t vbus_discharge);
tcpp0203_status_t tcpp0203_set_vconn_discharge(tcpp0203_obj_t *pobj, tcpp0203_vconn_discharge_t vconn_discharge);
tcpp0203_status_t tcpp0203_get_vconn_switch_ack(tcpp0203_obj_t *pobj, tcpp0203_vconn_switch_ack_t *p_vconn_switch_ack);
tcpp0203_status_t tcpp0203_get_gate_driver_provider_ack(tcpp0203_obj_t *pobj,
                                                        tcpp0203_gate_driver_provider_ack_t
                                                        *p_gate_driver_provider_ack);
tcpp0203_status_t tcpp0203_get_gate_driver_consumer_ack(tcpp0203_obj_t *pobj,
                                                        tcpp0203_gate_driver_consumer_ack_t
                                                        *p_gate_driver_consumer_ack);
tcpp0203_status_t tcpp0203_get_power_mode_ack(tcpp0203_obj_t *pobj, tcpp0203_power_mode_ack_t *p_power_mode_ack);
tcpp0203_status_t tcpp0203_get_vbus_discharge_ack(tcpp0203_obj_t *pobj,
                                                  tcpp0203_vbus_discharge_ack_t *p_vbus_discharge_ack);
tcpp0203_status_t tcpp0203_get_vconn_discharge_ack(tcpp0203_obj_t *pobj,
                                                   tcpp0203_vconn_discharge_ack_t *p_vconn_discharge_ack);
tcpp0203_status_t tcpp0203_get_ocp_vconn_flag(tcpp0203_obj_t *pobj, tcpp0203_ocp_vconn_flag_t *p_ocp_vconn_flag);
tcpp0203_status_t tcpp0203_get_ocp_vbus_flag(tcpp0203_obj_t *pobj, tcpp0203_ocp_vbus_flag_t *p_ocp_vbus_flag);
tcpp0203_status_t tcpp0203_get_ovp_vbus_flag(tcpp0203_obj_t *pobj, tcpp0203_ovp_vbus_flag_t *p_ovp_vbus_flag);
tcpp0203_status_t tcpp0203_get_ovp_cc_flag(tcpp0203_obj_t *pobj, tcpp0203_ovp_cc_flag_t *p_ovp_cc_flag);
tcpp0203_status_t tcpp0203_get_otp_flag(tcpp0203_obj_t *pobj, tcpp0203_otp_flag_t *p_otp_flag);
tcpp0203_status_t tcpp0203_get_vbus_ok_flag(tcpp0203_obj_t *pobj, tcpp0203_vbus_ok_flag_t *p_vbus_ok_flag);
tcpp0203_status_t tcpp0203_read_tcpp_type(tcpp0203_obj_t *pobj, tcpp0203_tcpp_type_t *p_tcpp_type);
tcpp0203_status_t tcpp0203_read_vconn_power(tcpp0203_obj_t *pobj, tcpp0203_vconn_power_t *p_vconn_power);
tcpp0203_status_t tcpp0203_write_ctrl_register(tcpp0203_obj_t *pobj, uint8_t *p_ctrl_register);
tcpp0203_status_t tcpp0203_read_ack_register(tcpp0203_obj_t *pobj, uint8_t *p_ack_register);
tcpp0203_status_t tcpp0203_read_flag_register(tcpp0203_obj_t *pobj, uint8_t *p_flag_register);
tcpp0203_status_t tcpp0203_get_vbus_voltage(tcpp0203_obj_t *pobj, uint32_t *p_voltage);
tcpp0203_status_t tcpp0203_get_vbus_current(tcpp0203_obj_t *pobj, uint32_t *p_current);
tcpp0203_status_t tcpp0203_start(tcpp0203_obj_t *pobj);
tcpp0203_status_t tcpp0203_stop(tcpp0203_obj_t *pobj);

#ifdef __cplusplus
}
#endif

#endif /* TCPP0203_H */
