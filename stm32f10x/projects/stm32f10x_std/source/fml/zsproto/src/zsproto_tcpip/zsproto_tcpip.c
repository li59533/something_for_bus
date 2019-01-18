/**
 **************************************************************************************************
 * @file        zsproto_tcpip.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "zsproto_tcpip.h"
#include "string.h"
#include "mc20_parameter.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    zsproto_tcpip_Modules 
 * @{  
 */

/**
 * @defgroup      zsproto_tcpip_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_tcpip_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_tcpip_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_tcpip_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_tcpip_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_tcpip_Public_Variables 
 * @brief         
 * @{  
 */

Zsproto_payload_t Zsproto_payload = 
{
    .count = 0,
};
int8_t g_Zsproto_To_Server_Package[100]={0};

/**
 * @}
 */

/**
 * @defgroup      zsproto_tcpip_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      zsproto_tcpip_Functions 
 * @brief         
 * @{  
 */
void Zsproto_Add_To_TLV(uint8_t target,uint8_t length,char * value)
{
    
    Zsproto_payload.Zsproto_TLV[Zsproto_payload.count].target = target;
    Zsproto_payload.Zsproto_TLV[Zsproto_payload.count].length = length;
    memcpy(Zsproto_payload.Zsproto_TLV[Zsproto_payload.count].value,value,length);
	Zsproto_payload.count ++;
}
int8_t * Zsproto_Make_Package_To_Server( uint32_t uniqueID,Zsproto_payload_t * Zsproto_payload,int8_t * package,uint16_t *package_len)
{
	uint8_t  i = 0;
	uint8_t  j = 0;
    int8_t * ptr = package;
    *(ptr + PROTO_OFFECT_HEADER)    = 0X5A;
    *(ptr + PROTO_OFFECT_FCF)       = 0;
    *(ptr + PROTO_OFFECT_SEQ)       = 0;
    *(ptr + PROTO_OFFECT_MODEL)     = 0;
    *(uint32_t *)(ptr + PROTO_OFFECT_DEVICE_ID) = uniqueID;
    *(ptr + PROTO_OFFECT_CMD)       = 0;
    ptr += PROTO_OFFECT_PAYLOAD;
	while (Zsproto_payload->count--)
	{
        *(ptr + i) = Zsproto_payload->Zsproto_TLV[j].target;
        *(ptr + i + 1) = Zsproto_payload->Zsproto_TLV[j].length;
		memcpy(ptr + i + 2, Zsproto_payload->Zsproto_TLV[j].value, Zsproto_payload->Zsproto_TLV[j].length);
		i = i + 2 + Zsproto_payload->Zsproto_TLV[j].length ;
		j ++;
	}
    ptr = package;
	
    *(ptr + PROTO_OFFECT_LENGTH) = (uint8_t)((i + 15) >> 8);
	*(ptr + 1 + PROTO_OFFECT_LENGTH) = (uint8_t)((i + 15) & 0x00ff);
	
    *package_len = i + 15;

    for (i = 0;i <*package_len;i++)
    {
        *(ptr + *package_len - 2) += *(ptr+PROTO_OFFECT_FCF+i+1);
    }
    *(ptr + *package_len - 1) = 0x53;

    if (Zsproto_payload->count > 5)
    {
        Zsproto_payload->count = 0;
    }
    return package;
}

void Zsproto_Data_Analysis(uint8_t *package,uint16_t package_len)
{
    uint8_t * ptr = package + PROTO_OFFECT_CMD;
    uint8_t next = 0;
    if (*(package + package_len - 1) == 'S')
    {
        if (Zsproto_Data_Check(package, package_len) == 1)
        {
            switch (*(ptr))
            {
                case ZSCmd_StdScanReq:break;
                case ZSCmd_StdConfigGetReq:break;
                case ZSCmd_StdConfigSetReq:
                {
                    while ((*(ptr + 1)) -- )
                    {
                        switch (*(ptr + 2 + next))
                        {
                            case 20:    
                            {
                                g_MC20Parameter_Config.ip[0] = *(ptr + 2 + next + 2);
                                g_MC20Parameter_Config.ip[1] = *(ptr + 2 + next + 3);
                                g_MC20Parameter_Config.ip[2] = *(ptr + 2 + next + 4);
                                g_MC20Parameter_Config.ip[3] = *(ptr + 2 + next + 5);                             
                                break;
                            }
                            case 21:
                            {
                                g_MC20Parameter_Config.port = *(ptr + 2 + next + 2);
                                break;
                            }
                            default:    break;
                        }

                        next += *(ptr + 2 + next + 1);
                    }
                    break;
                }
                default:break;
            }
        }

    }
    
}

int8_t Zsproto_Data_Check(uint8_t * buf,uint16_t len)
{
    uint8_t * ptr = buf;
    uint16_t buf_len = 0;
    uint16_t i = 0;
    uint8_t sum_check = 0;

    buf_len = *(ptr + 1) * 16 + *(ptr + 2);

    if (buf_len != len)
    {
        return -1;
    }
    ptr += PROTO_OFFECT_FCF;
    for (i = 0;i < (len - 5);i ++)
    {
        sum_check += *(ptr + i);
    }
    ptr = buf;
    if (sum_check != *(ptr + len - 2))
    {
        return -1;
    }
    return 1;
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

