# User Manual
--------
## 1 上传服务器

通讯协议基于**《ZS私有通讯协议》**
### 1.1 协议格式
```
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
    uint8_t FCS; // 帧校验15
    uint8_t Footer; // 帧尾
}ZSProto_t;
```
**Header:**0x5A
**Length:**Length字段表示数据包总长度，从Header字段到Footer字段
**FCF:**	默认0
**Seq:**	默认0
**Model:**	默认0
**DeviceID:**32bit
**Cmd:**
**Cmdpayload:**
**FCS:**	校验位，采用和校验方式，检验范围为`FCF`到`CmdPayload` 。
**Footer:**0x53

### 1.2 Payload字段
结构体格式采用TLV形式： 
**"T":**target
**"L":**length
**"V":**value

```
typedef struct
{
	unsigned char target;
	unsigned char length;
	char value[25];
}Zsproto_payload_TLV_t;

typedef struct
{
	unsigned char count;
	Zsproto_payload_TLV_t Zsproto_TLV[5];
}Zsproto_payload_t;
```

**T:**
|关键字|说明|
|---|---|
|01|纬度|
|02|纬度半球|
|03|经度|
|04|经度半球|
|05|里程|
|||
|||
|||





#### 1.1.1 设备扫描
```
请求：
Cmd:ZSCmd_StdScanReq
CmdPayload:
typedef struct
{
    uint16_t TargetModel; 	
    uint32_t TargetDeviceId;
}StdScanReqPayload_t;

应答：
Cmd:ZSCmd_StdScanResp
CmdPayload:
typedef struct
{
    uint16_t Model; 	
    uint32_t DeviceId;
}StdScanRespPayload_t;
```
#### 1.1.2 获取设备配置
```
请求：
Cmd:ZSCmd_StdConfigGetReq
CmdPayload:无该字段

应答：
Cmd:ZSCmd_StdConfigGetResp
CmdPayload:
typedef struct
{
    NULL; // 配置获取请求Payload为空 
}StdConfigGetRespPayload_t;
```
#### 1.1.3 设置设备配置
```
请求：
Cmd:ZSCmd_StdConfigSetReq
CmdPayload:
typedef struct
{
    uint8_t     TLVCount;
    TLVUnit_t   TLV[TLVCount];
}StdConfigSetReqPayload_t;
    
应答：
Cmd:ZSCmd_StdConfigSetResp
CmdPayload:
typedef struct
{
    uint8_t     Result;
    uint8_t     TLVCount;
    TLCUnit_t   TLV[TLVCount];
}StdConfigSetRespPayload_t;
```

## 1.2 Cmd规范
	zsproto命令分标准命令、自定义命令和保留命令。标准命令从0~0x7F（0~127），自定义命令从0x80~0xCF（128~207），保留命令从0xD0到0xFE（208~255）。
**支持命令**
```
typedef enum
{
    /* 所有ConnType均遵循的标准命令 */
	ZSCmd_NotSupport            = 0,    // 不支持的命令应答
	
    ZSCmd_StdConfigGetReq       = 60,	// 配置获取请求
    ZSCmd_StdConfigGetResp      = 61,	// 配置获取应答
    
    ZSCmd_StdConfigSetReq       = 62,	// 配置设置请求
    ZSCmd_StdConfigSetResp      = 63,	// 配置设备应答
        
    ZSCmd_StdScanReq            = 70,	// 扫描请求
    ZSCmd_StdScanResp           = 71,	// 扫描应答
    
}ZSCmd_e;
```

