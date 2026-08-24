#include "stm32f4xx.h"

constexpr uint32_t GPIOAEN = (1U << 0);
constexpr uint32_t PIN5    = (1U << 5);
constexpr uint32_t LED_PIN = PIN5;

int main()
{
	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

	while (true)
	{
		GPIOA->ODR ^= LED_PIN;
		for (int i = 0; i < 100000; i++) {}
	}
}
