# origin-pack: STMicroelectronics::tcpp0203_part_drivers@2.0.0
# file-format: 1.0.0
project(STMicroelectronics_tcpp0203_part_drivers_2_0_0)
cmake_minimum_required(VERSION 3.30)
add_library(STMicroelectronics_tcpp0203_part_drivers_2_0_0 INTERFACE)

# List of all CMSIS properties that influence conditions for this package


# Device specific defined symbols








# Enable all components in this package
if(CMSIS_ENTIRE_STMicroelectronics_tcpp0203_part_drivers_2_0_0)
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Board Part#Cgroup:USBPD#Csub:TCPP0203 Core#Cversion:1.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Board Part#Cgroup:USBPD#Csub:TCPP0203 IO#Cvariant:I2C EXTI ADC Polling#Cversion:1.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Board Part#Cgroup:USBPD#Csub:TCPP0203 IO#Cvariant:Custom#Cversion:1.0.0")
endif()

# All conditions used by this package

# condition: STMicroelectronics.tcpp0203_part_drivers.2.0.0:TCPP0203 CFG Condition
# description: STMicroelectronics configuration for TCPP0203 part driver
set(STMicroelectronics.tcpp0203_part_drivers.2.0.0_TCPP0203_CFG_Condition "1")
message(DEBUG "CMSIS condition STMicroelectronics.tcpp0203_part_drivers.2.0.0_TCPP0203_CFG_Condition enabled")


# condition: STMicroelectronics.tcpp0203_part_drivers.2.0.0:TCPP0203 Core Condition
# description: STMicroelectronics TCPP0203 Core Driver
set(STMicroelectronics.tcpp0203_part_drivers.2.0.0_TCPP0203_Core_Condition "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Board Part#.*Cgroup:USBPD#.*Csub:TCPP0203 IO(#.*|$)>,>>")
message(DEBUG "CMSIS condition STMicroelectronics.tcpp0203_part_drivers.2.0.0_TCPP0203_Core_Condition enabled")


# condition: STMicroelectronics.tcpp0203_part_drivers.2.0.0:TCPP0203 Custom IO Condition
# description: 
set(STMicroelectronics.tcpp0203_part_drivers.2.0.0_TCPP0203_Custom_IO_Condition "1")
message(DEBUG "CMSIS condition STMicroelectronics.tcpp0203_part_drivers.2.0.0_TCPP0203_Custom_IO_Condition enabled")


# condition: STMicroelectronics.tcpp0203_part_drivers.2.0.0:TCPP0203 IO I2C EXTI AND ADC Polling Condition
# description: STMicroelectronics TCPP0203 IO I2C AND ADC Polling Driver
set(STMicroelectronics.tcpp0203_part_drivers.2.0.0_TCPP0203_IO_I2C_EXTI_AND_ADC_Polling_Condition "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:I2C(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:ADC(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:EXTI(#.*|$)>,>>>")
message(DEBUG "CMSIS condition STMicroelectronics.tcpp0203_part_drivers.2.0.0_TCPP0203_IO_I2C_EXTI_AND_ADC_Polling_Condition enabled")

# Files and components in this package
if("Cvendor:STMicroelectronics#Cclass:Board Part#Cgroup:USBPD#Csub:TCPP0203 Core#Cversion:1.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Driver for TCPP0203 part
  message(DEBUG "Using component Board_Part_USBPD_TCPP0203_Core_1_0_0")
  target_compile_definitions(STMicroelectronics_tcpp0203_part_drivers_2_0_0 INTERFACE "$<${STMicroelectronics.tcpp0203_part_drivers.2.0.0_TCPP0203_Core_Condition}:-DCMSIS_USE_Board_Part_USBPD_TCPP0203_Core_1_0_0=1>")
  target_include_directories(STMicroelectronics_tcpp0203_part_drivers_2_0_0 INTERFACE "$<${STMicroelectronics.tcpp0203_part_drivers.2.0.0_TCPP0203_Core_Condition}:${CMAKE_CURRENT_LIST_DIR}/.>")
  target_sources(STMicroelectronics_tcpp0203_part_drivers_2_0_0 INTERFACE "$<${STMicroelectronics.tcpp0203_part_drivers.2.0.0_TCPP0203_Core_Condition}:${CMAKE_CURRENT_LIST_DIR}/tcpp0203.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Board Part#Cgroup:USBPD#Csub:TCPP0203 IO#Cvariant:I2C EXTI ADC Polling#Cversion:1.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # I2C AND ADC IO in polling mode for TCPP0203 part
  message(DEBUG "Using component Board_Part_USBPD_TCPP0203_IO_I2C_EXTI_ADC_Polling_1_0_0")
  target_compile_definitions(STMicroelectronics_tcpp0203_part_drivers_2_0_0 INTERFACE "$<${STMicroelectronics.tcpp0203_part_drivers.2.0.0_TCPP0203_IO_I2C_EXTI_AND_ADC_Polling_Condition}:-DCMSIS_USE_Board_Part_USBPD_TCPP0203_IO_I2C_EXTI_ADC_Polling_1_0_0=1>")
  target_include_directories(STMicroelectronics_tcpp0203_part_drivers_2_0_0 INTERFACE "$<${STMicroelectronics.tcpp0203_part_drivers.2.0.0_TCPP0203_IO_I2C_EXTI_AND_ADC_Polling_Condition}:${CMAKE_CURRENT_LIST_DIR}/interfaces/adc_i2c_exti>")
  target_sources(STMicroelectronics_tcpp0203_part_drivers_2_0_0 INTERFACE "$<${STMicroelectronics.tcpp0203_part_drivers.2.0.0_TCPP0203_IO_I2C_EXTI_AND_ADC_Polling_Condition}:${CMAKE_CURRENT_LIST_DIR}/interfaces/adc_i2c_exti/tcpp0203_io.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Board Part#Cgroup:USBPD#Csub:TCPP0203 IO#Cvariant:Custom#Cversion:1.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # Custom I/O layer for TCPP0203 part
  message(DEBUG "Using component Board_Part_USBPD_TCPP0203_IO_Custom_1_0_0")
  target_compile_definitions(STMicroelectronics_tcpp0203_part_drivers_2_0_0 INTERFACE "$<${STMicroelectronics.tcpp0203_part_drivers.2.0.0_TCPP0203_Custom_IO_Condition}:-DCMSIS_USE_Board_Part_USBPD_TCPP0203_IO_Custom_1_0_0=1>")
  target_include_directories(STMicroelectronics_tcpp0203_part_drivers_2_0_0 INTERFACE "$<${STMicroelectronics.tcpp0203_part_drivers.2.0.0_TCPP0203_Custom_IO_Condition}:${CMAKE_CURRENT_LIST_DIR}/interfaces/custom>")
  target_sources(STMicroelectronics_tcpp0203_part_drivers_2_0_0 INTERFACE "$<${STMicroelectronics.tcpp0203_part_drivers.2.0.0_TCPP0203_Custom_IO_Condition}:${CMAKE_CURRENT_LIST_DIR}/interfaces/custom/tcpp0203_io.c>")
endif()

