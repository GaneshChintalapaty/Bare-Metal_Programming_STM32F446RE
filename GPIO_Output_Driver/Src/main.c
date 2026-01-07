#include "stm32f446xx.h"

#define GPIOAEN (1U<<0)
#define PIN5 	(1U<<5)

int main(void)
{
	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

	while(1)
	{
		GPIOA->ODR ^= PIN5;
		for(int i = 0; i<1000000; i++);
	}
}
