/**
 **************************************************************************************************
 * @file        stm32f10x_hal_spi.h
 * @author
 * @version
 * @date        6/25/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _STM32F10X_HAL_SPI_H_
#define _STM32F10X_HAL_SPI_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    stm32f10x_hal_spi_Modules 
 * @{  
 */

/**
 * @defgroup      stm32f10x_hal_spi_Exported_Macros 
 * @{  
 */
#define HAL_SPI_COUNT   3
#define HAL_SPI1        0
#define HAL_SPI2        1
#define HAL_SPI3        2
/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_spi_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_spi_Exported_Types 
 * @{  
 */
typedef struct
{
    uint32_t        Clock;
    SPI_InitTypeDef Init;
}SPI_BaseConfigTypedef;

typedef struct
{
    SPI_TypeDef *Instance;
}SPI_InstanceTypedef;
/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_spi_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_spi_Exported_Functions 
 * @{  
 */
void HAL_SPI_Init(uint8_t HAL_SPIx);
void HAL_SPI_Open(uint8_t HAL_SPIx);
void HAL_SPI_Close(uint8_t HAL_SPIx);
void HAL_SPI_CS_Write(uint8_t HAL_SPIx,BitAction bitval);
uint16_t HAL_SPI_RW_Data(uint8_t HAL_SPIx,uint16_t data);
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
