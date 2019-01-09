/**
 **************************************************************************************************
 * @file        mc20_queue.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "mc20_queue.h"
#include "clog.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    mc20_queue_Modules 
 * @{  
 */

/**
 * @defgroup      mc20_queue_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_queue_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_queue_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_queue_Private_Types
 * @brief         
 * @{  
 */
typedef struct
{
    uint8_t cmd_id;
}MC20_Core_Task_t;

typedef struct
{
    MC20_Core_Task_t Core_task[20];
    uint8_t In;
    uint8_t Out;
    uint8_t Size;
    uint8_t Count;
}MC20_Queue_Core_t;


typedef struct
{
    uint8_t MsgBuf[400];
    uint16_t MsgBuf_Len;
}MC20_Msg_t;

typedef struct
{
    uint8_t ATcmdMsgBuf[20];
    uint8_t ATcmdMsgBuf_Len;
}MC20_ATcmdMsg_t;

typedef struct  
{
    MC20_Msg_t * Msgptr;
    uint8_t  In;
    uint8_t Out;
    uint8_t Size;
    uint8_t Count;
}MC20_Queue_MSG_t;

typedef struct  
{
    MC20_ATcmdMsg_t * ATcmdMsgptr;
    uint8_t  In;
    uint8_t Out;
    uint8_t Size;
    uint8_t Count;
}MC20_Queue_ATcmdMSG_t;

/**
 * @}
 */

/**
 * @defgroup      mc20_queue_Private_Variables 
 * @brief         
 * @{  
 */
MC20_Msg_t Rev[3];
MC20_Msg_t Send[3];
MC20_ATcmdMsg_t AT_Rev[3];

MC20_Queue_MSG_t MC20_Queue_Msg=
{
    .Msgptr = Rev,
    .Count = 0,
    .In = 0,
    .Out = 0,
    .Size = (sizeof(Rev)/sizeof(Rev[0])),

};

MC20_Queue_ATcmdMSG_t MC20_Queue_ATcmdMsg=
{
    .ATcmdMsgptr = AT_Rev,
    .Count = 0,
    .In = 0,
    .Out = 0,
    .Size = (sizeof(AT_Rev)/sizeof(AT_Rev[0])),

};

MC20_Queue_Core_t MC20_Queue_Core=
{
    .Count=0,
    .In = 0,
    .Out = 0,
    .Size = 10,
};
/**
 * @}
 */

/**
 * @defgroup      mc20_queue_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_queue_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_queue_Functions 
 * @brief         
 * @{  
 */





void MC20_ATcmd_In_to_Queue(uint8_t AT_id) 
{
    MC20_Queue_Core.Core_task[MC20_Queue_Core.In].cmd_id = AT_id;
    MC20_Queue_Core.In ++;
    MC20_Queue_Core.Count++;

    MC20_Queue_Core.In %= MC20_Queue_Core.Size;
    MC20_Queue_Core.Count %= MC20_Queue_Core.Size;
}
uint8_t MC20_ATcmd_Out_From_Queue(void)
{
    uint8_t AT_id = 0;
    if (MC20_Queue_Core.Count > 0)
    {
        AT_id = MC20_Queue_Core.Core_task[MC20_Queue_Core.Out].cmd_id;
        MC20_Queue_Core.Out ++;
        MC20_Queue_Core.Count --;

        MC20_Queue_Core.Out %= MC20_Queue_Core.Size;
    }
    return AT_id;
}
uint8_t MC20_ATcmd_Queue_Get_Count(void)
{
    return MC20_Queue_Core.Count;
}

//-----------------------------------------------------------------------


void MC20_Msg_In_to_Queue(uint8_t *buf,uint16_t len)
{
    memcpy(MC20_Queue_Msg.Msgptr[MC20_Queue_Msg.In].MsgBuf, buf, len);
    MC20_Queue_Msg.Msgptr[MC20_Queue_Msg.In].MsgBuf_Len = len;
    MC20_Queue_Msg.In ++;
    MC20_Queue_Msg.Count ++;
    MC20_Queue_Msg.In %= MC20_Queue_Msg.Size;
    MC20_Queue_Msg.Count %= MC20_Queue_Msg.Size;

}
void MC20_Msg_Out_From_Queue(uint8_t *buf,uint16_t *len)
{
    if (MC20_Queue_Msg.Count > 0)
    {
        memcpy(buf, MC20_Queue_Msg.Msgptr[MC20_Queue_Msg.Out].MsgBuf, MC20_Queue_Msg.Msgptr[MC20_Queue_Msg.Out].MsgBuf_Len);
        *len =  MC20_Queue_Msg.Msgptr[MC20_Queue_Msg.Out].MsgBuf_Len;
        MC20_Queue_Msg.Count -- ;
        MC20_Queue_Msg.Out ++;
        MC20_Queue_Msg.Out %= MC20_Queue_Msg.Size;
    }
}
uint8_t MC20_Msg_Queue_Get_Count(void)
{
    return MC20_Queue_Msg.Count;
}
//-----------------------------------------------------------------------
void MC20_ATcmdMsg_In_to_Queue(uint8_t *buf,uint16_t len)
{
    memcpy(MC20_Queue_ATcmdMsg.ATcmdMsgptr[MC20_Queue_ATcmdMsg.In].ATcmdMsgBuf, buf, len);
    MC20_Queue_ATcmdMsg.ATcmdMsgptr[MC20_Queue_ATcmdMsg.In].ATcmdMsgBuf_Len = len;

    MC20_Queue_ATcmdMsg.In ++;
    MC20_Queue_ATcmdMsg.Count ++;
    MC20_Queue_ATcmdMsg.In %= MC20_Queue_ATcmdMsg.Size;
    MC20_Queue_ATcmdMsg.Count %= MC20_Queue_ATcmdMsg.Size;
}
void MC20_ATcmdMsg_Out_From_Queue(uint8_t * rev_buf,uint8_t *len)
{
    if (MC20_Queue_ATcmdMsg.Count > 0)
    {
        memcpy(rev_buf,MC20_Queue_ATcmdMsg.ATcmdMsgptr[MC20_Queue_ATcmdMsg.Out].ATcmdMsgBuf,MC20_Queue_ATcmdMsg.ATcmdMsgptr[MC20_Queue_ATcmdMsg.Out].ATcmdMsgBuf_Len);        
        *len = MC20_Queue_ATcmdMsg.ATcmdMsgptr[MC20_Queue_ATcmdMsg.Out].ATcmdMsgBuf_Len;
        MC20_Queue_ATcmdMsg.Count --;
        MC20_Queue_ATcmdMsg.Out ++;
        MC20_Queue_ATcmdMsg.Out %= MC20_Queue_ATcmdMsg.Size;
    }
}
uint8_t MC20_ATcmdMsg_Queue_Get_Count(void)
{
    return MC20_Queue_ATcmdMsg.Count;
}

void MC20_AT_Queue_Init(void)
{
    MC20_Queue_ATcmdMsg.Count = 0;
    MC20_Queue_ATcmdMsg.In = 0;
    MC20_Queue_ATcmdMsg.Out = 0;
	MC20_Queue_Core.Count = 0;
	MC20_Queue_Core.In = 0;
	MC20_Queue_Core.Out = 0;
	
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

