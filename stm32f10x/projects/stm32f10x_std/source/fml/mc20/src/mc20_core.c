/**
 **************************************************************************************************
 * @file        mc20_core.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "mc20_core.h"
#include "mc20_queue.h"
#include "mc20_ATcmd.h"
#include "osal_clock.h"
#include "mc20_app.h"
#include "mc20_task.h"
#include "mc20_port.h"
#include "string.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    mc20_core_Modules 
 * @{  
 */

/**
 * @defgroup      mc20_core_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_core_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_core_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_core_Private_Types
 * @brief         
 * @{  
 */
typedef enum
{
    Rev_Wait=1,
    Rev_Pass,
    Rev_Timeout,
    Rev_Error,
}Core_Rev_Status_enum;

/**
 * @}
 */

/**
 * @defgroup      mc20_core_Private_Variables 
 * @brief         
 * @{  
 */
MC20_Status_t MC20_Status;
/**
 * @}
 */

/**
 * @defgroup      mc20_core_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_core_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void mc20_core_status_to_be(uint8_t core_status);
static void mc20_gprs_rev_status_to_be(uint8_t rev_status);
static void mc20_gprs_status_to_be(uint8_t gprs_status);
/**
 * @}
 */

/**
 * @defgroup      mc20_core_Functions 
 * @brief         
 * @{  
 */
void MC20_Init(void)
{
    MC20_Hal_Init();
}
void MC20_Core_Rev_Loop_Process(void)
{
    MC20_Status.GPRS_Status_Machine.status_Rev =1 ;

    MC20Task_Send_Event(MC20_TASK_GPRS_EVENT);

    MC20_Status.GPS_Status_Machine.status_Rev =1 ;
    MC20Task_Send_Event(MC20_TASK_GPS_EVENT);
}

