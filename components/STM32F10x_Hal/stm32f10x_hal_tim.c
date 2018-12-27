/**
 **************************************************************************************************
 * @file        stm32f10x_hal_tim.c
 * @author
 * @version
 * @date        12/6/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "stm32f10x.h"
#include "selftypedef.h"
#include "stm32f10x_hal_nvic.h"
#include "stm32f10x_hal_tim.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    stm32f10x_hal_tim_Modules 
 * @{  
 */

/**
 * @defgroup      stm32f10x_hal_tim_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_tim_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_tim_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_tim_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_tim_Private_Variables 
 * @brief         
 * @{  
 */
const TIM_BaseConfigTypedef TIM_BaseConfig[HAL_TIM_COUNT] =
{
    /* TIM1 */
    {
        TIM1,
        TIM1_UP_IRQn,
        RCC_APB2Periph_TIM1,
        {
            35 ,    /* TIM_Prescaler */
            TIM_CounterMode_Up, /* TIM_CounterMode */
            1000,   /* TIM_Period */
            TIM_CKD_DIV1,   /* TIM_ClockDivision */
            0,      /* TIM_RepetitionCounter */
        },
    },
    /* TIM2 */
    {
        TIM2,
        TIM2_IRQn,
        RCC_APB1Periph_TIM2,
        {
            71 ,    /* TIM_Prescaler */
            TIM_CounterMode_Up, /* TIM_CounterMode */
            999,   /* TIM_Period */
            TIM_CKD_DIV1,   /* TIM_ClockDivision */
            0,      /* TIM_RepetitionCounter */
        },
    },
    /* TIM3 */
    {
        TIM3,
        TIM3_IRQn,
        RCC_APB1Periph_TIM3,
        {
            35 ,    /* TIM_Prescaler */
            TIM_CounterMode_Up, /* TIM_CounterMode */
            1000,   /* TIM_Period */
            TIM_CKD_DIV1,   /* TIM_ClockDivision */
            0,      /* TIM_RepetitionCounter */
        },
    },
    /* TIM4 */
    {
        TIM4,
        TIM4_IRQn,
        RCC_APB1Periph_TIM4,
        {
            71 ,    /* TIM_Prescaler */
            TIM_CounterMode_Up, /* TIM_CounterMode */
            0xFFFF,   /* TIM_Period */
            TIM_CKD_DIV1,   /* TIM_ClockDivision */
            0,      /* TIM_RepetitionCounter */
        },
    },
    /* TIM5 */
    {
        TIM5,
        TIM5_IRQn,
        RCC_APB1Periph_TIM5,
        {
            35 ,    /* TIM_Prescaler */
            TIM_CounterMode_Up, /* TIM_CounterMode */
            1000,   /* TIM_Period */
            TIM_CKD_DIV1,   /* TIM_ClockDivision */
            0,      /* TIM_RepetitionCounter */
        },
    },
    /* TIM6 */
    {
        TIM6,
        TIM6_IRQn,
        RCC_APB1Periph_TIM6,
        {
            35 ,    /* TIM_Prescaler */
            TIM_CounterMode_Up, /* TIM_CounterMode */
            1000,   /* TIM_Period */
            TIM_CKD_DIV1,   /* TIM_ClockDivision */
            0,      /* TIM_RepetitionCounter */
        },
    },
    /* TIM7 */
    {
        TIM7,
        TIM7_IRQn,
        RCC_APB1Periph_TIM7,
        {
            71 ,    /* TIM_Prescaler */
            TIM_CounterMode_Up, /* TIM_CounterMode */
            999,   /* TIM_Period */
            TIM_CKD_DIV1,   /* TIM_ClockDivision */
            0,      /* TIM_RepetitionCounter */
        },
    },
};

