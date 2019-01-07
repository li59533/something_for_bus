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
  
    uint8_t ip[4];
    uint16_t port;
    uint16_t crc;           /*!< ���еĲ����ṹ����밴�ֽڶ��롣�����һ�������
                                 ��һ��uint16_t���͵����ݣ������������ڲ��洢ʱ��
                                 crcУ��ʹ洢���û��ڱ������ʱ���ù��ĸ�ֵ��ֵ��*/
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
