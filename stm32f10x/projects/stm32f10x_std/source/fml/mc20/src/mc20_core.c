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
#include "mc20_parameter.h"
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

void MC20_Core_Loop(void)
{
    static uint8_t mc20_module_status = 0;
    

    if (mc20_module_status == 0)
    {

    }
    else
    {
        MC20_Core_Run_Process();
    }
}

int8_t MC20_check_module(uint8_t mc20_module_status)
{
    static uint8_t mc20_device_mactinestatus = MC20_CMD_AT_REQ;
    static uint32_t time_record = 0;
    static uint8_t req_times_record = 0;
    uint8_t rev_buf_temp[20] = {0};
    uint8_t rev_buf_len = 0;
    if(mc20_module_status == 0)
    {
        switch (mc20_device_mactinestatus)
        {
            case MC20_CMD_AT_REQ: 
            {
                MC20_CMD_Send(MC20_CMD_AT_BUF,strlen(MC20_CMD_AT_BUF)); 
                req_times_record ++  ;
                time_record = OS_Clock_GetSystemClock();
                mc20_device_mactinestatus = MC20_CMD_AT_RESP;
                break;
            }
            case MC20_CMD_AT_RESP:
            {
                if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
                {
                    MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len);      
                    DEBUG("rev:%s\r\n",rev_buf_temp);   
                    if (strstr((char*)rev_buf_temp,"OK") > 0)
                    {
                        req_times_record = 0;
                        mc20_device_mactinestatus = MC20_CMD_ATE_REQ;

                    }
                    else
                    {
                        mc20_device_mactinestatus = MC20_CMD_AT_REQ;

                    }
                }
                else if ((OS_Clock_GetSystemClock() - time_record) > MC20_TIMEOUT_300MS)
                {
                        mc20_device_mactinestatus = MC20_CMD_AT_REQ;

                }
                break;
            }
            case MC20_CMD_ATE_REQ:
            {
                MC20_CMD_Send(MC20_CMD_ATE_BUF,strlen(MC20_CMD_ATE_BUF)); 
                req_times_record ++  ;
                time_record = OS_Clock_GetSystemClock();
                mc20_device_mactinestatus = MC20_CMD_ATE_RESP;
                break;
            }
            case MC20_CMD_ATE_RESP:
            {
                if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
                {
                    MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len);      
                    DEBUG("rev:%s\r\n",rev_buf_temp);   
                    if (strstr((char*)rev_buf_temp,"OK") > 0)
                    {
                        req_times_record = 0;
                        mc20_device_mactinestatus = MC20_CMD_CSQ_REQ;

                    }
                    else
                    {
                        mc20_device_mactinestatus = MC20_CMD_ATE_REQ;

                    }
                }
                else if ((OS_Clock_GetSystemClock() - time_record) > MC20_TIMEOUT_300MS)
                {
                        mc20_device_mactinestatus = MC20_CMD_ATE_REQ;

                }
                break;
            }
            case MC20_CMD_CSQ_REQ:
            {
                MC20_CMD_Send(MC20_CMD_CSQ_BUF,strlen(MC20_CMD_CSQ_BUF)); 
                req_times_record ++  ;
                time_record = OS_Clock_GetSystemClock();
                mc20_device_mactinestatus = MC20_CMD_CSQ_RESP;
                break;
            }
            case MC20_CMD_CSQ_RESP:
            {
                if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
                {
                    MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len);      
                    DEBUG("rev:%s\r\n",rev_buf_temp);   
                    if (strstr((char*)rev_buf_temp,"+CSQ") > 0)
                    {
                        req_times_record = 0;
                        mc20_module_status = 1;

                    }
                    else
                    {
                        mc20_device_mactinestatus = MC20_CMD_CSQ_REQ;
                    }
                }
                else if ((OS_Clock_GetSystemClock() - time_record) > MC20_TIMEOUT_300MS)
                {
                        mc20_device_mactinestatus = MC20_CMD_CSQ_REQ;

                }
                break;
            }
            default:break;
        }

        if (req_times_record > 5)
        {
            
        }
    }
    else
    {
        return 1;
    }
}

