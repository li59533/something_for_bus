/**
 **************************************************************************************************
 * @file        mc20_queue.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _MC20_QUEUE_H_
#define _MC20_QUEUE_H_
#include "self_def.h"
/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    mc20_queue_Modules 
 * @{  
 */

/**
 * @defgroup      mc20_queue_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_queue_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_queue_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_queue_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_queue_Exported_Functions 
 * @{  
 */
void MC20_ATcmd_In_to_Queue(uint8_t AT_id) ;
uint8_t MC20_ATcmd_Out_From_Queue(void);
uint8_t MC20_ATcmd_Queue_Get_Count(void);

void MC20_Msg_In_to_Queue(uint8_t *buf,uint16_t len);
void MC20_Msg_Out_From_Queue(uint8_t *buf,uint16_t *len);
uint8_t MC20_Msg_Queue_Get_Count(void);

void MC20_ATcmdMsg_In_to_Queue(uint8_t *buf,uint16_t len);
void MC20_ATcmdMsg_Out_From_Queue(uint8_t * rev_buf,uint8_t *len);
uint8_t MC20_ATcmdMsg_Queue_Get_Count(void);
void MC20_AT_Queue_Init(void);

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
