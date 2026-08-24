#include <cstdio>
#include <cstdint>
#include "stm32f4xx.h"
#include "uart.hpp"
#include "adc.hpp"
#include "systick.hpp"

constexpr uint32_t GPIOAEN = (1U << 0);
constexpr uint32_t PIN5    = (1U << 5);

constexpr uint32_t LED = PIN5;

int main()
{
	/*1.Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;

	/*2.Set PA5 as output pin*/
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

	uart2_tx_init();

	while (true)
	{
		printf("A second passed !! \n\r");
		GPIOA->ODR ^= LED;
		systickDelayMs(1000);
	}
}
