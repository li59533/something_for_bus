/**
 **************************************************************************************************
 * @file        zsproto.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _ZSPROTO_H_
#define _ZSPROTO_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    zsproto_Modules 
 * @{  
 */

/**
 * @defgroup      zsproto_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_Exported_Constants
 * @{  
 */
/************************* system define **************/
#define ZSPROTO_AHR_SIGN                'Z' // 0x5A, zsproto header
#define ZSPROTO_AFR_SIGN                'S' // 0x53, zsproto footer

#define ZSPROTO_BUFFER_SIZE_MAX         255

#define ZSPROTO_AHR_SIGN_OFFSET         0   
#define ZSPROTO_AHR_LENGTH_OFFSET       1    
#define ZSPROTO_APD_DATA_OFFSET         3

#define ZSPROTO_CONNTYPE_P2P            0
#define ZSPROTO_CONNTYPE_TCPIP          1
#define ZSPROTO_CONNTYPE_802            2
#define ZSPROTO_CONNTYPE_BLE            3
#define ZSPROTO_CONNTYPE_UART           4

#define ZSPROTO_FRAMETYPE_DATA          0
#define ZSPROTO_FRAMETYPE_ACK           1

#define ZSPROTO_MODEL_BROADCAST         0xFFFF
#define ZSPROTO_MODEL_NOTCASE           0x0000

#define ZSPROTO_ADDR_BROADCAST          0xFFFF
#define ZSPROTO_ADDR_NOTCARE            0x0000
/************************** user define *****************/
#define ZSPROTO_FLOWANALYSIS_ENABLE     1
#define ZSPROTO_FLOWCHANNEL_COUNT       1
#define ZSPROTO_FLOWCHANNEL_MAINTAIN    0

#define ZSPROTO_PACKETANALYSIS_ENABLE   0
#define ZSPROTO_PACKETCHANNEL_COUNT     1
/**
 * @}
 */

/**
 * @defgroup      zsproto_Exported_Types 
 * @{  
 */
#pragma pack(1)
typedef struct
{
    uint8_t Sign;
    uint16_t Length;
}ZSProtoAHR_t;

typedef struct
{
    uint8_t Sign;
}ZSProtoAFR_t;

typedef struct
{
    uint8_t Tag;
    uint8_t Len;
    union
    {
        uint8_t  Bit8;
        uint16_t Bit16;
        uint32_t Bit32;
        uint8_t  Array[100];
    }Value;
}ZSProtoTLV_t;

typedef struct
{
    uint8_t Buf[ZSPROTO_BUFFER_SIZE_MAX];
    uint16_t Length;
}ZSProtoPacket_t;

typedef struct
{
    ZSProtoPacket_t *pData;
    uint8_t In;
    uint8_t Out;
    uint8_t Size;
    uint8_t Count;
}ZSProtoPacketQueue_t;


/**
 * zsproto standard cmd define 
 */
typedef enum
{
    /* ����ConnType����ѭ�ı�׼���� */
	ZSCmd_NotSupport            = 0,    // ��֧�ֵ�����Ӧ��
	
	ZSCmd_StdGetCmdListReq      = 1,    // ��ȡ֧�ֵ������б�����
	ZSCmd_StdGetCmdListResp     = 2,    // ��ȡ֧�ֵ������б�Ӧ��
	
	
	ZSCmd_StdBeatNotify         = 10,   // ����
    
    ZSCmd_StdFWVersionGetReq    = 11,   // ��ȡ�汾������
    ZSCmd_StdFWVersionGetResp   = 12,   // ��ȡ�汾��Ӧ��
    
    ZSCmd_StdTimeSetReq         = 13,   // ʱ����������
    ZSCmd_StdTimeSetResp        = 14,   // ʱ������Ӧ��
    ZSCmd_StdTimeGetReq         = 15,   // ʱ���ȡ����
    ZSCmd_StdTimeGetResp        = 16,   // ʱ���ȡӦ��
    
    ZSCmd_StdDownloadNotify     = 20,	// ����֪ͨ
    ZSCmd_StdDownloadNameReq    = 21,   // �ļ�������
    ZSCmd_StdDownloadNameResp   = 22,   // �ļ���Ӧ��
    ZSCmd_StdDownloadInfoReq    = 23,	// �ļ���Ϣ����
    ZSCmd_StdDownloadInfoResp   = 24,	// �ļ���ϢӦ��
    ZSCmd_StdDownloadDataReq    = 25,	// �ļ���������
    ZSCmd_StdDownloadDataResp   = 26,	// �ļ�����Ӧ��
    
    /* ��ConnType������ѭ�ı�׼���� */
    ZSCmd_StdConnModelGetReq    = 50,    // ��ȡ�豸�Ĵ������ͺ��豸�ͺ�����
	ZSCmd_StdConnModelGetResp   = 51,    // ��ȡ�豸�Ĵ������ͺ��豸�ͺ�Ӧ��
	
    ZSCmd_StdConfigGetReq       = 60,	// ���û�ȡ����
    ZSCmd_StdConfigGetResp      = 61,	// ���û�ȡӦ��
    
    ZSCmd_StdConfigSetReq       = 62,	// ������������
    ZSCmd_StdConfigSetResp      = 63,	// �����豸Ӧ��
    
    ZSCmd_StdStatusReq          = 64,	// ״̬��ȡ����
    ZSCmd_StdStatusResp         = 65,	// ״̬��ȡӦ��
    
    ZSCmd_StdScanReq            = 70,	// ɨ������
    ZSCmd_StdScanResp           = 71,	// ɨ��Ӧ��
    
    ZSCmd_StdAssociateReq,	    = 72,   // ��������
    ZSCmd_StdAssociateResp      = 73,   // ����Ӧ�𣬴���->��������ʹ��
    
    ZSCmd_StdRegisterReq        = 74,	// ע�����󣬵���������
    ZSCmd_StdRegisterResp       = 75,	// ע��Ӧ��
}ZSCmd_e;

/**
 * zsproto standard cmdpayload define 
 */
typedef struct
{
    uint32_t UTCTicks;
}StdTimeSetReqPayload_t;

typedef struct
{
    uint8_t Result;
}StdTimeSetRespPayload_t;
#pragma pack()

#include "zsproto_p2p.h"
#include "zsproto_tcpip.h"
#include "zsproto_uart.h"
/**
 * @}
 */

/**
 * @defgroup      zsproto_Exported_Variables 
 * @{  
 */
extern uint32_t g_ZSProto_Seq;
extern ZSProtoPacket_t g_ZSProtoMakeCache;
/**
 * @}
 */

/**
 * @defgroup      zsproto_Exported_Functions 
 * @{  
 */
void ZSProto_FlowAnalysis(uint8_t channel,uint8_t *pBuf,uint8_t length);
void ZSProto_FlowSetCallback(uint8_t channel,void (*recv)(uint8_t *pBuf,uint16_t length));
uint8_t ZSProto_FlowGetCacheIdleLength(uint8_t channel);
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
