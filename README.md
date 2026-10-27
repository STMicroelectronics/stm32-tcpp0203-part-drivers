# __TCPP0203 Part Drivers__

![tag](https://img.shields.io/badge/tag-2.0.0-brightgreen.svg)
[![release note](https://img.shields.io/badge/release_note-view_html-gold.svg)](https://htmlpreview.github.io/?https://github.com/STMicroelectronics/stm32-tcpp0203-part-drivers/blob/main/Release_Notes.html)

## Overview

The TCPP0203 part drivers provides APIs to drive both TCPP02 and TCPPO3 components through I2C to read/write registers, EXTI to detect type C cable presence and ADC for VBUS and current sensing.

## Description

### Peripherals initialization:

Part TCPP0203 assumes that the initialization of all needed peripherals (I2C, ADC, EXTI,  GPIO) is done by the main application. After the MCU IPs have been initialized, the selected resources can be assigned to the TCPP object. This is done in `tcpp0203_io_init()`, which the user application must override.
That function is called by `tcpp0203_at_init()`; the `dev_id` field of the `tcpp0203_io_t` structure should be used to discriminate the resources to be assigned.

## How to use it?

To use the TCPP0203 part API, the application should define the `tcpp0203_obj_t` object and the `tcpp0203_io_init()` function to assign hardware resources to it.
The link between the two is made by `tcpp0203_init()`, which should be called after all the MCU peripherals have been initialized.

Once this is successfully done, all the other part APIs can be used freely.

Note :
  - FLGn pin of the TCPP0203 component indicates voltage presence on VBUS in hibernate and low power modes and errors (overvoltage, overtemperature, ...) in normal mode.
  - FLGn pin is an open drain output flag, floating when not connected. For that reason, it should be configured as PULL_UP in order to detect falling/raising EXTI callbacks triggered by plug/unplug type C cable events.