
#define STM32_GPIO_H

#include <stdint.h>

#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */

/*@} end of group Cortex_M23 */

typedef struct
{
	__IO uint32_t CR;          /*!< RCC clock control register,                                              Address offset: 0x00 */
	__IO uint32_t ICSCR;       /*!< RCC internal clock sources calibration register,                         Address offset: 0x04 */
	__IO uint32_t CFGR;        /*!< RCC clock configuration register,                                        Address offset: 0x08 */
	__IO uint32_t PLLCFGR;     /*!< RCC system PLL configuration register,                                   Address offset: 0x0C */
	__IO uint32_t PLLSAI1CFGR; /*!< RCC PLL SAI1 configuration register,                                     Address offset: 0x10 */
	__IO uint32_t PLLSAI2CFGR; /*!< RCC PLL SAI2 configuration register,                                     Address offset: 0x14 */
	__IO uint32_t CIER;        /*!< RCC clock interrupt enable register,                                     Address offset: 0x18 */
	__IO uint32_t CIFR;        /*!< RCC clock interrupt flag register,                                       Address offset: 0x1C */
	__IO uint32_t CICR;        /*!< RCC clock interrupt clear register,                                      Address offset: 0x20 */
	uint32_t      RESERVED0;   /*!< Reserved,                                                                Address offset: 0x24 */
	__IO uint32_t AHB1RSTR;    /*!< RCC AHB1 peripheral reset register,                                      Address offset: 0x28 */
	__IO uint32_t AHB2RSTR;    /*!< RCC AHB2 peripheral reset register,                                      Address offset: 0x2C */
	__IO uint32_t AHB3RSTR;    /*!< RCC AHB3 peripheral reset register,                                      Address offset: 0x30 */
	uint32_t      RESERVED1;   /*!< Reserved,                                                                Address offset: 0x34 */
	__IO uint32_t APB1RSTR1;   /*!< RCC APB1 peripheral reset register 1,                                    Address offset: 0x38 */
	__IO uint32_t APB1RSTR2;   /*!< RCC APB1 peripheral reset register 2,                                    Address offset: 0x3C */
	__IO uint32_t APB2RSTR;    /*!< RCC APB2 peripheral reset register,                                      Address offset: 0x40 */
	uint32_t      RESERVED2;   /*!< Reserved,                                                                Address offset: 0x44 */
	__IO uint32_t AHB1ENR;     /*!< RCC AHB1 peripheral clocks enable register,                              Address offset: 0x48 */
	__IO uint32_t AHB2ENR;     /*!< RCC AHB2 peripheral clocks enable register,                              Address offset: 0x4C */
	__IO uint32_t AHB3ENR;     /*!< RCC AHB3 peripheral clocks enable register,                              Address offset: 0x50 */
	uint32_t      RESERVED3;   /*!< Reserved,                                                                Address offset: 0x54 */
	__IO uint32_t APB1ENR1;    /*!< RCC APB1 peripheral clocks enable register 1,                            Address offset: 0x58 */
	__IO uint32_t APB1ENR2;    /*!< RCC APB1 peripheral clocks enable register 2,                            Address offset: 0x5C */
	__IO uint32_t APB2ENR;     /*!< RCC APB2 peripheral clocks enable register,                              Address offset: 0x60 */
	uint32_t      RESERVED4;   /*!< Reserved,                                                                Address offset: 0x64 */
	__IO uint32_t AHB1SMENR;   /*!< RCC AHB1 peripheral clocks enable in sleep and stop modes register,      Address offset: 0x68 */
	__IO uint32_t AHB2SMENR;   /*!< RCC AHB2 peripheral clocks enable in sleep and stop modes register,      Address offset: 0x6C */
	__IO uint32_t AHB3SMENR;   /*!< RCC AHB3 peripheral clocks enable in sleep and stop modes register,      Address offset: 0x70 */
	uint32_t      RESERVED5;   /*!< Reserved,                                                                Address offset: 0x74 */
	__IO uint32_t APB1SMENR1;  /*!< RCC APB1 peripheral clocks enable in sleep mode and stop modes register 1, Address offset: 0x78 */
	__IO uint32_t APB1SMENR2;  /*!< RCC APB1 peripheral clocks enable in sleep mode and stop modes register 2, Address offset: 0x7C */
	__IO uint32_t APB2SMENR;   /*!< RCC APB2 peripheral clocks enable in sleep mode and stop modes register, Address offset: 0x80 */
	uint32_t      RESERVED6;   /*!< Reserved,                                                                Address offset: 0x84 */
	__IO uint32_t CCIPR;       /*!< RCC peripherals independent clock configuration register,                Address offset: 0x88 */
	uint32_t      RESERVED7;   /*!< Reserved,                                                                Address offset: 0x8C */
	__IO uint32_t BDCR;        /*!< RCC backup domain control register,                                      Address offset: 0x90 */
	__IO uint32_t CSR;         /*!< RCC clock control & status register,                                     Address offset: 0x94 */
} RCC_TypeDef;