const TIM_PWMOCConfigTypedef TIM_PWMOC_Config[HAL_TIM_COUNT]=
{
    /* TIM1 */
    {
        /* TIM_OCChannelConfigTypedef */
        {
            /* CH1 */
            {
                DISABLE, /* state */
                /* TIM_OCInitTypeDef */
                {
                    TIM_OCMode_PWM1,
                    TIM_OutputState_Enable,
                    TIM_OutputNState_Disable,/* TIM1,TIM8 only */
                    10, /* TIM_Pulse */
                    TIM_OCPolarity_Low,
                    TIM_OCNPolarity_Low,    /* TIM1,TIM8 only */
                    TIM_OCIdleState_Reset,    /* TIM1,TIM8 only */
                    TIM_OCNIdleState_Reset, /* TIM1,TIM8 only */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_0,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
            },
            /* CH2 */
            {
                DISABLE, /* state */
                /* TIM_OCInitTypeDef */
                {
                    TIM_OCMode_PWM1,
                    TIM_OutputState_Enable,
                    TIM_OutputNState_Disable,/* TIM1,TIM8 only */
                    20, /* TIM_Pulse */
                    TIM_OCPolarity_Low,
                    TIM_OCNPolarity_Low,    /* TIM1,TIM8 only */
                    TIM_OCIdleState_Set,    /* TIM1,TIM8 only */
                    TIM_OCNIdleState_Reset, /* TIM1,TIM8 only */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_0,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},

            },
            /* CH3 */
            {
                DISABLE, /* state */
                /* TIM_OCInitTypeDef */
                {
                    TIM_OCMode_PWM1,
                    TIM_OutputState_Enable,
                    TIM_OutputNState_Disable,/* TIM1,TIM8 only */
                    10, /* TIM_Pulse */
                    TIM_OCPolarity_Low,
                    TIM_OCNPolarity_Low,    /* TIM1,TIM8 only */
                    TIM_OCIdleState_Set,    /* TIM1,TIM8 only */
                    TIM_OCNIdleState_Reset, /* TIM1,TIM8 only */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_0,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
            },
            /* CH4 */
            {
                DISABLE, /* state */
                /* TIM_OCInitTypeDef */
                {
                    TIM_OCMode_PWM1,
                    TIM_OutputState_Enable,
                    TIM_OutputNState_Disable,/* TIM1,TIM8 only */
                    10, /* TIM_Pulse */
                    TIM_OCPolarity_Low,
                    TIM_OCNPolarity_Low,    /* TIM1,TIM8 only */
                    TIM_OCIdleState_Set,    /* TIM1,TIM8 only */
                    TIM_OCNIdleState_Reset, /* TIM1,TIM8 only */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_0,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
            },
        },
        NULL,
    },
    /* TIM2 */
    {
        /* TIM_OCChannelConfigTypedef */
        {
            /* CH1 */
            {
                DISABLE, /* state */
                /* TIM_OCInitTypeDef */
                {
                    TIM_OCMode_PWM1,
                    TIM_OutputState_Enable,
                    TIM_OutputNState_Disable,/* TIM1,TIM8 only */
                    10, /* TIM_Pulse */
                    TIM_OCPolarity_Low,
                    TIM_OCNPolarity_Low,    /* TIM1,TIM8 only */
                    TIM_OCIdleState_Set,    /* TIM1,TIM8 only */
                    TIM_OCNIdleState_Reset, /* TIM1,TIM8 only */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_0,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
            },
            /* CH2 */
            {
                ENABLE, /* state */
                /* TIM_OCInitTypeDef */
                {
                    TIM_OCMode_PWM1,
                    TIM_OutputState_Enable,
                    TIM_OutputNState_Disable,/* TIM1,TIM8 only */
                    100, /* TIM_Pulse */
                    TIM_OCPolarity_Low,
                    TIM_OCNPolarity_Low,    /* TIM1,TIM8 only */
                    TIM_OCIdleState_Set,    /* TIM1,TIM8 only */
                    TIM_OCNIdleState_Reset, /* TIM1,TIM8 only */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_1,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},

            },
            /* CH3 */
            {
                DISABLE, /* state */
                /* TIM_OCInitTypeDef */
                {
                    TIM_OCMode_PWM1,
                    TIM_OutputState_Enable,
                    TIM_OutputNState_Disable,/* TIM1,TIM8 only */
                    10, /* TIM_Pulse */
                    TIM_OCPolarity_Low,
                    TIM_OCNPolarity_Low,    /* TIM1,TIM8 only */
                    TIM_OCIdleState_Set,    /* TIM1,TIM8 only */
                    TIM_OCNIdleState_Reset, /* TIM1,TIM8 only */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_0,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},

            },
            /* CH4 */
            {
                DISABLE, /* state */
                /* TIM_OCInitTypeDef */
                {
                    TIM_OCMode_PWM1,
                    TIM_OutputState_Enable,
                    TIM_OutputNState_Disable,/* TIM1,TIM8 only */
                    10, /* TIM_Pulse */
                    TIM_OCPolarity_Low,
                    TIM_OCNPolarity_Low,    /* TIM1,TIM8 only */
                    TIM_OCIdleState_Set,    /* TIM1,TIM8 only */
                    TIM_OCNIdleState_Reset, /* TIM1,TIM8 only */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_0,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
            },
        },
        NULL, /* GPIO_Remap */
    },
    /* TIM3 */
    {
        /* TIM_OCChannelConfigTypedef */
        {
            /* CH1 */
            {
                DISABLE, /* state */
                /* TIM_OCInitTypeDef */
                {
                    TIM_OCMode_PWM1,
                    TIM_OutputState_Enable,
                    TIM_OutputNState_Disable,/* TIM1,TIM8 only */
                    10, /* TIM_Pulse */
                    TIM_OCPolarity_Low,
                    TIM_OCNPolarity_Low,    /* TIM1,TIM8 only */
                    TIM_OCIdleState_Set,    /* TIM1,TIM8 only */
                    TIM_OCNIdleState_Reset, /* TIM1,TIM8 only */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_6,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
            },
            /* CH2 */
            {
                ENABLE, /* state */
                /* TIM_OCInitTypeDef */
                {
                    TIM_OCMode_PWM1,
                    TIM_OutputState_Disable,
                    TIM_OutputNState_Disable,/* TIM1,TIM8 only */
                    100, /* TIM_Pulse */
                    TIM_OCPolarity_Low,
                    TIM_OCNPolarity_Low,    /* TIM1,TIM8 only */
                    TIM_OCIdleState_Set,    /* TIM1,TIM8 only */
                    TIM_OCNIdleState_Reset, /* TIM1,TIM8 only */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_7,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},

            },
            /* CH3 */
            {
                DISABLE, /* state */
                /* TIM_OCInitTypeDef */
                {
                    TIM_OCMode_PWM1,
                    TIM_OutputState_Enable,
                    TIM_OutputNState_Disable,/* TIM1,TIM8 only */
                    10, /* TIM_Pulse */
                    TIM_OCPolarity_Low,
                    TIM_OCNPolarity_Low,    /* TIM1,TIM8 only */
                    TIM_OCIdleState_Set,    /* TIM1,TIM8 only */
                    TIM_OCNIdleState_Reset, /* TIM1,TIM8 only */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_0,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},

            },
            /* CH4 */
            {
                DISABLE, /* state */
                /* TIM_OCInitTypeDef */
                {
                    TIM_OCMode_PWM1,
                    TIM_OutputState_Enable,
                    TIM_OutputNState_Disable,/* TIM1,TIM8 only */
                    10, /* TIM_Pulse */
                    TIM_OCPolarity_Low,
                    TIM_OCNPolarity_Low,    /* TIM1,TIM8 only */
                    TIM_OCIdleState_Set,    /* TIM1,TIM8 only */
                    TIM_OCNIdleState_Reset, /* TIM1,TIM8 only */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_1,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
            },
        },
        NULL, /* GPIO_Remap */
    },
    /* TIM4 */
    {
        /* TIM_OCChannelConfigTypedef */
        {
            /* CH1 */
            {
                DISABLE, /* state */
                /* TIM_OCInitTypeDef */
                {
                    TIM_OCMode_PWM1,
                    TIM_OutputState_Enable,
                    TIM_OutputNState_Disable,/* TIM1,TIM8 only */
                    10, /* TIM_Pulse */
                    TIM_OCPolarity_Low,
                    TIM_OCNPolarity_Low,    /* TIM1,TIM8 only */
                    TIM_OCIdleState_Set,    /* TIM1,TIM8 only */
                    TIM_OCNIdleState_Reset, /* TIM1,TIM8 only */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_6,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
            },
            /* CH2 */
            {
                DISABLE, /* state */
                /* TIM_OCInitTypeDef */
                {
                    TIM_OCMode_PWM1,
                    TIM_OutputState_Disable,
                    TIM_OutputNState_Disable,/* TIM1,TIM8 only */
                    100, /* TIM_Pulse */
                    TIM_OCPolarity_Low,
                    TIM_OCNPolarity_Low,    /* TIM1,TIM8 only */
                    TIM_OCIdleState_Set,    /* TIM1,TIM8 only */
                    TIM_OCNIdleState_Reset, /* TIM1,TIM8 only */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_7,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},

            },
            /* CH3 */
            {
                ENABLE, /* state */
                /* TIM_OCInitTypeDef */
                {
                    TIM_OCMode_PWM1,
                    TIM_OutputState_Enable,
                    TIM_OutputNState_Disable,/* TIM1,TIM8 only */
                    50, /* TIM_Pulse */
                    TIM_OCPolarity_Low,
                    TIM_OCNPolarity_Low,    /* TIM1,TIM8 only */
                    TIM_OCIdleState_Set,    /* TIM1,TIM8 only */
                    TIM_OCNIdleState_Reset, /* TIM1,TIM8 only */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_8,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},

            },
            /* CH4 */
            {
                ENABLE, /* state */
                /* TIM_OCInitTypeDef */
                {
                    TIM_OCMode_PWM1,
                    TIM_OutputState_Enable,
                    TIM_OutputNState_Disable,/* TIM1,TIM8 only */
                    100, /* TIM_Pulse */
                    TIM_OCPolarity_Low,
                    TIM_OCNPolarity_Low,    /* TIM1,TIM8 only */
                    TIM_OCIdleState_Set,    /* TIM1,TIM8 only */
                    TIM_OCNIdleState_Reset, /* TIM1,TIM8 only */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_9,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
            },
        },
        NULL, /* GPIO_Remap */
    },
};

const TIM_ICConfigTypedef TIM_IC_Config[HAL_TIM_COUNT] = 
{
    /* TIM1 */
    {
        /* TIM_OCChannelConfigTypedef */
        {
            /* CH1 */
            {
                DISABLE, /* state */
                /* TIM_ICInitTypeDef */
                {
                    TIM_Channel_1,  /* TIM_Channel */
                    TIM_ICPolarity_Rising,  /* TIM_ICPolarity */
                    TIM_ICSelection_DirectTI,   /* TIM_ICSelection */
                    TIM_ICPSC_DIV1,     /* TIM_ICPrescaler */
                    0x00,               /* TIM_ICFilter */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_6,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
            },
            /* CH2 */
            {
                DISABLE, /* state */
                /* TIM_ICInitTypeDef */
                {
                    TIM_Channel_2,  /* TIM_Channel */
                    TIM_ICPolarity_Rising,  /* TIM_ICPolarity */
                    TIM_ICSelection_DirectTI,   /* TIM_ICSelection */
                    TIM_ICPSC_DIV1,     /* TIM_ICPrescaler */
                    0x00,               /* TIM_ICFilter */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_6,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},

            },
            /* CH3 */
            {
                DISABLE, /* state */
                /* TIM_ICInitTypeDef */
                {
                    TIM_Channel_3,  /* TIM_Channel */
                    TIM_ICPolarity_Rising,  /* TIM_ICPolarity */
                    TIM_ICSelection_DirectTI,   /* TIM_ICSelection */
                    TIM_ICPSC_DIV1,     /* TIM_ICPrescaler */
                    0x00,               /* TIM_ICFilter */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_6,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},

            },
            /* CH4 */
            {
                ENABLE, /* state */
                /* TIM_ICInitTypeDef */
                {
                    TIM_Channel_4,  /* TIM_Channel */
                    TIM_ICPolarity_Rising,  /* TIM_ICPolarity */
                    TIM_ICSelection_DirectTI,   /* TIM_ICSelection */
                    TIM_ICPSC_DIV1,     /* TIM_ICPrescaler */
                    0x00,               /* TIM_ICFilter */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_9,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},

            },
        },
        NULL,
        0,
    },
    /* TIM2 */
    {
        /* TIM_OCChannelConfigTypedef */
        {
            /* CH1 */
            {
                DISABLE, /* state */
                /* TIM_ICInitTypeDef */
                {
                    TIM_Channel_1,  /* TIM_Channel */
                    TIM_ICPolarity_Rising,  /* TIM_ICPolarity */
                    TIM_ICSelection_DirectTI,   /* TIM_ICSelection */
                    TIM_ICPSC_DIV1,     /* TIM_ICPrescaler */
                    0x00,               /* TIM_ICFilter */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_6,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
            },
            /* CH2 */
            {
                DISABLE, /* state */
                /* TIM_ICInitTypeDef */
                {
                    TIM_Channel_2,  /* TIM_Channel */
                    TIM_ICPolarity_Rising,  /* TIM_ICPolarity */
                    TIM_ICSelection_DirectTI,   /* TIM_ICSelection */
                    TIM_ICPSC_DIV1,     /* TIM_ICPrescaler */
                    0x00,               /* TIM_ICFilter */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_6,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},

            },
            /* CH3 */
            {
                DISABLE, /* state */
                /* TIM_ICInitTypeDef */
                {
                    TIM_Channel_3,  /* TIM_Channel */
                    TIM_ICPolarity_Rising,  /* TIM_ICPolarity */
                    TIM_ICSelection_DirectTI,   /* TIM_ICSelection */
                    TIM_ICPSC_DIV1,     /* TIM_ICPrescaler */
                    0x00,               /* TIM_ICFilter */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_6,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},

            },
            /* CH4 */
            {
                ENABLE, /* state */
                /* TIM_ICInitTypeDef */
                {
                    TIM_Channel_4,  /* TIM_Channel */
                    TIM_ICPolarity_Rising,  /* TIM_ICPolarity */
                    TIM_ICSelection_DirectTI,   /* TIM_ICSelection */
                    TIM_ICPSC_DIV1,     /* TIM_ICPrescaler */
                    0x00,               /* TIM_ICFilter */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_9,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},

            },
        },
        NULL,
        0,
    },
    /* TIM3 */
    {
        /* TIM_OCChannelConfigTypedef */
        {
            /* CH1 */
            {
                DISABLE, /* state */
                /* TIM_ICInitTypeDef */
                {
                    TIM_Channel_1,  /* TIM_Channel */
                    TIM_ICPolarity_Rising,  /* TIM_ICPolarity */
                    TIM_ICSelection_DirectTI,   /* TIM_ICSelection */
                    TIM_ICPSC_DIV1,     /* TIM_ICPrescaler */
                    0x00,               /* TIM_ICFilter */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_6,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
            },
            /* CH2 */
            {
                DISABLE, /* state */
                /* TIM_ICInitTypeDef */
                {
                    TIM_Channel_2,  /* TIM_Channel */
                    TIM_ICPolarity_Rising,  /* TIM_ICPolarity */
                    TIM_ICSelection_DirectTI,   /* TIM_ICSelection */
                    TIM_ICPSC_DIV1,     /* TIM_ICPrescaler */
                    0x00,               /* TIM_ICFilter */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_6,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},

            },
            /* CH3 */
            {
                DISABLE, /* state */
                /* TIM_ICInitTypeDef */
                {
                    TIM_Channel_3,  /* TIM_Channel */
                    TIM_ICPolarity_Rising,  /* TIM_ICPolarity */
                    TIM_ICSelection_DirectTI,   /* TIM_ICSelection */
                    TIM_ICPSC_DIV1,     /* TIM_ICPrescaler */
                    0x00,               /* TIM_ICFilter */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_6,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},

            },
            /* CH4 */
            {
                ENABLE, /* state */
                /* TIM_ICInitTypeDef */
                {
                    TIM_Channel_4,  /* TIM_Channel */
                    TIM_ICPolarity_Rising,  /* TIM_ICPolarity */
                    TIM_ICSelection_DirectTI,   /* TIM_ICSelection */
                    TIM_ICPSC_DIV1,     /* TIM_ICPrescaler */
                    0x00,               /* TIM_ICFilter */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_9,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},

            },
        },
        NULL,
        0,
    },
    /* TIM4 */
    {
        /* TIM_OCChannelConfigTypedef */
        {
            /* CH1 */
            {
                ENABLE, /* state */
                /* TIM_ICInitTypeDef */
                {
                    TIM_Channel_1,  /* TIM_Channel */
                    TIM_ICPolarity_Rising,  /* TIM_ICPolarity */
                    TIM_ICSelection_DirectTI,   /* TIM_ICSelection */
                    TIM_ICPSC_DIV1,     /* TIM_ICPrescaler */
                    0x00,               /* TIM_ICFilter */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_6,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
            },
            /* CH2 */
            {
                DISABLE, /* state */
                /* TIM_ICInitTypeDef */
                {
                    TIM_Channel_2,  /* TIM_Channel */
                    TIM_ICPolarity_Rising,  /* TIM_ICPolarity */
                    TIM_ICSelection_DirectTI,   /* TIM_ICSelection */
                    TIM_ICPSC_DIV1,     /* TIM_ICPrescaler */
                    0x00,               /* TIM_ICFilter */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_6,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},

            },
            /* CH3 */
            {
                DISABLE, /* state */
                /* TIM_ICInitTypeDef */
                {
                    TIM_Channel_3,  /* TIM_Channel */
                    TIM_ICPolarity_Rising,  /* TIM_ICPolarity */
                    TIM_ICSelection_DirectTI,   /* TIM_ICSelection */
                    TIM_ICPSC_DIV1,     /* TIM_ICPrescaler */
                    0x00,               /* TIM_ICFilter */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_6,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},

            },
            /* CH4 */
            {
                DISABLE, /* state */
                /* TIM_ICInitTypeDef */
                {
                    TIM_Channel_4,  /* TIM_Channel */
                    TIM_ICPolarity_Rising,  /* TIM_ICPolarity */
                    TIM_ICSelection_DirectTI,   /* TIM_ICSelection */
                    TIM_ICPSC_DIV1,     /* TIM_ICPrescaler */
                    0x00,               /* TIM_ICFilter */
                },
                /* GPIO_ConfigTypedef */
                {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_9,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},

            },
        },
        NULL,
        1,
    },
};

TIM_InstanceTypedef TIM_Instance[HAL_TIM_COUNT]=
{
    {TIM1},
    {TIM2},
    {TIM3},
    {TIM4},
    {TIM5},
    {TIM6},
    {TIM7},
    {TIM8},
};
/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_tim_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_tim_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_tim_Functions 
 * @brief         
 * @{  
 */
void HAL_TIM_Base_Init(uint8_t HAL_TIMx)
{
    TIM_BaseConfigTypedef *tim_base_config;
    TIM_InstanceTypedef *tim;

    tim_base_config = (TIM_BaseConfigTypedef*)&TIM_BaseConfig[HAL_TIMx];
    tim = &TIM_Instance[HAL_TIMx];

    TIM_DeInit(tim->Instance);

    if ((HAL_TIMx == HAL_TIM1) ||
        (HAL_TIMx == HAL_TIM8))
    {
        RCC_APB2PeriphClockCmd(tim_base_config->TIM_Clock,ENABLE);
    }
    else
    {
        RCC_APB1PeriphClockCmd(tim_base_config->TIM_Clock,ENABLE);
    }

    TIM_TimeBaseInit(tim->Instance,&tim_base_config->BaseInit);
}

void HAL_TIM_Base_Open(uint8_t HAL_TIMx)
{
    TIM_InstanceTypedef *tim;

    tim = &TIM_Instance[HAL_TIMx];
    tim->Instance->CNT = 0;
    TIM_Cmd(tim->Instance,ENABLE);
}

void HAL_TIM_Base_Close(uint8_t HAL_TIMx)
{
    TIM_InstanceTypedef *tim;

    tim = &TIM_Instance[HAL_TIMx];

    TIM_Cmd(tim->Instance,DISABLE);
}

void HAL_TIM_PWMOC_Init(uint8_t HAL_TIMx)
{
    TIM_BaseConfigTypedef *tim_base_config;
    TIM_PWMOCConfigTypedef *tim_pwm_config;
    TIM_InstanceTypedef *tim;

    tim_base_config = (TIM_BaseConfigTypedef*)&TIM_BaseConfig[HAL_TIMx];
    tim_pwm_config = (TIM_PWMOCConfigTypedef*)&TIM_PWMOC_Config[HAL_TIMx];
    tim = &TIM_Instance[HAL_TIMx];

    TIM_DeInit(tim->Instance);

    if ((HAL_TIMx == HAL_TIM1) ||
        (HAL_TIMx == HAL_TIM8))
    {
        RCC_APB2PeriphClockCmd(tim_base_config->TIM_Clock,ENABLE);
    }
    else
    {
        RCC_APB1PeriphClockCmd(tim_base_config->TIM_Clock,ENABLE);
    }

    TIM_TimeBaseInit(tim->Instance,&tim_base_config->BaseInit);

    for (int i=0; i<HAL_TIM_ACTIVE_CHANNEL_COUNT; i++)
    {
        if (tim_pwm_config->OCConfig[i].State == ENABLE)
        {
            if (i==0)
            {
                TIM_OC1Init(tim->Instance,&tim_pwm_config->OCConfig[i].OCInit);
                TIM_OC1PreloadConfig(tim->Instance,TIM_OCPreload_Enable);
            }
            else if (i==1)
            {
                TIM_OC2Init(tim->Instance,&tim_pwm_config->OCConfig[i].OCInit);
                TIM_OC2PreloadConfig(tim->Instance,TIM_OCPreload_Enable);
            }
            else if (i==2)
            {
                TIM_OC3Init(tim->Instance,&tim_pwm_config->OCConfig[i].OCInit);
                TIM_OC3PreloadConfig(tim->Instance,TIM_OCPreload_Enable);
            }
            else if (i==3)
            {
                TIM_OC4Init(tim->Instance,&tim_pwm_config->OCConfig[i].OCInit);
                TIM_OC4PreloadConfig(tim->Instance,TIM_OCPreload_Enable);
            }
            
            if (tim_pwm_config->OCConfig[i].OCInit.TIM_OutputState == ENABLE)
            {
                RCC_APB2PeriphClockCmd(tim_pwm_config->OCConfig[i].Port.Clock,ENABLE);
                GPIO_Init(tim_pwm_config->OCConfig[i].Port.GPIOx, &tim_pwm_config->OCConfig[i].Port.Init); 
            }
        }
    }

    TIM_ARRPreloadConfig(tim->Instance,ENABLE);
}

void HAL_TIM_PWMOC_Open(uint8_t HAL_TIMx)
{
    TIM_InstanceTypedef *tim;

    tim = &TIM_Instance[HAL_TIMx];

    TIM_Cmd(tim->Instance,ENABLE);
}

void HAL_TIM_PWMOC_Close(uint8_t HAL_TIMx)
{
    TIM_InstanceTypedef *tim;

    tim = &TIM_Instance[HAL_TIMx];

    TIM_Cmd(tim->Instance,DISABLE);
}

void HAL_TIM_IC_Init(uint8_t HAL_TIMx)
{
    TIM_BaseConfigTypedef *tim_base_config;
    TIM_ICConfigTypedef *tim_ic_config;
    TIM_InstanceTypedef *tim;

    tim_base_config = (TIM_BaseConfigTypedef*)&TIM_BaseConfig[HAL_TIMx];
    tim_ic_config = (TIM_ICConfigTypedef*)&TIM_IC_Config[HAL_TIMx];
    tim = &TIM_Instance[HAL_TIMx];

    TIM_DeInit(tim->Instance);

    if ((HAL_TIMx == HAL_TIM1) ||
        (HAL_TIMx == HAL_TIM8))
    {
        RCC_APB2PeriphClockCmd(tim_base_config->TIM_Clock,ENABLE);
    }
    else
    {
        RCC_APB1PeriphClockCmd(tim_base_config->TIM_Clock,ENABLE);
    }

    TIM_TimeBaseInit(tim->Instance,&tim_base_config->BaseInit);

    for (int i=0; i<HAL_TIM_ACTIVE_CHANNEL_COUNT; i++)
    {
        if (tim_ic_config->ICConfig[i].State == ENABLE)
        {
            if (tim_ic_config->PWMInputMode)
            {
                TIM_PWMIConfig(tim->Instance,&tim_ic_config->ICConfig[i].ICInit);
                TIM_SelectInputTrigger(tim->Instance,TIM_TS_TI1FP1);
                TIM_SelectSlaveMode(tim->Instance,TIM_SlaveMode_Reset);
                TIM_SelectMasterSlaveMode(tim->Instance,TIM_MasterSlaveMode_Enable);
            }
            else
            {
                TIM_ICInit(tim->Instance,&tim_ic_config->ICConfig[i].ICInit);
            }

            RCC_APB2PeriphClockCmd(tim_ic_config->ICConfig[i].Port.Clock,ENABLE);
            GPIO_Init(tim_ic_config->ICConfig[i].Port.GPIOx,&tim_ic_config->ICConfig[i].Port.Init);
        }
    }
}

void HAL_TIM_IC_Open(uint8_t HAL_TIMx)
{
    TIM_InstanceTypedef *tim;

    tim = &TIM_Instance[HAL_TIMx];

    TIM_Cmd(tim->Instance,ENABLE);
}

void HAL_TIM_IC_Close(uint8_t HAL_TIMx)
{
    TIM_InstanceTypedef *tim;

    tim = &TIM_Instance[HAL_TIMx];

    TIM_Cmd(tim->Instance,DISABLE);
}

void HAL_TIM_PrescalerConfig(uint8_t HAL_TIMx,uint16_t prescaler,uint16_t TIM_PSCReloadMode)
{
    TIM_InstanceTypedef *tim;

    tim = &TIM_Instance[HAL_TIMx];

    TIM_PrescalerConfig(tim->Instance,prescaler,TIM_PSCReloadMode);
}

void HAL_TIM_PeriodConfig(uint8_t HAL_TIMx,uint16_t period)
{
    TIM_InstanceTypedef *tim;

    tim = &TIM_Instance[HAL_TIMx];

    tim->Instance->ARR = period;
    tim->Instance->EGR = 0x0001;
}

void HAL_TIM_ITConfig(uint8_t HAL_TIMx,uint16_t TIM_IT,uint8_t PrePriority,uint8_t SubPriority,FunctionalState NewState)
{
    TIM_InstanceTypedef *tim;
    tim = &TIM_Instance[HAL_TIMx];
    HAL_NVIC_Config(TIM_BaseConfig[HAL_TIMx].TIM_IRQn,PrePriority,SubPriority,NewState);
    TIM_ITConfig(tim->Instance,TIM_IT,NewState);
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

