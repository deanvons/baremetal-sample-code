#include "stm32f4xx.h"
#include "adc.hpp"

constexpr uint32_t GPIOAEN       = (1U << 0);
constexpr uint32_t ADC1EN        = (1U << 8);
constexpr uint32_t ADC_CH1       = (1U << 0);
constexpr uint32_t ADC_SEQ_LEN_1 = 0x00;
constexpr uint32_t CR2_AD0N      = (1U << 0);
constexpr uint32_t CR2_SWSTART   = (1U << 30);
constexpr uint32_t SR_EOC        = (1U << 1);

void pa1_adc_init()
{
	/***Configure the ADC GPIO pin ***/

	/*Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;

	/*Set the mode of PA1 to analog*/
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);

	/***Configure the ADC module***/
	/*Enable clock access to ADC */
	RCC->APB2ENR |= ADC1EN;

	/*Conversion sequence start*/
	ADC1->SQR3 = ADC_CH1;

	/*Conversion sequence length*/
	ADC1->SQR1 = ADC_SEQ_LEN_1;

	/*Enable ADC module*/
	ADC1->CR2 |= CR2_AD0N;
}

void start_converstion()
{
	/*Start adc conversion*/
	ADC1->CR2 |= CR2_SWSTART;
}

uint32_t adc_read()
{
	/*Wait for conversion to be complete*/
	while (!(ADC1->SR & SR_EOC)) {}

	/*Read converted result*/
	return (ADC1->DR);
}
