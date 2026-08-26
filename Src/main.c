

#include <stdint.h>
#include "stm32f4xx.h"

#define GPIOAEN			(1U<<0)
#define GPIOCEN			(1U<<2)

#define LED_PIN (1UL << 5)  // define led pin 5
#define BTN_PIN	(1U << 13)	// define button pin 13

void led_on() {
	GPIOA->BSRR = LED_PIN; // turn on led
}

void led_off() {
	GPIOA->BSRR = (1U<<21); // turn off led
}

void toggle_led() {
	GPIOA->ODR ^= LED_PIN;
}


int main(void)
{
	//RCC_AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // turn clock on

	// turn clock on
	RCC->AHB1ENR |=GPIOAEN;
	RCC->AHB1ENR |=GPIOCEN;

	// general purpose output mode: bit pair = 01
	//GPIOA_MODER |= (1U << 10);
	GPIOA->MODER |= (1U << 10);
	//GPIOA_MODER &=~ (1U << 11);
	GPIOA->MODER &=~ (1U << 11);

	// button pin to input
	GPIOC->MODER &=~(1U<<26);
	GPIOC->MODER &=~(1U<<27);

	led_off();

	static int state;

    /* Loop forever */
	for(;;) {

		/*
		if(GPIOC->IDR & BTN_PIN) { // read button
			led_off();
		}
		else {
			led_on();
		}
		*/

		if(GPIOC->IDR & BTN_PIN) {
			state = 1;
		}

		if(!(GPIOC->IDR & BTN_PIN) && state) {
			toggle_led();
			state = 0;
		}
	}
}