#define RCC ((RCC_TypeDef *)0x40021000)

typedef struct
{
	__IO uint32_t GPIOx_MODER;
	__IO uint32_t GPIOx_OTYPER;
	__IO uint32_t GPIOx_OSPEEDR;


	__IO uint32_t GPIOx_PUPDR;
	__IO uint32_t GPIOx_IDR;
	__IO uint32_t GPIOx_ODR;
	__IO uint32_t GPIOx_BSRR;
	__IO uint32_t GPIOx_LCKR;
	__IO uint32_t GPIOx_AFRL;
	__IO uint32_t GPIOx_AFRH;
	__IO uint32_t GPIOx_BRR;
	__IO uint32_t GPIOx_ASCR;
} GPIOX_TypeDef;


#define GPIOA ((GPIOX_TypeDef *)0x48000000)
#define GPIOB ((GPIOX_TypeDef *)0x48000400)
#define GPIOC ((GPIOX_TypeDef *)0x48000800)
#define GPIOG ((GPIOX_TypeDef *)0x48001800)

typedef struct
{
	__IO uint32_t I2C_CR1;
	__IO uint32_t I2C_CR2;
	__IO uint32_t I2C_OAR1;
	__IO uint32_t I2C_OAR2;
	__IO uint32_t I2C_TIMINGR;
	__IO uint32_t I2C_TIMEOUTR;
	__IO uint32_t I2C_ISR;
	__IO uint32_t I2C_ICR;
	__IO uint32_t I2C_PECR;
	__IO uint32_t I2C_RXDR;
	__IO uint32_t I2C_TXDR;

} I2C_TypeDef;

#define I2C ((I2C_TypeDef *)0x40005400)

typedef struct
{
	__IO uint32_t USART_CR1;
	__IO uint32_t USART_CR2;
	__IO uint32_t USART_CR3;
	__IO uint32_t USART_BRR;
	__IO uint32_t USART_GTPR;
	__IO uint32_t USART_RTOR;
	__IO uint32_t USART_RQR;
	__IO uint32_t USART_ISR;
	__IO uint32_t USART_ICR;
	__IO uint32_t USART_RDR;
	__IO uint32_t USART_TDR;


} USART_TypeDef;

#define USART ((USART_TypeDef *)0x40004400)


typedef struct
{
	__IO uint32_t PWR_CR1;
	__IO uint32_t PWR_CR2;
	__IO uint32_t PWR_CR3;
	__IO uint32_t PWR_CR4;
	__IO uint32_t PWR_SR1;
	__IO uint32_t PWR_SR2;
	__IO uint32_t PWR_SCR;
	__IO uint32_t PWR_PUCRA;
	__IO uint32_t PWR_PDCRA;
	__IO uint32_t PWR_PUCRB;
	__IO uint32_t PWR_PDCRB;
	__IO uint32_t PWR_PUCRC;
	__IO uint32_t PWR_PDCRC;
	__IO uint32_t PWR_PUCRD;
	__IO uint32_t PWR_PDCRD;
	__IO uint32_t PWR_PUCRE;
	__IO uint32_t PWR_PDCRE;
	__IO uint32_t PWR_PUCRF;
	__IO uint32_t PWR_PDCRF;
	__IO uint32_t PWR_PUCRG;
	__IO uint32_t PWR_PDCRG;
	__IO uint32_t PWR_PUCRH;
	__IO uint32_t PWR_PDCRH;
	__IO uint32_t PWR_PUCRI;
	__IO uint32_t PWR_PDCRI;

} PWR_TypeDef;


#define PWR ((PWR_TypeDef *)0x40007000)


