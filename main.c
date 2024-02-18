// GABRIEL CUÁ
// ON-OFF LED & EVENT COUNT

#include <stdint.h>

// PERIPHERAL & BUS BASE ADDRESS
#define PERIPHERAL_BASE_ADDRESS			0x40000000U
#define FLASH_BASE_ADDRESS			0X08000000U
#define AHB_BASE_ADDRESS			0x40020000U
#define APB1_BASE_ADDRESS	 		0x40000000U
#define APB2_BASE_ADDRESS			0x40010000U

// IOPORT BASE ADDRESS
#define IOPORT_BASE_ADDRESS			0X50000000U

// GPIO BASE & SPECIFIC ADDRESS
#define GPIOA_BASE_ADDRESS			(IOPORT_BASE_ADDRESS + 0x00)
#define GPIOC_BASE_ADDRESS			(IOPORT_BASE_ADDRESS + 0x800)

// RCC BASE ADDRESS
#define RCC_BASE_ADDRESS			(AHB_BASE_ADDRESS + 0X1000)

// FUNCTIONS
void delay_ms(uint16_t);

// STRUCTS
typedef struct
{
	uint32_t MODER;
	uint32_t OTYPER;
	uint32_t OSPEEDR;
	uint32_t PUPDR;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t LCKR;
	uint32_t AFR[2];
	uint32_t BRR;
}GPIO_REG_DEF;

typedef struct
{
	uint32_t CR;
	uint32_t ICSCR;
	uint32_t CRRCR;
	uint32_t CFGR;
	uint32_t CIER;
	uint32_t CIFR;
	uint32_t CICR;
	uint32_t IOPRSTR;
	uint32_t AHBRSTR;
	uint32_t APB2RSTR;
	uint32_t APB1RSTR;
	uint32_t IOPENR;
	uint32_t AHBENR;
	uint32_t APB2ENR;
	uint32_t APB1ENR;
	uint32_t IOPSMENR;
	uint32_t AHBSMENR;
	uint32_t APB2SMENR;
	uint32_t APB1SMENR;
	uint32_t CCIPR;
	uint32_t CSR;
}RCC_REG_DEF;

int main(void) {

	GPIO_REG_DEF *GPIOA = GPIOA_BASE_ADDRESS;
	GPIO_REG_DEF *GPIOC = GPIOC_BASE_ADDRESS;
	RCC_REG_DEF *RCC = RCC_BASE_ADDRESS;

	// ENABLE GPIO A & C CLOCK
	RCC->IOPENR |= 1<<0 | 1<<2;

	GPIOA->MODER &= ~(1<<13);	// SET PA6 AS OUTPUT
	GPIOC->MODER &= ~(1<<15);	// SET PC7 AS INPUT
	GPIOC->MODER &= ~(1<<14);	// SET PC7 AS INPUT
	GPIOA->MODER &= ~(1<<18);	// SET PA9 AS INPUT
	GPIOA->MODER &= ~(1<<19);	// SET PA9 AS INPUT

	uint8_t counter = 0;
	uint8_t prev_button_state = 0;

	while(1)
	{
		if(GPIOC->IDR & 1<<7) {

            GPIOA->BSRR |= 1<<6;
            delay_ms(200);
            GPIOA->BSRR |= 1<<(6 + 16);
            delay_ms(200);
		}
		else {

            GPIOA->BSRR |= 1<<6;
            delay_ms(500);
            GPIOA->BSRR |= 1<<(6 + 16);
            delay_ms(500);
		}

		uint8_t current_button_state = (GPIOA->IDR & (1 << 9)) >> 9;

		if (current_button_state != prev_button_state) {

			if (current_button_state == 1) {

				counter++;
			}
			prev_button_state = current_button_state;
		}
	}
}

void delay_ms(uint16_t n) {

    uint16_t i;

    for (; n > 0; n--) {

        for (i = 0; i < 140; i++) {
        }
    }
}
