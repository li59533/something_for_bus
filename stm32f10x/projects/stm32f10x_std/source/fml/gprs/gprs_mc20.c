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
                Gprs_Process_Status.Connect_status = ;
            }
            break;
        case Gprs_Connect_ATE_Req:
            Gprs_AT_In_Queue(Gprs_CMD_ATE);
            break;
        case Gprs_Connect_ATE_Resp:
            if ()
            {
                Gprs_Process_Status.Connect_status = ;
            }
            break;
        case Gprs_Connect_IPR_Req:
            Gprs_AT_In_Queue(Gprs_CMD_IPR);
            break;
        case Gprs_Connect_IPR_Resp:
            if ()
            {
                Gprs_Process_Status.Connect_status = ;
            }
            break;
        case Gprs_Connect_CPIN_Req:
            Gprs_AT_In_Queue(Gprs_CMD_CPIN);
            break;
        case Gprs_Connect_CPIN_Resp:
            if ()
            {
                Gprs_Process_Status.Connect_status = ;
            }
            break;
        case Gprs_Connect_CSQ_Req:
            Gprs_AT_In_Queue(Gprs_CMD_CSQ);
            break;
        case Gprs_Connect_CSQ_Resp:
            if ()
            {
                Gprs_Process_Status.Connect_status = ;
            }
            break;  
        case Gprs_Connect_CREG_Req:
            Gprs_AT_In_Queue(Gprs_CMD_CREG);
            break;
        case Gprs_Connect_CREG_Resp:
            if ()
            {
                Gprs_Process_Status.Connect_status = ;
            }
            break;             
        case Gprs_Connect_CGREG_Req:
            Gprs_AT_In_Queue(Gprs_CMD_CGREG);
            break;
        case Gprs_Connect_CGREG_Resp:
            if ()
            {
                Gprs_Process_Status.Connect_status = ;
            }
            break;            
        case Gprs_Connect_QIFGCNT_Req:
            Gprs_AT_In_Queue(Gprs_CMD_QIFGCNT);
            break;
        case Gprs_Connect_QIFGCNT_Resp:
            if ()
            {
                Gprs_Process_Status.Connect_status = ;
            }
            break;             
        case Gprs_Connect_QICSGP_Req:
            Gprs_AT_In_Queue(Gprs_CMD_QICSGP);
            break;
        case Gprs_Connect_QICSGP_Resp:
            if ()
            {
                Gprs_Process_Status.Connect_status = ;
            }
            break;   
        case Gprs_Connect_QIDEACT_Req:
            Gprs_AT_In_Queue(Gprs_CMD_QIDEACT);
            break;
        case Gprs_Connect_QIDEACT_Resp:
            if ()
            {
                Gprs_Process_Status.Connect_status = ;
            }
            break;             
        case Gprs_Connect_QIMODE_Req:
            Gprs_AT_In_Queue(Gprs_CMD_QIMODE);
            break;
        case Gprs_Connect_QIMODE_Resp:
            if ()
            {
                Gprs_Process_Status.Connect_status = ;
            }
            break;             
        case Gprs_Connect_QIMUX_Req:
            Gprs_AT_In_Queue(Gprs_CMD_QIMUX);
            break;
        case Gprs_Connect_QIMUX_Resp:
            if ()
            {
                Gprs_Process_Status.Connect_status = ;
            }
            break;             
        case Gprs_Connect_QIREGAPP_Req:
            Gprs_AT_In_Queue(Gprs_CMD_QIREGAPP);
            break;
        case Gprs_Connect_QIREGAPP_Resp:
            if ()
            {
                Gprs_Process_Status.Connect_status = ;
            }
            break;            
        case Gprs_Connect_QIACT_Req:
            Gprs_AT_In_Queue(Gprs_CMD_QIACT);
            break;
        case Gprs_Connect_QIACT_Resp:
            if ()
            {
                Gprs_Process_Status.Connect_status = ;
            }
            break;  
        case Gprs_Connect_QILOCIP_Req:
            Gprs_AT_In_Queue(Gprs_CMD_QILOCIP);
            break;
        case Gprs_Connect_QILOCIP_Resp:
            if ()
            {
                Gprs_Process_Status.Connect_status = ;
            }
            break;             
        case Gprs_Connect_QIDNSIP_IP_Req:
            Gprs_AT_In_Queue(Gprs_CMD_QIDNSIP_IP);
            break;
        case Gprs_Connect_QIDNSIP_IP_Resp:
            if ()
            {
                Gprs_Process_Status.Connect_status = ;
            }
            break;   
        case Gprs_Connect_QIDNSIP_DOMAIN_Req:
            Gprs_AT_In_Queue(Gprs_CMD_QIDNSIP_DOMAIN);
            break;
        case Gprs_Connect_QIDNSIP_DOMAIN_Resp:
            if ()
            {
                Gprs_Process_Status.Connect_status = ;
            }
            break;              
        case Gprs_Connect_QIHEAD_Req:
            Gprs_AT_In_Queue(Gprs_CMD_QIHEAD);
            break;
        case Gprs_Connect_QIHEAD_Resp:
            if ()
            {
                Gprs_Process_Status.Connect_status = ;
            }
            break;             
        case Gprs_Connect_QIOPEN_Req:
            Gprs_AT_In_Queue(Gprs_CMD_QIOPEN);
            break;
        case Gprs_Connect_QIOPEN_Resp:
            if ()
            {
                Gprs_Process_Status.Connect_status = ;
            }
            break;             
        case Gprs_Connect_QISEND_Req:
            Gprs_AT_In_Queue(Gprs_CMD_QISEND);
            break;
        case Gprs_Connect_QISEND_Resp:
            if ()
            {
                Gprs_Process_Status.Connect_status = ;
            }
            break;            
        case Gprs_Connect_QISACK_Req:
            Gprs_AT_In_Queue(Gprs_CMD_QISACK);
            break;
        case Gprs_Connect_QISACK_Resp:
            if ()
            {
                Gprs_Process_Status.Connect_status = ;
            }
            break;             
            
            
            
            
    }
}

