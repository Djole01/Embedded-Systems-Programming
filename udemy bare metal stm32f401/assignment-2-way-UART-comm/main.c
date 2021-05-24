#include "stm32f4xx.h"                  // Device header

//PC13 - Push button
//PA5 - LED

void delayMs(int delay);
char USART2_read(void);
void USART2_Init(void);
void LED_play(int value);
void USART_write(int ch);
void push_button(void);

// push keyboard button on pc to control led on mcu
// push button on mcu to display message in tera term.
// to do , push button and then send the message if pushed.
int main(void)
{
	char c;
	RCC->AHB1ENR |=1;	      	// Enable Clock to PortA (for LED)
	RCC->AHB1ENR |=4;					// Enable clock for PortC (for PushButton)
	GPIOA->MODER |=0x400;			// Set pin as output, LED
	
	USART2_Init();
	
	while(1)
	{
		c = USART2_read();
		LED_play(c);
		push_button();
	}
}

void USART2_Init(void)
{
	RCC->AHB1ENR |= 1;				// Enable GPIOA Clock
	RCC->APB1ENR |= 0x20000;	// Enable USART2 Clock
	
	// Configure PA3 as USART2 RX, PA2 as USART2 TX.
	GPIOA->AFR[0] |= 0x7000;	// Alt7 for USART2 rx
	GPIOA->AFR[0] |= 0x0700;	// enable alternate function usart2 tx				- could've been written as 0x7700;
	
	GPIOA->MODER	|= 0x0080;	// Enable alternate function at PA3
	GPIOA->MODER  |= 0x0020;	// Enable alternate function at PA2
	
	USART2->BRR  = 0x0683;		// 9600 baudrate @16mHZ
	USART2->CR1	 = 0x0004; 		// Enable RX
	USART2->CR1 |=	0x0008;		// Enable TX
	USART2->CR1 |= 0x2000;		// Enable USART2
	
}

char USART2_read(void)
{
	if(USART2->SR & 0x0020){			// if char arrived
		return USART2->DR;
	}
	else {
		return 0;
	}
}

// blinks n amount of times based on char entered
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

void USART_write(int ch)
{
	// wait while TX buffer is empty
	while(!(USART2->SR & 0x0080)){}
		USART2->DR = (ch & 0xFF);
}

void push_button(void)
{
		if(!(GPIOC->IDR & 0x2000))	// if PC13 is high
		{
			USART_write('H');
			USART_write('i');
			delayMs(1000);
		}
}