void MC20_Core_Run_Process(void)
{
    static uint8_t core_status_machine = MC20_IDLE;
    static uint32_t atcmd_time_record = 0;
    static uint8_t rev_buf_temp[20];
    static uint8_t rev_buf_len;
    uint8_t rev_msg_buf_temp[400];
    uint16_t rev_msg_buf_len = 0;
    uint8_t * send_msg_buf_addr = 0;
    uint16_t send_msg_buf_len = 0;
    switch (core_status_machine)
    {
        case MC20_IDLE:
        {
            if (MC20_ATcmd_Queue_Get_Count() > 0)
            {
                core_status_machine = MC20_ATcmd_DeQueue();
            }

            if(MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                if (strstr((char *)rev_buf_temp,"CLOSED"))
                {
                    INFO("--rev:serverclosed\r\n");
                    mc20_gprs_status_machine_init();
                    core_status_machine =(MC20_CMD_QIOPEN);
                }	
            }
            break;
        }
        case MC20_CMD_AT:
        {
            MC20_CMD_Send(MC20_CMD_AT_BUF,strlen(MC20_CMD_AT_BUF));            
            core_status_machine =(MC20_CMD_AT_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            DEBUG("--cmd-at\r\n");
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
                    core_status_machine =(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Pass);
                    DEBUG("--rev-at-pass\r\n");
                }
                else
                {
					core_status_machine =(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Error);
                    DEBUG("--rev-at-error\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    core_status_machine =(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Timeout);
                    DEBUG("--rev-at-timout\r\n");
            }
            
            break;
        }
        case MC20_CMD_ATE:
        {
            MC20_CMD_Send(MC20_CMD_ATE_BUF,strlen(MC20_CMD_ATE_BUF));            
            core_status_machine =(MC20_CMD_ATE_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            DEBUG("--cmd-ate\r\n");
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
                    core_status_machine =(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Pass);
                    DEBUG("--rev-ATE-pass\r\n");
                    
                }
                else
                {
					core_status_machine =(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Error);
                    DEBUG("--rev-ATE-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    core_status_machine =(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Timeout);
                    DEBUG("--rev-ATE-TIMOUT\r\n");
            }
            
            break;
        }
        case MC20_CMD_IPR:
        {
            MC20_CMD_Send(MC20_CMD_IPR_BUF,strlen(MC20_CMD_IPR_BUF));            
            core_status_machine =(MC20_CMD_IPR_Resp);
            atcmd_time_record = OS_Clock_GetSystemClock();
            DEBUG("--cmd-IPR\r\n");
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
                    core_status_machine =(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Pass);
                    DEBUG("--rev-IPR-pass\r\n");
                }
                else
                {
					core_status_machine =(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Error);
                    DEBUG("--rev-IPR-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    core_status_machine =(MC20_IDLE);
                    MC20_Core_Gprs_RevStatus_To_Be(Rev_Timeout);
                    DEBUG("--rev-IPR-TIMOUTs\r\n");
            }
    
            break;
        }
        case GPRS_CMD_CPIN_REQ:
        {
            MC20_CMD_Send(MC20_CMD_CPIN_BUF,strlen(MC20_CMD_CPIN_BUF));            
            core_status_machine =(GPRS_CMD_CPIN_RESP);
            atcmd_time_record = OS_Clock_GetSystemClock();
            DEBUG("--cmd-CPIN\r\n");
            break;
        }
        case GPRS_CMD_CPIN_RESP:
        {
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char*)rev_buf_temp,"+CPIN: READY") > 0)
                {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_CPIN_RESP,Rev_Pass);
                    DEBUG("--rev-CPIN-pass\r\n");
                }
                else
                {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_CPIN_RESP,Rev_Error);
                    DEBUG("--rev-CPIN-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_3000MS)
            {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_CPIN_RESP,Rev_Timeout);
                    DEBUG("--rev-CPIN-TIMOUT\r\n");
            }
          
            break;
        }
        case GPRS_CMD_CSQ_REQ:
        {
            MC20_CMD_Send(MC20_CMD_CSQ_BUF,strlen(MC20_CMD_CSQ_BUF));            
            core_status_machine =(GPRS_CMD_CSQ_RESP);
            atcmd_time_record = OS_Clock_GetSystemClock();
            DEBUG("--cmd-CSQ\r\n");
            break;
        }
        case GPRS_CMD_CSQ_RESP:
        {
			MC20_Core_Gprs_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"+CSQ") > 0)
                {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_CSQ_RESP,Rev_Pass);
                    DEBUG("--rev-CSQ-pass\r\n");
                }
                else
                {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_CSQ_RESP,Rev_Error);
                    DEBUG("--rev-CSQ-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_CSQ_RESP,Rev_Timeout);
                    DEBUG("--rev-CSQ-TIMOUT\r\n");
            }           
            break;
        }
        case GPRS_CMD_CREG_REQ:
        {
            MC20_CMD_Send(MC20_CMD_CREG_BUF,strlen(MC20_CMD_CREG_BUF));            
            core_status_machine =(GPRS_CMD_CREG_RESP);
            atcmd_time_record = OS_Clock_GetSystemClock();
            DEBUG("--cmd-CREG\r\n");
            break;
        }
        case GPRS_CMD_CREG_RESP:
        {
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"+CREG: 0,1") > 0)
                {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_CREG_RESP,Rev_Pass);
                    DEBUG("--rev-CREG-pass\r\n");
                }
                else
                {                    
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_CREG_RESP,Rev_Error);
                    DEBUG("--rev-CREG-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_CREG_RESP,Rev_Timeout);
                    DEBUG("--rev-CREG-TIMOUT\r\n");
            }           
            break;
        }
        case GPRS_CMD_CGREG_REQ:
        {
            MC20_CMD_Send(MC20_CMD_CGREG_BUF,strlen(MC20_CMD_CGREG_BUF));            
            core_status_machine =(GPRS_CMD_CGREG_RESP);
            atcmd_time_record = OS_Clock_GetSystemClock();
            DEBUG("--cmd-CGREG\r\n");
            break;
        }
        case GPRS_CMD_CGREG_RESP:
        {			
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"+CGREG:") > 0)
                {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_CGREG_RESP,Rev_Pass);
                    DEBUG("--rev-CGREG-pass\r\n");
                }
                else
                {
					core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_CGREG_RESP,Rev_Error);
                    DEBUG("--rev-CGREG-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_CGREG_RESP,Rev_Timeout);
                    DEBUG("--rev-CGREG-TIMOUT\r\n");
            }
            
            break;
        }
        case GPRS_CMD_QIFGCNT_REQ:
        {
            MC20_CMD_Send(MC20_CMD_QIFGCNT_BUF,strlen(MC20_CMD_QIFGCNT_BUF));            
            core_status_machine =(GPRS_CMD_QIFGCNT_RESP);
            atcmd_time_record = OS_Clock_GetSystemClock();
            DEBUG("--cmd-QIFGCNT\r\n");
            break;
        }
        case GPRS_CMD_QIFGCNT_RESP:
        {
			MC20_Core_Gprs_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIFGCNT_RESP,Rev_Pass);
                    DEBUG("--rev-QIFGCNT-pass\r\n");
                }
                else
                {
					core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIFGCNT_RESP,Rev_Error);
                    DEBUG("--rev-QIFGCNT-pass\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIFGCNT_RESP,Rev_Timeout);
                    DEBUG("--rev-QIFGCNT-pass\r\n");
            }
           
            break;
        }
        case GPRS_CMD_QICSGP_REQ:
        {
            MC20_CMD_Send(MC20_CMD_QICSGP_BUF,strlen(MC20_CMD_QICSGP_BUF));            
            core_status_machine =(GPRS_CMD_QICSGP_RESP);
            atcmd_time_record = OS_Clock_GetSystemClock();
            DEBUG("--cmd-QICSGP\r\n");
            break;
        }
        case GPRS_CMD_QICSGP_RESP:
        {
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QICSGP_RESP,Rev_Pass);
                    DEBUG("--rev-QICSGP-pass\r\n");
                }
                else
                {
					core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QICSGP_RESP,Rev_Error);
                    DEBUG("--rev-QICSGP-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QICSGP_RESP,Rev_Timeout);
                    DEBUG("--rev-QICSGP-TIMOUT\r\n");
            }
            
            break;
        }
        case GPRS_CMD_QIDEAT_REQ:
        {
            MC20_CMD_Send(MC20_CMD_QIDEACT_BUF,strlen(MC20_CMD_QIDEACT_BUF));            
            core_status_machine =(GPRS_CMD_QIDEAT_RESP);
            atcmd_time_record = OS_Clock_GetSystemClock();
            DEBUG("--cmd-QIDACT\r\n");
            break;
        }
        case GPRS_CMD_QIDEAT_RESP:
        {			
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"DEACT OK") > 0)
                {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIDEAT_RESP, Rev_Pass);
                    DEBUG("--rev-QIDEACT-pass\r\n");
                }
                else
                {
					core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIDEAT_RESP, Rev_Error);
                    DEBUG("--rev-QIDEACT-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_40000MS)
            {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIDEAT_RESP, Rev_Timeout);
                    DEBUG("--rev-QIDEAVT-TIMOUT\r\n");
            }
            
            break;
        }
        case GPRS_CMD_QIMODE_REQ:
        {
            MC20_CMD_Send(MC20_CMD_QIMODE_BUF,strlen(MC20_CMD_QIMODE_BUF));            
            core_status_machine =(GPRS_CMD_QIMODE_RESP);
            atcmd_time_record = OS_Clock_GetSystemClock();
            DEBUG("--cmd-QIMODE\r\n");
            break;
        }
        case GPRS_CMD_QIMODE_RESP:
        {
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIMODE_RESP, Rev_Pass);
                    DEBUG("--rev-QIMODE-pass\r\n");
                }
                else
                {
					core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIMODE_RESP, Rev_Error);
                    DEBUG("--rev-QIMODE-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIMODE_RESP, Rev_Timeout);
                    DEBUG("--rev-QIMODE-TIMOUT\r\n");
            }
            
            break;
        }
        case GPRS_CMD_QIMUX_REQ:
        {
            MC20_CMD_Send(MC20_CMD_QIMUX_BUF,strlen(MC20_CMD_QIMUX_BUF));            
            core_status_machine =(GPRS_CMD_QIMUX_RESP);
            atcmd_time_record = OS_Clock_GetSystemClock();
            DEBUG("--cmd-QIMUX\r\n");
            break;
        }
        case GPRS_CMD_QIMUX_RESP:
        {
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIMUX_RESP, Rev_Pass);
                    DEBUG("--rev-QIMUX-pass\r\n");
                }
                else
                {
					core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIMUX_RESP, Rev_Error);
                    DEBUG("--rev-QIMUX-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIMUX_RESP, Rev_Timeout);
                    DEBUG("--rev-QIMUX-TIMOUT\r\n");
            }
            
            break;
        }
        case GPRS_CMD_QIREGAPP_REQ:
        {
            MC20_CMD_Send(MC20_CMD_QIREGAPP_BUF,strlen(MC20_CMD_QIREGAPP_BUF));            
            core_status_machine =(GPRS_CMD_QIREGAPP_RESP);
            atcmd_time_record = OS_Clock_GetSystemClock();
            DEBUG("--cmd-QIREGAPP\r\n");
            break;
        }
        case GPRS_CMD_QIREGAPP_RESP:
        {
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIREGAPP_RESP, Rev_Pass);
                    DEBUG("--rev-QIREGAPP-pass\r\n");
                }
                else
                {
					core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIREGAPP_RESP, Rev_Error);
                    DEBUG("--rev-QIREGAPP-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIREGAPP_RESP, Rev_Timeout);
                    DEBUG("--rev-QIREGAPP-TIMOUT\r\n");
            }
            
            break;
        }
        case GPRS_CMD_QIACT_REQ:
        {
            MC20_CMD_Send(MC20_CMD_QIACT_BUF,strlen(MC20_CMD_QIACT_BUF));            
            core_status_machine =(GPRS_CMD_QIACT_RESP);
            atcmd_time_record = OS_Clock_GetSystemClock();
            DEBUG("--cmd-QIACT\r\n");
            break;
        }
        case GPRS_CMD_QIACT_RESP:
        {
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIACT_RESP, Rev_Pass);

                    DEBUG("--rev-QIACT-pass\r\n");
                }
                else
                {
					core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIACT_RESP, Rev_Error);

                    DEBUG("--rev-QIACT-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_60000MS)
            {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIACT_RESP, Rev_Timeout);
                    DEBUG("--rev-QIACT-TIMOUT\r\n");
            }
            
            break;
        }
        case GPRS_CMD_QILOCIP_REQ:
        {
            MC20_CMD_Send(MC20_CMD_QILOCIP_BUF,strlen(MC20_CMD_QILOCIP_BUF));            
            core_status_machine =(GPRS_CMD_QILOCIP_RESP);
            atcmd_time_record = OS_Clock_GetSystemClock();
            DEBUG("--cmd-QILOCIP\r\n");
            break;
        }
        case GPRS_CMD_QILOCIP_RESP:
        {
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,".") > 0)
                {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QILOCIP_RESP, Rev_Pass);
                    DEBUG("--rev-QILOCIP-pass\r\n");
                }
                else
                {
					core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QILOCIP_RESP, Rev_Error);
                    DEBUG("--rev-QILOCIP-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QILOCIP_RESP, Rev_Timeout);
                    DEBUG("--rev-QILOCIP-TIMOUT\r\n");
            }
            
            break;
        }
        case GPRS_CMD_QIDNSIP_IP_REQ:
        {
            MC20_CMD_Send(MC20_CMD_QIDNSIP_IP_BUF,strlen(MC20_CMD_QIDNSIP_IP_BUF));            
            core_status_machine =(GPRS_CMD_QIDNSIP_IP_RESP);
            atcmd_time_record = OS_Clock_GetSystemClock();
            DEBUG("--cmd-QIDNSIP_IP\r\n");
            break;
        }
        case GPRS_CMD_QIDNSIP_IP_RESP:
        {
			MC20_Core_Gprs_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIDNSIP_IP_RESP, Rev_Pass);
                    DEBUG("--rev-QIDNSIP_IP-pass\r\n");
                }
                else
                {
					core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIDNSIP_IP_RESP, Rev_Error);
                    DEBUG("--rev-QIDNSIP_IP-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIDNSIP_IP_RESP, Rev_Timeout);
                    DEBUG("--rev-QIDNSIP_IP-TIMOUT\r\n");
            }
            
            break;
        }
        case GPRS_CMD_QIDNSIP_DOMAIN_REQ:
        {
            MC20_CMD_Send(MC20_CMD_QIDNSIP_DOMAIN_BUF,strlen(MC20_CMD_QIDNSIP_DOMAIN_BUF));            
            core_status_machine =(GPRS_CMD_QIDNSIP_DOMAIN_RESP);
            atcmd_time_record = OS_Clock_GetSystemClock();
            DEBUG("--cmd-QIDNSIP_DOMAIN\r\n");
            break;
        }
        case GPRS_CMD_QIDNSIP_DOMAIN_RESP:
        {
			MC20_Core_Gprs_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIDNSIP_DOMAIN_RESP, Rev_Pass);
                    DEBUG("--rev-QIDNSIP_DOMAIN-pass\r\n");
                }
                else
                {
					core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIDNSIP_DOMAIN_RESP, Rev_Error);
                    DEBUG("--rev-QIDNSIP_DOMAIN-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIDNSIP_DOMAIN_RESP, Rev_Timeout);
                    DEBUG("--rev-QIDNSIP_DOMAIN-TIMOUT\r\n");
            }
            
            break;
        }
        case GPRS_CMD_QIHEAD_REQ:
        {
            MC20_CMD_Send(MC20_CMD_QIHEAD_BUF,strlen(MC20_CMD_QIHEAD_BUF));            
            core_status_machine =(GPRS_CMD_QIHEAD_RESP);
            atcmd_time_record = OS_Clock_GetSystemClock();
            DEBUG("--cmd-QIHEAD\r\n");
            break;
        }
        case GPRS_CMD_QIHEAD_RESP:
        {
			MC20_Core_Gprs_RevStatus_To_Be(Rev_Wait);
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"OK") > 0)
                {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIHEAD_RESP, Rev_Pass);
                    DEBUG("--rev-QIHEAD-pass\r\n");
                }
                else
                {
					core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIHEAD_RESP, Rev_Error);
                    DEBUG("--rev-QIHEAD-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_300MS)
            {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIHEAD_RESP, Rev_Timeout);
                    DEBUG("--rev-QIHEAD-TIMOUT\r\n");
            }            
            break;
        }
        case GPRS_CMD_QIOPEN_REQ:
        {
            sprintf(MC20_CMD_QIOPEN_USER_BUF, "AT+QIOPEN=\"TCP\",\"%d.%d.%d.%d\",\"%d\"\r\n", \
            g_MC20Parameter_Config.ip[0],g_MC20Parameter_Config.ip[1],g_MC20Parameter_Config.ip[2],g_MC20Parameter_Config.ip[3],g_MC20Parameter_Config.port);
            MC20_CMD_Send(MC20_CMD_QIOPEN_USER_BUF,strlen(MC20_CMD_QIOPEN_USER_BUF));            
            core_status_machine =(GPRS_CMD_QIOPEN_RESP);
            atcmd_time_record = OS_Clock_GetSystemClock();
            DEBUG("--cmd-QIOPEN\r\n");
            break;
        }
        case GPRS_CMD_QIOPEN_RESP:
        {
            if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
            {
                MC20_ATcmdMsg_Out_From_Queue(rev_buf_temp,&rev_buf_len); 
                DEBUG("rev:%s\r\n",rev_buf_temp);  
                if (strstr((char *)rev_buf_temp,"CONNECT") > 0)
                {
                    if ((strstr((char *)rev_buf_temp,"OK"))> 0||(strstr((char *)rev_buf_temp,"ALREADY")))
                    {
                        core_status_machine =(MC20_IDLE);
                        MC20_GPRS_Order(GPRS_CMD_QIOPEN_RESP, Rev_Pass);
                        DEBUG("--rev-QIOPEN-pass\r\n");
                    }
                    else
                    {
                        core_status_machine =(MC20_IDLE);
                        MC20_GPRS_Order(GPRS_CMD_QIOPEN_RESP, Rev_Error);
                        DEBUG("--rev-QIOPEN-pass\r\n");
                    }
                }
                else
                {
					//mc20_core_status_to_be(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIOPEN_RESP, Rev_Timeout);
                    DEBUG("--rev-QIOPEN-ERROR\r\n");
                }
            }
            else if ((OS_Clock_GetSystemClock() - atcmd_time_record) > MC20_TIMEOUT_60000MS)
            {
                    core_status_machine =(MC20_IDLE);
                    MC20_GPRS_Order(GPRS_CMD_QIOPEN_RESP, Rev_Timeout);
                    DEBUG("--rev-QIOPEN-ERROR\r\n");
            }
            
            break;
        }
        
        default:break;
    }
/*

*/

	memcpy(rev_buf_temp,0,20);
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

