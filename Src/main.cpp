#include <cstdio>
#include <cstdint>
#include "stm32f4xx.h"
#include "uart.hpp"

constexpr uint32_t GPIOAEN = (1U << 0);
constexpr uint32_t GPIOA_5 = (1U << 5);

constexpr uint32_t LED_PIN = GPIOA_5;

char key;

int main()
{
	/*1.Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;

	/*2.Set PA5 as output pin*/
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);

	uart2_rxtx_init();

	while (true)
	{
		key = uart2_read();
		if (key == '1')
		{
			GPIOA->ODR |= LED_PIN;
		}
		else
		{
			GPIOA->ODR &= ~LED_PIN;
		}
	}
}
