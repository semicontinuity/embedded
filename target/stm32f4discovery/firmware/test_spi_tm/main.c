/**
 * Test SPI communication.
 * Adopted from examples of http://stm32f4-discovery.net
 */

/* Include core modules */
#include "stm32fxxx_hal.h"

#include "tm_stm32_disco.h"
#include "tm_stm32_spi.h"
#include "tm_stm32_gpio.h"


void cs__init(void) {
    TM_GPIO_Init(GPIOB, GPIO_Pin_12, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_Low);
}

void cs__low(void) {
    TM_GPIO_SetPinLow(GPIOB, GPIO_Pin_12);
}

void cs__high(void) {
    TM_GPIO_SetPinHigh(GPIOB, GPIO_Pin_12);
}


/*
 * Displays "    .   " at 8-digit 7-segment indicator module.
 * Indicator module has 2 HC595 latches.
 * First latch drives cathodes and selects segments, e.g 0x7F is 01111111b -> allows current to flow to topmost segment (for dot)
 * Second latch drives anodes and selects digit, e.g 0x08 is 00001000b -> 5th digit is driven
 *
 * Connections
 *
 * Using SPI2 (SPI_NSS_SOFT):
 * NSS PB12  -> RCLK
 * SCK PB13  -> SCLK
 * MISO PB14
 * MOSI PB15 -> DI
 */
int main(void) {
	/* Init system clock for maximum system speed */
	TM_RCC_InitSystem();
	
	/* Init HAL layer */
	HAL_Init();
	
	/* Init leds */
	TM_DISCO_LedInit();

    cs__init();

	/* Init SPI */
	TM_SPI_Init(SPI2, TM_SPI_PinsPack_2);

	cs__low();
    TM_SPI_Send(SPI2, 0x7F);
    TM_SPI_Send(SPI2, 0x08);
    cs__high();

    TM_DISCO_LedOn(LED_GREEN);

	while (1) {
		/* Do nothing */
	}
}
