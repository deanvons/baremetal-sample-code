#include <cstdio>
#include <cstdint>
#include "stm32f4xx.h"
#include "uart.hpp"
#include "adc.hpp"

uint32_t sensor_value;

int main()
{
	uart2_tx_init();
	pa1_adc_init();
	start_converstion();

	while (true)
	{
		sensor_value = adc_read();
		printf("Sensor value : %d \n\r", static_cast<int>(sensor_value));
	}
}
