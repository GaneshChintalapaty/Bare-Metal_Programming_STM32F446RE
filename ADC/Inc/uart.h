/*
 * uart.h
 *
 *  Created on: Feb 8, 2026
 *      Author: GaneshChintalapaty
 */

#ifndef UART_H_
#define UART_H_
#include "stm32f446xx.h"
#include<stdint.h>

void uart2_init_tx(void);
char uart2_Read(void);
void uart2_init_tx_rx(void);

#endif /* UART_H_ */
