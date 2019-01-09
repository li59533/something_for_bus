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
#include "clog.h"
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
    Rev_Null=1,
    Rev_Wait,
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
static void mc20_func_status_machine_init(void);
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
    static uint8_t rev_buf_temp[20];
    static uint8_t rev_buf_len;
    memcpy(rev_buf_temp,0,20);
    switch (MC20_Status.CORE_Status_Machine.status_machine)
    {
        case MC20_IDLE:
        {
            if (MC20_ATcmd_Queue_Get_Count() > 0)
            {
                MC20_Status.CORE_Status_Machine.status_machine = MC20_ATcmd_Out_From_Queue();
            }
            break;
        }
        case MC20_CMD_AT:
        {
            MC20_CMD_Send(MC20_CMD_AT_BUF,strlen(MC20_CMD_AT_BUF));            
            mc20_core_status_to_be(MC20_CMD_AT_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-at\r\n");
            break;
        }
        case MC20_CMD_AT_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len);      
                DEBUG("rev:%s\r\n",rev_buf_temp);   
                if (strstr((char*)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                    INFO("--rev-at-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                    INFO("--rev-at-error\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
                    INFO("--rev-at-timout\r\n");
            }
            
            break;
        }
        case MC20_CMD_ATE:
        {
            MC20_CMD_Send(MC20_CMD_ATE_BUF,strlen(MC20_CMD_ATE_BUF));            
            mc20_core_status_to_be(MC20_CMD_ATE_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-ate\r\n");
            break;
        }
        case MC20_CMD_ATE_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char*)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                    INFO("--rev-ATE-pass\r\n");
                    
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                    INFO("--rev-ATE-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
                    INFO("--rev-ATE-TIMOUT\r\n");
            }
            
            break;
        }
        case MC20_CMD_IPR:
        {
            MC20_CMD_Send(MC20_CMD_IPR_BUF,strlen(MC20_CMD_IPR_BUF));            
            mc20_core_status_to_be(MC20_CMD_IPR_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-IPR\r\n");
            break;
        }
        case MC20_CMD_IPR_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char*)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                    INFO("--rev-IPR-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                    INFO("--rev-IPR-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
                    INFO("--rev-IPR-TIMOUTs\r\n");
            }
    
            break;
        }
        case MC20_CMD_CPIN:
        {
            MC20_CMD_Send(MC20_CMD_CPIN_BUF,strlen(MC20_CMD_CPIN_BUF));            
            mc20_core_status_to_be(MC20_CMD_IPR_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-CPIN\r\n");
            break;
        }
        case MC20_CMD_CPIN_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char*)rev_buf_temp,"+CPIN: READY") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                    INFO("--rev-CPIN-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                    INFO("--rev-CPIN-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_3000MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
                    INFO("--rev-CPIN-TIMOUT\r\n");
            }
          
            break;
        }
        case MC20_CMD_CSQ:
        {
            MC20_CMD_Send(MC20_CMD_CSQ_BUF,strlen(MC20_CMD_CSQ_BUF));            
            mc20_core_status_to_be(MC20_CMD_CSQ_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-CSQ\r\n");
            break;
        }
        case MC20_CMD_CSQ_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"+CSQ") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                    INFO("--rev-CSQ-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                    INFO("--rev-CSQ-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
                    INFO("--rev-CSQ-TIMOUT\r\n");
            }
           
            break;
        }
        case MC20_CMD_CREG:
        {
            MC20_CMD_Send(MC20_CMD_CREG_BUF,strlen(MC20_CMD_CREG_BUF));            
            mc20_core_status_to_be(MC20_CMD_CREG_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-CREG\r\n");
            break;
        }
        case MC20_CMD_CREG_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"+CREG: 0,1") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                    INFO("--rev-CREG-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                    INFO("--rev-CREG-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
                    INFO("--rev-CREG-TIMOUT\r\n");
            }
           
            break;
        }
        case MC20_CMD_CGREG:
        {
            MC20_CMD_Send(MC20_CMD_CGREG_BUF,strlen(MC20_CMD_CGREG_BUF));            
            mc20_core_status_to_be(MC20_CMD_CGREG_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-CGREG\r\n");
            break;
        }
        case MC20_CMD_CGREG_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"+CGREG: 0,1") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                    INFO("--rev-CGREG-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                    INFO("--rev-CGREG-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
                    INFO("--rev-CGREG-TIMOUT\r\n");
            }
            
            break;
        }
        case MC20_CMD_QIFGCNT:
        {
            MC20_CMD_Send(MC20_CMD_QIFGCNT_BUF,strlen(MC20_CMD_QIFGCNT_BUF));            
            mc20_core_status_to_be(MC20_CMD_QIFGCNT_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-QIFGCNT\r\n");
            break;
        }
        case MC20_CMD_QIFGCNT_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                    INFO("--rev-QIFGCNT-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                    INFO("--rev-QIFGCNT-pass\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
                    INFO("--rev-QIFGCNT-pass\r\n");
            }
           
            break;
        }
        case MC20_CMD_QICSGP:
        {
            MC20_CMD_Send(MC20_CMD_QICSGP_BUF,strlen(MC20_CMD_QICSGP_BUF));            
            mc20_core_status_to_be(MC20_CMD_QICSGP_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-QICSGP\r\n");
            break;
        }
        case MC20_CMD_QICSGP_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                    INFO("--rev-QICSGP-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                    INFO("--rev-QICSGP-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
                    INFO("--rev-QICSGP-TIMOUT\r\n");
            }
            
            break;
        }
        case MC20_CMD_QIDEACT:
        {
            MC20_CMD_Send(MC20_CMD_QIDEACT_BUF,strlen(MC20_CMD_QIDEACT_BUF));            
            mc20_core_status_to_be(MC20_CMD_QIDEACT_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-QIDACT\r\n");
            break;
        }
        case MC20_CMD_QIDEACT_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"DEACT OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                    INFO("--rev-QIDEACT-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                    INFO("--rev-QIDEACT-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_40000MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
                    INFO("--rev-QIDEAVT-TIMOUT\r\n");
            }
            
            break;
        }
        case MC20_CMD_QIMODE:
        {
            MC20_CMD_Send(MC20_CMD_QIMODE_BUF,strlen(MC20_CMD_QIMODE_BUF));            
            mc20_core_status_to_be(MC20_CMD_QIMODE_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-QIMODE\r\n");
            break;
        }
        case MC20_CMD_QIMODE_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                    INFO("--rev-QIMODE-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                    INFO("--rev-QIMODE-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
                    INFO("--rev-QIMODE-TIMOUT\r\n");
            }
            
            break;
        }
        case MC20_CMD_QIMUX:
        {
            MC20_CMD_Send(MC20_CMD_QIMUX_BUF,strlen(MC20_CMD_QIMUX_BUF));            
            mc20_core_status_to_be(MC20_CMD_QIMUX_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-QIMUX\r\n");
            break;
        }
        case MC20_CMD_QIMUX_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                    INFO("--rev-QIMUX-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                    INFO("--rev-QIMUX-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
                    INFO("--rev-QIMUX-TIMOUT\r\n");
            }
            
            break;
        }
        case MC20_CMD_QIREGAPP:
        {
            MC20_CMD_Send(MC20_CMD_QIREGAPP_BUF,strlen(MC20_CMD_QIREGAPP_BUF));            
            mc20_core_status_to_be(MC20_CMD_QIREGAPP_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-QIREGAPP\r\n");
            break;
        }
        case MC20_CMD_QIREGAPP_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                    INFO("--rev-QIREGAPP-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                    INFO("--rev-QIREGAPP-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
                    INFO("--rev-QIREGAPP-TIMOUT\r\n");
            }
            
            break;
        }
        case MC20_CMD_QIACT:
        {
            MC20_CMD_Send(MC20_CMD_QIACT_BUF,strlen(MC20_CMD_QIACT_BUF));            
            mc20_core_status_to_be(MC20_CMD_QIACT_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-QIACT\r\n");
            break;
        }
        case MC20_CMD_QIACT_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                    INFO("--rev-QIACT-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                    INFO("--rev-QIACT-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_60000MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
                    INFO("--rev-QIACT-TIMOUT\r\n");
            }
            
            break;
        }
        case MC20_CMD_QILOCIP:
        {
            MC20_CMD_Send(MC20_CMD_QILOCIP_BUF,strlen(MC20_CMD_QILOCIP_BUF));            
            mc20_core_status_to_be(MC20_CMD_QILOCIP_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-QILOCIP\r\n");
            break;
        }
        case MC20_CMD_QILOCIP_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,".") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                    INFO("--rev-QILOCIP-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                    INFO("--rev-QILOCIP-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
                    INFO("--rev-QILOCIP-TIMOUT\r\n");
            }
            
            break;
        }
        case MC20_CMD_QIDNSIP_IP:
        {
            MC20_CMD_Send(MC20_CMD_QIDNSIP_IP_BUF,strlen(MC20_CMD_QIDNSIP_IP_BUF));            
            mc20_core_status_to_be(MC20_CMD_QIDNSIP_IP_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-QIDNSIP_IP\r\n");
            break;
        }
        case MC20_CMD_QIDNSIP_IP_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                    INFO("--rev-QIDNSIP_IP-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                    INFO("--rev-QIDNSIP_IP-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
                    INFO("--rev-QIDNSIP_IP-TIMOUT\r\n");
            }
            
            break;
        }
        case MC20_CMD_QIDNSIP_DOMAIN:
        {
            MC20_CMD_Send(MC20_CMD_QIDNSIP_DOMAIN_BUF,strlen(MC20_CMD_QIDNSIP_DOMAIN_BUF));            
            mc20_core_status_to_be(MC20_CMD_QIDNSIP_DOMAIN_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-QIDNSIP_DOMAIN\r\n");
            break;
        }
        case MC20_CMD_QIDNSIP_DOMAIN_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                    INFO("--rev-QIDNSIP_DOMAIN-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                    INFO("--rev-QIDNSIP_DOMAIN-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
                    INFO("--rev-QIDNSIP_DOMAIN-TIMOUT\r\n");
            }
            
            break;
        }
        case MC20_CMD_QIHEAD:
        {
            MC20_CMD_Send(MC20_CMD_QIHEAD_BUF,strlen(MC20_CMD_QIHEAD_BUF));            
            mc20_core_status_to_be(MC20_CMD_QIHEAD_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-QIHEAD\r\n");
            break;
        }
        case MC20_CMD_QIHEAD_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                    INFO("--rev-QIHEAD-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                    INFO("--rev-QIHEAD-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
                    INFO("--rev-QIHEAD-TIMOUT\r\n");
            }
            
            break;
        }
        case MC20_CMD_QIOPEN:
        {
            MC20_CMD_Send(MC20_CMD_QIOPEN_BUF,strlen(MC20_CMD_QIOPEN_BUF));            
            mc20_core_status_to_be(MC20_CMD_QIOPEN_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-QIOPEN\r\n");
            break;
        }
        case MC20_CMD_QIOPEN_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"CONNECT OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                    INFO("--rev-QIOPEN-pass\r\n");
                }
                else
                {
					//mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                    INFO("--rev-QIOPEN-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_60000MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
                    INFO("--rev-QIOPEN-ERROR\r\n");
            }
            
            break;
        }
        case MC20_CMD_QISEND:
        {
            MC20_CMD_Send(MC20_CMD_QISEND_BUF,strlen(MC20_CMD_QISEND_BUF));            
            mc20_core_status_to_be(MC20_CMD_QISEND_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-QISEND\r\n");
            break;
        }
        case MC20_CMD_QISEND_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,">") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                    INFO("--rev-QISEND-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                    INFO("--rev-QISEND-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
                    INFO("--rev-QISEND-TIMOUT\r\n");
            }
            
            break;
        }
        case MC20_CMD_QISACK:
        {
            MC20_CMD_Send(MC20_CMD_QISACK_BUF,strlen(MC20_CMD_QISACK_BUF));            
            mc20_core_status_to_be(MC20_CMD_QISACK_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-QISACK\r\n");
            break;
        }
        case MC20_CMD_QISACK_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                    INFO("--rev-QISACK-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                    INFO("--rev-QISACK-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
                    INFO("--rev-QISACK-TIMOUT\r\n");
            }
            
            break;
        }
        case MC20_CMD_QPOWD:
        {
            MC20_CMD_Send(MC20_CMD_QPOWD_BUF,strlen(MC20_CMD_QPOWD_BUF));            
            mc20_core_status_to_be(MC20_CMD_QPOWD_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-QPOWD\r\n");
            break;
        }
        case MC20_CMD_QPOWD_Resp:
        {
			mc20_gprs_rev_status_to_be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"NORMAL POWER DOWN") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Pass);
                    INFO("--rev-QPOWD-pass\r\n");
                    
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Error);
                    INFO("--rev-QPOWD-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    mc20_gprs_rev_status_to_be(Rev_Timeout);
                    INFO("--rev-QPOWD-TIMOUT\r\n");
            }
            
            break;
        }
        case MC20_HAL_RESTART:
        {
            MC20_Power_Pin_Rest();
            mc20_core_status_to_be(MC20_HAL_RESTART_Resp);
            mc20_func_status_machine_init();
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-RESTART\r\n");
            break;
        }
        case MC20_HAL_RESTART_Resp:
        {
           
            if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_1000MS)
            {
                MC20_Power_Pin_Set();                     
            }

            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                atcmd_time_record = OS_Clock_GetSystemClock();
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                
                if (strstr((char *)rev_buf_temp,"SMS Ready") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
					mc20_func_status_machine_init();
                    INFO("--rev-RESTART-pass\r\n");
                }
                else
                {					
                    
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_10000MS)
            {
                mc20_core_status_to_be(MC20_HAL_RESTART);            
                INFO("--rev-RESTART-??\r\n");    
            }
            break;

        }
        default:break;
    }
}
void MC20_GPRS_Start_Process(void)
{
    static uint8_t rev_count = 0;
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
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;
                    rev_count<6?mc20_gprs_status_to_be(MC20_CMD_AT):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    
                    break;
                case Rev_Error:
                    rev_count ++;
                    rev_count<6?mc20_gprs_status_to_be(MC20_CMD_AT):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
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
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_ATE):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_ATE):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
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
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_IPR):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_IPR):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
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
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_CPIN):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                 
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_CPIN):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
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
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_CSQ):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_CSQ):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
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
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_CREG):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_CREG):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
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
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_QIFGCNT):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_QIFGCNT):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
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
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_QIDEACT):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_QIDEACT):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
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
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_QIMODE):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_QIMODE):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
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
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_QIMUX):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_QIMUX):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
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
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_QIREGAPP):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_QIREGAPP):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
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
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_QIACT):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_QIACT):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
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
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_QILOCIP):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_QILOCIP):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
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
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_QIDNSIP_IP):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_QIDNSIP_IP):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
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
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_QIHEAD):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_QIHEAD):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
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
                    INFO("--LINK_OK\r\n");
                    mc20_gprs_status_to_be(MC20_GPRS_CONNECT_ING);
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    mc20_gprs_status_to_be(MC20_GPRS_CONNECT_ING);
                    break;
                case Rev_Error:
                    mc20_gprs_status_to_be(MC20_GPRS_CONNECT_ING);
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
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_QISEND):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_QISEND):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
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
                    rev_count = 0;
                    break;
                case Rev_Timeout:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_QISACK):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                case Rev_Error:
                    rev_count ++;                  
                    rev_count<3?mc20_gprs_status_to_be(MC20_CMD_QISACK):MC20_ATcmd_In_to_Queue(MC20_HAL_RESTART);
                    break;
                default:break;
            }
            break;
        }
        case MC20_GPRS_CONNECT_ING:
            break;
        default:
        {
            rev_count = 0;
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
    mc20_gprs_rev_status_to_be(Rev_Wait);
    MC20_Status.GPRS_Status_Machine.status_machine = gprs_status;
}

static void mc20_gprs_rev_status_to_be(uint8_t rev_status)
{
    MC20_Status.GPRS_Status_Machine.status_Rev = rev_status;
}


static void mc20_func_status_machine_init(void)
{
    MC20_Status.GPRS_Status_Machine.status_machine = MC20_IDLE;
    MC20_Status.GPRS_Status_Machine.status_Rev = Rev_Wait;
    MC20_AT_Queue_Init();
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

