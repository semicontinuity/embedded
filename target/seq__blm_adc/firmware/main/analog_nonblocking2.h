#ifndef ANALOG_NONBLOCKING_H
#define ANALOG_NONBLOCKING_H


#include <stdint.h>


#include "stm32_def.h"
#include "PinAF_STM32F1.h"
#include "stm32yyxx_ll_adc.h"
#include "analog.h"


#ifdef __cplusplus
extern "C" {
#endif


/* Private_Variables */
#if (defined(HAL_ADC_MODULE_ENABLED) && !defined(HAL_ADC_MODULE_ONLY)) ||\
    (defined(HAL_DAC_MODULE_ENABLED) && !defined(HAL_DAC_MODULE_ONLY))
static PinName g_current_pin = NC;
#endif


#ifndef ADC_SAMPLINGTIME
#if defined(ADC_SAMPLETIME_8CYCLES_5)
#define ADC_SAMPLINGTIME        ADC_SAMPLETIME_8CYCLES_5;
#elif defined(ADC_SAMPLETIME_12CYCLES_5)
#define ADC_SAMPLINGTIME        ADC_SAMPLETIME_12CYCLES_5;
#elif defined(ADC_SAMPLETIME_13CYCLES_5)
#define ADC_SAMPLINGTIME        ADC_SAMPLETIME_13CYCLES_5;
#elif defined(ADC_SAMPLETIME_15CYCLES)
#define ADC_SAMPLINGTIME        ADC_SAMPLETIME_15CYCLES;
#elif defined(ADC_SAMPLETIME_16CYCLES)
#define ADC_SAMPLINGTIME        ADC_SAMPLETIME_16CYCLES;
#elif defined(ADC_SAMPLETIME_19CYCLES_5)
#define ADC_SAMPLINGTIME        ADC_SAMPLETIME_19CYCLES_5;
#endif
#endif /* !ADC_SAMPLINGTIME */


/*
 * Minimum ADC sampling time is required when reading
 * internal channels so set it to max possible value.
 * It can be defined more precisely by defining:
 * ADC_SAMPLINGTIME_INTERNAL
 * to the desired ADC sample time.
 */
#ifndef ADC_SAMPLINGTIME_INTERNAL
#if defined(ADC_SAMPLETIME_480CYCLES)
#define ADC_SAMPLINGTIME_INTERNAL ADC_SAMPLETIME_480CYCLES
#elif defined(ADC_SAMPLETIME_384CYCLES)
#define ADC_SAMPLINGTIME_INTERNAL ADC_SAMPLETIME_384CYCLES
#elif defined(ADC_SAMPLETIME_810CYCLES_5)
#define ADC_SAMPLINGTIME_INTERNAL ADC_SAMPLETIME_810CYCLES_5
#elif defined(ADC_SAMPLETIME_640CYCLES_5)
#define ADC_SAMPLINGTIME_INTERNAL ADC_SAMPLETIME_640CYCLES_5
#elif defined(ADC_SAMPLETIME_601CYCLES_5)
#define ADC_SAMPLINGTIME_INTERNAL ADC_SAMPLETIME_601CYCLES_5
#elif defined(ADC_SAMPLETIME_247CYCLES_5)
#define ADC_SAMPLINGTIME_INTERNAL ADC_SAMPLETIME_247CYCLES_5
#elif defined(ADC_SAMPLETIME_239CYCLES_5)
#define ADC_SAMPLINGTIME_INTERNAL ADC_SAMPLETIME_239CYCLES_5
#elif defined(ADC_SAMPLETIME_160CYCLES_5)
#define ADC_SAMPLINGTIME_INTERNAL ADC_SAMPLETIME_160CYCLES_5
#else
#error "ADC sampling time could not be defined for internal channels!"
#endif
#endif /* !ADC_SAMPLINGTIME_INTERNAL */



#ifndef ADC_REGULAR_RANK_1
#define ADC_REGULAR_RANK_1  1
#endif


/* Private Functions */
static uint32_t get_adc_channel(PinName pin)
{
    uint32_t function = pinmap_function(pin, PinMap_ADC);
    uint32_t channel = 0;
    switch (STM_PIN_CHANNEL(function)) {
#ifdef ADC_CHANNEL_0
        case 0:
      channel = ADC_CHANNEL_0;
      break;
#endif
        case 1:
            channel = ADC_CHANNEL_1;
            break;
        case 2:
            channel = ADC_CHANNEL_2;
            break;
        case 3:
            channel = ADC_CHANNEL_3;
            break;
        case 4:
            channel = ADC_CHANNEL_4;
            break;
        case 5:
            channel = ADC_CHANNEL_5;
            break;
        case 6:
            channel = ADC_CHANNEL_6;
            break;
        case 7:
            channel = ADC_CHANNEL_7;
            break;
        case 8:
            channel = ADC_CHANNEL_8;
            break;
        case 9:
            channel = ADC_CHANNEL_9;
            break;
        case 10:
            channel = ADC_CHANNEL_10;
            break;
        case 11:
            channel = ADC_CHANNEL_11;
            break;
        case 12:
            channel = ADC_CHANNEL_12;
            break;
        case 13:
            channel = ADC_CHANNEL_13;
            break;
        case 14:
            channel = ADC_CHANNEL_14;
            break;
        case 15:
            channel = ADC_CHANNEL_15;
            break;
#ifdef ADC_CHANNEL_16
            case 16:
      channel = ADC_CHANNEL_16;
      break;
#endif
        case 17:
            channel = ADC_CHANNEL_17;
            break;
#ifdef ADC_CHANNEL_18
            case 18:
      channel = ADC_CHANNEL_18;
      break;
#endif
#ifdef ADC_CHANNEL_19
            case 19:
      channel = ADC_CHANNEL_19;
      break;
#endif
#ifdef ADC_CHANNEL_20
            case 20:
      channel = ADC_CHANNEL_20;
      break;
    case 21:
      channel = ADC_CHANNEL_21;
      break;
    case 22:
      channel = ADC_CHANNEL_22;
      break;
    case 23:
      channel = ADC_CHANNEL_23;
      break;
    case 24:
      channel = ADC_CHANNEL_24;
      break;
    case 25:
      channel = ADC_CHANNEL_25;
      break;
    case 26:
      channel = ADC_CHANNEL_26;
      break;
#ifdef ADC_CHANNEL_27
    case 27:
      channel = ADC_CHANNEL_27;
      break;
    case 28:
      channel = ADC_CHANNEL_28;
      break;
    case 29:
      channel = ADC_CHANNEL_29;
      break;
    case 30:
      channel = ADC_CHANNEL_30;
      break;
    case 31:
      channel = ADC_CHANNEL_31;
      break;
#endif
#endif
        default:
            channel = 0;
            break;
    }
    return channel;
}


static uint32_t get_adc_internal_channel(PinName pin)
{
    uint32_t channel = 0;
    switch (pin) {
#if defined(ADC_CHANNEL_TEMPSENSOR)
        case PADC_TEMP:
      channel = ADC_CHANNEL_TEMPSENSOR;
      break;
#endif
#if defined(ADC_CHANNEL_TEMPSENSOR_ADC1)
        case PADC_TEMP:
      channel = ADC_CHANNEL_TEMPSENSOR_ADC1;
      break;
#endif
#if defined(ADC5) && defined(ADC_CHANNEL_TEMPSENSOR_ADC5)
        case PADC_TEMP_ADC5:
      channel = ADC_CHANNEL_TEMPSENSOR_ADC5;
      break;
#endif
#ifdef ADC_CHANNEL_VREFINT
        case PADC_VREF:
      channel = ADC_CHANNEL_VREFINT;
      break;
#endif
#ifdef ADC_CHANNEL_VBAT
        case PADC_VBAT:
      channel = ADC_CHANNEL_VBAT;
      break;
#endif
        default:
            channel = 0;
            break;
    }
    return channel;
}


void adc_pin_init(PinName pin) {
    pinmap_pinout(pin, PinMap_ADC);
}

void adc_channel_init(ADC_HandleTypeDef &AdcHandle, const PinName &pin, int rank) {
    ADC_ChannelConfTypeDef  AdcChannelConf = {};

#if !defined(STM32L0xx)
#if !defined(STM32G0xx)
    AdcChannelConf.SamplingTime = ADC_SAMPLINGTIME;                     /* Sampling time value to be set for the selected channel */
#else
    AdcChannelConf.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;        /* Sampling time value to be set for the selected channel */
#endif
#endif
#if !defined(STM32F0xx) && !defined(STM32F1xx) && !defined(STM32F2xx) && \
    !defined(STM32F4xx) && !defined(STM32F7xx) && !defined(STM32G0xx) && \
    !defined(STM32L0xx) && !defined(STM32L1xx) && \
    !defined(STM32F373xC) && !defined(STM32F378xx)
    AdcChannelConf.SingleDiff   = ADC_SINGLE_ENDED;                 /* Single-ended input channel */
    AdcChannelConf.OffsetNumber = ADC_OFFSET_NONE;                  /* No offset subtraction */
#endif
#if !defined(STM32F0xx) && !defined(STM32F1xx) && !defined(STM32F2xx) && \
    !defined(STM32G0xx) && !defined(STM32L0xx) && !defined(STM32L1xx) && \
    !defined(STM32WBxx) && !defined(STM32F373xC) && !defined(STM32F378xx)
    AdcChannelConf.Offset = 0;                                      /* Parameter discarded because offset correction is disabled */
#endif
#if defined (STM32H7xx) || defined(STM32MP1xx)
    AdcChannelConf.OffsetRightShift = DISABLE;                      /* No Right Offset Shift */
  AdcChannelConf.OffsetSignedSaturation = DISABLE;                /* Signed saturation feature is not used */
#endif

    uint32_t channel = get_adc_channel(pin);
    AdcChannelConf.Channel      = channel;
    AdcChannelConf.Rank         = rank;
    HAL_ADC_ConfigChannel(&AdcHandle, &AdcChannelConf);
}


bool adc_calibrate(ADC_HandleTypeDef &AdcHandle) {
#if defined(STM32F0xx) || defined(STM32F1xx) || defined(STM32F3xx) || \
    defined(STM32G0xx) || defined(STM32G4xx) || defined(STM32H7xx) || \
    defined(STM32L0xx) || defined(STM32L4xx) || defined(STM32MP1xx) || \
    defined(STM32WBxx)
/*##-2.1- Calibrate ADC then Start the conversion process ####################*/
#if defined(STM32F0xx) || defined(STM32G0xx) || defined(STM32F1xx) || \
    defined(STM32F373xC) || defined(STM32F378xx)
    if (HAL_ADCEx_Calibration_Start(&AdcHandle) !=  HAL_OK)
#elif defined (STM32H7xx) || defined(STM32MP1xx)
        if (HAL_ADCEx_Calibration_Start(&AdcHandle, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED) != HAL_OK)
  #else
    if (HAL_ADCEx_Calibration_Start(&AdcHandle, ADC_SINGLE_ENDED) !=  HAL_OK)
#endif
    {
        /* ADC Calibration Error */
        return false;
    }
#endif
    return true;
}

/**
  * @brief  initialize ADC pin
  * @param  pin : the pin to use
  * @param  resolution : resolution for converted data: 6/8/10/12/14/16
  * @retval true if ok
  */
bool adc_init(ADC_HandleTypeDef &AdcHandle, PinName pin, uint32_t resolution) {
    uint32_t samplingTime = ADC_SAMPLINGTIME;

    AdcHandle.Instance = (ADC_TypeDef *)pinmap_peripheral(pin, PinMap_ADC);


#ifdef ADC_CLOCK_DIV
    AdcHandle.Init.ClockPrescaler        = ADC_CLOCK_DIV;                 /* (A)synchronous clock mode, input ADC clock divided */
#endif
#ifdef ADC_RESOLUTION_12B
    switch (resolution) {
#ifdef ADC_RESOLUTION_6B
    case 6:
      AdcHandle.Init.Resolution          = ADC_RESOLUTION_6B;             /* resolution for converted data */
      break;
#endif
    case 8:
      AdcHandle.Init.Resolution          = ADC_RESOLUTION_8B;             /* resolution for converted data */
      break;
    case 10:
      AdcHandle.Init.Resolution          = ADC_RESOLUTION_10B;            /* resolution for converted data */
      break;
    case 12:
    default:
      AdcHandle.Init.Resolution          = ADC_RESOLUTION_12B;            /* resolution for converted data */
      break;
#ifdef ADC_RESOLUTION_14B
    case 14:
      AdcHandle.Init.Resolution          = ADC_RESOLUTION_14B;            /* resolution for converted data */
      break;
#endif
#ifdef ADC_RESOLUTION_16B
    case 16:
      AdcHandle.Init.Resolution          = ADC_RESOLUTION_16B;            /* resolution for converted data */
      break;
#endif
  }
#else
    UNUSED(resolution);
#endif
#ifdef ADC_DATAALIGN_RIGHT
    AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;           /* Right-alignment for converted data */
#endif
#ifdef ADC_SCAN_SEQ_FIXED
    AdcHandle.Init.ScanConvMode          = ADC_SCAN_SEQ_FIXED;            /* Sequencer disabled (ADC conversion on only 1 channel: channel set on rank 1) */
#else
    AdcHandle.Init.ScanConvMode          = DISABLE;                       /* Sequencer disabled (ADC conversion on only 1 channel: channel set on rank 1) */
#endif
#ifdef ADC_EOC_SINGLE_CONV
    AdcHandle.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;           /* EOC flag picked-up to indicate conversion end */
#endif
#if !defined(STM32F1xx) && !defined(STM32F2xx) && !defined(STM32F4xx) && \
    !defined(STM32F7xx) && !defined(STM32F373xC) && !defined(STM32F378xx)
    AdcHandle.Init.LowPowerAutoWait      = DISABLE;                       /* Auto-delayed conversion feature disabled */
#endif
#if !defined(STM32F1xx) && !defined(STM32F2xx) && !defined(STM32F3xx) && \
    !defined(STM32F4xx) && !defined(STM32F7xx) && !defined(STM32G4xx) && \
    !defined(STM32H7xx) && !defined(STM32L4xx) && !defined(STM32MP1xx) && \
    !defined(STM32WBxx)
    AdcHandle.Init.LowPowerAutoPowerOff  = DISABLE;                       /* ADC automatically powers-off after a conversion and automatically wakes-up when a new conversion is triggered */
#endif
#ifdef ADC_CHANNELS_BANK_A
    AdcHandle.Init.ChannelsBank          = ADC_CHANNELS_BANK_A;
#endif
    AdcHandle.Init.ContinuousConvMode    = ENABLE;                       /* Continuous mode disabled to have only 1 conversion at each conversion trig */
#if !defined(STM32F0xx) && !defined(STM32L0xx)
    AdcHandle.Init.NbrOfConversion       = 1;                             /* Specifies the number of ranks that will be converted within the regular group sequencer. */
#endif
    AdcHandle.Init.DiscontinuousConvMode = DISABLE;                       /* Parameter discarded because sequencer is disabled */
#if !defined(STM32F0xx) && !defined(STM32G0xx) && !defined(STM32L0xx)
    AdcHandle.Init.NbrOfDiscConversion   = 0;                             /* Parameter discarded because sequencer is disabled */
#endif
    AdcHandle.Init.ExternalTrigConv      = ADC_SOFTWARE_START;            /* Software start to trig the 1st conversion manually, without external event */
#if !defined(STM32F1xx) && !defined(STM32F373xC) && !defined(STM32F378xx)
    AdcHandle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE; /* Parameter discarded because software trigger chosen */
#endif
#if !defined(STM32F1xx) && !defined(STM32H7xx) && !defined(STM32MP1xx) && \
    !defined(STM32F373xC) && !defined(STM32F378xx)
    AdcHandle.Init.DMAContinuousRequests = DISABLE;                       /* DMA one-shot mode selected (not applied to this example) */
#endif
#ifdef ADC_CONVERSIONDATA_DR
    AdcHandle.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;      /* Regular Conversion data stored in DR register only */
#endif
#ifdef ADC_OVR_DATA_OVERWRITTEN
    AdcHandle.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;      /* DR register is overwritten with the last conversion result in case of overrun */
#endif
#ifdef ADC_LEFTBITSHIFT_NONE
    AdcHandle.Init.LeftBitShift          = ADC_LEFTBITSHIFT_NONE;         /* No bit shift left applied on the final ADC convesion data */
#endif

#if defined(STM32F0xx)
    AdcHandle.Init.SamplingTimeCommon    = samplingTime;
#endif
#if defined(STM32G0xx)
    AdcHandle.Init.SamplingTimeCommon1   = samplingTime;              /* Set sampling time common to a group of channels. */
  AdcHandle.Init.SamplingTimeCommon2   = samplingTime;              /* Set sampling time common to a group of channels, second common setting possible.*/
#endif
#if defined(STM32L0xx)
    AdcHandle.Init.LowPowerFrequencyMode = DISABLE;                       /* To be enabled only if ADC clock < 2.8 MHz */
  AdcHandle.Init.SamplingTime          = samplingTime;
#endif
#if !defined(STM32F0xx) && !defined(STM32F1xx) && !defined(STM32F2xx) && \
    !defined(STM32F3xx) && !defined(STM32F4xx) && !defined(STM32F7xx) && \
    !defined(STM32L1xx)
    AdcHandle.Init.OversamplingMode      = DISABLE;
    /* AdcHandle.Init.Oversample ignore for STM32L0xx as oversampling disabled */
    /* AdcHandle.Init.Oversampling ignored for other as oversampling disabled */
#endif
#if defined(ADC_CFGR_DFSDMCFG) && defined(DFSDM1_Channel0)
    AdcHandle.Init.DFSDMConfig           = ADC_DFSDM_MODE_DISABLE;        /* ADC conversions are not transferred by DFSDM. */
#endif
#ifdef ADC_TRIGGER_FREQ_HIGH
    AdcHandle.Init.TriggerFrequencyMode  = ADC_TRIGGER_FREQ_HIGH;
#endif

    AdcHandle.State = HAL_ADC_STATE_RESET;
    AdcHandle.DMA_Handle = NULL;
    AdcHandle.Lock = HAL_UNLOCKED;
    /* Some other ADC_HandleTypeDef fields exists but not required */

    g_current_pin = pin; /* Needed for HAL_ADC_MspInit*/

    if (HAL_ADC_Init(&AdcHandle) != HAL_OK) {
        return false;
    }

    return true;
}


/**
  * @brief  Start conversion on a corresponding ADC pin
  * @retval true if ok
  */
bool adc_conversion_start(ADC_HandleTypeDef &AdcHandle) {
    /*##-3- Start the conversion process ####################*/
    return !(HAL_ADC_Start(&AdcHandle) != HAL_OK);
}

/**
  * @brief  Check that conversion is running on a corresponding ADC pin
  * @retval true if ok
  */
bool adc_conversion_is_running(ADC_HandleTypeDef &AdcHandle) {
    return HAL_IS_BIT_CLR(AdcHandle.Instance->ISR, (ADC_FLAG_EOC | ADC_FLAG_EOS));
}

/**
  * @brief  Check that conversion is running on a corresponding ADC pin
  * @retval true if ok
  */
bool adc_conversion_await(ADC_HandleTypeDef &AdcHandle) {
    if (HAL_ADC_PollForConversion(&AdcHandle, 10) != HAL_OK) {
        /* End Of Conversion flag not set on time */
        return false;
    }
    return true;
}

/**
  * @brief  Get conversion result of a corresponding ADC pin
  * @retval conversion value
  */
uint32_t adc_conversion_get(ADC_HandleTypeDef &AdcHandle) {

    /* Update ADC state machine */
    SET_BIT(AdcHandle.State, HAL_ADC_STATE_REG_EOC);

    /* Determine whether any further conversion upcoming on group regular       */
    /* by external trigger, continuous mode or scan sequence on going.          */
    if(ADC_IS_SOFTWARE_START_REGULAR(&AdcHandle) &&
       (AdcHandle.Init.ContinuousConvMode == DISABLE)   )
    {
        /* If End of Sequence is reached, disable interrupts */
        if( __HAL_ADC_GET_FLAG(&AdcHandle, ADC_FLAG_EOS) )
        {
            /* Allowed to modify bits ADC_IT_EOC/ADC_IT_EOS only if bit             */
            /* ADSTART==0 (no conversion on going)                                  */
            if (ADC_IS_CONVERSION_ONGOING_REGULAR(&AdcHandle) == RESET)
            {
                /* Disable ADC end of single conversion interrupt on group regular */
                /* Note: Overrun interrupt was enabled with EOC interrupt in          */
                /* HAL_Start_IT(), but is not disabled here because can be used       */
                /* by overrun IRQ process below.                                      */
                __HAL_ADC_DISABLE_IT(&AdcHandle, ADC_IT_EOC | ADC_IT_EOS);

                /* Set ADC state */
                        ADC_STATE_CLR_SET(AdcHandle.State,
                                          HAL_ADC_STATE_REG_BUSY,
                                          HAL_ADC_STATE_READY);
            }
            else
            {
                /* Change ADC state to error state */
                SET_BIT(AdcHandle.State, HAL_ADC_STATE_ERROR_CONFIG);

                /* Set ADC error code to ADC IP internal error */
                SET_BIT(AdcHandle.ErrorCode, HAL_ADC_ERROR_INTERNAL);
            }
        }
    }

    /* Clear end of conversion flag of regular group if low power feature       */
    /* "LowPowerAutoWait " is disabled, to not interfere with this feature      */
    /* until data register is read using function HAL_ADC_GetValue().           */
    if (AdcHandle.Init.LowPowerAutoWait == DISABLE)
    {
        /* Clear regular group conversion flag */
        __HAL_ADC_CLEAR_FLAG(&AdcHandle, (ADC_FLAG_EOC | ADC_FLAG_EOS));
    }

    return HAL_ADC_GetValue(&AdcHandle);
}


/**
  * @brief  de-initialize ADC channel
  * @retval true if ok
  */
bool adc_deinit(ADC_HandleTypeDef &AdcHandle) {

    if (HAL_ADC_Stop(&AdcHandle) != HAL_OK) {
        /* Stop Conversation Error */
        return false;
    }

    if (HAL_ADC_DeInit(&AdcHandle) != HAL_OK) {
        return false;
    }

    if (__LL_ADC_COMMON_INSTANCE(AdcHandle.Instance) != 0U) {
        LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(AdcHandle.Instance), LL_ADC_PATH_INTERNAL_NONE);
    }
    return true;
}



#ifdef __cplusplus
}
#endif

#endif
