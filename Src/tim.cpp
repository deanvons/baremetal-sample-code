#include "stm32f4xx.h"
#include "tim.hpp"

constexpr uint32_t TIM2EN = (1U << 0);
constexpr uint32_t TIM3EN = (1U << 1);

constexpr uint32_t CR1_CEN   = (1U << 0);
constexpr uint32_t OC_TOGGLE = ((1U << 4) | (1U << 5));
constexpr uint32_t CCER_CC1E = (1U << 0);

constexpr uint32_t GPIOAEN   = (1U << 0);
constexpr uint32_t AFR5_TIM  = (1U << 20);
constexpr uint32_t AFR6_TIM  = (1U << 25);
constexpr uint32_t CCER_CC1S = (1U << 0);

void tim2_1hz_init()
{
	/*Enable clock access to tim2*/
	RCC->APB1ENR |= TIM2EN;

	/*Set prescaler value*/
	TIM2->PSC = 1600 - 1;   //  16 000 000 / 1 600 = 10 000
	/*Set auto-reload value*/
	TIM2->ARR = 10000 - 1;  // 10 000 / 10 000 = 1
	/*Clear counter*/
	TIM2->CNT = 0;

	/*Enable timer*/
	TIM2->CR1 = CR1_CEN;
}

void tim2_pa5_output_compare()
{
	/*Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;

	/*Set PA5 mode to alternate function*/
	GPIOA->MODER &=~(1U<<10);
	GPIOA->MODER |= (1U<<11);

	/*Set PA5 alternate function type to TIM2_CH1 (AF01)*/
	GPIOA->AFR[0] |= AFR5_TIM;

	/*Enable clock access to tim2*/
	RCC->APB1ENR |= TIM2EN;

	/*Set prescaler value*/
	TIM2->PSC = 1600 - 1;   //  16 000 000 / 1 600 = 10 000
	/*Set auto-reload value*/
	TIM2->ARR = 10000 - 1;  // 10 000 / 10 000 = 1

	/*Set output compare toggle mode*/
	TIM2->CCMR1 = OC_TOGGLE;

	/*Enable tim2 ch1 in compare mode*/
	TIM2->CCER |= CCER_CC1E;

	/*Clear counter*/
	TIM2->CNT = 0;
	/*Enable timer*/
	TIM2->CR1 = CR1_CEN;
}

void tim3_pa6_input_capture()
{
	/*Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;

	/*Set PA6 mode to alternate function*/
	GPIOA->MODER &=~(1U<<12);
	GPIOA->MODER |= (1U<<13);

	/*Set PA6 alternate function type to TIM3_CH1 (AF02)*/
	GPIOA->AFR[0] |= AFR6_TIM;

	/*Enable clock access to tim3*/
	RCC->APB1ENR |= TIM3EN;

	/*Set Prescaler*/
	TIM3->PSC = 16000 - 1; // 16 000 000 /16 000

	/*Set CH1 to input capture*/
	TIM3->CCMR1 = CCER_CC1S;

	/*Set CH1 to capture at rising edge*/
	TIM3->CCER = CCER_CC1E;

	/*Enable TIM3*/
	TIM3->CR1 = CR1_CEN;
}
