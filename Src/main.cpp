#include <cstdio>
#include <cstdint>
#include "stm32f4xx.h"
#include "uart.hpp"
#include "adc.hpp"
#include "systick.hpp"
#include "tim.hpp"

// Setup: connect a jumper wire from PA5 to PA6

int timestamp = 0;

int main()
{
	tim2_pa5_output_compare();
	tim3_pa6_input_capture();

	while (true)
	{
		/*Wait until edge is captured*/
		while (!(TIM3->SR & SR_CC1IF)) {}

		/*Read captured value*/
		timestamp = TIM3->CCR1;
	}
}
