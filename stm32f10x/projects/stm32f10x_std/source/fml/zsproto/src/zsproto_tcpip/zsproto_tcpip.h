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
#define PROTO_OFFECT_HEADER     0
#define PROTO_OFFECT_LENGTH     1
#define PROTO_OFFECT_FCF        3
#define PROTO_OFFECT_SEQ        5
#define PROTO_OFFECT_MODEL      6
#define PROTO_OFFECT_DEVICE_ID  8
#define PROTO_OFFECT_CMD       12
#define PROTO_OFFECT_PAYLOAD       13
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

typedef struct
{
	unsigned char target;
	unsigned char length;
	char value[20];
}Zsproto_payload_TLV_t;

typedef struct
{
	unsigned char count;
	Zsproto_payload_TLV_t Zsproto_TLV[10];
}Zsproto_payload_t;




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
extern Zsproto_payload_t Zsproto_payload;
/**
 * @defgroup      zsproto_tcpip_Exported_Functions 
 * @{  
 */
void Zsproto_Add_To_TLV(uint8_t target,uint8_t length,char * value);
int8_t * Zsproto_Make_Package_To_Server( uint32_t uniqueID,Zsproto_payload_t * Zsproto_payload,int8_t * package,uint16_t *package_len);
int8_t Zsproto_Data_Check(uint8_t * buf,uint16_t len);
void Zsproto_Data_Analysis(uint8_t *package,uint16_t package_len);




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
