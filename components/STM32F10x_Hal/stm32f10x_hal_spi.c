/**
 **************************************************************************************************
 * @file        stm32f10x_hal_spi.c
 * @author
 * @version
 * @date        6/25/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "stm32f10x.h"
#include "stm32f10x_hal_gpio.h"
#include "stm32f10x_hal_spi.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    stm32f10x_hal_spi_Modules 
 * @{  
 */

/**
 * @defgroup      stm32f10x_hal_spi_IO_Defines 
 * @brief         
 * @{  
 */

typedef struct
{
    GPIO_ConfigTypedef  CS;
    GPIO_ConfigTypedef  SCLK;
    GPIO_ConfigTypedef  MISO;
    GPIO_ConfigTypedef  MOSI;
}SPI_IOTypedef;

const SPI_IOTypedef SPI_IO[HAL_SPI_COUNT] = 
{
    {
        {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_9,GPIO_Speed_50MHz,GPIO_Mode_Out_PP},
        {RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_5,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
        {RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_6,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
        {RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_7,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
    },
    {
        {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_12,GPIO_Speed_50MHz,GPIO_Mode_Out_PP},
        {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_13,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
        {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_14,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
        {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_15,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
    },
};

/**
 * @}
 */

/**
 * @defgroup       stm32f10x_hal_spi_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_spi_Constants_Defines 
 * @brief         
 * @{  
 */
const SPI_BaseConfigTypedef SPI_BaseConfig[HAL_SPI_COUNT] = 
{
    {
        RCC_APB2Periph_SPI1,
        {
            SPI_Direction_2Lines_FullDuplex,
            SPI_Mode_Master,
            SPI_DataSize_8b,
            SPI_CPOL_Low,
            SPI_CPHA_1Edge,
            SPI_NSS_Soft,
            SPI_BaudRatePrescaler_64,
            SPI_FirstBit_MSB,
            7,
        },
    },
    {
        RCC_APB1Periph_SPI2,
        {
            SPI_Direction_2Lines_FullDuplex,
            SPI_Mode_Master,
            SPI_DataSize_8b,
            SPI_CPOL_Low,
            SPI_CPHA_1Edge,
            SPI_NSS_Soft,
            SPI_BaudRatePrescaler_64,
            SPI_FirstBit_MSB,
            7,
        },
    },
    {
        RCC_APB1Periph_SPI3,
        {
            SPI_Direction_2Lines_FullDuplex,
            SPI_Mode_Master,
            SPI_DataSize_8b,
            SPI_CPOL_Low,
            SPI_CPHA_1Edge,
            SPI_NSS_Soft,
            SPI_BaudRatePrescaler_64,
            SPI_FirstBit_MSB,
            7,
        },
    },
};

SPI_InstanceTypedef SPI_Instance[HAL_SPI_COUNT] = 
{
    SPI1,
    SPI2,
    SPI3,
};
/**
 * @}
 */

/**
 * @defgroup       stm32f10x_hal_spi_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_spi_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_spi_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_spi_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_spi_Functions 
 * @brief         
 * @{  
 */
void HAL_SPI_Init(uint8_t HAL_SPIx)
{
    SPI_IOTypedef *spi_io;
    SPI_BaseConfigTypedef *spi_base_config;
    SPI_InstanceTypedef *spi;

    spi_io = (SPI_IOTypedef*)&SPI_IO[HAL_SPIx];
    spi_base_config = (SPI_BaseConfigTypedef*)&SPI_BaseConfig[HAL_SPIx];
    spi = &SPI_Instance[HAL_SPIx];

    RCC_APB2PeriphClockCmd(spi_io->CS.Clock,ENABLE);
    RCC_APB2PeriphClockCmd(spi_io->MISO.Clock,ENABLE);
    RCC_APB2PeriphClockCmd(spi_io->MOSI.Clock,ENABLE);
    RCC_APB2PeriphClockCmd(spi_io->SCLK.Clock,ENABLE);

    GPIO_Init(spi_io->CS.GPIOx,&spi_io->CS.Init);
    GPIO_Init(spi_io->MISO.GPIOx,&spi_io->MISO.Init);
    GPIO_Init(spi_io->MOSI.GPIOx,&spi_io->MOSI.Init);
    GPIO_Init(spi_io->SCLK.GPIOx,&spi_io->SCLK.Init);

    if (HAL_SPIx == HAL_SPI1)
    {
        RCC_APB2PeriphClockCmd(spi_base_config->Clock,ENABLE);
    }
    else
    {
        RCC_APB1PeriphClockCmd(spi_base_config->Clock,ENABLE);
    }
    SPI_Init(spi->Instance,&spi_base_config->Init);
}

void HAL_SPI_Open(uint8_t HAL_SPIx)
{
    SPI_Cmd(SPI_Instance[HAL_SPIx].Instance,ENABLE);
}

void HAL_SPI_Close(uint8_t HAL_SPIx)
{
    SPI_Cmd(SPI_Instance[HAL_SPIx].Instance,DISABLE);
}

void HAL_SPI_CS_Write(uint8_t HAL_SPIx,BitAction bitval)
{
    GPIO_WriteBit(SPI_IO[HAL_SPIx].CS.GPIOx,SPI_IO[HAL_SPIx].CS.Init.GPIO_Pin,bitval);
}

uint16_t HAL_SPI_RW_Data(uint8_t HAL_SPIx,uint16_t data)
{
    while (SPI_I2S_GetFlagStatus(SPI_Instance[HAL_SPIx].Instance,SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPI_Instance[HAL_SPIx].Instance,data);
    while (SPI_I2S_GetFlagStatus(SPI_Instance[HAL_SPIx].Instance,SPI_I2S_FLAG_RXNE) == RESET);
    return SPI_I2S_ReceiveData(SPI_Instance[HAL_SPIx].Instance); 
}

//void HAL_SPI1_Init()
//{
//    GPIO_InitTypeDef GPIO_InitStructure;
//    SPI_InitTypeDef SPI_InitStructure;
//
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
//    GPIO_Init(GPIOA,&GPIO_InitStructure);
//
//    SPI1_CS_HIGH;
//    GPIO_InitStructure.GPIO_Pin = SPI1_CS_PIN;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_Init(SPI1_CS_PORT,&GPIO_InitStructure);
//
//    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;     //无数据为低
//    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;    //数据捕获第一个边沿
//    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64; //分频
//    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;   //8位数据
//    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //双向全双工
//    SPI_InitStructure.SPI_CRCPolynomial = 7;
//    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;  //数据传输从MSB开始
//    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;       //主机
//    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;           //NSS软件控制
//    SPI_Init(SPI1,&SPI_InitStructure);
//
//    SPI_Cmd(SPI1,ENABLE);
//}

//uint8_t HAL_SPI1_RW_Byte(uint8_t u8dat)
//{
//   while (SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)==RESET);
//   SPI_I2S_SendData(SPI1,u8dat);
//   while (SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE)==RESET);
//   return SPI_I2S_ReceiveData(SPI1);
//}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

