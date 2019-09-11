#include "stm32f4xx.h"
#include "Delay.h"
//------------------------------------------------------
//Delay_us
//------------------------------------------------------
void Delay_us (uint32_t time)
{
	uint32_t i=0;
	uint32_t j=0;
	for (i=0;i<time;i++)
	{
		for (j=0;j<delay_const;j++){}
	}
}
//------------------------------------------------------
//Delay_ms
//------------------------------------------------------
void Delay_ms (uint32_t time)
{
	uint32_t i=0;
	for (i=0;i<time;i++)
	{
		Delay_us(1000);
	}
}
