/*
 * adc.c
 *
 *  Created on: Feb 9, 2026
 *      Author: GaneshChintalapaty
 */

#include<adc.h>
#include "stm32f446xx.h"

#define GPIOAEN (1U<<0)	//Enable GPIOA
#define ADC1EN (1U<<8)	//To enable ADC module

void PA1_ADC_Init(void)
{
	//Configure the ADC GPIO pin
	RCC->AHB1ENR |= GPIOAEN;
	//Enable clock access to GPIOA
	//Set PA1 to analog mode
	//Configure ADC module
	//Enable clock access to ADC module
	//Configure ADC parameters
}
