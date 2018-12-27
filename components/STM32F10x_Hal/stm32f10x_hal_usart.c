/**
 **************************************************************************************************
 * @file        stm32f10x_hal_usart.c
 * @author
 * @version
 * @date        5/29/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "stm32f10x.h"
#include "selftypedef.h"
#include "stm32f10x_hal_conf.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    stm32f10x_hal_usart_Modules 
 * @{  
 */

/**
 * @defgroup      stm32f10x_hal_usart_IO_Defines 
 * @brief         
 * @{  
 */
typedef struct
{
    GPIO_ConfigTypedef TxPort;
    GPIO_ConfigTypedef RxPort;
    uint32_t GPIO_Remap;
}USART_IOTypedef;

const USART_IOTypedef USART_IO[HAL_USART_COUNT] = 
{
    {
        {RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_9,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
        {RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_10,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
        NULL,
    },
    {
        {RCC_APB2Periph_GPIOD,GPIOD,GPIO_Pin_5,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
        {RCC_APB2Periph_GPIOD,GPIOD,GPIO_Pin_6,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
        GPIO_Remap_USART2,
    },
    {
        {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_10,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
        {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_11,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
        NULL,
    },
    {
        {RCC_APB2Periph_GPIOC,GPIOC,GPIO_Pin_10,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
        {RCC_APB2Periph_GPIOC,GPIOC,GPIO_Pin_11,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
        NULL,
    },
    {
        {RCC_APB2Periph_GPIOC,GPIOC,GPIO_Pin_12,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
        {RCC_APB2Periph_GPIOD,GPIOD,GPIO_Pin_2,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
        NULL,
    },
};
/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_usart_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_usart_Constants_Defines 
 * @brief         
 * @{  
 */
const USART_BaseConfigTypedef USART_BaseConfig[HAL_USART_COUNT] = 
{
    /* USART1 */
    {
        USART1,
        USART1_IRQn,
        RCC_APB2Periph_USART1,
        {
            115200,
            USART_WordLength_8b,
            USART_StopBits_1,
            USART_Parity_No,
            USART_Mode_Tx|USART_Mode_Rx,
            USART_HardwareFlowControl_None,
        },
        USART_TransmissionMode_DMA,
        USART_TransmissionMode_DMA,
    },
    /* USART2 */
    {
        USART2,
        USART2_IRQn,
        RCC_APB1Periph_USART2,
        {
            115200,
            USART_WordLength_8b,
            USART_StopBits_1,
            USART_Parity_No,
            USART_Mode_Tx|USART_Mode_Rx,
            USART_HardwareFlowControl_None,
        },
        USART_TransmissionMode_DMA,
        USART_TransmissionMode_DMA,
    },
    /* USART3 */
    {
        USART3,
        USART3_IRQn,
        RCC_APB1Periph_USART3,
        {
            115200,
            USART_WordLength_8b,
            USART_StopBits_1,
            USART_Parity_No,
            USART_Mode_Tx|USART_Mode_Rx,
            USART_HardwareFlowControl_None,
        },
        USART_TransmissionMode_DMA,
        USART_TransmissionMode_DMA,
    },
};

const USART_ExConfigTypedef USART_ExConfig[HAL_USART_COUNT] = 
{
    /* USART1 */
    {
        /* Tx DMA Config */
        {
            RCC_AHBPeriph_DMA1,
            DMA1_Channel4,
            DMA_Mode_Normal,
            DMA1_Channel4_IRQn,
        },
        /* Rx DMA Config */
        {
            RCC_AHBPeriph_DMA1,
            DMA1_Channel5,
            DMA_Mode_Normal,
            DMA1_Channel5_IRQn,
        },
    },
    /* USART2 */
    {
        /* Tx DMA Config */
        {
            RCC_AHBPeriph_DMA1,
            DMA1_Channel7,
            DMA_Mode_Normal,
            DMA1_Channel7_IRQn,
        },
        /* Rx DMA Config */
        {
            RCC_AHBPeriph_DMA1,
            DMA1_Channel6,
            DMA_Mode_Normal,
            DMA1_Channel6_IRQn,
        },
    },
    /* USART3 */
    {
        /* Tx DMA Config */
        {
            RCC_AHBPeriph_DMA1,
            DMA1_Channel2,
            DMA_Mode_Normal,
            DMA1_Channel2_IRQn,
        },
        /* Rx DMA Config */
        {
            RCC_AHBPeriph_DMA1,
            DMA1_Channel3,
            DMA_Mode_Normal,
            DMA1_Channel3_IRQn,
        },
    },
};
/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_usart_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_usart_Private_Variables 
 * @brief         
 * @{  
 */
static uint8_t USART1_Tx_Buf[100];
static uint8_t USART1_Rx_Buf[100];
static uint8_t USART2_Tx_Buf[100];
static uint8_t USART2_Rx_Buf[100];
static uint8_t USART3_Tx_Buf[100];
static uint8_t USART3_Rx_Buf[100];

USART_InstanceTypedef USART_Instance[HAL_USART_COUNT] = 
{
    /* USART1 */
    {
        USART1,
        {
            USART1_Tx_Buf,
            sizeof(USART1_Tx_Buf)/sizeof(USART1_Tx_Buf[0]),
            0,
            0,
        },
        {
            USART1_Rx_Buf,
            sizeof(USART1_Rx_Buf)/sizeof(USART1_Rx_Buf[0]),
            0,
            0,
        },
    },
    /* USART2 */
    {
        USART2,
        {
            USART2_Tx_Buf,
            sizeof(USART2_Tx_Buf)/sizeof(USART2_Tx_Buf[0]),
            0,
            0,
        },
        {
            USART2_Rx_Buf,
            sizeof(USART2_Rx_Buf)/sizeof(USART2_Rx_Buf[0]),
            0,
            0,
        },
    },
    /* USART3 */
    {
        USART3,
        {
            USART3_Tx_Buf,
            sizeof(USART3_Tx_Buf)/sizeof(USART3_Tx_Buf[0]),
            0,
            0,
        },
        {
            USART3_Rx_Buf,
            sizeof(USART3_Rx_Buf)/sizeof(USART3_Rx_Buf[0]),
            0,
            0,
        },
    },
};
/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_usart_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_usart_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_usart_Functions 
 * @brief         
 * @{  
 */
void HAL_USART_Init(uint8_t HAL_USARTx)
{
    USART_BaseConfigTypedef *usart_base_config;
    USART_ExConfigTypedef *usart_ex_config;
    USART_IOTypedef *usart_io;
    USART_InstanceTypedef *usart;

    usart_base_config = (USART_BaseConfigTypedef *)&USART_BaseConfig[HAL_USARTx];
    usart_io = (USART_IOTypedef *)&USART_IO[HAL_USARTx];
    usart = &USART_Instance[HAL_USARTx];
    
    USART_DeInit(usart->Instance);

    if (HAL_USARTx == HAL_USART1)
    {
        RCC_APB2PeriphClockCmd(usart_base_config->USART_Clock,ENABLE);
    }
    else
    {
        RCC_APB1PeriphClockCmd(usart_base_config->USART_Clock,ENABLE);
    }

    USART_Init(usart->Instance,&usart_base_config->Init);

    RCC_APB2PeriphClockCmd(usart_io->TxPort.Clock,ENABLE);
    RCC_APB2PeriphClockCmd(usart_io->RxPort.Clock,ENABLE);

    GPIO_Init(usart_io->TxPort.GPIOx,&usart_io->TxPort.Init);
    GPIO_Init(usart_io->RxPort.GPIOx,&usart_io->RxPort.Init);

    if (usart_io->GPIO_Remap != NULL)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
        GPIO_PinRemapConfig(usart_io->GPIO_Remap,ENABLE);
    }

    if (usart_base_config->TxTransmissionMode == USART_TransmissionMode_DMA)
    {
        usart_ex_config = (USART_ExConfigTypedef*)&USART_ExConfig[HAL_USARTx];
        DMA_InitTypeDef DMA_InitStructure;
        RCC_AHBPeriphClockCmd(usart_ex_config->TxDMAConfig.DMA_Clock,ENABLE);
        DMA_DeInit(usart_ex_config->TxDMAConfig.DMA_Channel);
        DMA_InitStructure = HAL_DMA_USART_StructInit((uint32_t)&usart->Instance->DR,(uint32_t)usart->TxBuf.pBuf,0,DMA_DIR_PeripheralDST,usart_ex_config->TxDMAConfig.DMA_Mode);
        DMA_Cmd(usart_ex_config->TxDMAConfig.DMA_Channel,DISABLE);
        DMA_Init(usart_ex_config->TxDMAConfig.DMA_Channel,&DMA_InitStructure);
        USART_DMACmd(usart->Instance,USART_DMAReq_Tx,ENABLE);
    }
    else if (usart_base_config->TxTransmissionMode == USART_TransmissionMode_IRQ)
    {

    }
    else if (usart_base_config->TxTransmissionMode == USART_TransmissionMode_Query)
    {

    }
    else
    {

    }
    
    if (usart_base_config->RxTransmissionMode == USART_TransmissionMode_DMA)
    {
        DMA_InitTypeDef DMA_InitStructure;
        RCC_AHBPeriphClockCmd(usart_ex_config->RxDMAConfig.DMA_Clock,ENABLE);
        DMA_DeInit(usart_ex_config->RxDMAConfig.DMA_Channel);
        DMA_InitStructure = HAL_DMA_USART_StructInit((uint32_t)&usart->Instance->DR,(uint32_t)usart->RxBuf.pBuf,usart->RxBuf.Size,DMA_DIR_PeripheralSRC,usart_ex_config->RxDMAConfig.DMA_Mode);
        DMA_Init(usart_ex_config->RxDMAConfig.DMA_Channel,&DMA_InitStructure);
        USART_DMACmd(usart->Instance,USART_DMAReq_Rx,ENABLE);
        DMA_Cmd(usart_ex_config->RxDMAConfig.DMA_Channel,ENABLE);
    }
    else if (usart_base_config->RxTransmissionMode == USART_TransmissionMode_IRQ)
    {

    }
    else if (usart_base_config->RxTransmissionMode == USART_TransmissionMode_Query)
    {

    }
    else
    {

    }
}

void HAL_USART_Open(uint8_t HAL_USARTx)
{
    USART_Cmd(USART_Instance[HAL_USARTx].Instance,ENABLE);
}

void HAL_USART_Close(uint8_t HAL_USARTx)
{
    USART_Cmd(USART_Instance[HAL_USARTx].Instance,DISABLE);
}

void HAL_USART_ITConfig(uint8_t HAL_USARTx,uint16_t USART_IT,uint8_t PrePriority,uint8_t SubPriority,FunctionalState NewState)
{
    HAL_NVIC_Config(USART_BaseConfig[HAL_USARTx].IRQn,PrePriority,SubPriority,NewState);
    USART_ITConfig(USART_BaseConfig[HAL_USARTx].Instance,USART_IT,NewState);
}

void HAL_USART_Tx_DMAITConfig(uint8_t HAL_USARTx,uint32_t DMA_IT,uint8_t PrePriority,uint8_t SubPriority,FunctionalState NewState)
{
    HAL_NVIC_Config(USART_ExConfig[HAL_USARTx].TxDMAConfig.DMA_IRQChannel, PrePriority, SubPriority, NewState);
    DMA_ITConfig(USART_ExConfig[HAL_USARTx].TxDMAConfig.DMA_Channel, DMA_IT, NewState); 
}

void HAL_USART_Rx_DMAITConfig(uint8_t HAL_USARTx,uint32_t DMA_IT,uint8_t PrePriority,uint8_t SubPriority,FunctionalState NewState)
{
    HAL_NVIC_Config(USART_ExConfig[HAL_USARTx].RxDMAConfig.DMA_IRQChannel, PrePriority, SubPriority, NewState);
    DMA_ITConfig(USART_ExConfig[HAL_USARTx].RxDMAConfig.DMA_Channel, DMA_IT, NewState); 
}

void HAL_USART_SendBytesDMA(uint8_t HAL_USARTx,uint8_t *pBuf,uint16_t length)
{
    uint16_t i=0,send_length = 0;
    uint32_t addr = 0;
    USART_InstanceTypedef *usart;
    USART_ExConfigTypedef *usart_ex_config;
        
    usart_ex_config = (USART_ExConfigTypedef *)&USART_ExConfig[HAL_USARTx];
    usart = &USART_Instance[HAL_USARTx];

    for(i=0; i<length; i++)
    {
        usart->TxBuf.pBuf[usart->TxBuf.WritePtr++] = pBuf[i];
        usart->TxBuf.WritePtr %= usart->TxBuf.Size;
    }

    if (DMA_GetCurrDataCounter(usart_ex_config->TxDMAConfig.DMA_Channel) == 0)
    {
        addr = (uint32_t)&usart->TxBuf.pBuf[usart->TxBuf.ReadPtr];
        if (usart->TxBuf.ReadPtr > usart->TxBuf.WritePtr)
        {
            send_length = usart->TxBuf.Size - usart->TxBuf.ReadPtr;
        }
        else
        {
            send_length = usart->TxBuf.WritePtr - usart->TxBuf.ReadPtr;
        }
        if (send_length > 0)
        {
            usart->TxBuf.ReadPtr = (usart->TxBuf.ReadPtr+send_length) % usart->TxBuf.Size;
            DMA_Cmd(usart_ex_config->TxDMAConfig.DMA_Channel,DISABLE);
            usart_ex_config->TxDMAConfig.DMA_Channel->CMAR = addr;
            usart_ex_config->TxDMAConfig.DMA_Channel->CNDTR = send_length;
            DMA_Cmd(usart_ex_config->TxDMAConfig.DMA_Channel,ENABLE);
        }
    }
}

void HAL_USART_SendBytesDMAISR(uint8_t HAL_USARTx)
{
    uint16_t send_length = 0;
    uint32_t addr = 0;
    USART_InstanceTypedef *usart;
    USART_ExConfigTypedef *usart_ex_config;
        
    usart_ex_config = (USART_ExConfigTypedef *)&USART_ExConfig[HAL_USARTx];
    usart = &USART_Instance[HAL_USARTx];

    if (DMA_GetCurrDataCounter(usart_ex_config->TxDMAConfig.DMA_Channel) == 0)
    {
        addr = (uint32_t)&usart->TxBuf.pBuf[usart->TxBuf.ReadPtr];
        if (usart->TxBuf.ReadPtr > usart->TxBuf.WritePtr)
        {
            send_length = usart->TxBuf.Size - usart->TxBuf.ReadPtr;
        }
        else
        {
            send_length = usart->TxBuf.WritePtr - usart->TxBuf.ReadPtr;
        }
        if (send_length > 0)
        {
            usart->TxBuf.ReadPtr = (usart->TxBuf.ReadPtr+send_length) % usart->TxBuf.Size;
            DMA_Cmd(usart_ex_config->TxDMAConfig.DMA_Channel,DISABLE);
            usart_ex_config->TxDMAConfig.DMA_Channel->CMAR = addr;
            usart_ex_config->TxDMAConfig.DMA_Channel->CNDTR = send_length;
            DMA_Cmd(usart_ex_config->TxDMAConfig.DMA_Channel,ENABLE);
        }
    }
}

void HAL_USART_SendBytesQuery(uint8_t HAL_USARTx,uint8_t* pBuf,uint16_t length)
{
    USART_InstanceTypedef *usart;
    uint8_t* p = pBuf;

    usart = &USART_Instance[HAL_USARTx];

    while (length--)
    {
        USART_SendData(usart->Instance,*p++);
        while (USART_GetFlagStatus(usart->Instance,USART_FLAG_TXE) == RESET); 
    }
}

void HAL_USART_SendBytesInt(uint8_t HAL_USARTx,uint8_t* pBuf,uint16_t length)
{
    uint16_t i;
    
    USART_InstanceTypedef *usart;
        
    usart = &USART_Instance[HAL_USARTx];

    for(i=0; i<length; i++)
    {
        usart->TxBuf.pBuf[usart->TxBuf.WritePtr++] = pBuf[i];
        usart->TxBuf.WritePtr %= usart->TxBuf.Size;
    }

    USART_SendData(usart->Instance,usart->TxBuf.pBuf[usart->TxBuf.ReadPtr++]);
    usart->TxBuf.ReadPtr %= usart->TxBuf.Size;
    USART_ITConfig(usart->Instance,USART_IT_TXE,ENABLE);
}

void HAL_USART_SendBytesIntISR(uint8_t HAL_USARTx)
{
    USART_InstanceTypedef *usart;
    usart = &USART_Instance[HAL_USARTx];

    if (usart->TxBuf.ReadPtr != usart->TxBuf.WritePtr)
    {
        USART_SendData(usart->Instance,usart->TxBuf.pBuf[usart->TxBuf.ReadPtr++]);
        usart->TxBuf.ReadPtr %= usart->TxBuf.Size;
    }
    else
    {
        USART_ITConfig(usart->Instance,USART_IT_TXE,DISABLE);
    }
}

uint16_t HAL_USART_ReadBytesDMA(uint8_t HAL_USARTx,uint8_t* pBuf,uint16_t count)
{
    uint16_t read_count = 0;
    USART_InstanceTypedef *usart;
    USART_ExConfigTypedef *usart_ex_config;
        
    uint8_t* p = pBuf;

    usart = &USART_Instance[HAL_USARTx];
    usart_ex_config = (USART_ExConfigTypedef *)&USART_ExConfig[HAL_USARTx];

    while (count--)
    {
        usart->RxBuf.WritePtr = usart->RxBuf.Size - DMA_GetCurrDataCounter(usart_ex_config->RxDMAConfig.DMA_Channel);
        if (usart->RxBuf.ReadPtr == usart->RxBuf.WritePtr)
        {
            return read_count;
        }

        *p++ = usart->RxBuf.pBuf[usart->RxBuf.ReadPtr++];
        usart->RxBuf.ReadPtr %= usart->RxBuf.Size;
        read_count++;
    }
    return read_count;
}

uint16_t HAL_USART_ReadBytesInt(uint8_t HAL_USARTx,uint8_t *pBuf,uint16_t count)
{
    uint16_t read_count = 0;
    USART_InstanceTypedef *usart;
        
    uint8_t* p = pBuf;

    usart = &USART_Instance[HAL_USARTx];

    while (count--)
    {
        if (usart->RxBuf.ReadPtr == usart->RxBuf.WritePtr)
        {
            return read_count;
        }
        *p++ = usart->RxBuf.pBuf[usart->RxBuf.ReadPtr++];
        usart->RxBuf.ReadPtr %= usart->RxBuf.Size;
        read_count++;
    }
    return read_count;
}

void HAL_USART_ReadBytesIntISR(uint8_t HAL_USARTx,uint16_t data)
{
    USART_InstanceTypedef *usart;

    usart = &USART_Instance[HAL_USARTx];

    usart->RxBuf.pBuf[usart->RxBuf.WritePtr++] = data;
    usart->RxBuf.WritePtr %= usart->RxBuf.Size;
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

