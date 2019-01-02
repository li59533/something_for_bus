/**
 **************************************************************************************************
 * @file        mc20_app.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "mc20_app.h"
#include "mc20_port.h"
#include "mc20_core.h"
#include "mc20_task.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    mc20_app_Modules 
 * @{  
 */

/**
 * @defgroup      mc20_app_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_app_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_app_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_app_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_app_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_app_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_app_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      mc20_app_Functions 
 * @brief         
 * @{  
 */
void MC20_Module_Init(void)
{
    MC20_Hal_Init();
    MC20_Module_Restart();
}

void MC20_Gprs_Start(void)
{
    MC20Task_Send_Event(MC20_TASK_GPRS_EVENT);
}

void MC20_Gprs_Loop_Process(void)
{
    switch (s_MC20_Func_Status.Gprs_status)
    {
        case MC20_CMD_AT:
        {
            s_MC20_Func_Status.Gprs_status = MC20_CMD_AT_Resp;
            MC20_ATcmd_In_to_Queue(MC20_CMD_AT);
            break;
        }
        case MC20_CMD_AT_Resp:break;
        case MC20_CMD_ATE:
        {
            s_MC20_Func_Status.Gprs_status = MC20_CMD_ATE_Resp;
            MC20_ATcmd_In_to_Queue(MC20_CMD_ATE);
            break;
        }
        case MC20_CMD_ATE_Resp:break;
        case MC20_CMD_CPIN:
        {
            s_MC20_Func_Status.Gprs_status = MC20_CMD_CPIN_Resp;
            MC20_ATcmd_In_to_Queue(MC20_CMD_CPIN);
            break;
        }       
        case MC20_CMD_CPIN_Resp:break;
        case MC20_CMD_CSQ:
        {
            s_MC20_Func_Status.Gprs_status = MC20_CMD_CSQ_Resp;
            MC20_ATcmd_In_to_Queue(MC20_CMD_CSQ);
            break;
        }  
        case MC20_CMD_CSQ_Resp:break;
        case MC20_CMD_CREG:
        {
            s_MC20_Func_Status.Gprs_status = MC20_CMD_CREG_Resp;
            MC20_ATcmd_In_to_Queue(MC20_CMD_CREG);
            break;
        }  
        case MC20_CMD_CREG_Resp:break;
        case MC20_CMD_QIFGCNT:
        {
            s_MC20_Func_Status.Gprs_status = MC20_CMD_QIFGCNT_Resp;
            MC20_ATcmd_In_to_Queue(MC20_CMD_QIFGCNT);
            break;
        }  
        case MC20_CMD_QIFGCNT_Resp:break;
        case MC20_CMD_QIMODE:
        {
            s_MC20_Func_Status.Gprs_status = MC20_CMD_QIMODE_Resp;
            MC20_ATcmd_In_to_Queue(MC20_CMD_QIMODE);
            break;
        }  
        case MC20_CMD_QIMODE_Resp:break;
        case MC20_CMD_QIMUX:
        {
            s_MC20_Func_Status.Gprs_status = MC20_CMD_QIMUX_Resp;
            MC20_ATcmd_In_to_Queue(MC20_CMD_QIMUX);
            break;
        }  
        case MC20_CMD_QIMUX_Resp:break;
        case MC20_CMD_QIDEACT:
        {
            s_MC20_Func_Status.Gprs_status = MC20_CMD_QIDEACT_Resp;
            MC20_ATcmd_In_to_Queue(MC20_CMD_QIDEACT);
            break;
        }  
        case MC20_CMD_QIDEACT_Resp:break;
        case MC20_CMD_QIREGAPP:
        {
            s_MC20_Func_Status.Gprs_status = MC20_CMD_QIREGAPP_Resp;
            MC20_ATcmd_In_to_Queue(MC20_CMD_QIREGAPP);
            break;
        }  
        case MC20_CMD_QIREGAPP_Resp:break;
        case MC20_CMD_QIACT:
        {
            s_MC20_Func_Status.Gprs_status = MC20_CMD_QIACT_Resp;
            MC20_ATcmd_In_to_Queue(MC20_CMD_QIACT);
            break;
        }  
        case MC20_CMD_QIACT_Resp:break;
        case MC20_CMD_QILOCIP:
        {
            s_MC20_Func_Status.Gprs_status = MC20_CMD_QILOCIP_Resp;
            MC20_ATcmd_In_to_Queue(MC20_CMD_QILOCIP);
            break;
        } 
        case MC20_CMD_QILOCIP_Resp:break;
        case MC20_CMD_QIOPEN:
        {
            s_MC20_Func_Status.Gprs_status = MC20_CMD_QIOPEN_Resp;
            MC20_ATcmd_In_to_Queue(MC20_CMD_QIOPEN);
            break;
        } 
        case MC20_CMD_QIOPEN_Resp:break;
        case MC20_CMD_QISEND:
        {
            s_MC20_Func_Status.Gprs_status = MC20_CMD_QISEND_Resp;
            MC20_ATcmd_In_to_Queue(MC20_CMD_QISEND);
            break;
        } 
        case MC20_CMD_QISEND_Resp:break;
        default:break;
    }
}
int8_t MC20_Gprs_Get_Status(void)
{
    return s_MC20_Func_Status.Gprs_status;
}


void MC20_Module_Restart(void)
{
    MC20Task_Clear_Event(MC20_TASK_GPRS_EVENT);
    MC20_ATcmd_In_to_Queue(MC20_CMD_QPOWD);
    MC20_Power_Pin_Rest();
    MC20Task_Timer_Start_Event(MC20_TASK_MODULE_RESTART_EVENT,2000);
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

