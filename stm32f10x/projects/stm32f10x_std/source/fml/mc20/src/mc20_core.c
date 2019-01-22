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
typedef enum
{   
    MC20_CHECKING = 1,
    MC20_LOADING,
    MC20_RUNNING,
    MC20_STOPPING,
}MC20_Module_Status_Enum;


typedef struct
{
    uint8_t BT;
    uint8_t gprs;
    uint8_t gps;
}mc20_func_switchstatus_t;



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

MC20_Core_Moduleconf_t mc20_core_moduleconf = 
{
    .QIDNSIP_value = 0,
    .ip = {192,168,1,1},
    .port = 0,
};
/**
 * @}
 */

/**
 * @defgroup      mc20_core_Private_Variables 
 * @brief         
 * @{  
 */
mc20_func_switchstatus_t mc20_func_switchstatus = 
{
    0,0,0,
};
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

static int8_t mc20_checking_func(void);//from at to csq 
static int8_t mc20_loading_func(void);
static void mc20_core_cmdsend(const char * cmdbuf);
static void mc20_running_func(void);
static uint8_t mc20_core_gprsAtcmd_process(uint8_t core_statusmachine,const char * checkbuf,uint32_t atcmd_timerecord,uint32_t atcmd_maxouttime);
static uint8_t mc20_core_gprsAtcmd_QIOPEN_process(uint8_t core_statusmachine,uint32_t atcmd_timerecord,uint32_t atcmd_maxouttime);
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

void MC20_Core_Gprsconf_Init(MC20_Core_Moduleconf_t * conf)
{
    mc20_core_moduleconf.QIDNSIP_value = conf->QIDNSIP_value;
    mc20_core_moduleconf.port  = conf->port;
    mc20_core_moduleconf.ip[0] = conf->ip[0];
    mc20_core_moduleconf.ip[1] = conf->ip[1];
    mc20_core_moduleconf.ip[2] = conf->ip[2];
    mc20_core_moduleconf.ip[3] = conf->ip[3];
    mc20_core_moduleconf.domian = conf->domian;


    if (mc20_core_moduleconf.QIDNSIP_value == 0)
    {
        sprintf(MC20_CMD_QIOPEN_USER_BUF,"AT+QIOPEN=\"TCP\",\"%d.%d.%d.%d\",\"%d\"\r\n",mc20_core_moduleconf.ip[0],\
                                                                                        mc20_core_moduleconf.ip[1],\
                                                                                        mc20_core_moduleconf.ip[2],\
                                                                                        mc20_core_moduleconf.ip[3],\
                                                                                        mc20_core_moduleconf.port);
    }
    else if (mc20_core_moduleconf.QIDNSIP_value == 1)
    {
        sprintf(MC20_CMD_QIOPEN_USER_BUF, "AT+QIOPEN=\"TCP\",\"%s\",\"%d\"\r\n", mc20_core_moduleconf.domian,\
                                                                                mc20_core_moduleconf.port);
    }
}


