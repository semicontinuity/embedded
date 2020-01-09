/**
 * Test I2C comm with BLM board(s)
 */
#include "stm32fxxx_hal.h"
#include "defines.h"
#include "tm_stm32_disco.h"
#include "tm_stm32_delay.h"
#include "tm_stm32_i2c.h"

#define ADDRESS     0x60


uint8_t data_array[3];


int main(void) {
	/* Init system clock for maximum system speed */
	TM_RCC_InitSystem();
  
	/* Init HAL layer */
	HAL_Init();
	
	/* Init leds */
	TM_DISCO_LedInit();
	
	/* Init delay */
	TM_DELAY_Init();
	
	/* Init I2C, SCL = PB8, SDA = PB9, available on Arduino headers and on all discovery boards */
	/* For STM32F4xx and STM32F7xx lines */
	TM_I2C_Init(I2C1, TM_I2C_PinsPack_2, 100000);
	

	data_array[0] = 0x00; /* Data 0 */
	data_array[1] = 0xFF; /* Data 1 */
	data_array[2] = 0x00; /* Data 2 */	
	TM_I2C_WriteMulti(I2C1, ADDRESS, 0x01, data_array, 3);

	data_array[0] = 0x00; /* Data 0 */
	data_array[1] = 0x00; /* Data 1 */
	data_array[2] = 0xFF; /* Data 2 */	
	TM_I2C_WriteMulti(I2C1, ADDRESS, 0x02, data_array, 3);
	
	while (1) {
	}
}
