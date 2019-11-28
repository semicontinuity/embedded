/**
 * Test SPI communication
 * Adopted from examples of http://stm32f4-discovery.net
 */
/* Include core modules */
#include "stm32fxxx_hal.h"
/* Include my libraries here */
#include "defines.h"
#include "tm_stm32_disco.h"
#include "tm_stm32_spi.h"

int main(void) {
	/* Init system clock for maximum system speed */
	TM_RCC_InitSystem();
	
	/* Init HAL layer */
	HAL_Init();
	
	/* Init leds */
	TM_DISCO_LedInit();

	/* Init SPI */

	TM_SPI_Init(SPI2, TM_SPI_PinsPack_1);

	/* Connect MOSI and MISO pins together! */

    TM_SPI_Send(SPI2, 0x01);
    TM_SPI_Send(SPI2, 0xFF);

    TM_DISCO_LedOn(LED_GREEN);

	while (1) {
		/* Do nothing */
	}
}
