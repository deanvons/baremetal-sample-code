// Where is the LED connected?
// Port:  A
// Pin:   5

#include <cstdint>

constexpr uint32_t PERIPH_BASE       = 0x40000000UL;
constexpr uint32_t AHB1PERIPH_OFFSET = 0x00020000UL;
constexpr uint32_t AHB1PERIPH_BASE   = PERIPH_BASE + AHB1PERIPH_OFFSET;
constexpr uint32_t GPIOA_OFFSET      = 0x0000UL;
constexpr uint32_t GPIOA_BASE        = AHB1PERIPH_BASE + GPIOA_OFFSET;

constexpr uint32_t RCC_OFFSET = 0x3800UL;
constexpr uint32_t RCC_BASE   = AHB1PERIPH_BASE + RCC_OFFSET;

constexpr uint32_t AHB1EN_R_OFFSET = 0x30UL;
#define RCC_AHB1EN_R (*reinterpret_cast<volatile uint32_t*>(RCC_BASE + AHB1EN_R_OFFSET))

constexpr uint32_t MODE_R_OFFSET = 0x00UL;
#define GPIOA_MODE_R (*reinterpret_cast<volatile uint32_t*>(GPIOA_BASE + MODE_R_OFFSET))

constexpr uint32_t OD_R_OFFSET = 0x14UL;
#define GPIOA_OD_R (*reinterpret_cast<volatile uint32_t*>(GPIOA_BASE + OD_R_OFFSET))

constexpr uint32_t GPIOAEN = (1U << 0);

constexpr uint32_t PIN5    = (1U << 5);
constexpr uint32_t LED_PIN = PIN5;

int main()
{
	/*1. Enable clock access to GPIOA*/
	RCC_AHB1EN_R |= GPIOAEN;

	/*2.Set PA5 as output pin*/
	GPIOA_MODE_R |= (1U<<10);  // Set bit 10 to 1
	GPIOA_MODE_R &=~(1U<<11); //  Set bit 11 to 0

	while (true)
	{
		/*Toggle PA5*/
		GPIOA_OD_R ^= LED_PIN;
		for (int i = 0; i < 100000; i++) {}
	}
}
