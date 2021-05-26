#include "stm32f4xx.h"                  // Device header

//PA5 - LED
//PC13 - Push button

int main(void)
{
	RCC ->AHB1ENR |= 4;			// enable clock for gpio port C
	RCC ->AHB1ENR |= 1;			// enable clock for gpio port A

	GPIOA->MODER |= 0x400;						// set PA5 output, 0b 0000 0000 0000 0000 0000 0100 0000 0000 , corresponds to pin 5.
	while(1)
	{
		if(GPIOC->IDR & 0x2000)	// if PC13 is high
		{
			GPIOA->BSRR = 0x200000;	// turn off LED using reset part of BSRR register.
		}
		else{
			GPIOA->BSRR = 0x20;		// Turn on the LED using set part of BSRR register.
		}
	}
}
