/**
 **************************************************************************************************
 * @file        zsproto_tcpip.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _ZSPROTO_TCPIP_H_
#define _ZSPROTO_TCPIP_H_
#include "self_def.h"
#include "mc20_core_gps.h"
/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    zsproto_tcpip_Modules 
 * @{  
 */

/**
 * @defgroup      zsproto_tcpip_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_tcpip_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_tcpip_Exported_Types 
 * @{  
 */

typedef enum
{
    ZSCmd_StdConfigGetReq       = 60,	// ���û�ȡ����
    ZSCmd_StdConfigGetResp      = 61,	// ���û�ȡӦ��
    
    ZSCmd_StdConfigSetReq       = 62,	// ������������
    ZSCmd_StdConfigSetResp      = 63,	// �����豸Ӧ��
        
    ZSCmd_StdScanReq            = 70,	// ɨ������
    ZSCmd_StdScanResp           = 71,	// ɨ��Ӧ��
}ZSCmd_e;

#pragma pack(1)

typedef struct
{
    uint8_t 	Header; // ֡ͷ
    uint16_t 	Length; // ���ݰ��ܳ���
    
	uint16_t  FCF;	// ֡������
	uint8_t   Seq;	// ���к�
	uint16_t  Model;	// ���ͷ��豸�ͺ�
	uint32_t  DeviceId;	// ���ͷ��豸ID
	
	uint8_t  Cmd; // ��������
	//uint8_t *CmdPayload; // �������� 
    
    uint8_t FCS; // ֡У��
    uint8_t Footer; // ֡β
}ZSProto_t;
#pragma pack()


/**
 * zsproto cmd define 
 */

/**
 * zsproto p2p cmdpayload define
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_tcpip_Exported_Variables 
 * @{  
 */

/**
 * @}
 */
extern int8_t g_Zsproto_To_Server_Package[];
/**
 * @defgroup      zsproto_tcpip_Exported_Functions 
 * @{  
 */
void Zsproto_Make_Payload(GPS_GNSS_DATA_t * GPS_GNSS_DATA_buf,uint8_t * otherdata);

uint16_t Zsproto_Make_Package_To_Server(int8_t * pBuf,uint16_t len,uint32_t uniqueID);

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
