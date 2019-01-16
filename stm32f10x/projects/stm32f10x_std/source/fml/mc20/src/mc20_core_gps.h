/**
 **************************************************************************************************
 * @file        mc20_core_gps.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _MC20_CORE_GPS_H_
#define _MC20_CORE_GPS_H_
#include "self_def.h"
/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    mc20_core_gps_Modules 
 * @{  
 */

/**
 * @defgroup      mc20_core_gps_Exported_Macros 
 * @{  
 */
typedef struct
{
    char postion_status[2];
    char lattude_value[10];
    char lattude_hemisphere[2];
    char longitude_value[11];
    char longitude_hemisphere[2];
    char ground_rate[6];
    char ground_direction[6];

}GPS_GNSS_DATA_t;
/**
 * @}
 */

/**
 * @defgroup      mc20_core_gps_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_core_gps_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_core_gps_Exported_Variables 
 * @{  
 */
extern GPS_GNSS_DATA_t GPS_GNSS_DATA;
/**
 * @}
 */

/**
 * @defgroup      mc20_core_gps_Exported_Functions 
 * @{  
 */
void MC20_GPS_Start_Process(void);
void MC20_Core_Gps_RevStatus_To_Be(uint8_t rev_status);
void MC20_Gps_Status_To_Be(uint8_t gps_status);
int8_t MC20_Core_GPS_DATA_CheckSum_XOR(int8_t * checkbuf,uint8_t checklen); 
int8_t MC20_Core_Gps_GNSS_Data_Analysis(int8_t * gnss_data_buf);
uint8_t MC20_Gps_Status_Is(void);
void MC20_Gps_Flash_GNSS_Data(void);



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
