/**
 **************************************************************************************************
 * @file        ODB_Init.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _ODB_INIT_H_
#define _ODB_INIT_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    ODB_Init_Modules 
 * @{  
 */

/**
 * @defgroup      ODB_Init_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ODB_Init_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ODB_Init_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ODB_Init_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ODB_Init_Exported_Functions 
 * @{  
 */
void OBD_Init(void);
void OBD_Start_Get_Mileage(void);
void OBD_Start_Get_Speed(void);
uint16_t OBD_Get_Mileage(void);
uint16_t OBD_Get_Speed(void);
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