void MC20_Core_Loop(void)
{
    static uint8_t mc20_module_status = 0;
    
    switch (mc20_module_status)
    {
        case MC20_CHECKING:
        {
            if(mc20_checking_func() == 1)
            {
                mc20_module_status = MC20_LOADING;
            }
            break;
        }
        case MC20_LOADING:
        {
            if(mc20_loading_func() == 1)
            {
                mc20_module_status = MC20_RUNNING;
            }
            break;
        }
        case MC20_RUNNING:
        {
			mc20_running_func();
            break;
        }
        
        case MC20_STOPPING:
        {
                
            break;
        }
        default:break;
    }
}
static int8_t mc20_checking_func(void)//from at to csq 
{
    static uint8_t mc20_device_mactinestatus = MC20_CMD_AT_REQ;
    static uint32_t time_record = 0;
    static uint8_t req_times_record = 0;
    uint8_t rev_buf_temp[20] = {0};
    uint8_t rev_buf_len = 0;
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
                    return 1;

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
        case MC20_HAL_RESTART_REQ: 
        {
            MC20_Power_Pin_Rest();
            time_record = OS_Clock_GetSeconds();
            mc20_device_mactinestatus = MC20_HAL_RESTART_RESP;
            break;
        }
        case MC20_HAL_RESTART_RESP:
        {
            if ((OS_Clock_GetSeconds() - time_record) > 2||(time_record - OS_Clock_GetSeconds()) > 2)
            {
                MC20_Power_Pin_Set();
                mc20_device_mactinestatus = MC20_CMD_AT_REQ;
            }
            break;
        }
        default:break;
    }


    if (req_times_record > 5)
    {
        req_times_record = 0;
        mc20_device_mactinestatus = MC20_HAL_RESTART_REQ;
    }
    return -1;
}
static int8_t mc20_loading_func(void)   
{
    if ((mc20_func_switchstatus.BT + \
         mc20_func_switchstatus.gprs + \
         mc20_func_switchstatus.gps) > 0)
    {
        return 1 ;
    }
    else
    {
        return 0;
    }
}
static void mc20_running_func(void)
{
    static uint8_t core_statusmachine = MC20_IDLE;
    static uint32_t atcmd_timerecord = 0;
    switch (core_statusmachine)
    {
        case MC20_IDLE:
        {
            if (MC20_ATcmd_Queue_Get_Count() > 0)
            {
                core_statusmachine = MC20_ATcmd_DeQueue();
            }
            break;
        }
        case GPRS_CMD_CPIN_REQ:
        {
            mc20_core_cmdsend(MC20_CMD_CPIN_BUF);
            core_statusmachine = GPRS_CMD_CPIN_RESP;
            atcmd_timerecord = OS_Clock_GetSystemClock();
            break;
        }
        case GPRS_CMD_CPIN_RESP:
        {
            core_statusmachine = mc20_core_gprsAtcmd_process(core_statusmachine,\
                                                             "+CPIN: READY",\
                                                             atcmd_timerecord,\
                                                             MC20_TIMEOUT_3000MS);
            break;
        }
        case GPRS_CMD_CSQ_REQ:
        {
            mc20_core_cmdsend(MC20_CMD_CSQ_BUF);
            core_statusmachine = GPRS_CMD_CSQ_RESP;
            atcmd_timerecord = OS_Clock_GetSystemClock();
            break;
        }
        case GPRS_CMD_CSQ_RESP:
        {
            core_statusmachine = mc20_core_gprsAtcmd_process(core_statusmachine,\
                                                             "+CSQ",\
                                                             atcmd_timerecord,\
                                                             MC20_TIMEOUT_300MS);
            break;
        }
        case GPRS_CMD_CREG_REQ:
        {
            mc20_core_cmdsend(MC20_CMD_CREG_BUF);
            core_statusmachine = GPRS_CMD_CREG_RESP;
            atcmd_timerecord = OS_Clock_GetSystemClock();
            break;
        }
        case GPRS_CMD_CREG_RESP:
        {
            core_statusmachine = mc20_core_gprsAtcmd_process(core_statusmachine,\
                                                             "+CREG",\
                                                             atcmd_timerecord,\
                                                             MC20_TIMEOUT_300MS);
            break;
        }
        case GPRS_CMD_CGREG_REQ:
        {
            mc20_core_cmdsend(MC20_CMD_CGREG_BUF);
            core_statusmachine = GPRS_CMD_CGREG_RESP;
            atcmd_timerecord = OS_Clock_GetSystemClock();
            break;
        }
        case GPRS_CMD_CGREG_RESP:
        {
            core_statusmachine = mc20_core_gprsAtcmd_process(core_statusmachine,\
                                                             "+CGREG",\
                                                             atcmd_timerecord,\
                                                             MC20_TIMEOUT_300MS);
            break;
        }
        case GPRS_CMD_QIFGCNT_REQ:
        {
            mc20_core_cmdsend(MC20_CMD_QIFGCNT_BUF);
            core_statusmachine = GPRS_CMD_QIFGCNT_RESP;
            atcmd_timerecord = OS_Clock_GetSystemClock();
            break;
        }
        case GPRS_CMD_QIFGCNT_RESP:
        {
            core_statusmachine = mc20_core_gprsAtcmd_process(core_statusmachine,\
                                                             "OK",\
                                                             atcmd_timerecord,\
                                                             MC20_TIMEOUT_300MS);
            break;
        }
        case GPRS_CMD_QICSGP_REQ:
        {
            mc20_core_cmdsend(MC20_CMD_QICSGP_BUF);
            core_statusmachine = GPRS_CMD_QICSGP_RESP;
            atcmd_timerecord = OS_Clock_GetSystemClock();
            break;
        }
        case GPRS_CMD_QICSGP_RESP:
        {
            core_statusmachine = mc20_core_gprsAtcmd_process(core_statusmachine,\
                                                             "OK",\
                                                             atcmd_timerecord,\
                                                             MC20_TIMEOUT_300MS);
            break;
        }
        case GPRS_CMD_QIDEAT_REQ:
        {
            mc20_core_cmdsend(MC20_CMD_QIDEACT_BUF);
            core_statusmachine = GPRS_CMD_QIDEAT_RESP;
            atcmd_timerecord = OS_Clock_GetSystemClock();
            break;
        }
        case GPRS_CMD_QIDEAT_RESP:
        {
            core_statusmachine = mc20_core_gprsAtcmd_process(core_statusmachine,\
                                                             "OK",\
                                                             atcmd_timerecord,\
                                                             MC20_TIMEOUT_300MS);
            break;
        }
        case GPRS_CMD_QIMODE_REQ:
        {
            mc20_core_cmdsend(MC20_CMD_QIMODE_BUF);
            core_statusmachine = GPRS_CMD_QIMODE_RESP;
            atcmd_timerecord = OS_Clock_GetSystemClock();
            break;
        }
        case GPRS_CMD_QIMODE_RESP:
        {
            core_statusmachine = mc20_core_gprsAtcmd_process(core_statusmachine,\
                                                             "OK",\
                                                             atcmd_timerecord,\
                                                             MC20_TIMEOUT_300MS);
            break;
        }
        case GPRS_CMD_QIMUX_REQ:
        {           
            mc20_core_cmdsend(MC20_CMD_QIMUX_BUF);       
            core_statusmachine =(GPRS_CMD_QIMUX_RESP);
            atcmd_timerecord = OS_Clock_GetSystemClock();
            break;
        }
        case GPRS_CMD_QIMUX_RESP:
        {
            core_statusmachine = mc20_core_gprsAtcmd_process(core_statusmachine,\
                                                             "OK",\
                                                             atcmd_timerecord,\
                                                             MC20_TIMEOUT_300MS);
            break;
        }
        case GPRS_CMD_QIREGAPP_REQ:
        {
            mc20_core_cmdsend(MC20_CMD_QIREGAPP_BUF);     
            core_statusmachine =(GPRS_CMD_QIREGAPP_RESP);
            atcmd_timerecord = OS_Clock_GetSystemClock();
            break;
        }
        case GPRS_CMD_QIREGAPP_RESP:
        {
            core_statusmachine = mc20_core_gprsAtcmd_process(core_statusmachine,\
                                                             "OK",\
                                                             atcmd_timerecord,\
                                                             MC20_TIMEOUT_300MS);
            break;
        }
        case GPRS_CMD_QIACT_REQ:
        {
            mc20_core_cmdsend(MC20_CMD_QIACT_BUF);     
            core_statusmachine =(GPRS_CMD_QIACT_RESP);
            atcmd_timerecord = OS_Clock_GetSystemClock();
            break;
        }
        case GPRS_CMD_QIACT_RESP:
        {
            core_statusmachine = mc20_core_gprsAtcmd_process(core_statusmachine,\
                                                             "OK",\
                                                             atcmd_timerecord,\
                                                             MC20_TIMEOUT_300MS);
            break;
        }
        case GPRS_CMD_QILOCIP_REQ:
        {
            mc20_core_cmdsend(MC20_CMD_QILOCIP_BUF);     
            core_statusmachine =(GPRS_CMD_QILOCIP_RESP);
            atcmd_timerecord = OS_Clock_GetSystemClock();
            break;
        }
        case GPRS_CMD_QILOCIP_RESP:
        {
            core_statusmachine = mc20_core_gprsAtcmd_process(core_statusmachine,\
                                                             "OK",\
                                                             atcmd_timerecord,\
                                                             MC20_TIMEOUT_300MS);
            break;
        }
        case GPRS_CMD_QIDNSIP_IP_REQ:
        {
            mc20_core_cmdsend(MC20_CMD_QIDNSIP_IP_BUF);     
            core_statusmachine =(GPRS_CMD_QIDNSIP_IP_RESP);
            atcmd_timerecord = OS_Clock_GetSystemClock();
            break;
        }
        case GPRS_CMD_QIDNSIP_IP_RESP:
        {
            core_statusmachine = mc20_core_gprsAtcmd_process(core_statusmachine,\
                                                             "OK",\
                                                             atcmd_timerecord,\
                                                             MC20_TIMEOUT_300MS);
            break;
        }
        case GPRS_CMD_QIDNSIP_DOMAIN_REQ:
        {
            mc20_core_cmdsend(MC20_CMD_QIDNSIP_DOMAIN_BUF);     
            core_statusmachine =(GPRS_CMD_QIDNSIP_DOMAIN_REQ);
            atcmd_timerecord = OS_Clock_GetSystemClock();
            break;
        }
        case GPRS_CMD_QIDNSIP_DOMAIN_RESP:
        {
            core_statusmachine = mc20_core_gprsAtcmd_process(core_statusmachine,\
                                                             "OK",\
                                                             atcmd_timerecord,\
                                                             MC20_TIMEOUT_300MS);
            break;
        }
        case GPRS_CMD_QIHEAD_REQ:
        {
            mc20_core_cmdsend(MC20_CMD_QIHEAD_BUF);     
            core_statusmachine =(GPRS_CMD_QIHEAD_RESP);
            atcmd_timerecord = OS_Clock_GetSystemClock();
            break;
        }
        case GPRS_CMD_QIHEAD_RESP:
        {
            core_statusmachine = mc20_core_gprsAtcmd_process(core_statusmachine,\
                                                             "OK",\
                                                             atcmd_timerecord,\
                                                             MC20_TIMEOUT_300MS);
            break;
        }
        case GPRS_CMD_QIOPEN_REQ:
        {
            mc20_core_cmdsend(MC20_CMD_QIOPEN_USER_BUF);     
            core_statusmachine =(GPRS_CMD_QIOPEN_RESP);
            atcmd_timerecord = OS_Clock_GetSystemClock();
            break;
        }
        case GPRS_CMD_QIOPEN_RESP:
        {
            core_statusmachine = mc20_core_gprsAtcmd_QIOPEN_process(core_statusmachine,\
                                                                    atcmd_timerecord,\
                                                                    MC20_TIMEOUT_300MS);
            break;
        }
        default: break;
    }
}

