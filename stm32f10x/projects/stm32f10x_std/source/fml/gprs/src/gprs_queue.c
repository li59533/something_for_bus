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


/**
 * @}
 */

/**
 * @defgroup      gprs_queue_Public_Variables 
 * @brief         
 * @{  
 */
Gprs_AT_Queue_t g_Gprs_AT_Queue=
{
    .Count = 0,
    .In = 0,
    .Out = 0,
    .Size = 10,
};
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
void Gprs_AT_In_Queue(uint8_t gprs_AT_name)
{
    g_Gprs_AT_Queue.Name[g_Gprs_AT_Queue.In].AT_Name = gprs_AT_name;
    g_Gprs_AT_Queue.In ++;
    g_Gprs_AT_Queue.Count ++;
    g_Gprs_AT_Queue.In %= g_Gprs_AT_Queue.Size;
    g_Gprs_AT_Queue.Count %= g_Gprs_AT_Queue.Size;
}

uint8_t Gprs_AT_Out_Queue(void)
{
    uint8_t gprs_AT_out_name = 0;
    if (g_Gprs_AT_Queue.Count > 0)
    {
        gprs_AT_out_name = g_Gprs_AT_Queue.Name[g_Gprs_AT_Queue.Out].AT_Name;
        g_Gprs_AT_Queue.Out ++ ; 
        g_Gprs_AT_Queue.Count --;
    }
    g_Gprs_AT_Queue.Out %= g_Gprs_AT_Queue.Size ;
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

