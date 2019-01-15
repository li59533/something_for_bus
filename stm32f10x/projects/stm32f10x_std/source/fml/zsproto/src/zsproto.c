/**
 **************************************************************************************************
 * @file        zsproto.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "zsproto.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    zsproto_Modules 
 * @{  
 */

/**
 * @defgroup      zsproto_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_Private_Types
 * @brief         
 * @{  
 */
typedef struct
{
    uint8_t buf[ZSPROTO_BUFFER_SIZE_MAX + 50];
    uint16_t index;
    void (*recv)(uint8_t *pBuf,uint16_t length);
}ZSProtoFlowCache_t;

#if ZSPROTO_PACKETANALYSIS_ENABLE == 1
typedef struct
{
    void (*recv)(uint8_t *pBuf,uint16_t length);
}ZSProtoPacketCache_t;
#endif
/**
 * @}
 */

/**
 * @defgroup      zsproto_Private_Variables 
 * @brief         
 * @{  
 */
static ZSProtoFlowCache_t s_ZSProtoFlowCacheList[ZSPROTO_FLOWCHANNEL_COUNT];

#if ZSPROTO_PACKETANALYSIS_ENABLE == 1
static ZSProtoPacketCache_t s_ZSProtoPacketCacheList[ZSPROTO_PACKETCHANNEL_COUNT] = 
{
    NULL,
};
#endif
/**
 * @}
 */

/**
 * @defgroup      zsproto_Public_Variables 
 * @brief         
 * @{  
 */
uint32_t g_ZSProto_Seq = 0;

ZSProtoPacket_t g_ZSProtoMakeCache;
/**
 * @}
 */

/**
 * @defgroup      zsproto_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_Functions 
 * @brief         
 * @{  
 */
#if ZSPROTO_PACKETANALYSIS_ENABLE == 1
void ZSProto_PacketSetCallback(uint8_t channel,void (*recv)(uint8_t *pBuf,uint16_t length))
{
    s_ZSProtoPacketCacheList[channel].recv = recv;
}
#endif

static uint16_t zsproto_flow_decode(uint8_t channel)
{
    uint16_t offset = 0;
    uint16_t remove_count = 0;
    uint16_t remain_len = s_ZSProtoFlowCacheList[channel].index;
    uint8_t *pBuf = s_ZSProtoFlowCacheList[channel].buf;

    while (remain_len >= sizeof(ZSProtoAHR_t) + sizeof(ZSProtoAFR_t))
    {
        if (pBuf[ZSPROTO_AHR_SIGN_OFFSET + offset] == ZSPROTO_AHR_SIGN)
        {
            uint16_t len = *(uint16_t*)(&pBuf[ZSPROTO_AHR_LENGTH_OFFSET + offset]);
            if (len <= ZSPROTO_BUFFER_SIZE_MAX)
            {
                if (remain_len >= len)
                {
                    if (pBuf[ZSPROTO_AHR_SIGN_OFFSET + offset + len - 1] == ZSPROTO_AFR_SIGN)
                    {
                        if (s_ZSProtoFlowCacheList[channel].recv != NULL)
                        {
                            s_ZSProtoFlowCacheList[channel].recv(&pBuf[ZSPROTO_AHR_SIGN_OFFSET+offset], len);
                        }
                        remain_len -= len;
                        remove_count += len;
                        offset += len;
                    }
                    else
                    {
                        offset++;
                        remain_len--;
                        remove_count++;
                    }
                }
                else
                {
                    break;
                }
            }
            else
            {
                offset++;
                remain_len--;
                remove_count++;
            }
        }
        else
        {
            offset++;
            remain_len--;
            remove_count++;
        }
    }

    if (offset != 0)
    {
        for (int i=0; i < remain_len; i++)
        {
            pBuf[i] = pBuf[offset+i];
        }
    }

    return remove_count;
}

void ZSProto_FlowAnalysis(uint8_t channel,uint8_t *pBuf,uint8_t length)
{
    uint16_t empty_count = 0,read_count = 0;

    if (length > 0)
    {
        empty_count = sizeof(s_ZSProtoFlowCacheList[channel].buf) - s_ZSProtoFlowCacheList[channel].index;

        if (length > empty_count)
        {
            read_count = empty_count;
        }
        else
        {
            read_count = length;
        }

        memcpy(&s_ZSProtoFlowCacheList[channel].buf[s_ZSProtoFlowCacheList[channel].index],pBuf,read_count);
        s_ZSProtoFlowCacheList[channel].index += read_count;
        s_ZSProtoFlowCacheList[channel].index -= zsproto_flow_decode(channel);
    }
}

void ZSProto_FlowSetCallback(uint8_t channel,void (*recv)(uint8_t *pBuf,uint16_t length))
{
    s_ZSProtoFlowCacheList[channel].recv = recv;
}

uint8_t ZSProto_FlowGetCacheIdleLength(uint8_t channel)
{
    return (sizeof(s_ZSProtoFlowCacheList[channel].buf) - s_ZSProtoFlowCacheList[channel].index);
}
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

