#include "stm32f4xx.h"                  // Device header

void delayMs (int delay);

int main(void)
{
	RCC ->AHB1ENR |= 1;			// enable clock
	GPIOA->MODER	|= 0x400; // set as output, led pin
	while(1)
	{
		GPIOA->BSRR = 0x20;		// Set PA5 high
		delayMs(50);
		
		GPIOA->BSRR = 0x00200000;	// 0b 0000 0000 0010 0000 0000 0000 0000 0000 bit reset 5, BSRR bit 21.
		delayMs(400);
		
	
	
	}
}

void delayMs (int delay)
{
	int i;
	for(; delay>0;delay--){
		for(i =0;i<3195;i++);
	}
}
