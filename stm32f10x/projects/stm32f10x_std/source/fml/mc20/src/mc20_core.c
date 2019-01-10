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
#include "mc20_core_gprs.h"
#include "mc20_core_gps.h"
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
    uint8_t rev_msg_buf_temp[400];
    uint16_t rev_msg_buf_len;
    
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
			MC20_Core_Gprs_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len);      
                DEBUG("rev:%s\r\n",rev_buf_temp);   
                if (strstr((char*)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Pass);
                    INFO("--rev-at-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Error);
                    INFO("--rev-at-error\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Timeout);
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
			MC20_Core_Gprs_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char*)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Pass);
                    INFO("--rev-ATE-pass\r\n");
                    
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Error);
                    INFO("--rev-ATE-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Timeout);
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
			MC20_Core_Gprs_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char*)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Pass);
                    INFO("--rev-IPR-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Error);
                    INFO("--rev-IPR-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Timeout);
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
			MC20_Core_Gprs_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char*)rev_buf_temp,"+CPIN: READY") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Pass);
                    INFO("--rev-CPIN-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Error);
                    INFO("--rev-CPIN-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_3000MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Timeout);
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
			MC20_Core_Gprs_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"+CSQ") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Pass);
                    INFO("--rev-CSQ-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Error);
                    INFO("--rev-CSQ-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Timeout);
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
			MC20_Core_Gprs_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"+CREG: 0,1") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Pass);
                    INFO("--rev-CREG-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Error);
                    INFO("--rev-CREG-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Timeout);
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
			MC20_Core_Gprs_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"+CGREG: 0,1") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Pass);
                    INFO("--rev-CGREG-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Error);
                    INFO("--rev-CGREG-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Timeout);
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
			MC20_Core_Gprs_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Pass);
                    INFO("--rev-QIFGCNT-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Error);
                    INFO("--rev-QIFGCNT-pass\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Timeout);
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
			MC20_Core_Gprs_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Pass);
                    INFO("--rev-QICSGP-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Error);
                    INFO("--rev-QICSGP-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Timeout);
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
			MC20_Core_Gprs_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"DEACT OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Pass);
                    INFO("--rev-QIDEACT-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Error);
                    INFO("--rev-QIDEACT-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_40000MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Timeout);
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
			MC20_Core_Gprs_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Pass);
                    INFO("--rev-QIMODE-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Error);
                    INFO("--rev-QIMODE-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Timeout);
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
			MC20_Core_Gprs_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Pass);
                    INFO("--rev-QIMUX-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Error);
                    INFO("--rev-QIMUX-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Timeout);
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
			MC20_Core_Gprs_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Pass);
                    INFO("--rev-QIREGAPP-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Error);
                    INFO("--rev-QIREGAPP-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Timeout);
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
			MC20_Core_Gprs_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Pass);
                    INFO("--rev-QIACT-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Error);
                    INFO("--rev-QIACT-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_60000MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Timeout);
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
			MC20_Core_Gprs_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,".") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Pass);
                    INFO("--rev-QILOCIP-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Error);
                    INFO("--rev-QILOCIP-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Timeout);
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
			MC20_Core_Gprs_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Pass);
                    INFO("--rev-QIDNSIP_IP-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Error);
                    INFO("--rev-QIDNSIP_IP-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Timeout);
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
			MC20_Core_Gprs_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Pass);
                    INFO("--rev-QIDNSIP_DOMAIN-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Error);
                    INFO("--rev-QIDNSIP_DOMAIN-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Timeout);
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
			MC20_Core_Gprs_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Pass);
                    INFO("--rev-QIHEAD-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Error);
                    INFO("--rev-QIHEAD-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Timeout);
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
			MC20_Core_Gprs_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"CONNECT") > 0)
                {
                    if ((strstr((char *)rev_buf_temp,"OK"))> 0||(strstr((char *)rev_buf_temp,"ALREADY")))
                    {
                        mc20_core_status_to_be(MC20_IDLE);
                        MC20_Core_Gprs_RevStatus_To_Be(Rev_Pass);
                        INFO("--rev-QIOPEN-pass\r\n");
                    }
                    else
                    {
                        mc20_core_status_to_be(MC20_IDLE);
                        MC20_Core_Gprs_RevStatus_To_Be(Rev_Error);
                        INFO("--rev-QIOPEN-pass\r\n");
                    }
                }
                else
                {
					//mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Error);
                    INFO("--rev-QIOPEN-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_60000MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Timeout);
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
			MC20_Core_Gprs_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,">") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Pass);
                    INFO("--rev-QISEND-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Error);
                    INFO("--rev-QISEND-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Timeout);
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
			MC20_Core_Gprs_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Pass);
                    INFO("--rev-QISACK-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Error);
                    INFO("--rev-QISACK-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Timeout);
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
			MC20_Core_Gprs_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"NORMAL POWER DOWN") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Pass);
                    INFO("--rev-QPOWD-pass\r\n");
                    
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Error);
                    INFO("--rev-QPOWD-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Timeout);
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
        case MC20_GPS_QGNSSC:
        {
            MC20_CMD_Send(MC20_CMD_QGNSSC_BUF,strlen(MC20_CMD_QGNSSC_BUF));            
            mc20_core_status_to_be(MC20_GPS_QGNSSC_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-QGNSSC\r\n");
            break;
        }
        case MC20_GPS_QGNSSC_Resp:
        {
			MC20_Core_Gps_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gps_RevStatus_To_Be(Rev_Pass);
                    INFO("--rev-QGNSSC-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gps_RevStatus_To_Be(Rev_Error);
                    INFO("--rev-QGNSSC-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gps_RevStatus_To_Be(Rev_Timeout);
                    INFO("--rev-QGNSSC-TIMOUT\r\n");
            }
            
            break;
        }
        case MC20_GPS_QGNSSTS:
        {
            MC20_CMD_Send(MC20_CMD_QGNSSTS_BUF,strlen(MC20_CMD_QGNSSTS_BUF));            
            mc20_core_status_to_be(MC20_GPS_QGNSSTS_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-QGNSSTS\r\n");
            break;
        }
        case MC20_GPS_QGNSSTS_Resp:
        {
			MC20_Core_Gps_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gps_RevStatus_To_Be(Rev_Pass);
                    INFO("--rev-QGNSSTS-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gps_RevStatus_To_Be(Rev_Error);
                    INFO("--rev-QGNSSTS-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gps_RevStatus_To_Be(Rev_Timeout);
                    INFO("--rev-QGNSSTS-TIMOUT\r\n");
            }
            
            break;
        }
        case MC20_GPS_QGNSSEPO:
        {
            MC20_CMD_Send(MC20_CMD_QGNSSEPO_BUF,strlen(MC20_CMD_QGNSSEPO_BUF));            
            mc20_core_status_to_be(MC20_GPS_QGNSSEPO_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-QGNSSEPO\r\n");
            break;
        }
        case MC20_GPS_QGNSSEPO_Resp:
        {
			MC20_Core_Gps_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gps_RevStatus_To_Be(Rev_Pass);
                    INFO("--rev-QGNSSEPO-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gps_RevStatus_To_Be(Rev_Error);
                    INFO("--rev-QGNSSEPO-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gps_RevStatus_To_Be(Rev_Timeout);
                    INFO("--rev-QGNSSEPO-TIMOUT\r\n");
            }
            
            break;
        }
        case MC20_GPS_QGEPOAID:
        {
            MC20_CMD_Send(MC20_CMD_QGEPOAID_BUF,strlen(MC20_CMD_QGEPOAID_BUF));            
            mc20_core_status_to_be(MC20_GPS_QGEPOAID_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-QGEPOAID\r\n");
            break;
        }
        case MC20_GPS_QGEPOAID_Resp:
        {
			MC20_Core_Gps_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gps_RevStatus_To_Be(Rev_Pass);
                    INFO("--rev-QGEPOAID-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gps_RevStatus_To_Be(Rev_Error);
                    INFO("--rev-QGEPOAID-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gps_RevStatus_To_Be(Rev_Timeout);
                    INFO("--rev-QGEPOAID-TIMOUT\r\n");
            }
            
            break;
        }
        case MC20_GPS_QGNSSRD:
        {
            MC20_CMD_Send(MC20_CMD_QGNSSRD_BUF,strlen(MC20_CMD_QGNSSRD_BUF));            
            mc20_core_status_to_be(MC20_GPS_QGNSSRD_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-QGNSSRD\r\n");
            break;
        } 
        case MC20_GPS_QGNSSRD_Resp:
        {
			MC20_Core_Gps_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gps_RevStatus_To_Be(Rev_Pass);
                    INFO("--rev-QGNSSRD-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gps_RevStatus_To_Be(Rev_Error);
                    INFO("--rev-QGNSSRD-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gps_RevStatus_To_Be(Rev_Timeout);
                    INFO("--rev-QGNSSRD-TIMOUT\r\n");
            }            
            break;
        }
        case MC20_GPS_QGNSSRD_RMC:
        {
            MC20_CMD_Send(MC20_CMD_QGNSSRD_RMC_BUF,strlen(MC20_CMD_QGNSSRD_RMC_BUF));            
            mc20_core_status_to_be(MC20_GPS_QGNSSRD_RMC_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            INFO("--cmd-QGNSSRD_RMC\r\n");
            break;
        }
        case MC20_GPS_QGNSSRD_RMC_Resp:
        {
            MC20_Core_Gps_RevStatus_To_Be(Rev_Wait);
            if (MC20_Msg_Queue_Get_Count() > 0)
            {
                
                MC20_Msg_Out_From_Queue(rev_msg_buf_temp,&rev_msg_buf_len); 
                DEBUG("rev:%s\r\n",rev_msg_buf_temp);  
                if (strstr((char *)rev_msg_buf_temp,"OK") > 0)
                {
                    DEBUG("%s\r\n",rev_msg_buf_temp);
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gps_RevStatus_To_Be(Rev_Pass);
                    INFO("--rev-QGNSSRD_RMC-pass\r\n");
                }
                else
                {
					mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gps_RevStatus_To_Be(Rev_Error);
                    INFO("--rev-QGNSSRD_RMC-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    mc20_core_status_to_be(MC20_IDLE);
                    MC20_Core_Gps_RevStatus_To_Be(Rev_Timeout);
                    INFO("--rev-QGNSSRD_RMC-TIMOUT\r\n");
            }       
            break;
        }
        default:break;
    }

    if (strstr((char *)rev_buf_temp,"CLOSED"))
    {
        INFO("--rev:serverclosed\r\n");
        mc20_func_status_machine_init();
        MC20_Gprs_Status_To_Be(MC20_CMD_QIOPEN);
    }
	else if(MC20_ATcmdMsg_Queue_Get_Count() > 0)
	{
		MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
		if (strstr((char *)rev_buf_temp,"CLOSED"))
		{
			INFO("--rev:serverclosed\r\n");
			mc20_func_status_machine_init();
			MC20_Gprs_Status_To_Be(MC20_CMD_QIOPEN);
		}	
	}
	memcpy(rev_buf_temp,0,20);
}



void MC20_GPS_GetLocation_Process(void)
{

}

void MC20_Core_Gprs_RevStatus_To_Be(uint8_t rev_status)
{
    MC20_Status.GPRS_Status_Machine.status_Rev = rev_status;
}

static void mc20_core_status_to_be(uint8_t core_status)
{
    MC20_Status.CORE_Status_Machine.status_machine = core_status;
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

