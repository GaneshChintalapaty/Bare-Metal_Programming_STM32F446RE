#include<stdio.h>
#include<stdint.h>
#include "stm32f446xx.h"
#include<uart.h>

int main(void)
{
	uart2_init();
	while(1)
	{
		printf("Hello from STM32F466E!\n\r");	//Send data to serial port
		for(int i = 0; i < 1000000; i++);		//Delay
	}
}


