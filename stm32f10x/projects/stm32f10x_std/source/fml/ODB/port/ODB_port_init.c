/**
 **************************************************************************************************
 * @file        ODB_port_init.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "ODB_port_init.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    ODB_port_init_Modules 
 * @{  
 */

/**
 * @defgroup      ODB_port_init_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ODB_port_init_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ODB_port_init_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ODB_port_init_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ODB_port_init_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ODB_port_init_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ODB_port_init_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void odb_can_init(void);
/**
 * @}
 */

/**
 * @defgroup      ODB_port_init_Functions 
 * @brief         
 * @{  
 */
void ODB_Hal_Init(void)
{
    odb_can_init(void);
}

static void odb_can_init(void)
{
    CAN_InitTypeDef  CAN_InitStruct;
    CAN_FilterInitTypeDef CAN_FilterInitStruct;
    NVIC_InitTypeDef  NVIC_InitStruct;
    GPIO_InitTypeDef GPIO_InitStruct;
   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA,&GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStruct);

    GPIO_PinRemapConfig(GPIO_Remap2_CAN1 , ENABLE);

    NVIC_InitStruct.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;　　//我这使用的是CAN1的接收中断，实际上，CAN1还有发送中断：USB_HP_CAN1_TX_IRQn。注意，CAN1中断是和USB是共用的，所以如果你打开了CAN1中断，就不能再用USB中断了。
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3; 　　 //抢占优先级 = 0
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0 ;　　 //子优先级 = 34
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
 
    NVIC_Init(&NVIC_InitStruct);
    CAN_DeInit(CAN1);

    CAN_StructInit(&CAN_InitStruct);

    CAN_InitStruct.CAN_TTCM = DISABLE;
    CAN_InitStruct.CAN_ABOM = DISABLE;
    CAN_InitStruct.CAN_AWUM = DISABLE;
    CAN_InitStruct.CAN_NART = DISABLE;
    CAN_InitStruct.CAN_RFLM = DISABLE;
    CAN_InitStruct.CAN_TXFP = DISABLE;
    CAN_InitStruct.CAN_Mode = CAN_Mode_Normal;

    /* CAN Baudrate = 1MBps*/
    CAN_InitStruct.CAN_SJW = CAN_SJW_1tq;
    CAN_InitStruct.CAN_BS1 = CAN_BS1_3tq;
    CAN_InitStruct.CAN_BS2 = CAN_BS2_5tq;
    CAN_InitStruct.CAN_Prescaler = 4;
    CAN_Init(CAN1, &CAN_InitStruct);

    CAN_FilterInitStruct.CAN_FilterNumber = 0;
    CAN_FilterInitStruct.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStruct.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitStruct.CAN_FilterIdHigh = 0x0000;
    CAN_FilterInitStruct.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStruct.CAN_FilterMaskIdHigh = 0x0000;
    CAN_FilterInitStruct.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStruct.CAN_FilterFIFOAssignment = 0;
    CAN_FilterInitStruct.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(&CAN_FilterInitStruct);

    CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE)//FIFO0消息挂号中断屏蔽


    
}

void ODB_Data_Send(uint8_t * buf)
{
    CanTxMsg TxMessage;
    TxMessage.DLC =0 ;
    TxMessage.ExtId =0 ;
    TxMessage.IDE = 0;
    TxMessage.RTR = 0;
    TxMessage.StdId = 0;
    memcpy(TxMessage.Data,buf,8);
    CAN_Transmit(CAN1, &TxMessage);
}

void ODB_CAN1_RX0_IRQHandler(void)
{
    CanRxMsg RxMessage;
    if(CAN_GetITStatus(CAN1, CAN_IT_FMP0) != RESET)
    {
        CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
    }
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

