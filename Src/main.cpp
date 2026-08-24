#include <cstdint>

constexpr uint32_t PERIPH_BASE       = 0x40000000UL;
constexpr uint32_t AHB1PERIPH_OFFSET = 0x00020000UL;
constexpr uint32_t AHB1PERIPH_BASE   = PERIPH_BASE + AHB1PERIPH_OFFSET;
constexpr uint32_t GPIOA_OFFSET      = 0x0000UL;
constexpr uint32_t GPIOA_BASE        = AHB1PERIPH_BASE + GPIOA_OFFSET;

constexpr uint32_t RCC_OFFSET = 0x3800UL;
constexpr uint32_t RCC_BASE   = AHB1PERIPH_BASE + RCC_OFFSET;

constexpr uint32_t GPIOAEN = (1U << 0);

constexpr uint32_t PIN5    = (1U << 5);
constexpr uint32_t LED_PIN = PIN5;

struct RCC_TypeDef
{
	volatile uint32_t DUMMY[12];
	volatile uint32_t AHB1ENR;       /*!< RCC AHB1 peripheral clock register, Address offset: 0x30 */
};

struct GPIO_TypeDef
{
	volatile uint32_t MODER;    /*!< GPIO port mode register, Address offset: 0x00 */
	volatile uint32_t DUMMY[4];
	volatile uint32_t ODR;      /*!< GPIO port output data register, Address offset: 0x14 */
};

#define RCC   (reinterpret_cast<RCC_TypeDef*>(RCC_BASE))
#define GPIOA (reinterpret_cast<GPIO_TypeDef*>(GPIOA_BASE))

int main()
{
	/*1. Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;

	/*2.Set PA5 as output pin*/
	GPIOA->MODER |= (1U<<10);  // Set bit 10 to 1
	GPIOA->MODER &=~(1U<<11); //  Set bit 11 to 0

	while (true)
	{
		GPIOA->ODR ^= LED_PIN;
		for (int i = 0; i < 100000; i++) {}
	}
}
