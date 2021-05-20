#include "stm32f4xx.h"                  // Device header

void delayMs(int delay);
char USART2_read(void);
void USART2_Init(void);
void LED_play(int value);


int main(void)
{
	char c;
	RCC->AHB1ENR |=1;	      	// Enable Clock to PortA (for LED)
	GPIOA->MODER |=0x400;			// Set pin as output, LED
	
	USART2_Init();
	
	while(1)
	{
		c = USART2_read();
		LED_play(c);
	}
}

void USART2_Init(void)
{
	RCC->AHB1ENR |= 1;				// Enable GPIOA Clock
	RCC->APB1ENR |= 0x20000;	// Enable USART2 Clock
	
	// Configure PA3 as USART2 RX
	GPIOA->AFR[0] |= 0x7000;	// Alt7 for USART2
	GPIOA->MODER	|= 0x0080;	// Enable alternate function at PA3
	
	USART2->BRR  = 0x008B;		// 115200 baudrate @16mHZ
	USART2->CR1	 = 0x0004; 		// Enable RX
	USART2->CR1 |= 0x2000;		// Enable USART2
	
}

char USART2_read(void)
{
	while(!(USART2->SR & 0x0020)){}	// wait until char arrives
	return USART2->DR;
}

void LED_play(int value)
{
	value %= 16;
	for(; value>0;value--)
	{
		GPIOA->BSRR = 0x20;		// Turn on LED
		delayMs(100);
		GPIOA->BSRR = 0x00200000;	// Turn LED off
		delayMs(100);
	}
	delayMs(400);
}

void delayMs(int delay)
{
	int i;
	for(;delay>0;delay--)
	{
		for(i=0;i<3195;i++);
	}
}
