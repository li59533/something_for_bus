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
    ZSCmd_StdConfigGetReq       = 60,	// 配置获取请求
    ZSCmd_StdConfigGetResp      = 61,	// 配置获取应答
    
    ZSCmd_StdConfigSetReq       = 62,	// 配置设置请求
    ZSCmd_StdConfigSetResp      = 63,	// 配置设备应答
        
    ZSCmd_StdScanReq            = 70,	// 扫描请求
    ZSCmd_StdScanResp           = 71,	// 扫描应答
}ZSCmd_e;

#pragma pack(1)

typedef struct
{
    uint8_t 	Header; // 帧头
    uint16_t 	Length; // 数据包总长度
    
	uint16_t  FCF;	// 帧控制域
	uint8_t   Seq;	// 序列号
	uint16_t  Model;	// 发送方设备型号
	uint32_t  DeviceId;	// 发送方设备ID
	
	uint8_t  Cmd; // 命令类型
	//uint8_t *CmdPayload; // 命令内容 
    
    uint8_t FCS; // 帧校验
    uint8_t Footer; // 帧尾
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
