// PA5 LED
// AHB1
// RCC->AHB1ENR
// GPIOx_MODER
// GPIOx_ODR

#include "stm32f4xx.h"              // Device header
void delayMs (int delay);

int main(void)
{
	RCC->AHB1ENR |= 1; 							  // enalbe GPIOA clock
	
	GPIOA->MODER |= 0x400;						// 0b 0000 0000 0000 0000 0000 0100 0000 0000 , corresponds to pin 5.
																				
 	
	while(1){
		
		GPIOA->ODR = 0x20;							// ob 0010 0000
		delayMs(100);
		GPIOA->ODR &=~0x20;						// sets only bit 5 low
		delayMs(100);
	
	}
}

void delayMs (int delay)
{
	int i;
	for(; delay>0;delay--){
		for(i =0;i<3195;i++);
	}
}

