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
void Zsproto_Make_Payload(GPS_GNSS_DATA_t * GPS_GNSS_DATA_buf,uint8_t * otherdata)
{
	int count = 0;
    sprintf((char *)g_Zsproto_To_Server_Package, "%s,%s,%s,%s", GPS_GNSS_DATA_buf->lattude_value,\
                GPS_GNSS_DATA_buf->lattude_hemisphere,\
                GPS_GNSS_DATA_buf->longitude_value,\
                GPS_GNSS_DATA_buf->longitude_hemisphere);
	count = strlen(g_Zsproto_To_Server_Package);
}

uint16_t Zsproto_Make_Package_To_Server(int8_t * pBuf,uint16_t len,uint32_t uniqueID)
{
	uint16_t i = 0;
	uint16_t len_temp = len;
    while (len_temp --)
    {
        *(pBuf + len_temp + 12) = *(pBuf + len_temp);
    }

    *(pBuf) = 0x5A; //header

    *(pBuf+1) = (len +15)>>8;            //len
    *(pBuf+2) = (len +15)&0x00ff;

    *(pBuf+3) = 0;//fcf
    *(pBuf+4) = 0;

    *(pBuf+5) = 0;//seq

    *(pBuf+6) = 0;//model 
    *(pBuf+7) = 0;

    *(pBuf+8) = (int8_t)(uniqueID >> 24);
    *(pBuf+9) = (int8_t)((uniqueID & 0x00ff0000) >> 16);
    *(pBuf+10) = (int8_t)((uniqueID & 0x0000ff00) >> 8);
    *(pBuf+11) = (int8_t)((uniqueID & 0x000000ff));

    *(pBuf+12) = 0;//Cmd


    for (i = 0;i < (len + 10);i++)
    {
        *(pBuf + len + 13) += *(pBuf+i+1);
    }
    *(pBuf + len + 14) = 0x53;

    return len + 15;
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

