/**
 **************************************************************************************************
 * @file        system_param.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _SYSTEM_PARAM_H_
#define _SYSTEM_PARAM_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    system_param_Modules 
 * @{  
 */

/**
 * @defgroup      system_param_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Exported_Types 
 * @{  
 */
#pragma pack(1)
typedef struct
{
  

    uint16_t crc;           /*!< 所有的参数结构体必须按字节对齐。且最后一个必须包
                                 含一个uint16_t类型的数据，该数据用于内部存储时的
                                 crc校验和存储，用户在保存参数时不用关心该值数值。*/
}SystemParam_Config_t;
#pragma pack()
/**
 * @}
 */

/**
 * @defgroup      system_param_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Exported_Functions 
 * @{  
 */
int16_t SystemParam_Init(void);

int16_t SystemParam_Read(void);

void SystemParam_Save(void);

void SystemParam_Reset(void);

void SystemParam_Apply(void);

void SystemParam_Update(SystemParam_Config_t *config);
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
