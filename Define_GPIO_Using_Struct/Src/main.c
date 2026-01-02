/*
 * File: main.c
 * author: Ganesh Chintalapaty
 * Objective: Define GPIO registers using struct
 *
 * Board used: NUCLEO-F446RE (STM32F446RE)
 *
 * Where is the LED connected?
 *
 * PORT: PORTA
 * Pin: 5
 *
 * */

#include<stdint.h>

#define PERIPH_BASE 		(0x40000000UL)												//Peripheral Base address
#define AHB1PERIPH_OFFSET 	(0x00020000UL)												//Advanced High-performance Bus 1 offset
#define AHB1PERIPH_BASE		(PERIPH_BASE + AHB1PERIPH_OFFSET)							//Advanced High-performance Bus 1 address
#define GPIOA_OFFSET		(0x00000000UL)												//GPIOA offset
#define GPIOA_BASE			(AHB1PERIPH_BASE + GPIOA_OFFSET)							//GPIOA address
#define RCC_OFFSET			(0x00003800UL)												//Reset Clock Control offset
#define RCC_BASE			(AHB1PERIPH_BASE + RCC_OFFSET)								//Reset Clock Control address
#define GPIOAEN				(1U<<0)														//GPIOA Enable
#define SET_PIN5			(1U<<5)														//Set Pin 5
#define CLEAR_PIN5			~(1U<<5)													//Clear Pin 5

#define __IO volatile

typedef struct
{
	__IO uint32_t MODER;	//GPIO port Mode register offset: 0x00
	__IO uint32_t OTYPER;	//GPIO port output type register offset: 0x04
	__IO uint32_t OSPEEDR;	//GPIO port speed register offset: 0x08
	__IO uint32_t PUPDR;	//GPIO port pull up pull down register offset: 0x0C
	__IO uint32_t IDR;		//GPIO port input data register offset: 0x10
	__IO uint32_t ODR;		//GPIO port output data register offset: 0x14
	__IO uint32_t BSRR;		//GPIO port Bit set Reset register offset: 0x18
	__IO uint32_t LCKR;		//GPIO port configuration lock register offset: 0x1C
	__IO uint32_t AFR[2];	//GPIO port alternative function register offset: 0x20-0x24
}GPIO_TypeDef;

typedef struct
{
  __IO uint32_t CR;           /* RCC clock control register,                     Address offset: 0x00 */
  __IO uint32_t PLLCFGR;      /* RCC PLL configuration register,                 Address offset: 0x04 */
  __IO uint32_t CFGR;         /* RCC clock configuration register,               Address offset: 0x08 */
  __IO uint32_t CIR;          /* RCC clock interrupt register,                   Address offset: 0x0C */
  __IO uint32_t AHB1RSTR;     /* RCC AHB1 peripheral reset register,              Address offset: 0x10 */
  __IO uint32_t AHB2RSTR;     /* RCC AHB2 peripheral reset register,              Address offset: 0x14 */
  __IO uint32_t AHB3RSTR;     /* RCC AHB3 peripheral reset register,              Address offset: 0x18 */
       uint32_t RESERVED0;    /* Reserved, 0x1C */
  __IO uint32_t APB1RSTR;     /* RCC APB1 peripheral reset register,              Address offset: 0x20 */
  __IO uint32_t APB2RSTR;     /* RCC APB2 peripheral reset register,              Address offset: 0x24 */
       uint32_t RESERVED1[2]; /* Reserved, 0x28-0x2C */
  __IO uint32_t AHB1ENR;      /* RCC AHB1 peripheral clock enable register,       Address offset: 0x30 */
  __IO uint32_t AHB2ENR;      /* RCC AHB2 peripheral clock enable register,       Address offset: 0x34 */
  __IO uint32_t AHB3ENR;      /* RCC AHB3 peripheral clock enable register,       Address offset: 0x38 */
       uint32_t RESERVED2;    /* Reserved, 0x3C */
  __IO uint32_t APB1ENR;      /* RCC APB1 peripheral clock enable register,       Address offset: 0x40 */
  __IO uint32_t APB2ENR;      /* RCC APB2 peripheral clock enable register,       Address offset: 0x44 */
       uint32_t RESERVED3[2]; /* Reserved, 0x48-0x4C */
  __IO uint32_t AHB1LPENR;    /* RCC AHB1 peripheral clock enable in low power,   Address offset: 0x50 */
  __IO uint32_t AHB2LPENR;    /* RCC AHB2 peripheral clock enable in low power,   Address offset: 0x54 */
  __IO uint32_t AHB3LPENR;    /* RCC AHB3 peripheral clock enable in low power,   Address offset: 0x58 */
       uint32_t RESERVED4;    /* Reserved, 0x5C */
  __IO uint32_t APB1LPENR;    /* RCC APB1 peripheral clock enable in low power,   Address offset: 0x60 */
  __IO uint32_t APB2LPENR;    /* RCC APB2 peripheral clock enable in low power,   Address offset: 0x64 */
       uint32_t RESERVED5[2]; /* Reserved, 0x68-0x6C */
  __IO uint32_t BDCR;         /* RCC Backup domain control register,              Address offset: 0x70 */
  __IO uint32_t CSR;          /* RCC clock control & status register,             Address offset: 0x74 */
       uint32_t RESERVED6[2]; /* Reserved, 0x78-0x7C */
  __IO uint32_t SSCGR;        /* RCC spread spectrum clock generation register,   Address offset: 0x80 */
  __IO uint32_t PLLI2SCFGR;   /* RCC PLLI2S configuration register,               Address offset: 0x84 */
       uint32_t RESERVED7;    /* Reserved, 0x88 */
  __IO uint32_t DCKCFGR;	  /* RCC Dedicated clocks configuration register*/
} RCC_TypeDef;


#define RCC ((RCC_TypeDef*)RCC_BASE)
#define GPIOA ((GPIO_TypeDef*)GPIOA_BASE)


int main(void)
{
	//Enable clock access to GPIOA//
	RCC->AHB1ENR |= GPIOAEN;

	//SET GPIOA pin 5 as OUTPUT pin//
	GPIOA->MODER |=(1U<<10);	//Set bit 10 of mode register to 1
	GPIOA->MODER &= ~(1U<<11);	//Set bit 11 of mode register to 0

	while(1)
	{
		GPIOA->ODR |= SET_PIN5;				//set pin 5
		for(int i = 0; i < 100000; i++);	//delay
		GPIOA->ODR &= CLEAR_PIN5;			//clear pin 5
		for(int i = 0; i < 100000; i++);	//delay
	}
}
