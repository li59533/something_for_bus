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
