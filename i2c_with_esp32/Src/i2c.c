#include "stm32f446xx.h"



#define 	GPIOBEN			               (1U<<1)
#define 	I2C1EN			               (1U<<21)

#define 	I2C_100KHZ						80	//0B 0101 0000 = Decimal = 80	//0B 0101 0000 = Decimal = 80
#define 	SD_MODE_MAX_RISE_TIME			17
#define		CR1_PE			               (1U<<0)

/*
 * PB8 ---- SCL
 * PB9 ----- SDA
 * */

void I2C1_init(void)
{
	/*Enable clock access to GPIOB*/
	RCC->AHB1ENR |=GPIOBEN;
	/*Set PB8 and PB9 mode to alternate function*/
	GPIOB->MODER &=~(1U<<16);
	GPIOB->MODER |=(1U<<17);

	GPIOB->MODER &=~(1U<<18);
	GPIOB->MODER |=(1U<<19);
	/*Set PB8 and PB9 output type to  open drain*/
	GPIOB->OTYPER |=(1U<<8);
	GPIOB->OTYPER |=(1U<<9);
	/*Enable Pull-up for PB8 and PB9*/
	GPIOB->PUPDR |=(1U<<16);
	GPIOB->PUPDR &=~(1U<<17);

	GPIOB->PUPDR |=(1U<<18);
	GPIOB->PUPDR &=~(1U<<19);
	/*Set PB8 and PB9 alternate function type to I2C (AF4)*/
	GPIOB->AFR[1] &=~(1U<<0);
	GPIOB->AFR[1] &=~(1U<<1);
	GPIOB->AFR[1] |=(1U<<2);
	GPIOB->AFR[1] &=~(1U<<3);

	GPIOB->AFR[1] &=~(1U<<4);
	GPIOB->AFR[1] &=~(1U<<5);
	GPIOB->AFR[1] |=(1U<<6);
	GPIOB->AFR[1] &=~(1U<<7);
	/*Enable clock access to I2C1*/
	RCC->APB1ENR |= I2C1EN;
	/*Enter reset mode  */
	I2C1->CR1 |= (1U<<15);
	/*Come out of reset mode  */
	I2C1->CR1 &=~(1U<<15);
	/*Set Peripheral clock frequency*/
	I2C1->CR2 = (1U<<4);
	/*Set I2C to standard mode, 100kHz clock */
	I2C1->CCR = I2C_100KHZ;
	/*Set rise time */
	I2C1->TRISE = SD_MODE_MAX_RISE_TIME;
	/*Enable I2C1 module */
	I2C1->CR1 |= CR1_PE;

}

void I2C1_byteRead(char saddr, char maddr, char* data) {

      volatile int tmp;

	  /* Wait until bus not busy */
	  while (I2C1->SR2 & (SR2_BUSY)){}

	  /* Generate start */
	  I2C1->CR1 |= CR1_START;

	  /* Wait until start flag is set */
	  while (!(I2C1->SR1 & (SR1_SB))){}

	  /* Transmit slave address + Write */
	   I2C1->DR = saddr << 1;

	  /* Wait until addr flag is set */
	   while (!(I2C1->SR1 & (SR1_ADDR))){}

	  /* Clear addr flag */
	  tmp = I2C1->SR2;

      /* Send memory address */
      I2C1->DR = maddr;

      /*Wait until transmitter empty */
     while (!(I2C1->SR1 & SR1_TXE)){}

     /*Generate restart */
      I2C1->CR1 |= CR1_START;

      /* Wait until start flag is set */
     while (!(I2C1->SR1 & SR1_SB)){}

     /* Transmit slave address + Read */
     I2C1->DR = saddr << 1 | 1;

     /* Wait until addr flag is set */
    while (!(I2C1->SR1 & (SR1_ADDR))){}

    /* Disable Acknowledge */
    I2C1->CR1 &= ~CR1_ACK;

    /* Clear addr flag */
    tmp = I2C1->SR2;

    /* Generate stop after data received */
     I2C1->CR1 |= CR1_STOP;

    /* Wait until RXNE flag is set */
    while (!(I2C1->SR1 & SR1_RXNE)){}

    /* Read data from DR */
      *data++ = I2C1->DR;
}
