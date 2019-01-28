#include "stm32f1xx_hal.h"
#include "dma.h"
#include "led2.h"
#include "tim.h"
#include "usart.h"


void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef clkinitstruct = {0};
  RCC_OscInitTypeDef oscinitstruct = {0};
  
  /* Configure PLL ------------------------------------------------------*/
  /* PLL configuration: PLLCLK = (HSI / 2) * PLLMUL = (8 / 2) * 16 = 64 MHz */
  /* PREDIV1 configuration: PREDIV1CLK = PLLCLK / HSEPredivValue = 64 / 1 = 64 MHz */
  /* Enable HSI and activate PLL with HSi_DIV2 as source */
  oscinitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSI;
  oscinitstruct.HSEState        = RCC_HSE_OFF;
  oscinitstruct.LSEState        = RCC_LSE_OFF;
  oscinitstruct.HSIState        = RCC_HSI_ON;
  oscinitstruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  oscinitstruct.HSEPredivValue    = RCC_HSE_PREDIV_DIV1;
  oscinitstruct.PLL.PLLState    = RCC_PLL_ON;
  oscinitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSI_DIV2;
  oscinitstruct.PLL.PLLMUL      = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&oscinitstruct)!= HAL_OK)
  {
    /* Initialization Error */
    while(1); 
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
  clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  if (HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_2)!= HAL_OK)
  {
    /* Initialization Error */
    while(1); 
  }
}


void Error_Handler(void)
{
  while(1)
  {
    led2__toggle();
    HAL_Delay(100);
  }
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  led2__toggle();
}

uint8_t data = 'A';


HAL_StatusTypeDef start_dma(TIM_HandleTypeDef *htim, uint32_t SrcAddress, uint32_t DstAddress, uint16_t Length)
{
  /* Check the parameters */
  assert_param(IS_TIM_DMA_INSTANCE(htim->Instance));

  if((htim->State == HAL_TIM_STATE_BUSY))
  {
    return HAL_BUSY;
  }
  else if((htim->State == HAL_TIM_STATE_READY))
  {
    htim->State = HAL_TIM_STATE_BUSY;
  }
  /* Enable the DMA channel */
  HAL_DMA_Start(htim->hdma[TIM_DMA_ID_UPDATE], SrcAddress, DstAddress, Length);

  /* Enable the TIM Update DMA request */
  __HAL_TIM_ENABLE_DMA(htim, TIM_DMA_UPDATE);

  /* Enable the Peripheral */
  __HAL_TIM_ENABLE(htim);

  /* Return function status */
  return HAL_OK;
}


int main(void) {
  HAL_Init();    
  SystemClock_Config();
  led2__init();

  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_TIM4_Init();

  if (start_dma(&htim4, (uint32_t)&data, (uint32_t) &huart1.Instance->DR, 1) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }

  while (1)
  {
  }
}
