#include "stm32f4xx.h"                  // Device header
#include <stdio.h>

void USART2_init(void);

int main(void)
{
	int n;
	char str[100];
	USART2_init();
	
	printf("Hello from the other side\r\n");
	fprintf(stdout,"test for stdout\r\n");
	fprintf(stderr,"test for stderr\r\n");
	
	while(1)
	{
		printf("How old are you ?");
		scanf("%d", &n);
		printf("Your age is : %d\r\n",n);
		printf("Enter your first name :");
		gets(str);
		printf("Hi :");
		puts(str);
		printf("\r\n");
	}
}








void USART2_init(void)
{
	// enable clock for usart2 bus.
	// set alternate function for usart2 TX and RX GPIO pins
	// 
	
	RCC->AHB1ENR |= 1;				// Enable GPIOA Clock
	RCC->APB1ENR |= 0x20000;	// Enable USART2 Clock
	
	// Configure PA3 as USART2 RX, PA2 as USART2 TX.
	GPIOA->AFR[0] |= 0x7000;	// Alt7 for USART2 rx
	GPIOA->AFR[0] |= 0x0700;	// enable alternate function usart2 tx
	
	GPIOA->MODER	|= 0x00A0;	// Enable alternate function at PA3 and PA2
	
	USART2->BRR  = 0x0683;		// 9600 baudrate @16mHZ
	USART2->CR1	 = 0x000C; 		// Enable RX, TX
	USART2->CR1 |= 0x2000;		// Enable USART2
}

int USART2_write(int ch)
{
	//Wait for Tx buffer empty
	while(!(USART2->SR & 0x0080)){}
	USART2->DR = (ch& 0xFF);
	return ch;
}

int USART2_read(void)
{
	//Wait for Rx buffer empty
	while(!(USART2->SR & 0x0020)){}
	return USART2->DR;
}

struct __FILE { int handle; };
FILE __stdin  = {0};
FILE __stdout = {1};
FILE __stderr = {2};

int fgetc(FILE *f)
{
	int c;
	c = USART2_read();
	if(c == '\r'){
		USART2_write(c);
		c='\n';
	}
	USART2_write(c);
	
	return c;
}

int fputc(int c, FILE *f)
{
	return USART2_write(c);
}
