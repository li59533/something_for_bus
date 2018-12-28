/**
 **************************************************************************************************
 * @file        gprs_queue.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "gprs_queue.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    gprs_queue_Modules 
 * @{  
 */

/**
 * @defgroup      gprs_queue_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_queue_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_queue_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_queue_Private_Types
 * @brief         
 * @{  
 */
typedef struct
{
    GPRSMsg_t *pData;
    uint8_t In;
    uint8_t Out;
    uint8_t Size;
    uint8_t Count;
}GPRSMsgQueue_t;
/**
 * @}
 */

/**
 * @defgroup      gprs_queue_Private_Variables 
 * @brief         
 * @{  
 */
GPRSPacket_t s_GPRSRecvPacketBuf[8];

GPRSMsgQueue_t s_GPRSRecvPacketQueue=
{
    .pData = s_GPRSRecvPacketBuf,
    .In = 0,
    .Out = 0,
    .Count = 0,
    .Size = sizeof(s_GPRSRecvPacketBuf)/sizeof(s_GPRSRecvPacketBuf[0]),

};

GPRSPacket_t s_GPRSSendPacketBuf[8];
GPRSPacketQueue_t s_GPRSSendPacketQueue = 
{
    .pData = s_GPRSSendPacketBuf,
    .In = 0,
    .Out = 0,
    .Count = 0,
    .Size = sizeof(s_GPRSSendPacketBuf)/sizeof(s_GPRSSendPacketBuf[0]),
};

GPRSMsg_t s_GPRSMsgBuf[10];
GPRSMsgQueue_t s_GPRSMsgQueue = 
{
    .pData = s_GPRSMsgBuf,
    .In = 0,
    .Out = 0,
    .Count = 0,
    .Size = sizeof(s_GPRSMsgBuf)/sizeof(s_GPRSMsgBuf[0]),
};

/**
 * @}
 */

/**
 * @defgroup      gprs_queue_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_queue_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_queue_Functions 
 * @brief         
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

