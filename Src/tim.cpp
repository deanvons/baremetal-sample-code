#include "stm32f4xx.h"
#include "tim.hpp"

constexpr uint32_t TIM2EN  = (1U << 0);
constexpr uint32_t CR1_CEN = (1U << 0);

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
