/**
 **************************************************************************************************
 * @file        mc20_port.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _MC20_PORT_H_
#define _MC20_PORT_H_
#include "self_def.h"
/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    mc20_port_Modules 
 * @{  
 */

/**
 * @defgroup      mc20_port_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_port_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_port_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_port_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_port_Exported_Functions 
 * @{  
 */
void MC20_Hal_Init(void);
void MC20_DMA_IRQ(void);
void MC20_Uart_IDLE_IRQ(void);
void MC20_Power_Pin_Set(void);
void MC20_Power_Pin_Rest(void);
void MC20_CMD_Send(const char  * cmd_buf,uint8_t cmd_len);
void MC20_Data_Send(uint8_t * data_buf,uint16_t data_len);


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
