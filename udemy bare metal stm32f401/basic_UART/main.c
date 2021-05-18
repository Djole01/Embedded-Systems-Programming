//APB1 bit 17	:USART2 - enabling clock for APB1 USART2
//USART connected to PA2

#include "stm32f4xx.h"                  // Device header

void USART2_Init(void);
void USART_write(int ch);
void delayMs(int delay);

int main(void){
	
	USART2_Init();
	
	while(1){
		USART_write('H');
		USART_write('i');
		delayMs(1000);
	}
}

void USART2_Init(void){
	RCC->APB1ENR |= 0x20000;	// enable clock for APB1 USART2
	RCC->AHB1ENR |= 1;	// enable clock for PA2

	GPIOA->AFR[0] = 0x0700;	// enable alternate function usart2
	GPIOA->MODER |= 0x0020;	// set pa2 to alternate function
	
	USART2->BRR = 0x0683;	//9600 @16MHZ
	USART2->CR1 =	0x0008;	// 4th bit high, bit 3, enable TX
	USART2->CR1 |= 0x2000;	// bit number 13 high, enable usart2	, configs first, enable module last.
}

void USART_write(int ch){
	// wait while TX buffer is empty
	while(!(USART2->SR & 0x0080)){}
		USART2->DR = (ch & 0xFF);
}

void delayMs(int delay){
	int i;
	for(;delay>0;delay--){
		for(i=0;i<3195;i++);
	}
}
