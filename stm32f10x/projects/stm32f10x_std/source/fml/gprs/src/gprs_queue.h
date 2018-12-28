/**
 **************************************************************************************************
 * @file        gprs_queue.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _GPRS_QUEUE_H_
#define _GPRS_QUEUE_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    gprs_queue_Modules 
 * @{  
 */
#define GPRS_BUFFER_SIZE_MAX    500
/**
 * @defgroup      gprs_queue_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_queue_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_queue_Exported_Types 
 * @{  
 */

typedef enum
{
    GPRSMsgType_NULL,
    GPRSMsgType_SendData,
    GPRSMsgType_GetCSQ,
    GPRSMsgType_GetQISACK,
    GPRSMsgType_InitCmd,
    GPRSMsgType_ConnectCmd,
    GPRSMsgType_CloseCmd,
}GPRSMsgType_e;

typedef struct
{
    uint8_t NextReq;
}
GPRSMsgInitCmd_t;

typedef struct
{
    uint8_t SocketIndex;
}
GPRSMsgConnectCmd_t;

typedef struct
{
    uint8_t SocketIndex;
}
GPRSMsgCloseCmd_t;

typedef struct
{
    uint8_t SocketIndex;
}
GPRSMsgQISACK_t;

typedef struct
{
    GPRSMsgType_e Type;
    union
    {
        GPRSMsgInitCmd_t    InitCmd;
        GPRSMsgConnectCmd_t ConnectCmd;
        GPRSMsgCloseCmd_t   CloseCmd;
        GPRSMsgQISACK_t     QISACKCmd;
    };
}GPRSMsg_t;

typedef struct
{
    uint8_t Buf[GPRS_BUFFER_SIZE_MAX];
    uint16_t Length;
    uint8_t  Sn;
}GPRSPacket_t;

typedef struct
{
    GPRSPacket_t *pData;
    uint8_t In;
    uint8_t Out;
    uint8_t Size;
    uint8_t Count;
}GPRSPacketQueue_t;

//--------------------------

typedef struct
{
    uint8_t AT_Name;
}Gprs_AT_Name_t;

typedef struct
{
    Gprs_AT_Name_t Name[10];
    uint8_t In;
    uint8_t Out;
    uint8_t Size;
    uint8_t Count;
}Gprs_AT_Queue_t;
/**
 * @}
 */

/**
 * @defgroup      gprs_queue_Exported_Variables 
 * @{  
 */

/**
 * @}
 */
extern Gprs_AT_Queue_t g_Gprs_AT_Queue;
/**
 * @defgroup      gprs_queue_Exported_Functions 
 * @{  
 */
void Gprs_AT_In_Queue(uint8_t gprs_AT_name);
uint8_t Gprs_AT_Out_Queue(void);
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
