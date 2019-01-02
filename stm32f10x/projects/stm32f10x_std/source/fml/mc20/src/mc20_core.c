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
typedef struct
{
    uint8_t Core_status;
    uint8_t Gprs_status;
    uint8_t BT_Status;
}MC20_Func_Status_t;
/**
 * @}
 */

/**
 * @defgroup      mc20_core_Private_Variables 
 * @brief         
 * @{  
 */
MC20_Func_Status_t s_MC20_Func_Status=
{
    .BT_Status=0,
    .Core_status=0,
    .Gprs_status=0,
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

/**
 * @}
 */

/**
 * @defgroup      mc20_core_Functions 
 * @brief         
 * @{  
 */
void MC20_Core_Loop_process(void)
{
    static uint16_t cmd_timeout_record = 0;
    static uint8_t cmd_count_record = 0;
    uint8_t rev_buf_temp[20] = {0};
    uint8_t rev_buf_len_temp = 0;
    if (s_MC20_Func_Status.Core_status == MC20_IDLE)//check current mc20-module status is idel?               
    {
        if (MC20_ATcmd_Queue_Get_Count() > 0 )
        {
            s_MC20_Func_Status.Core_status = MC20_ATcmd_Out_From_Queue();
        }
    }

    switch (s_MC20_Func_Status.Core_status)
    {
        case MC20_IDLE:
        {              
                cmd_timeout_record = 0;
                break;
        }
        case MC20_CMD_AT:
        {
                MC20_CMD_Send(MC20_CMD_AT_BUF,sizeof(MC20_CMD_AT_BUF));
                cmd_timeout_record = OS_Clock_GetSystemClock();
                s_MC20_Func_Status.Core_status = MC20_CMD_AT_Resp;
                break;
        }
        case MC20_CMD_AT_Resp:
        {
                    
                if (MC20_Msg_Queue_Get_Count())
                {
                    MC20_Msg_Out_From_Queue(rev_buf_temp,&rev_buf_len_temp);
                    if (strstr(rev_buf_temp, "OK") > 0)
                    {              
                        cmd_count_record = 0;          
                        s_MC20_Func_Status.Gprs_status = MC20_CMD_ATE;
                    }
                    else
                    {
                        s_MC20_Func_Status.Gprs_status = MC20_CMD_AT;                                           
                    }
                    s_MC20_Func_Status.Core_status  = MC20_IDLE;
                }

                if (OS_Clock_GetSystemClock() - cmd_timeout_record > 100)
                {
                    s_MC20_Func_Status.Gprs_status = MC20_CMD_AT;
                    s_MC20_Func_Status.Core_status  = MC20_IDLE;
                }    
                if (s_MC20_Func_Status.Gprs_status == MC20_CMD_AT)
                {
                    cmd_count_record ++;    
                }
                if (cmd_count_record > 5)
                {
                    cmd_count_record = 0;
                    MC20_Module_Restart();
                }
                break;
        }
        case MC20_CMD_ATE:
        {
                MC20_CMD_Send(MC20_CMD_ATE_BUF,sizeof(MC20_CMD_ATE_BUF));
                cmd_timeout_record = OS_Clock_GetSystemClock(void);
                s_MC20_Func_Status.Core_status = MC20_CMD_ATE_Resp;
                break;
        }
        case MC20_CMD_ATE_Resp:
        {
                if (MC20_Msg_Queue_Get_Count())
                {
                    MC20_Msg_Out_From_Queue(rev_buf_temp,&rev_buf_len_temp);
                    if (strstr(rev_buf_temp, "OK") > 0)
                    {          
                        cmd_count_record = 0;                  
                        s_MC20_Func_Status.Gprs_status = MC20_CMD_CPIN;
                    }
                    else
                    {
                        s_MC20_Func_Status.Gprs_status = MC20_CMD_ATE;                  
                    }
                    s_MC20_Func_Status.Core_status  = MC20_IDLE;
                }

                if (OS_Clock_GetSystemClock() - cmd_timeout_record > 100)
                {
                    s_MC20_Func_Status.Gprs_status = MC20_CMD_ATE;
                    s_MC20_Func_Status.Core_status  = MC20_IDLE;
                }      
                if (s_MC20_Func_Status.Gprs_status == MC20_CMD_ATE)
                {
                    cmd_count_record ++;    
                }
                if (cmd_count_record > 5)
                {
                    cmd_count_record = 0;
                    MC20_Module_Restart();
                }                           
                break;
        }
        case MC20_CMD_IPR:
        {
                MC20_CMD_Send(MC20_CMD_IPR_BUF,sizeof(MC20_CMD_IPR_BUF));
                cmd_timeout_record = OS_Clock_GetSystemClock(void);
                s_MC20_Func_Status.Core_status = MC20_CMD_IPR_Resp;
                break;
        }
        case MC20_CMD_IPR_Resp:
        {
              
                break;
        }
        case MC20_CMD_CPIN:
        {
                MC20_CMD_Send(MC20_CMD_CPIN_BUF,sizeof(MC20_CMD_CPIN_BUF));
                cmd_timeout_record = OS_Clock_GetSystemClock(void);
                s_MC20_Func_Status.Core_status = MC20_CMD_CPIN_Resp;
                break;
        }
        case MC20_CMD_CPIN_Resp:
        {
                if (MC20_Msg_Queue_Get_Count())
                {
                    MC20_Msg_Out_From_Queue(rev_buf_temp,&rev_buf_len_temp);
                    if (strstr(rev_buf_temp, "READY") > 0)
                    {                        
                        cmd_count_record = 0;  
                        s_MC20_Func_Status.Gprs_status = MC20_CMD_CSQ;
                    }
                    else
                    {
                        s_MC20_Func_Status.Gprs_status = MC20_CMD_CPIN;                  
                    }
                    s_MC20_Func_Status.Core_status  = MC20_IDLE;
                }

                if (OS_Clock_GetSystemClock() - cmd_timeout_record > 100)
                {
                    s_MC20_Func_Status.Gprs_status = MC20_CMD_CPIN;
                    s_MC20_Func_Status.Core_status  = MC20_IDLE;
                }   
                if (s_MC20_Func_Status.Gprs_status == MC20_CMD_CPIN)
                {
                    cmd_count_record ++;    
                }
                if (cmd_count_record > 5)
                {
                    cmd_count_record = 0;
                    MC20_Module_Restart();
                }                               
                break;
        }
        case MC20_CMD_CSQ:
        {
                MC20_CMD_Send(MC20_CMD_CSQ_BUF,sizeof(MC20_CMD_CSQ_BUF));
                cmd_timeout_record = OS_Clock_GetSystemClock(void);
                s_MC20_Func_Status.Core_status = MC20_CMD_CSQ_Resp;
                break;
        }
        case MC20_CMD_CSQ_Resp:
        {
                if (MC20_Msg_Queue_Get_Count())
                {
                    MC20_Msg_Out_From_Queue(rev_buf_temp,&rev_buf_len_temp);
                    if (strstr(rev_buf_temp, "CSQ") > 0)
                    {          
                        cmd_count_record = 0;                
                        s_MC20_Func_Status.Gprs_status = MC20_CMD_CREG;
                    }
                    else
                    {
                        s_MC20_Func_Status.Gprs_status = MC20_CMD_CSQ;                  
                    }
                    s_MC20_Func_Status.Core_status  = MC20_IDLE;
                }

                if (OS_Clock_GetSystemClock() - cmd_timeout_record > 50)
                {
                    s_MC20_Func_Status.Gprs_status = MC20_CMD_CSQ;
                    s_MC20_Func_Status.Core_status  = MC20_IDLE;
                }  
                if (s_MC20_Func_Status.Gprs_status == MC20_CMD_CSQ)
                {
                    cmd_count_record ++;    
                }
                if (cmd_count_record > 5)
                {
                    cmd_count_record = 0;
                    MC20_Module_Restart();
                }
                break;
        }
        case MC20_CMD_CREG:
        {
                MC20_CMD_Send(MC20_CMD_CREG_BUF,sizeof(MC20_CMD_CREG_BUF));
                cmd_timeout_record = OS_Clock_GetSystemClock(void);
                s_MC20_Func_Status.Core_status = MC20_CMD_CREG_Resp;
                break;
        }
        case MC20_CMD_CREG_Resp:
        {
                if (MC20_Msg_Queue_Get_Count())
                {
                    MC20_Msg_Out_From_Queue(rev_buf_temp,&rev_buf_len_temp);
                    if (strstr(rev_buf_temp, "OK") > 0)
                    {            
                        cmd_count_record = 0;              
                        s_MC20_Func_Status.Gprs_status = MC20_CMD_CREG;
                    }
                    else
                    {
                        s_MC20_Func_Status.Gprs_status = MC20_CMD_CGREG;                  
                    }
                    s_MC20_Func_Status.Core_status  = MC20_IDLE;
                }

                if (OS_Clock_GetSystemClock() - cmd_timeout_record > 100)
                {
                    s_MC20_Func_Status.Gprs_status = MC20_CMD_CGREG;
                    s_MC20_Func_Status.Core_status  = MC20_IDLE;
                }      
                if (s_MC20_Func_Status.Gprs_status == MC20_CMD_CGREG)
                {
                    cmd_count_record ++;    
                }
                if (cmd_count_record > 5)
                {
                    cmd_count_record = 0;
                    MC20_Module_Restart();
                }                            
                break;
        }
        case MC20_CMD_CGREG:
        {
                MC20_CMD_Send(MC20_CMD_CGREG_BUF,sizeof(MC20_CMD_CGREG_BUF));
                cmd_timeout_record = OS_Clock_GetSystemClock(void);
                s_MC20_Func_Status.Core_status = MC20_CMD_CGREG_Resp;
                break;
        }
        case MC20_CMD_CGREG_Resp:
        {
                
                break;
        }
        case MC20_CMD_QIFGCNT:
        {
                MC20_CMD_Send(MC20_CMD_QIFGCNT_BUF,sizeof(MC20_CMD_QIFGCNT_BUF));
                cmd_timeout_record = OS_Clock_GetSystemClock(void);
                s_MC20_Func_Status.Core_status = MC20_CMD_QIFGCNT_Resp;
                break;
        }
        case MC20_CMD_QIFGCNT_Resp:
        {
                if (MC20_Msg_Queue_Get_Count())
                {
                    MC20_Msg_Out_From_Queue(rev_buf_temp,&rev_buf_len_temp);
                    if (strstr(rev_buf_temp, "OK") > 0)
                    {     
                        cmd_count_record = 0;                      
                        s_MC20_Func_Status.Gprs_status = MC20_CMD_QICSGP;
                    }
                    else
                    {
                        s_MC20_Func_Status.Gprs_status = MC20_CMD_QIFGCNT;                  
                    }
                    s_MC20_Func_Status.Core_status  = MC20_IDLE;
                }

                if (OS_Clock_GetSystemClock() - cmd_timeout_record > 100)
                {
                    s_MC20_Func_Status.Gprs_status = MC20_CMD_QIFGCNT;
                    s_MC20_Func_Status.Core_status  = MC20_IDLE;
                }    
                if (s_MC20_Func_Status.Gprs_status == MC20_CMD_QIFGCNT)
                {
                    cmd_count_record ++;    
                }
                if (cmd_count_record > 5)
                {
                    cmd_count_record = 0;
                    MC20_Module_Restart();
                }               
                              
                break;
        }
        case MC20_CMD_QICSGP:
        {
                MC20_CMD_Send(MC20_CMD_QICSGP_BUF,sizeof(MC20_CMD_QICSGP_BUF));
                cmd_timeout_record = OS_Clock_GetSystemClock(void);
                s_MC20_Func_Status.Core_status = MC20_CMD_QICSGP_Resp;
                break;
        }
        case MC20_CMD_QICSGP_Resp:
        {
               
                break;
        }
        case MC20_CMD_QIDEACT:
        {
                MC20_CMD_Send(MC20_CMD_QIDEACT_BUF,sizeof(MC20_CMD_QIDEACT_BUF));
                cmd_timeout_record = OS_Clock_GetSystemClock(void);
                s_MC20_Func_Status.Core_status = MC20_CMD_QIDEACT_Resp;
                break;
        }
        case MC20_CMD_QIDEACT_Resp:
        {
                if (MC20_Msg_Queue_Get_Count())
                {
                    MC20_Msg_Out_From_Queue(rev_buf_temp,&rev_buf_len_temp);
                    if (strstr(rev_buf_temp, "OK") > 0)
                    {                        
                        cmd_count_record = 0;   
                        s_MC20_Func_Status.Gprs_status = MC20_CMD_QIMODE;
                    }
                    else
                    {
                        s_MC20_Func_Status.Gprs_status = MC20_CMD_QIDEACT;                  
                    }
                    s_MC20_Func_Status.Core_status  = MC20_IDLE;
                }

                if (OS_Clock_GetSystemClock() - cmd_timeout_record > 100)
                {
                    s_MC20_Func_Status.Gprs_status = MC20_CMD_QIDEACT;
                    s_MC20_Func_Status.Core_status  = MC20_IDLE;
                }  
                if (s_MC20_Func_Status.Gprs_status == MC20_CMD_QIDEACT)
                {
                    cmd_count_record ++;    
                }
                if (cmd_count_record > 5)
                {
                    cmd_count_record = 0;
                    MC20_Module_Restart();
                }                                
                break;
        }
        case MC20_CMD_QIMODE:
        {
                MC20_CMD_Send(MC20_CMD_QIMODE_BUF,sizeof(MC20_CMD_QIMODE_BUF));
                cmd_timeout_record = OS_Clock_GetSystemClock(void);
                s_MC20_Func_Status.Core_status = MC20_CMD_QIMODE_Resp;
                break;
        }
        case MC20_CMD_QIMODE_Resp:
        {
                if (MC20_Msg_Queue_Get_Count())
                {
                    MC20_Msg_Out_From_Queue(rev_buf_temp,&rev_buf_len_temp);
                    if (strstr(rev_buf_temp, "OK") > 0)
                    {           
                        cmd_count_record = 0;               
                        s_MC20_Func_Status.Gprs_status = MC20_CMD_QIMUX;
                    }
                    else
                    {
                        s_MC20_Func_Status.Gprs_status = MC20_CMD_QIMODE;                  
                    }
                    s_MC20_Func_Status.Core_status  = MC20_IDLE;
                }

                if (OS_Clock_GetSystemClock() - cmd_timeout_record > 50)
                {
                    s_MC20_Func_Status.Gprs_status = MC20_CMD_QIMODE;
                    s_MC20_Func_Status.Core_status  = MC20_IDLE;
                }
                if (s_MC20_Func_Status.Gprs_status == MC20_CMD_QIMODE)
                {
                    cmd_count_record ++;    
                }
                if (cmd_count_record > 5)
                {
                    cmd_count_record = 0;
                    MC20_Module_Restart();
                }                                  
                break;
        }
        case MC20_CMD_QIMUX:
        {
                MC20_CMD_Send(MC20_CMD_QIMUX_BUF,sizeof(MC20_CMD_QIMUX_BUF));
                cmd_timeout_record = OS_Clock_GetSystemClock(void);
                s_MC20_Func_Status.Core_status = MC20_CMD_QIMUX_Resp;
                break;
        }
        case MC20_CMD_QIMUX_Resp:
        {
                if (MC20_Msg_Queue_Get_Count())
                {
                    MC20_Msg_Out_From_Queue(rev_buf_temp,&rev_buf_len_temp);
                    if (strstr(rev_buf_temp, "OK") > 0)
                    {                  
                        cmd_count_record = 0;        
                        s_MC20_Func_Status.Gprs_status = MC20_CMD_QIREGAPP;
                    }
                    else
                    {
                        s_MC20_Func_Status.Gprs_status = MC20_CMD_QIMUX;                  
                    }
                    s_MC20_Func_Status.Core_status  = MC20_IDLE;
                }

                if (OS_Clock_GetSystemClock() - cmd_timeout_record > 50)
                {
                    s_MC20_Func_Status.Gprs_status = MC20_CMD_QIMUX;
                    s_MC20_Func_Status.Core_status  = MC20_IDLE;
                }  
                if (s_MC20_Func_Status.Gprs_status == MC20_CMD_QIMUX)
                {
                    cmd_count_record ++;    
                }
                if (cmd_count_record > 5)
                {
                    cmd_count_record = 0;
                    MC20_Module_Restart();
                }                                
                break;
        }
        case MC20_CMD_QIREGAPP:
        {
                MC20_CMD_Send(MC20_CMD_QIREGAPP_BUF,sizeof(MC20_CMD_QIREGAPP_BUF));
                cmd_timeout_record = OS_Clock_GetSystemClock(void);
                s_MC20_Func_Status.Core_status = MC20_CMD_QIREGAPP_Resp;
                break;
        }
        case MC20_CMD_QIREGAPP_Resp:
        {
                if (MC20_Msg_Queue_Get_Count())
                {
                    MC20_Msg_Out_From_Queue(rev_buf_temp,&rev_buf_len_temp);
                    if (strstr(rev_buf_temp, "OK") > 0)
                    {        
                        cmd_count_record = 0;                        
                        s_MC20_Func_Status.Gprs_status = MC20_CMD_QIACT;
                    }
                    else
                    {
                        s_MC20_Func_Status.Gprs_status = MC20_CMD_QIREGAPP;                  
                    }
                    s_MC20_Func_Status.Core_status  = MC20_IDLE;
                }

                if (OS_Clock_GetSystemClock() - cmd_timeout_record > 50)
                {
                    s_MC20_Func_Status.Gprs_status = MC20_CMD_QIREGAPP;
                    s_MC20_Func_Status.Core_status  = MC20_IDLE;
                } 
                if (s_MC20_Func_Status.Gprs_status == MC20_CMD_QIREGAPP)
                {
                    cmd_count_record ++;    
                }
                if (cmd_count_record > 5)
                {
                    cmd_count_record = 0;
                    MC20_Module_Restart();
                }                                 
                break;
        }
        case MC20_CMD_QIACT:
        {
                MC20_CMD_Send(MC20_CMD_QIACT_BUF,sizeof(MC20_CMD_QIACT_BUF));
                cmd_timeout_record = OS_Clock_GetSystemClock(void);
                s_MC20_Func_Status.Core_status = MC20_CMD_QIACT_Resp;
                break;
        }
        case MC20_CMD_QIACT_Resp:
        {
                if (MC20_Msg_Queue_Get_Count())
                {
                    MC20_Msg_Out_From_Queue(rev_buf_temp,&rev_buf_len_temp);
                    if (strstr(rev_buf_temp, "OK") > 0)
                    {             
                        cmd_count_record = 0;             
                        s_MC20_Func_Status.Gprs_status = MC20_CMD_QILOCIP;
                    }
                    else
                    {
                        s_MC20_Func_Status.Gprs_status = MC20_CMD_QIACT;                  
                    }
                    s_MC20_Func_Status.Core_status  = MC20_IDLE;
                }

                if (OS_Clock_GetSystemClock() - cmd_timeout_record > 50)
                {
                    s_MC20_Func_Status.Gprs_status = MC20_CMD_QIACT;
                    s_MC20_Func_Status.Core_status  = MC20_IDLE;
                }      
                if (s_MC20_Func_Status.Gprs_status == MC20_CMD_QIACT)
                {
                    cmd_count_record ++;    
                }
                if (cmd_count_record > 5)
                {
                    cmd_count_record = 0;
                    MC20_Module_Restart();
                }            
                break;
        }
        case MC20_CMD_QILOCIP:
        {
                MC20_CMD_Send(MC20_CMD_QILOCIP_BUF,sizeof(MC20_CMD_QILOCIP_BUF));
                cmd_timeout_record = OS_Clock_GetSystemClock(void);
                s_MC20_Func_Status.Core_status = MC20_CMD_QILOCIP_Resp;
                break;
        }
        case MC20_CMD_QILOCIP_Resp:
        {
                if (MC20_Msg_Queue_Get_Count())
                {
                    MC20_Msg_Out_From_Queue(rev_buf_temp,&rev_buf_len_temp);
                    if (strstr(rev_buf_temp, ".") > 0)
                    {   
                                             
                        s_MC20_Func_Status.Gprs_status = MC20_CMD_QIDNSIP_IP;
                    }
                    else
                    {
                        s_MC20_Func_Status.Gprs_status = MC20_CMD_QILOCIP;                  
                    }
                    s_MC20_Func_Status.Core_status  = MC20_IDLE;
                }

                if (OS_Clock_GetSystemClock() - cmd_timeout_record > 50)
                {
                    s_MC20_Func_Status.Gprs_status = MC20_CMD_QILOCIP;
                    s_MC20_Func_Status.Core_status  = MC20_IDLE;
                }   
                if (s_MC20_Func_Status.Gprs_status == MC20_CMD_QILOCIP)
                {
                    cmd_count_record ++;    
                }
                if (cmd_count_record > 5)
                {
                    cmd_count_record = 0;
                    MC20_Module_Restart();
                }                              
                break;
        }
        case MC20_CMD_QIDNSIP_IP:
        {
                MC20_CMD_Send(MC20_CMD_QIDNSIP_IP_BUF,sizeof(MC20_CMD_QIDNSIP_IP_BUF));
                cmd_timeout_record = OS_Clock_GetSystemClock(void);
                s_MC20_Func_Status.Core_status = MC20_CMD_QIDNSIP_IP_Resp;
                break;
        }
        case MC20_CMD_QIDNSIP_IP_Resp:
        {
           
                break;
        }
        case MC20_CMD_QIDNSIP_DOMAIN:
        {
                MC20_CMD_Send(MC20_CMD_QIDNSIP_DOMAIN_BUF,sizeof(MC20_CMD_QIDNSIP_DOMAIN_BUF));
                cmd_timeout_record = OS_Clock_GetSystemClock(void);
                s_MC20_Func_Status.Core_status = MC20_CMD_QIDNSIP_DOMAIN_Resp;
                break;
        }
        case MC20_CMD_QIDNSIP_DOMAIN_Resp:
        {
          
                break;
        }
        case MC20_CMD_QIHEAD:
        {
                MC20_CMD_Send(MC20_CMD_QIHEAD_BUF,sizeof(MC20_CMD_QIHEAD_BUF));
                cmd_timeout_record = OS_Clock_GetSystemClock(void);
                s_MC20_Func_Status.Core_status = MC20_CMD_QIHEAD_Resp;
                break;
        }
        case MC20_CMD_QIHEAD_Resp:
        {
                 
                break;
        }
        case MC20_CMD_QIOPEN:
        {
                MC20_CMD_Send(MC20_CMD_QIOPEN_BUF,sizeof(MC20_CMD_QIOPEN_BUF));
                cmd_timeout_record = OS_Clock_GetSystemClock(void);
                s_MC20_Func_Status.Core_status = MC20_CMD_QIOPEN_Resp;
                break;
        }
        case MC20_CMD_QIOPEN_Resp:
        {
                if (MC20_Msg_Queue_Get_Count()==2)
                {
                    MC20_Msg_Out_From_Queue(rev_buf_temp,&rev_buf_len_temp);
                    MC20_Msg_Out_From_Queue(rev_buf_temp,&rev_buf_len_temp);
                    if (strstr(rev_buf_temp, "OK") > 0)
                    {                        
                        cmd_count_record = 0;     
                    }
                    else
                    {
                        s_MC20_Func_Status.Gprs_status = MC20_CMD_QIOPEN;                  
                    }
                    s_MC20_Func_Status.Core_status  = MC20_IDLE;
                }

                if (OS_Clock_GetSystemClock() - cmd_timeout_record > 500)
                {
                    s_MC20_Func_Status.Gprs_status = MC20_CMD_QIOPEN;
                    s_MC20_Func_Status.Core_status  = MC20_IDLE;
                }         
                if (s_MC20_Func_Status.Gprs_status == MC20_CMD_QIOPEN)
                {
                    cmd_count_record ++;    
                }
                if (cmd_count_record > 5)
                {
                    cmd_count_record = 0;
                    MC20_Module_Restart();
                }                         
                break;
        }
        case MC20_CMD_QISEND
        {
                MC20_CMD_Send(MC20_CMD_QISEND_BUF,sizeof(MC20_CMD_QISEND_BUF));
                cmd_timeout_record = OS_Clock_GetSystemClock(void);
                s_MC20_Func_Status.Core_status = MC20_CMD_QISEND_Resp;
                break;
        }
        case MC20_CMD_QISEND_Resp:
        {
                if (MC20_Msg_Queue_Get_Count())
                {
                    MC20_Msg_Out_From_Queue(rev_buf_temp,&rev_buf_len_temp);
                    if (strstr(rev_buf_temp, ">") > 0)
                    {                        
                        cmd_count_record = 0; 
                    }
                    else
                    {
                        s_MC20_Func_Status.Gprs_status = MC20_CMD_QISEND;                  
                    }
                    s_MC20_Func_Status.Core_status  = MC20_IDLE;
                }

                if (OS_Clock_GetSystemClock() - cmd_timeout_record > 50)
                {
                    s_MC20_Func_Status.Gprs_status = MC20_CMD_QISEND;
                    s_MC20_Func_Status.Core_status  = MC20_IDLE;
                }       
                if (s_MC20_Func_Status.Gprs_status == MC20_CMD_QISEND)
                {
                    cmd_count_record ++;    
                }
                if (cmd_count_record > 5)
                {
                    cmd_count_record = 0;
                    MC20_Module_Restart();
                }                           
                break;
        }
        case MC20_CMD_QISACK:
        {
                MC20_CMD_Send(MC20_CMD_QISACK_BUF,sizeof(MC20_CMD_QISACK_BUF));
                cmd_timeout_record = OS_Clock_GetSystemClock(void);
                s_MC20_Func_Status.Core_status = MC20_CMD_QISACK_Resp;
                break;
        }
        case MC20_CMD_QISACK_Resp:
        {
            
                break;
        }
        default:break;
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

