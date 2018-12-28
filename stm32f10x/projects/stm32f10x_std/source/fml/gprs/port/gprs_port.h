/**
 **************************************************************************************************
 * @file        gprs_port.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _GPRS_PORT_H_
#define _GPRS_PORT_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    gprs_port_Modules 
 * @{  
 */

/**
 * @defgroup      gprs_port_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_port_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_port_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_port_Exported_Variables 
 * @{  
 */
extern uint8_t test_gprs_dma[200];
/**
 * @}
 */

/**
 * @defgroup      gprs_port_Exported_Functions 
 * @{  
 */
void Gprs_Hal_Init(void);  //hal init include :pin,usartR_T,
void Gprs_CMD_Send(uint8_t *gprs_cmd_buf, uint8_t gprs_cmd_len);//cmd data sent func
void Gprs_Power_Pin_Set(void) ;  //module power control pin
void Gprs_Power_Pin_Rest(void) ; //module power control pin
void Gprs_DMA_IRQ(void);   //DMA_IRQ
void Gprs_Uart_IDLE_IRQ(void);
void Gprs_Task_uart_R_test(void);

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
