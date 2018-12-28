/**
 **************************************************************************************************
 * @file        gprs_mc20.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "gprs_mc20.h"
#include "gprs_port.h"
#include "gprs_parameter.h"
#include "gprs_queue.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    gprs_mc20_Modules 
 * @{  
 */

/**
 * @defgroup      gprs_mc20_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_mc20_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_mc20_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_mc20_Private_Types
 * @brief         
 * @{  
 */
typedef struct
{
    uint8_t Connect_status;
    uint8_t idel_status;
    uint8_t n;
}Gprs_Process_Status_t;
/**
 * @}
 */

/**
 * @defgroup      gprs_mc20_Private_Variables 
 * @brief         
 * @{  
 */
Gprs_Process_Status_t Gprs_Process_Status=
{
    .Connect_status = 0,
    .idel_status = 0,
}
/**
 * @}
 */

/**
 * @defgroup      gprs_mc20_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      gprs_mc20_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void gprs_mdule_status_init(void);
/**
 * @}
 */

/**
 * @defgroup      gprs_mc20_Functions 
 * @brief         
 * @{  
 */
void Gprs_Module_Init(void)
{
    Gprs_Hal_Init();
    gprs_mdule_status_init();
    
}


static void gprs_mdule_status_init(void)
{
    Gprs_Module_Status = Gprs_Power_On_Req;
}

void Gprs_Module_PowerOff(void)
{

}

void Gprs_Rev_Loop_Process(void)  //call this func in 10ms
{

}





int8_t Gprs_Power_Status(void)   //return module power status
{
    return g_Gprs_Power_Status;
}


void Gprs_Power_Power_On_Process(void)
{

}



void Gprs_Connect_Process(void)
{
    switch (Gprs_Process_Status.Connect_status)
    {
        case Gprs_Connect_AT_Req:
            Gprs_AT_In_Queue(Gprs_CMD_AT);
            break;
        case Gprs_Connect_AT_Resp:
            if ()
            {
                status = ;
            }

    }
}

void Gprs_Idel_Loop_Process(void)
{
    outqueue>0

    switch (Gprs_Process_Status.idel_status)
    {
        case Gprs_idel_AT_Req:
            Gprs_CMD_Send(GPRS_CMD_AT, sizeof(GPRS_CMD_AT));

        case Gprs_idel_AT_Resp:
             
    }
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

