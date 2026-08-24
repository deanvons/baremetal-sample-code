#include <cstdio>
#include <cstdint>
#include "stm32f4xx.h"
#include "uart.hpp"

int main()
{
	uar2_tx_init();

	while (true)
	{
		printf("Hello from STM32F4........\n\r");
	}
}
