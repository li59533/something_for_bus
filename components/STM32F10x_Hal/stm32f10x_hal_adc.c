/**
 **************************************************************************************************
 * @file        stm32f10x_hal_adc.c
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
#include "stm32f10x_hal_conf.h"
#include "stm32f10x_hal_adc.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    stm32f10x_hal_adc_Modules 
 * @{  
 */

/**
 * @defgroup      stm32f10x_hal_adc_IO_Defines 
 * @brief         
 * @{  
 */
typedef struct
{
    GPIO_ConfigTypedef  Port;
    uint8_t             Channel;
    uint8_t             Rank;
}ADC_IOTypedef;

#if HAL_ADC1_CHANNEL_COUNT > 0
const ADC_IOTypedef ADC1_IO[HAL_ADC1_CHANNEL_COUNT]=
{
    {
        RCC_APB2Periph_GPIOC,GPIOC,GPIO_Pin_0,GPIO_Speed_50MHz,GPIO_Mode_AIN,
        ADC_Channel_10,
        1,
    },
    {
        NULL,NULL,NULL,NULL,NULL,
        ADC_Channel_16,
        2,
    },
    {
        NULL,NULL,NULL,NULL,NULL,
        ADC_Channel_17,
        3,
    },
};
#endif
/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_adc_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_adc_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_adc_Private_Types
 * @brief         
 * @{  
 */
const ADC_BaseConfigTypedef ADC_BaseConfig[HAL_ADC_COUNT]=
{
    {
        ADC1,
        ADC1_2_IRQn,
        RCC_APB2Periph_ADC1,
        {
            ADC_Mode_Independent,   /* ADC_Mode */
            ENABLE, /* ADC_ScanConvMode */
            DISABLE, /* ADC_ContinuousConvMode */
            ADC_ExternalTrigConv_T4_CC4,  /* ADC_ExternalTrigConv */
            ADC_DataAlign_Right,        /* ADC_DataAlign */
            HAL_ADC1_CHANNEL_COUNT,         /* ADC_NbrOfChannel */
        },
        ADC_DataManagement_DMA,
        1,
    },
};

const ADC_ExConfigTypedef ADC_ExConfig[HAL_ADC_COUNT] = 
{
    {
        /* ADC_DMAConfigTypedef */
        {
            /* DMA_Clock */
            RCC_AHBPeriph_DMA1,
            /* DMA_Channel */
            DMA1_Channel1,
            /* DMA_Mode */
            DMA_Mode_Circular,
            /* DMA_IRQChannel */
            DMA1_Channel1_IRQn,
        },
        /* TIM_BaseConfigTypedef */ 
        {
            TIM4,
            TIM4_IRQn,
            RCC_APB1Periph_TIM4,
            {
                /* Prescaler */
                71,
                /* CounterMode */
                TIM_CounterMode_Up,
                /* Period */
                5000,
                /* ClockDivision */
                TIM_CKD_DIV1,
                /* RepetitionCounter */
                0,
            },
        },
        TIM_TRGOSource_OC4Ref,
        4,  /* TIM_OC_Channel */
        {
            ENABLE, /* state */
            /* TIM_OCInitTypeDef */
            {
                TIM_OCMode_PWM1,
                TIM_OutputState_Enable,
                TIM_OutputNState_Disable,/* TIM1,TIM8 only */
                1000, /* TIM_Pulse */
                TIM_OCPolarity_Low,
                TIM_OCNPolarity_Low,    /* TIM1,TIM8 only */
                TIM_OCIdleState_Set,    /* TIM1,TIM8 only */
                TIM_OCNIdleState_Reset, /* TIM1,TIM8 only */
            },
            /* GPIO_ConfigTypedef */
            {RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_9,GPIO_Speed_50MHz,GPIO_Mode_AF_PP},
        },
        NULL,   /* GPIO_Remap */
    }
};
/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_adc_Private_Variables 
 * @brief         
 * @{  
 */
#if HAL_ADC1_CHANNEL_COUNT > 0
static uint16_t ADC1_Buf[HAL_ADC1_CHANNEL_COUNT];
#endif

#if HAL_ADC2_CHANNEL_COUNT > 0
static uint16_t ADC2_Buf[HAL_ADC2_CHANNEL_COUNT];
#endif

#if HAL_ADC3_CHANNEL_COUNT > 0
static uint16_t ADC3_Buf[HAL_ADC3_CHANNEL_COUNT];
#endif

ADC_InstanceTypedef ADC_Instance[HAL_ADC_COUNT]=
{
    /* ADC1 */
    {
        ADC1,
        {
            ADC1_Buf,
            sizeof(ADC1_Buf)/sizeof(ADC1_Buf[0]),
        },
    }
};
/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_adc_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_adc_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      stm32f10x_hal_adc_Functions 
 * @brief         
 * @{  
 */
void HAL_ADC_Init(uint8_t HAL_ADCx)
{
    ADC_BaseConfigTypedef *adc_base_config;
    ADC_ExConfigTypedef *adc_ex_config;
    ADC_IOTypedef *adc_io;
    ADC_InstanceTypedef *adc;
    uint8_t channel_count = 0;

    adc_base_config = (ADC_BaseConfigTypedef*)&ADC_BaseConfig[HAL_ADCx];

#if HAL_ADC1_CHANNEL_COUNT > 0
    if (HAL_ADCx == HAL_ADC1)
    {
        adc_io = (ADC_IOTypedef*)&ADC1_IO;
        channel_count = HAL_ADC1_CHANNEL_COUNT;
    }
#endif
#if HAL_ADC2_CHANNEL_COUNT > 0
    if(HAL_ADCx == HAL_ADC2)
    {
        adc_io = (ADC_IOTypedef*)&ADC2_IO;
        channel_count = HAL_ADC2_CHANNEL_COUNT;
    }
#endif

    adc = &ADC_Instance[HAL_ADCx];

    RCC_APB2PeriphClockCmd(adc_base_config->ADC_Clock,ENABLE);

    /* ADC Channel Config */
    for (int i=0; i<channel_count; i++)
    {
        if (adc_io[i].Port.Clock != NULL)
        {
            RCC_APB2PeriphClockCmd(adc_io[i].Port.Clock,ENABLE);
            GPIO_Init(adc_io[i].Port.GPIOx,&adc_io[i].Port.Init);
        }
        else if (adc_io[i].Channel == ADC_Channel_16 || adc_io[i].Channel == ADC_Channel_17)
        {
            ADC_TempSensorVrefintCmd(ENABLE);
        }
    }
    
    adc_ex_config = (ADC_ExConfigTypedef*)&ADC_ExConfig[HAL_ADCx];
    if (adc_base_config->DataManagement == ADC_DataManagement_DMA)
    {
        RCC_AHBPeriphClockCmd(adc_ex_config->DMA_Config.DMA_Clock,ENABLE);
        DMA_DeInit(adc_ex_config->DMA_Config.DMA_Channel);
        DMA_InitTypeDef DMA_InitStructure;
        DMA_InitStructure = HAL_DMA_ADC_StructInit((uint32_t)&adc->Instance->DR,(uint32_t)adc->Buf.pBuf,adc->Buf.Size,DMA_DIR_PeripheralSRC,adc_ex_config->DMA_Config.DMA_Mode);
        DMA_Init(adc_ex_config->DMA_Config.DMA_Channel,&DMA_InitStructure);
        DMA_Cmd(adc_ex_config->DMA_Config.DMA_Channel,ENABLE);
        ADC_DMACmd(adc->Instance,ENABLE);
    }
    else if (adc_base_config->DataManagement == ADC_DataManagement_Query)
    {

    }

    ADC_Init(adc->Instance,&adc_base_config->Init);

    for (int i=0; i<channel_count; i++)
    {
        ADC_RegularChannelConfig(adc->Instance,adc_io[i].Channel,adc_io[i].Rank,ADC_SampleTime_239Cycles5);
    }

    if (adc_base_config->ExTrigger)
    {
        if ((adc_ex_config->TIM_Base.Instance == TIM1) ||
            (adc_ex_config->TIM_Base.Instance == TIM8))
        {
            RCC_APB2PeriphClockCmd(adc_ex_config->TIM_Base.TIM_Clock,ENABLE);
        }
        else
        {
            RCC_APB1PeriphClockCmd(adc_ex_config->TIM_Base.TIM_Clock,ENABLE);
        }
        
        TIM_TimeBaseInit(adc_ex_config->TIM_Base.Instance,&adc_ex_config->TIM_Base.BaseInit);

        if (adc_ex_config->TIM_OC_Channelx != NULL )
        {
            if (adc_ex_config->TIM_OC_Channelx == 1)
            {
                TIM_OC1Init(adc_ex_config->TIM_Base.Instance,&adc_ex_config->TIM_OC.OCInit);
                TIM_OC1PreloadConfig(adc_ex_config->TIM_Base.Instance,TIM_OCPreload_Enable);
            }
            else if (adc_ex_config->TIM_OC_Channelx == 2)
            {
                TIM_OC2Init(adc_ex_config->TIM_Base.Instance,&adc_ex_config->TIM_OC.OCInit);
                TIM_OC2PreloadConfig(adc_ex_config->TIM_Base.Instance,TIM_OCPreload_Enable);
            }
            else if (adc_ex_config->TIM_OC_Channelx == 3)
            {
                TIM_OC3Init(adc_ex_config->TIM_Base.Instance,&adc_ex_config->TIM_OC.OCInit);
                TIM_OC3PreloadConfig(adc_ex_config->TIM_Base.Instance,TIM_OCPreload_Enable);
            }
            else if (adc_ex_config->TIM_OC_Channelx == 4)
            {
                TIM_OC4Init(adc_ex_config->TIM_Base.Instance,&adc_ex_config->TIM_OC.OCInit);
                TIM_OC4PreloadConfig(adc_ex_config->TIM_Base.Instance,TIM_OCPreload_Enable);
            }

            if (adc_ex_config->TIM_OC.OCInit.TIM_OutputState == ENABLE)
            {
                RCC_APB2PeriphClockCmd(adc_ex_config->TIM_OC.Port.Clock,ENABLE);
                GPIO_Init(adc_ex_config->TIM_OC.Port.GPIOx, &adc_ex_config->TIM_OC.Port.Init); 
                if (adc_ex_config->GPIO_Remap != NULL)
                {
                    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
                    GPIO_PinRemapConfig(adc_ex_config->GPIO_Remap,ENABLE);
                }
            }
        }
        TIM_ARRPreloadConfig(adc_ex_config->TIM_Base.Instance,ENABLE);
        ADC_ExternalTrigConvCmd(adc_base_config->Instance,ENABLE);
    }

    ADC_Cmd(adc_base_config->Instance,ENABLE);

    ADC_ResetCalibration(adc_base_config->Instance);
    while (ADC_GetResetCalibrationStatus(adc_base_config->Instance));
    ADC_StartCalibration(adc_base_config->Instance);
    while (ADC_GetCalibrationStatus(adc_base_config->Instance)); 
}

void HAL_ADC_Open(uint8_t HAL_ADCx)
{
    ADC_Cmd(ADC_Instance[HAL_ADCx].Instance,ENABLE);
    if(ADC_BaseConfig[HAL_ADCx].ExTrigger)
    {
        TIM_SelectMasterSlaveMode(ADC_ExConfig[HAL_ADCx].TIM_Base.Instance,TIM_MasterSlaveMode_Enable);
        TIM_SelectOutputTrigger(ADC_ExConfig[HAL_ADCx].TIM_Base.Instance,ADC_ExConfig[HAL_ADCx].TIM_TRGOSource);
        TIM_Cmd(ADC_ExConfig[HAL_ADCx].TIM_Base.Instance,ENABLE);
    }
    else
    {
        ADC_SoftwareStartConvCmd(ADC_Instance[HAL_ADCx].Instance,ENABLE);
    }
}

void HAL_ADC_DMAITConfig(uint8_t HAL_ADCx,uint32_t DMA_IT,uint8_t PrePriority,uint8_t SubPriority,FunctionalState NewState)
{
    HAL_NVIC_Config(ADC_ExConfig[HAL_ADCx].DMA_Config.DMA_IRQChannel,PrePriority,SubPriority,NewState);
    DMA_ITConfig(ADC_ExConfig[HAL_ADCx].DMA_Config.DMA_Channel,DMA_IT,NewState);
}

void HAL_ADC_GetValue_DMAISR(uint8_t HAL_ADCx,uint16_t *pBuf,ErrorStatus *status)
{
    ADC_ExConfigTypedef *adc_ex_config;
    *status = ERROR;

    adc_ex_config = (ADC_ExConfigTypedef*)&ADC_ExConfig[HAL_ADCx];
    if (DMA_GetITStatus(DMA1_IT_TC1) != RESET)
    {
        
        ADC_InstanceTypedef *adc;    
        adc = &ADC_Instance[HAL_ADCx];

        DMA_ClearITPendingBit(DMA1_IT_TC1);
        for(int i=0; i<adc->Buf.Size; i++)
        {
            pBuf[i] = adc->Buf.pBuf[i];
        }   

        volatile static uint32_t adc_tmp;
        adc_tmp = adc->Buf.pBuf[0];
        adc_tmp = adc_tmp*2950/4096;
        *status = SUCCESS;
    }
}

void HAL_ADC_GetValue_Query(uint8_t HAL_ADCx,uint16_t *pBuf,ErrorStatus *status)
{
    ADC_InstanceTypedef *adc;
    
    *status = ERROR;
    adc = &ADC_Instance[HAL_ADCx];

    while (ADC_GetFlagStatus(adc->Instance,ADC_FLAG_EOC) == RESET);
    volatile static uint32_t tmp = 0;
    ADC_ClearFlag(adc->Instance,ADC_FLAG_EOC);
    pBuf[0] = ADC_GetConversionValue(ADC1);
    tmp = adc->Instance->DR;
    tmp = tmp*3300/4096;
    *status = SUCCESS;
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

