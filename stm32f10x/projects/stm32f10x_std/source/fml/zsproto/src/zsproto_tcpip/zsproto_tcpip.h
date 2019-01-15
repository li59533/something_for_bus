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
    union
    {
        struct
        {
            uint8_t AckReq:1;
            uint8_t Sec:1;
            uint8_t Pending:1;
            uint8_t Trans:1;
            uint8_t reserve1:2;
            uint8_t FrameType:2;
            uint8_t reserve2:3;
            uint8_t Gateway:1;
            uint8_t ConnType:4;
        }bitfield;
        uint8_t Value;
    }FCF;
    uint8_t  Seq;
    uint16_t Model;
    uint32_t DeviceId;
    uint8_t  Cmd;
    uint8_t* CmdPayload;
}ZSProtoAPDU_TCPIP_t; // app protocol data unit
#pragma pack()

typedef struct
{
    uint8_t 	Header; // ֡ͷ
    uint16_t 	Length; // ���ݰ��ܳ���
    {
        uint16_t  FCF;	// ֡������
        uint8_t   Seq;	// ���к�
        uint16_t  Model;	// ���ͷ��豸�ͺ�
        uint32_t  DeviceId;	// ���ͷ��豸ID
        {
            uint8_t Cmd; // ��������
            uint8_t *CmdPayload; // �������� 
        }
    }
    uint8_t FCS; // ֡У��
    uint8_t Footer; // ֡β
}ZSProto_t;
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

/**
 * @defgroup      zsproto_tcpip_Exported_Functions 
 * @{  
 */

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
