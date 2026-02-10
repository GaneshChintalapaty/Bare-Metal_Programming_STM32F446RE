/*
 * uart.c
 *
 *  Created on: Feb 8, 2026
 *      Author: GaneshChintalapaty
 */

#include<uart.h>

#define GPIOAEN (1U<<0)		//To enable clock access to GPIOA
#define UART2EN (1U<<17)	//17th Bit to enable USART/UART 2 on APB1 bus - refer data sheet
#define CR1_TE (1U<<3)		//Enable TX
#define CR1_RE (1U<<2)		//Enable RX
#define CR1_UE (1U<<13)		//Enable UART
#define SR_TXE (1U<<7)		//Transmit register (SR - Status Register)
#define SR_RXNE (1U<<5)		//Receive register (SR - Status Register)

#define SYS_Freq 16000000	//16MHz clock
#define APB1_CLK SYS_Freq
#define UART_BaudRate 115200

static void UART_set_BaudRate(USART_TypeDef *USARTx, uint32_t PeriphCLK, uint32_t BaudRate);
static uint16_t compute_UART_BD(uint32_t PeriphCLK, uint32_t BaudRate);
void UART2_write(int ch);

int __io_putchar(int ch)
{
	UART2_write(ch);
	return ch;
}

void uart2_init_tx(void)
{
	//Configure GPIO pins
	//Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;
	//Set PA2 mode to alternate function mode
	GPIOA->MODER &= ~(1U<<4);	//Clear bit 4
	GPIOA->MODER |= (1U<<5);	//Set bit 5 to set PA2 in alternate function mode - refer data sheet
	//Set PA2 alternate function type to UART_TX (AF07) refer data sheet for the truth table
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

	//Configure UART module
	//Enable clock access to UART2
	RCC->APB1ENR |= UART2EN;
	//Configure UART baud rate
	UART_set_BaudRate(USART2, APB1_CLK, UART_BaudRate);
	//Configure transfer direction
	USART2->CR1 = CR1_TE;
	//Enable UART module
	USART2->CR1 |= CR1_UE;

}

void uart2_init_tx_rx(void)
{
	//Configure GPIO pins
	//Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;
	//Set PA2 mode to alternate function mode
	GPIOA->MODER &= ~(1U<<4);	//Clear bit 4
	GPIOA->MODER |= (1U<<5);	//Set bit 5 to set PA2 in alternate function mode - refer data sheet
	//Set PA2 alternate function type to UART_TX (AF07) refer data sheet for the truth table
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);
	//Set PA3 mode to alternate function mode
	GPIOA->MODER &= ~(1U<<6);	//Clear bit 6
	GPIOA->MODER |= (1U<<7);	//Set bit 7 to set PA2 in alternate function mode - refer data sheet
	//Set PA alternate function type to UART_TX (AF07) refer data sheet for the truth table
	GPIOA->AFR[0] |= (1U<<12);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] &= ~(1U<<15);


	//Configure UART module
	//Enable clock access to UART2
	RCC->APB1ENR |= UART2EN;
	//Configure UART baud rate
	UART_set_BaudRate(USART2, APB1_CLK, UART_BaudRate);
	//Configure transfer direction
	USART2->CR1 = (CR1_TE | CR1_RE);
	//Enable UART module
	USART2->CR1 |= CR1_UE;

}

char uart2_Read(void)
{
	//Make sure receive data register is not empty
	while(!(USART2->SR & SR_RXNE));
	//Read Data
	return USART2->DR;
}

void UART2_write(int ch)
{
	//Make sure transmit data register is empty
	while(!(USART2->SR & SR_TXE));
	//Write to transmit data register
	USART2->DR = (ch & 0xFF);
}

static void UART_set_BaudRate(USART_TypeDef *USARTx, uint32_t PeriphCLK, uint32_t BaudRate)
{
	USARTx->BRR = compute_UART_BD(PeriphCLK, BaudRate);
}

static uint16_t compute_UART_BD(uint32_t PeriphCLK, uint32_t BaudRate)
{
	return ((PeriphCLK + (BaudRate/2U))/BaudRate);
}

