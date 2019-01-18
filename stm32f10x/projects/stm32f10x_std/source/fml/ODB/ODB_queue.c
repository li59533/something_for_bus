/**
 **************************************************************************************************
 * @file        ODB_queue.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "ODB_queue.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    ODB_queue_Modules 
 * @{  
 */

/**
 * @defgroup      ODB_queue_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ODB_queue_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ODB_queue_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ODB_queue_Private_Types
 * @brief         
 * @{  
 */
typedef struct
{
    uint8_t MsgBuf[8];
    uint8_t MsgBuf_Len;
}ODB_Msg_t;

typedef struct  
{
    MC20_Msg_t * Msgptr;
    uint8_t  In;
    uint8_t Out;
    uint8_t Size;
    uint8_t Count;
}ODB_Queue_MSG_t;
/**
 * @}
 */

/**
 * @defgroup      ODB_queue_Private_Variables 
 * @brief         
 * @{  
 */
ODB_Msg_t ODB_R[5];
ODB_Msg_t ODB_T[5];



ODB_Queue_MSG_t ODB_Queue_MSG_R;
/**
 * @}
 */

/**
 * @defgroup      ODB_queue_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ODB_queue_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ODB_queue_Functions 
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

