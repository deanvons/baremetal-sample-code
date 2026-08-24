#include <cstdio>
#include <cstdint>
#include "stm32f4xx.h"
#include "uart.hpp"
#include "adc.hpp"
#include "systick.hpp"
#include "tim.hpp"

int main()
{
	tim2_pa5_output_compare();

	while (true)
	{
	}
}
