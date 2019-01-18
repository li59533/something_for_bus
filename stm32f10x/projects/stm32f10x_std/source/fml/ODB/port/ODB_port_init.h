/**
 **************************************************************************************************
 * @file        ODB_port_init.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _ODB_PORT_INIT_H_
#define _ODB_PORT_INIT_H_
#include "self_def.h"
/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    ODB_port_init_Modules 
 * @{  
 */

/**
 * @defgroup      ODB_port_init_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ODB_port_init_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ODB_port_init_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ODB_port_init_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ODB_port_init_Exported_Functions 
 * @{  
 */


void ODB_Hal_Init(void);
void ODB_Data_Send(uint8_t * buf);
void ODB_CAN1_RX0_IRQHandler(void);
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