void Gprs_Idel_Loop_Process(void)
{
    outqueue>0
    if()
    {
      status = Gprs_AT_Out_Queue();
    }
    switch (status)
    {
        case Gprs_CMD_AT:
          Gprs_CMD_Send(GPRS_CMD_AT,sizeof(GPRS_CMD_AT));
          break;
        case Gprs_CMD_AT_RESP:  
        case Gprs_CMD_ATE:
          Gprs_CMD_Send(GPRS_CMD_ATE,sizeof(GPRS_CMD_ATE));
          break;
          case Gprs_CMD_ATE:
        case Gprs_CMD_IPR:
          Gprs_CMD_Send(GPRS_CMD_IPR,sizeof(GPRS_CMD_IPR));
          break;
          case Gprs_CMD_IPR:
        case Gprs_CMD_CPIN:  
          Gprs_CMD_Send(GPRS_CMD_CPIN,sizeof(GPRS_CMD_CPIN));
          break;          
          case Gprs_CMD_CPIN:  
        case Gprs_CMD_CSQ:
          Gprs_CMD_Send(GPRS_CMD_CSQ,sizeof(GPRS_CMD_CSQ));
          break;          
          case Gprs_CMD_CSQ:
        case Gprs_CMD_CREG:
          Gprs_CMD_Send(GPRS_CMD_CREG,sizeof(GPRS_CMD_CREG));
          break;
          case Gprs_CMD_CREG:  
        case Gprs_CMD_CGREG:
          Gprs_CMD_Send(GPRS_CMD_CGREG,sizeof(GPRS_CMD_CGREG));
          break;          
          case Gprs_CMD_CGREG:
        case Gprs_CMD_QIFGCNT:
          Gprs_CMD_Send(GPRS_CMD_QIFGCNT,sizeof(GPRS_CMD_QIFGCNT));
          break;          
          case Gprs_CMD_QIFGCNT:
        case Gprs_CMD_QICSGP:
          Gprs_CMD_Send(GPRS_CMD_QICSGP,sizeof(GPRS_CMD_QICSGP));
          break;          
          case Gprs_CMD_QICSGP:
        case Gprs_CMD_QIDEACT:
          Gprs_CMD_Send(GPRS_CMD_QIDEACT,sizeof(GPRS_CMD_QIDEACT));
          break;          
          case Gprs_CMD_QIDEACT:
        case Gprs_CMD_QIMODE:
          Gprs_CMD_Send(GPRS_CMD_QIMODE,sizeof(GPRS_CMD_QIMODE));
          break;          
        case Gprs_CMD_QIMODE:
        case Gprs_CMD_QIMUX:
          Gprs_CMD_Send(GPRS_CMD_QIMUX,sizeof(GPRS_CMD_QIMUX));
          break;          
          case Gprs_CMD_QIMUX:
        case Gprs_CMD_QIREGAPP:  
          Gprs_CMD_Send(GPRS_CMD_QIREGAPP,sizeof(GPRS_CMD_QIREGAPP));
          break;          
          case Gprs_CMD_QIREGAPP: 
        case Gprs_CMD_QIACT:
          Gprs_CMD_Send(GPRS_CMD_QIACT,sizeof(GPRS_CMD_QIACT));
          break;          
          case Gprs_CMD_QIACT:
        case Gprs_CMD_QILOCIP:
          Gprs_CMD_Send(GPRS_CMD_QILOCIP,sizeof(GPRS_CMD_QILOCIP));
          break;          
          case Gprs_CMD_QILOCIP:
        case Gprs_CMD_QIDNSIP_IP:  
          Gprs_CMD_Send(GPRS_CMD_QIDNSIP_IP,sizeof(GPRS_CMD_QIDNSIP_IP));
          break;          
          case Gprs_CMD_QIDNSIP_IP: 
        case Gprs_CMD_QIDNSIP_DOMAIN:
          Gprs_CMD_Send(GPRS_CMD_QIDNSIP_DOMAIN,sizeof(GPRS_CMD_QIDNSIP_DOMAIN));
          break;          
          case Gprs_CMD_QIDNSIP_DOMAIN:
        case Gprs_CMD_QIHEAD:
          Gprs_CMD_Send(GPRS_CMD_QIHEAD,sizeof(GPRS_CMD_QIHEAD));
          break;          
          case Gprs_CMD_QIHEAD:
        case Gprs_CMD_QIOPEN:
          Gprs_CMD_Send(GPRS_CMD_QIOPEN,sizeof(GPRS_CMD_QIOPEN));
          break;          
          case Gprs_CMD_QIOPEN:
        case Gprs_CMD_QISEND:
          Gprs_CMD_Send(GPRS_CMD_QISEND,sizeof(GPRS_CMD_QISEND));
          break;          
          case Gprs_CMD_QISEND:
        case Gprs_CMD_QISACK:
          Gprs_CMD_Send(GPRS_CMD_QISACK,sizeof(GPRS_CMD_QISACK));
          break;          
          case Gprs_CMD_QISACK:


          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
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

