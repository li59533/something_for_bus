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
    uint8_t 	Header; // 帧头
    uint16_t 	Length; // 数据包总长度
    {
        uint16_t  FCF;	// 帧控制域
        uint8_t   Seq;	// 序列号
        uint16_t  Model;	// 发送方设备型号
        uint32_t  DeviceId;	// 发送方设备ID
        {
            uint8_t Cmd; // 命令类型
            uint8_t *CmdPayload; // 命令内容 
        }
    }
    uint8_t FCS; // 帧校验
    uint8_t Footer; // 帧尾
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