void MC20_Core_Run_Process(void)
{
    static uint32_t atcmd_time_record = 0;
    uint8_t * rev_buf_temp;
    if (MC20_Status.CORE_Status_Machine.status_machine == MC20_IDLE)
    {
        if (MC20_ATcmd_Queue_Get_Count() > 0)
        {
            MC20_Status.CORE_Status_Machine.status_machine = MC20_ATcmd_Out_From_Queue();
        }
    }

    switch (MC20_Status.CORE_Status_Machine.status_machine)
    {
        case MC20_IDLE:
        {

            break;
        }
        case MC20_CMD_AT:
        {
            MC20_CMD_Send(MC20_CMD_AT_BUF,strlen(MC20_CMD_AT_BUF));            
            mc20_core_status_to_be(MC20_CMD_AT_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            break;
        }
        case MC20_CMD_AT_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                rev_buf_temp = MC20_ATcmdMsg_Out_From_Queue(0);
                if (strstr((char*)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
            }
            
            break;
        }
        case MC20_CMD_ATE:
        {
            MC20_CMD_Send(MC20_CMD_ATE_BUF,strlen(MC20_CMD_ATE_BUF));            
            mc20_core_status_to_be(MC20_CMD_ATE_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            break;
        }
        case MC20_CMD_ATE_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                rev_buf_temp = MC20_ATcmdMsg_Out_From_Queue(0);
                if (strstr((char*)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
            }
            
            break;
        }
        case MC20_CMD_IPR:
        {
            MC20_CMD_Send(MC20_CMD_IPR_BUF,strlen(MC20_CMD_IPR_BUF));            
            mc20_core_status_to_be(MC20_CMD_IPR_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            break;
        }
        case MC20_CMD_IPR_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                rev_buf_temp = MC20_ATcmdMsg_Out_From_Queue(0);
                if (strstr((char*)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
            }
    
            break;
        }
        case MC20_CMD_CPIN:
        {
            MC20_CMD_Send(MC20_CMD_CPIN_BUF,strlen(MC20_CMD_CPIN_BUF));            
            mc20_core_status_to_be(MC20_CMD_IPR_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            break;
        }
        case MC20_CMD_CPIN_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                rev_buf_temp = MC20_ATcmdMsg_Out_From_Queue(0);
                if (strstr((char*)rev_buf_temp,"+CPIN: READY") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_3000MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
            }
          
            break;
        }
        case MC20_CMD_CSQ:
        {
            MC20_CMD_Send(MC20_CMD_CSQ_BUF,strlen(MC20_CMD_CSQ_BUF));            
            mc20_core_status_to_be(MC20_CMD_CSQ_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            break;
        }
        case MC20_CMD_CSQ_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                rev_buf_temp = MC20_ATcmdMsg_Out_From_Queue(0);
                if (strstr((char *)rev_buf_temp,"+CSQ") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
            }
           
            break;
        }
        case MC20_CMD_CREG:
        {
            MC20_CMD_Send(MC20_CMD_CREG_BUF,strlen(MC20_CMD_CREG_BUF));            
            mc20_core_status_to_be(MC20_CMD_CREG_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            break;
        }
        case MC20_CMD_CREG_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                rev_buf_temp = MC20_ATcmdMsg_Out_From_Queue(0);
                if (strstr((char *)rev_buf_temp,"+CREG: 0,1") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
            }
           
            break;
        }
        case MC20_CMD_CGREG:
        {
            MC20_CMD_Send(MC20_CMD_CGREG_BUF,strlen(MC20_CMD_CGREG_BUF));            
            mc20_core_status_to_be(MC20_CMD_CGREG_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            break;
        }
        case MC20_CMD_CGREG_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                rev_buf_temp = MC20_ATcmdMsg_Out_From_Queue(0);
                if (strstr((char *)rev_buf_temp,"+CGREG: 0,1") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
            }
            
            break;
        }
        case MC20_CMD_QIFGCNT:
        {
            MC20_CMD_Send(MC20_CMD_QIFGCNT_BUF,strlen(MC20_CMD_QIFGCNT_BUF));            
            mc20_core_status_to_be(MC20_CMD_QIFGCNT_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            break;
        }
        case MC20_CMD_QIFGCNT_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                rev_buf_temp = MC20_ATcmdMsg_Out_From_Queue(0);
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
            }
           
            break;
        }
        case MC20_CMD_QICSGP:
        {
            MC20_CMD_Send(MC20_CMD_QICSGP_BUF,strlen(MC20_CMD_QICSGP_BUF));            
            mc20_core_status_to_be(MC20_CMD_QICSGP_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            break;
        }
        case MC20_CMD_QICSGP_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                rev_buf_temp = MC20_ATcmdMsg_Out_From_Queue(0);
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
            }
            
            break;
        }
        case MC20_CMD_QIDEACT:
        {
            MC20_CMD_Send(MC20_CMD_QIDEACT_BUF,strlen(MC20_CMD_QIDEACT_BUF));            
            mc20_core_status_to_be(MC20_CMD_QIDEACT_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            break;
        }
        case MC20_CMD_QIDEACT_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                rev_buf_temp = MC20_ATcmdMsg_Out_From_Queue(0);
                if (strstr((char *)rev_buf_temp,"DEACT OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_40000MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
            }
            
            break;
        }
        case MC20_CMD_QIMODE:
        {
            MC20_CMD_Send(MC20_CMD_QIMODE_BUF,strlen(MC20_CMD_QIMODE_BUF));            
            mc20_core_status_to_be(MC20_CMD_QIMODE_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            break;
        }
        case MC20_CMD_QIMODE_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                rev_buf_temp = MC20_ATcmdMsg_Out_From_Queue(0);
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
            }
            
            break;
        }
        case MC20_CMD_QIMUX:
        {
            MC20_CMD_Send(MC20_CMD_QIMUX_BUF,strlen(MC20_CMD_QIMUX_BUF));            
            mc20_core_status_to_be(MC20_CMD_QIMUX_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            break;
        }
        case MC20_CMD_QIMUX_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                rev_buf_temp = MC20_ATcmdMsg_Out_From_Queue(0);
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
            }
            
            break;
        }
        case MC20_CMD_QIREGAPP:
        {
            MC20_CMD_Send(MC20_CMD_QIREGAPP_BUF,strlen(MC20_CMD_QIREGAPP_BUF));            
            mc20_core_status_to_be(MC20_CMD_QIREGAPP_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            break;
        }
        case MC20_CMD_QIREGAPP_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                rev_buf_temp = MC20_ATcmdMsg_Out_From_Queue(0);
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
            }
            
            break;
        }
        case MC20_CMD_QIACT:
        {
            MC20_CMD_Send(MC20_CMD_QIACT_BUF,strlen(MC20_CMD_QIACT_BUF));            
            mc20_core_status_to_be(MC20_CMD_QIACT_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            break;
        }
        case MC20_CMD_QIACT_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                rev_buf_temp = MC20_ATcmdMsg_Out_From_Queue(0);
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_60000MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
            }
            
            break;
        }
        case MC20_CMD_QILOCIP:
        {
            MC20_CMD_Send(MC20_CMD_QILOCIP_BUF,strlen(MC20_CMD_QILOCIP_BUF));            
            mc20_core_status_to_be(MC20_CMD_QILOCIP_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            break;
        }
        case MC20_CMD_QILOCIP_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                rev_buf_temp = MC20_ATcmdMsg_Out_From_Queue(0);
                if (strstr((char *)rev_buf_temp,".") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
            }
            
            break;
        }
        case MC20_CMD_QIDNSIP_IP:
        {
            MC20_CMD_Send(MC20_CMD_QIDNSIP_IP_BUF,strlen(MC20_CMD_QIDNSIP_IP_BUF));            
            mc20_core_status_to_be(MC20_CMD_QIDNSIP_IP_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            break;
        }
        case MC20_CMD_QIDNSIP_IP_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                rev_buf_temp = MC20_ATcmdMsg_Out_From_Queue(0);
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
            }
            
            break;
        }
        case MC20_CMD_QIDNSIP_DOMAIN:
        {
            MC20_CMD_Send(MC20_CMD_QIDNSIP_DOMAIN_BUF,strlen(MC20_CMD_QIDNSIP_DOMAIN_BUF));            
            mc20_core_status_to_be(MC20_CMD_QIDNSIP_DOMAIN_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            break;
        }
        case MC20_CMD_QIDNSIP_DOMAIN_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                rev_buf_temp = MC20_ATcmdMsg_Out_From_Queue(0);
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
            }
            
            break;
        }
        case MC20_CMD_QIHEAD:
        {
            MC20_CMD_Send(MC20_CMD_QIHEAD_BUF,strlen(MC20_CMD_QIHEAD_BUF));            
            mc20_core_status_to_be(MC20_CMD_QIHEAD_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            break;
        }
        case MC20_CMD_QIHEAD_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                rev_buf_temp = MC20_ATcmdMsg_Out_From_Queue(0);
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
            }
            
            break;
        }
        case MC20_CMD_QIOPEN:
        {
            MC20_CMD_Send(MC20_CMD_QIOPEN_BUF,strlen(MC20_CMD_QIOPEN_BUF));            
            mc20_core_status_to_be(MC20_CMD_QIOPEN_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            break;
        }
        case MC20_CMD_QIOPEN_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                rev_buf_temp = MC20_ATcmdMsg_Out_From_Queue(0);
                if (strstr((char *)rev_buf_temp,"CONNECT OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_60000MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
            }
            
            break;
        }
        case MC20_CMD_QISEND:
        {
            MC20_CMD_Send(MC20_CMD_QISEND_BUF,strlen(MC20_CMD_QISEND_BUF));            
            mc20_core_status_to_be(MC20_CMD_QISEND_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            break;
        }
        case MC20_CMD_QISEND_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                rev_buf_temp = MC20_ATcmdMsg_Out_From_Queue(0);
                if (strstr((char *)rev_buf_temp,">") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
            }
            
            break;
        }
        case MC20_CMD_QISACK:
        {
            MC20_CMD_Send(MC20_CMD_QISACK_BUF,strlen(MC20_CMD_QISACK_BUF));            
            mc20_core_status_to_be(MC20_CMD_QISACK_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            break;
        }
        case MC20_CMD_QISACK_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                rev_buf_temp = MC20_ATcmdMsg_Out_From_Queue(0);
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
            }
            
            break;
        }
        case MC20_CMD_QPOWD:
        {
            MC20_CMD_Send(MC20_CMD_QPOWD_BUF,strlen(MC20_CMD_QPOWD_BUF));            
            mc20_core_status_to_be(MC20_CMD_QPOWD_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            break;
        }
        case MC20_CMD_QPOWD_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                rev_buf_temp = MC20_ATcmdMsg_Out_From_Queue(0);
                if (strstr((char *)rev_buf_temp,"NORMAL POWER DOWN") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                    
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
            }
            
            break;
        }  
        default:break;
    }
}
void MC20_GPRS_Start_Process(void)
{
    switch (MC20_Status.GPRS_Status_Machine.status_machine)
    {
        case MC20_CMD_AT:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_AT);
            mc20_gprs_status_to_be(MC20_CMD_AT_Resp);
            break;
        }
        case MC20_CMD_AT_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    mc20_gprs_status_to_be(MC20_CMD_ATE);
                    break;
                case Rev_Timeout:
                    mc20_gprs_status_to_be(MC20_CMD_AT);
                    break;
                case Rev_Error:
                    mc20_gprs_status_to_be(MC20_CMD_AT);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_ATE:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_ATE);
            mc20_gprs_status_to_be(MC20_CMD_ATE_Resp);
            break;
        }
        case MC20_CMD_ATE_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    mc20_gprs_status_to_be(MC20_CMD_IPR);
                    break;
                case Rev_Timeout:
                    mc20_gprs_status_to_be(MC20_CMD_ATE);
                    break;
                case Rev_Error:
                    mc20_gprs_status_to_be(MC20_CMD_ATE);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_IPR:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_IPR);
            mc20_gprs_status_to_be(MC20_CMD_IPR_Resp);
            break;
        }
        case MC20_CMD_IPR_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    mc20_gprs_status_to_be(MC20_CMD_CPIN);
                    break;
                case Rev_Timeout:
                    mc20_gprs_status_to_be(MC20_CMD_IPR);
                    break;
                case Rev_Error:
                    mc20_gprs_status_to_be(MC20_CMD_IPR);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_CPIN:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_CPIN);
            mc20_gprs_status_to_be(MC20_CMD_CPIN_Resp);
            break;
        }
        case MC20_CMD_CPIN_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    mc20_gprs_status_to_be(MC20_CMD_CSQ);
                    break;
                case Rev_Timeout:
                    mc20_gprs_status_to_be(MC20_CMD_CPIN);
                    break;
                case Rev_Error:
                    mc20_gprs_status_to_be(MC20_CMD_CPIN);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_CSQ:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_CSQ);
            mc20_gprs_status_to_be(MC20_CMD_CSQ_Resp);
            break;
        }
        case MC20_CMD_CSQ_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    mc20_gprs_status_to_be(MC20_CMD_CREG);
                    break;
                case Rev_Timeout:
                    mc20_gprs_status_to_be(MC20_CMD_CSQ);
                    break;
                case Rev_Error:
                    mc20_gprs_status_to_be(MC20_CMD_CSQ);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_CREG:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_CREG);
            mc20_gprs_status_to_be(MC20_CMD_CREG_Resp);
            break;
        }
        case MC20_CMD_CREG_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    mc20_gprs_status_to_be(MC20_CMD_QIFGCNT);
                    break;
                case Rev_Timeout:
                    mc20_gprs_status_to_be(MC20_CMD_CREG);
                    break;
                case Rev_Error:
                    mc20_gprs_status_to_be(MC20_CMD_CREG);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_QIFGCNT:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_QIFGCNT);
            mc20_gprs_status_to_be(MC20_CMD_QIFGCNT_Resp);
            break;
        }
        case MC20_CMD_QIFGCNT_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    mc20_gprs_status_to_be(MC20_CMD_QIDEACT);
                    break;
                case Rev_Timeout:
                    mc20_gprs_status_to_be(MC20_CMD_QIFGCNT);
                    break;
                case Rev_Error:
                    mc20_gprs_status_to_be(MC20_CMD_QIFGCNT);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_QIDEACT:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_QIDEACT);
            mc20_gprs_status_to_be(MC20_CMD_QIDEACT_Resp);
            break;
        }
        case MC20_CMD_QIDEACT_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    mc20_gprs_status_to_be(MC20_CMD_QIMODE);
                    break;
                case Rev_Timeout:
                    mc20_gprs_status_to_be(MC20_CMD_QIDEACT);
                    break;
                case Rev_Error:
                    mc20_gprs_status_to_be(MC20_CMD_QIDEACT);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_QIMODE:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_QIMODE);
            mc20_gprs_status_to_be(MC20_CMD_QIMODE_Resp);
            break;
        }
        case MC20_CMD_QIMODE_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    mc20_gprs_status_to_be(MC20_CMD_QIMUX);
                    break;
                case Rev_Timeout:
                    mc20_gprs_status_to_be(MC20_CMD_QIMODE);
                    break;
                case Rev_Error:
                    mc20_gprs_status_to_be(MC20_CMD_QIMODE);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_QIMUX:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_QIMUX);
            mc20_gprs_status_to_be(MC20_CMD_QIMUX_Resp);
            break;
        }
        case MC20_CMD_QIMUX_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    mc20_gprs_status_to_be(MC20_CMD_QIREGAPP);
                    break;
                case Rev_Timeout:
                    mc20_gprs_status_to_be(MC20_CMD_QIMUX);
                    break;
                case Rev_Error:
                    mc20_gprs_status_to_be(MC20_CMD_QIMUX);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_QIREGAPP:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_QIREGAPP);
            mc20_gprs_status_to_be(MC20_CMD_QIREGAPP_Resp);
            break;
        }
        case MC20_CMD_QIREGAPP_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    mc20_gprs_status_to_be(MC20_CMD_QIACT);
                    break;
                case Rev_Timeout:
                    mc20_gprs_status_to_be(MC20_CMD_QIREGAPP);
                    break;
                case Rev_Error:
                    mc20_gprs_status_to_be(MC20_CMD_QIREGAPP);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_QIACT:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_QIACT);
            mc20_gprs_status_to_be(MC20_CMD_QIACT_Resp);
            break;
        }
        case MC20_CMD_QIACT_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    mc20_gprs_status_to_be(MC20_CMD_QILOCIP);
                    break;
                case Rev_Timeout:
                    mc20_gprs_status_to_be(MC20_CMD_QIACT);
                    break;
                case Rev_Error:
                    mc20_gprs_status_to_be(MC20_CMD_QIACT);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_QILOCIP:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_QILOCIP);
            mc20_gprs_status_to_be(MC20_CMD_QILOCIP_Resp);
            break;
        }
        case MC20_CMD_QILOCIP_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    mc20_gprs_status_to_be(MC20_CMD_QIDNSIP_IP);
                    break;
                case Rev_Timeout:
                    mc20_gprs_status_to_be(MC20_CMD_QILOCIP);
                    break;
                case Rev_Error:
                    mc20_gprs_status_to_be(MC20_CMD_QILOCIP);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_QIDNSIP_IP:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_QIDNSIP_IP);
            mc20_gprs_status_to_be(MC20_CMD_QIDNSIP_IP_Resp);
            break;
        }
        case MC20_CMD_QIDNSIP_IP_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    mc20_gprs_status_to_be(MC20_CMD_QIHEAD);
                    break;
                case Rev_Timeout:
                    mc20_gprs_status_to_be(MC20_CMD_QIDNSIP_IP);
                    break;
                case Rev_Error:
                    mc20_gprs_status_to_be(MC20_CMD_QIDNSIP_IP);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_QIHEAD:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_QIHEAD);
            mc20_gprs_status_to_be(MC20_CMD_QIHEAD_Resp);
            break;
        }
        case MC20_CMD_QIHEAD_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    mc20_gprs_status_to_be(MC20_CMD_QIOPEN);
                    break;
                case Rev_Timeout:
                    mc20_gprs_status_to_be(MC20_CMD_QIHEAD);
                    break;
                case Rev_Error:
                    mc20_gprs_status_to_be(MC20_CMD_QIHEAD);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_QIOPEN:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_QIOPEN);
            mc20_gprs_status_to_be(MC20_CMD_QIOPEN_Resp);
            break;
        }
        case MC20_CMD_QIOPEN_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    mc20_gprs_status_to_be(MC20_CMD_QISEND);
                    break;
                case Rev_Timeout:
                    mc20_gprs_status_to_be(MC20_CMD_QIOPEN);
                    break;
                case Rev_Error:
                    mc20_gprs_status_to_be(MC20_CMD_QIOPEN);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_QISEND:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_QISEND);
            mc20_gprs_status_to_be(MC20_CMD_QISEND_Resp);
            break;
        }
        case MC20_CMD_QISEND_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    mc20_gprs_status_to_be(MC20_CMD_QISACK);
                    break;
                case Rev_Timeout:
                    mc20_gprs_status_to_be(MC20_CMD_QISEND);
                    break;
                case Rev_Error:
                    mc20_gprs_status_to_be(MC20_CMD_QISEND);
                    break;
                default:break;
            }
            break;
        }
        case MC20_CMD_QISACK:
        {
            MC20_ATcmd_In_to_Queue(MC20_CMD_QISACK);
            mc20_gprs_status_to_be(MC20_CMD_QISACK_Resp);
            break;
        }
        case MC20_CMD_QISACK_Resp:
        {
            switch (MC20_Status.GPRS_Status_Machine.status_Rev)
            {
                case Rev_Wait:
                    break;
                case Rev_Pass:
                    mc20_gprs_status_to_be(123);
                    break;
                case Rev_Timeout:
                    mc20_gprs_status_to_be(MC20_CMD_QISACK);
                    break;
                case Rev_Error:
                    mc20_gprs_status_to_be(MC20_CMD_QISACK);
                    break;
                default:break;
            }
            break;
        }
        default:
        {
            MC20_Status.GPRS_Status_Machine.status_machine = MC20_CMD_AT;
        }
        break;
    }
}

void MC20_GPS_Start_Process(void)
{
    switch (MC20_Status.GPS_Status_Machine.status_machine)
    {

    }
}
void MC20_GPS_GetLocation_Process(void)
{

}


static void mc20_core_status_to_be(uint8_t core_status)
{
    MC20_Status.CORE_Status_Machine.status_machine = core_status;
}
static void mc20_gprs_status_to_be(uint8_t gprs_status)
{
    MC20_Status.GPRS_Status_Machine.status_machine = gprs_status;
}

static void mc20_gprs_rev_status_to_be(uint8_t rev_status)
{
    MC20_Status.GPRS_Status_Machine.status_Rev = rev_status;
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

