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
static void mc20_core_idel(void);
static void mc20_core_cmd_AT(void);
static void mc20_core_cmd_ATE(void);
static void mc20_core_cmd_IPR(void);
static void mc20_core_cmd_CPIN(void);
static void mc20_core_cmd_CSQ(void);
static void mc20_core_cmd_CGRE(void);
static void mc20_core_cmd_CGREG(void);
static void mc20_core_cmd_QIFGCNT(void);
static void mc20_core_cmd_QICSGP(void);
static void mc20_core_cmd_QIDEACT(void);
static void mc20_core_cmd_QIMODE(void);
static void mc20_core_cmd_QIMUX(void);
static void mc20_core_cmd_QIREGAPP(void);
static void mc20_core_cmd_QIACT(void);
static void mc20_core_cmd_QILOCIP(void);
static void mc20_core_cmd_QIDNSIP_IP(void);
static void mc20_core_cmd_QIDNSIP_DOMAIN(void);
static void mc20_core_cmd_QIHEAD(void);
static void mc20_core_cmd_QIOPEN(void);
static void mc20_core_cmd_QISEND(void);
static void mc20_core_cmd_QISACK(void);
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
    if (s_MC20_Func_Status.Core_status == MC20_IDLE)//check current mc20-module status is idel?               
    {
        if (MC20_ATcmd_Queue_Get_Count() > 0 )
        {
            s_MC20_Func_Status.Core_status = MC20_ATcmd_Out_to_Queue();
        }
    }

    switch (s_MC20_Func_Status.Core_status)
    {
        case MC20_IDLE:
            mc20_core_idel();
            break;
        case MC20_CMD_AT:
            mc20_core_cmd_AT();
            s_MC20_Func_Status.Core_status = MC20_CMD_AT_Resp;
            break;
        case MC20_CMD_AT_Resp:
            
        case MC20_CMD_ATE:
        case MC20_CMD_ATE_Resp:
        case MC20_CMD_IPR:
        case MC20_CMD_IPR_Resp:
        case MC20_CMD_CPIN:
        case MC20_CMD_CPIN_Resp:
        case MC20_CMD_CSQ:
        case MC20_CMD_CSQ_Resp:
        case MC20_CMD_CREG:
        case MC20_CMD_CREG_Resp:
        case MC20_CMD_CGREG:
        case MC20_CMD_CGREG_Resp:
        case MC20_CMD_QIFGCNT:
        case MC20_CMD_QIFGCNT_Resp:
        case MC20_CMD_QICSGP:
        case MC20_CMD_QICSGP_Resp:
        case MC20_CMD_QIDEACT:
        case MC20_CMD_QIDEACT_Resp:
        case MC20_CMD_QIMODE:
        case MC20_CMD_QIMODE_Resp:
        case MC20_CMD_QIMUX:
        case MC20_CMD_QIMUX_Resp:
        case MC20_CMD_QIREGAPP:
        case MC20_CMD_QIREGAPP_Resp:
        case MC20_CMD_QIACT:
        case MC20_CMD_QIACT_Resp:
        case MC20_CMD_QILOCIP:
        case MC20_CMD_QILOCIP_Resp:
        case MC20_CMD_QIDNSIP_IP:
        case MC20_CMD_QIDNSIP_IP_Resp:
        case MC20_CMD_QIDNSIP_DOMAIN:
        case MC20_CMD_QIDNSIP_DOMAIN_Resp:
        case MC20_CMD_QIHEAD:
        case MC20_CMD_QIHEAD_Resp:
        case MC20_CMD_QIOPEN:
        case MC20_CMD_QIOPEN_Resp:
        case MC20_CMD_QISEND:
        case MC20_CMD_QISEND_Resp:
        case MC20_CMD_QISACK:
        case MC20_CMD_QISACK_Resp:
    }
}

static void mc20_core_idel(void)
{
    ;
}


static void mc20_core_cmd_AT(void)
{
    MC20_CMD_Send(MC20_CMD_AT_BUF,sizeof(MC20_CMD_AT_BUF));
}
static void mc20_core_cmd_ATE(void)
{
    ;
}
static void mc20_core_cmd_IPR(void)
{
    ;
}
static void mc20_core_cmd_CPIN(void)
{
    ;
}
static void mc20_core_cmd_CSQ(void)
{
    ;
}
static void mc20_core_cmd_CGRE(void)
{
    ;
}
static void mc20_core_cmd_CGREG(void)
{
    ;
}
static void mc20_core_cmd_QIFGCNT(void)
{
    ;
}
static void mc20_core_cmd_QICSGP(void)
{
    ;
}
static void mc20_core_cmd_QIDEACT(void)
{
    ;
}
static void mc20_core_cmd_QIMODE(void)
{
    ;
}
static void mc20_core_cmd_QIMUX(void)
{
    ;
}
static void mc20_core_cmd_QIREGAPP(void)
{
    ;
}
static void mc20_core_cmd_QIACT(void)
{
    ;
}
static void mc20_core_cmd_QILOCIP(void)
{
    ;
}
static void mc20_core_cmd_QIDNSIP_IP(void)
{
    ;
}
static void mc20_core_cmd_QIDNSIP_DOMAIN(void)
{
    ;
}
static void mc20_core_cmd_QIHEAD(void)
{
    ;
}
static void mc20_core_cmd_QIOPEN(void)
{
    ;
}
static void mc20_core_cmd_QISEND(void)
{
    ;
}
static void mc20_core_cmd_QISACK(void)
{
    ;
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

