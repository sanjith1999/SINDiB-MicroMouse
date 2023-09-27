#include "adc.h"



uint16_t readADC(adc_channels channel, uint8_t timeout)
{
    ADC_ChannelConfTypeDef sConfig = {0};
    uint16_t adc_val = 0;
    switch (channel)
    {
        case RF_RECEIVER:
        	sConfig.Channel = ADC_CHANNEL_4;
            break;

        case DL_RECEIVER:
        	sConfig.Channel = ADC_CHANNEL_8;
            break;

        case LF_RECEIVER:
        	sConfig.Channel = ADC_CHANNEL_9;
            break;

        case BAT_VOL:
        	sConfig.Channel = ADC_CHANNEL_13;
            break;
        
        case DR_RECEIVER:
        	sConfig.Channel = ADC_CHANNEL_14;
            break;
    }


    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_84CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
      Error_Handler();
    }

    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1,timeout);
    adc_val = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);

    return adc_val;
}
