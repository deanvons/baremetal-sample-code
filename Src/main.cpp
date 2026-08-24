#include "stm32f4xx.h"

constexpr uint32_t GPIOAEN = (1U << 0);
constexpr uint32_t GPIOCEN = (1U << 2);

constexpr uint32_t PIN5  = (1U << 5);
constexpr uint32_t PIN13 = (1U << 13);

constexpr uint32_t LED_PIN = PIN5;
constexpr uint32_t BTN_PIN = PIN13;

int main()
{
	/*Enable clock access to GPIOA and GPIOC*/
	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOCEN;

	/*Set PA5 as output pin*/
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

	/*Set PC13 as input pin*/
	GPIOC->MODER &=~(1U<<26);
	GPIOC->MODER &=~(1U<<27);

	while (true)
	{
		/*Check if BTN is pressed*/
		if (GPIOC->IDR & BTN_PIN)
		{
			/*Turn on led*/
			GPIOA->BSRR = LED_PIN;
		}
		else
		{
			/*Turn off led*/
			GPIOA->BSRR = (1U<<21);
		}
	}
}
