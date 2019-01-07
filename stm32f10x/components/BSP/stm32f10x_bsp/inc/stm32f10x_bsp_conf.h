/**
 **************************************************************************************************
 * @file        stm32f10x_bsp_conf.h
 * @author
 * @version     V2.0.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _STM32F10X_BSP_CONF_H_
#define _STM32F10X_BSP_CONF_H_

#include "stm32f10x.h"
#include "stdio.h"

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    stm32f10x_bsp_conf_Modules 
 * @{  
 */

/**
 * @defgroup      stm32f10x_bsp_conf_Exported_Macros 
 * @{  
 */
#define BSP_GPIO_MODULE_ENABLE          0
#define BSP_NVIC_MODULE_ENABLE          0
#define BSP_DMA_MODULE_ENABLE           0
#define BSP_SYSTICK_MODULE_ENABLE       1
#define BSP_USART_MODULE_ENABLE         0
#define BSP_EXTI_MODULE_ENABLE          0
#define BSP_FLASH_MODULE_ENABLE         1
#define BSP_SPI_MODULE_ENABLE           0
#define BSP_ADC_MODULE_ENABLE           0
#define BSP_RTC_MODULE_ENABLE           0
#define BSP_WDG_MODULE_ENABLE           0
#define BSP_TIM_MODULE_ENABLE           0
#define BSP_PWM_MODULE_ENABLE           0
#define BSP_I2CSW_MODULE_ENABLE         0

#if BSP_GPIO_MODULE_ENABLE == 1
#include "stm32f10x_bsp_gpio.h"
#endif

#if BSP_NVIC_MODULE_ENABLE == 1
#include "stm32f10x_bsp_nvic.h"
#endif

#if BSP_DMA_MODULE_ENABLE == 1
#include "stm32f10x_bsp_dma.h"
#endif

#if BSP_USART_MODULE_ENABLE == 1
#include "stm32f10x_bsp_usart.h"
#include "stm32f10x_bsp_usart_conf.h"
#include "stm32f10x_bsp_usart_cb.h"
#endif

#if BSP_SYSTICK_MODULE_ENABLE == 1
#include "stm32f10x_bsp_systick.h"
#endif

#if BSP_EXTI_MODULE_ENABLE == 1
#include "stm32f10x_bsp_exti.h"
#include "stm32f10x_bsp_exti_conf.h"
#endif

#if BSP_FLASH_MODULE_ENABLE == 1
#include "stm32f10x_bsp_flash.h"
#endif

#if BSP_SPI_MODULE_ENABLE == 1
#include "stm32f10x_bsp_spi.h"
#include "stm32f10x_bsp_spi_conf.h"
#endif

#if BSP_TIM_MODULE_ENABLE == 1
#include "stm32f10x_bsp_tim.h"
#include "stm32f10x_bsp_tim_conf.h"
#endif

#if BSP_ADC_MODULE_ENABLE == 1
#include "stm32f10x_bsp_adc.h"
#include "stm32f10x_bsp_adc_conf.h"
#endif

#if BSP_RTC_MODULE_ENABLE == 1
#include "stm32f10x_bsp_rtc.h"
#include "stm32f10x_bsp_rtc_conf.h"
#endif

#if BSP_WDG_MODULE_ENABLE == 1
#include "stm32f10x_bsp_wdg.h"
#include "stm32f10x_bsp_wdg_conf.h"
#endif

#if BSP_I2CSW_MODULE_ENABLE == 1
#include "stm32f10x_bsp_i2c_sw.h"
#include "stm32f10x_bsp_i2c_sw_conf.h"
#endif

#if BSP_PWM_MODULE_ENABLE == 1
#include "stm32f10x_bsp_pwm.h"
#include "stm32f10x_bsp_pwm_conf.h"
#endif


#define BSP_CHIP_ID_LEN         12
#define BSP_READ_CHIP_ID(pBuf)  \
                                do \
                                { \
                                    int i; \
                                    for(i=0; i<12; i++) \
                                    { \
                                        pBuf[i] = *(uint8_t*)(0x1FFFF7E0+i); \
                                    } \
                                }while(0);                                     
/**
 * @}
 */

/**
 * @defgroup      stm32f10x_bsp_conf_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_bsp_conf_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_bsp_conf_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_bsp_conf_Exported_Functions 
 * @{  
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
#endif