static void mc20_core_cmdsend(const char * cmdbuf)
{
    MC20_CMD_Send(cmdbuf,strlen(cmdbuf)); 
}

static uint8_t mc20_core_gprsAtcmd_process(uint8_t core_statusmachine,const char * checkbuf,uint32_t atcmd_timerecord,uint32_t atcmd_maxouttime)
{
    uint8_t rev_buftemp[20] = { 0 };
    uint8_t rev_buflen = 0;
    if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
    {
        MC20_ATcmdMsg_Out_From_Queue(rev_buftemp,&rev_buflen); 
        DEBUG("rev:%s\r\n",rev_buftemp);  
        if (strstr((char*)rev_buftemp,checkbuf) > 0)
        {
            MC20_GPRS_Order(core_statusmachine,Rev_Pass);
        }
        else
        {
            MC20_GPRS_Order(core_statusmachine,Rev_Error);
        }
        core_statusmachine =(MC20_IDLE);
    }
    else if ((OS_Clock_GetSystemClock() - atcmd_timerecord) > atcmd_maxouttime)
    {
            MC20_GPRS_Order(core_statusmachine,Rev_Timeout);
            core_statusmachine =(MC20_IDLE);
    }
    return core_statusmachine;
}

static uint8_t mc20_core_gprsAtcmd_QIOPEN_process(uint8_t core_statusmachine,uint32_t atcmd_timerecord,uint32_t atcmd_maxouttime)
{
    uint8_t rev_buftemp[20] = { 0 };
    uint8_t rev_buflen = 0;
    if (MC20_ATcmdMsg_Queue_Get_Count() > 0)
    {
        MC20_ATcmdMsg_Out_From_Queue(rev_buftemp,&rev_buflen); 
        DEBUG("rev:%s\r\n",rev_buftemp);  

        if (strstr((char *)rev_buftemp,"CONNECT") > 0)
        {
            if ((strstr((char *)rev_buftemp,"OK"))> 0||(strstr((char *)rev_buftemp,"ALREADY")))
            {
                MC20_GPRS_Order(core_statusmachine,Rev_Pass);
                
                DEBUG("--rev-QIOPEN-pass\r\n");
            }
            else
            {
                MC20_GPRS_Order(core_statusmachine,Rev_Error);
            }
            core_statusmachine =(MC20_IDLE);
        }
        
    }
    else if ((OS_Clock_GetSystemClock() - atcmd_timerecord) > atcmd_maxouttime)
    {
            MC20_GPRS_Order(core_statusmachine,Rev_Timeout);
            core_statusmachine =(MC20_IDLE);
    }
    return core_statusmachine;
}

void MC20_Core_Func_Control(uint8_t gprs_control,uint8_t gps_control,uint8_t bt_control)
{
    if (bt_control > 0)
    {
        mc20_func_switchstatus.BT = 1;
    }else
    {
        mc20_func_switchstatus.BT = 0;
    }

    if (gprs_control > 0)
    {
        mc20_func_switchstatus.gprs = 1;
    }else
    {
        mc20_func_switchstatus.gprs = 0;
    }

    if (gps_control > 0)
    {
        mc20_func_switchstatus.gps = 1;
    }else
    {
        mc20_func_switchstatus.gps = 0;
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

