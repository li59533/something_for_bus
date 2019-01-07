/**
 **************************************************************************************************
 * @file        stm32f10x_bsp_flash.h
 * @author
 * @version
 * @date        9/19/2017
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _STM32F10X_BSP_FLASH_H_
#define _STM32F10X_BSP_FLASH_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    stm32f10x_bsp_flash_Modules 
 * @{  
 */

/**
 * @defgroup      stm32f10x_bsp_flash_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_bsp_flash_Exported_Constants
 * @{  
 */
#if defined (STM32F10X_HD) || defined (STM32F10X_CL)
#define BSP_FLASH_SECTOR_SIZE   2048
#elif defined (STM32F10X_MD) || defined (STM32F10X_LD)
#define BSP_FLASH_SECTOR_SIZE   1024
#endif
/**
 * @}
 */

/**
 * @defgroup      stm32f10x_bsp_flash_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_bsp_flash_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_bsp_flash_Exported_Functions 
 * @{  
 */
void BSP_FLASH_EraseSector(uint32_t addr);
void BSP_FLASH_WriteBytes(uint32_t addr,uint8_t *pBuf,uint16_t count);
void BSP_FLASH_ReadBytes(uint32_t addr,uint8_t *pBuf,uint16_t count);
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
