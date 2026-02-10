#include<stdio.h>
#include<stdint.h>
#include "stm32f446xx.h"
#include<uart.h>

#define GPIOAEN (1U<<0)
#define GPIOA_5 (1U<<5)
#define LEDPIN GPIOA_5

char key;

int main(void)
{
	//Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;
	//Set PA5 as OUTPUT pin
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);
	//INIT UART module
	uart2_init_tx_rx();
	while(1)
	{
		key = uart2_Read();
		if(key =='1')
		{
			GPIOA->ODR |= LEDPIN;
		}
		else
		{
			GPIOA->ODR &= ~LEDPIN;
		}
	}
}


