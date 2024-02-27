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
#define GPIOB_BASE_ADDRESS			(IOPORT_BASE_ADDRESS + 0x400)
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

// DEFINITIONS
GPIO_REG_DEF *GPIOA = GPIOA_BASE_ADDRESS;
GPIO_REG_DEF *GPIOB = GPIOB_BASE_ADDRESS;
GPIO_REG_DEF *GPIOC = GPIOC_BASE_ADDRESS;
RCC_REG_DEF *RCC = RCC_BASE_ADDRESS;

int main(void) {

    // ENABLE GPIO A, B & C CLOCK
    RCC->IOPENR |= 1<<0 | 1<<1 | 1<<2;

    // SET ENABLE PINS AS OUTPUTS
    GPIOA->MODER &= ~(1<<17);   // PA8	// Display 1
    GPIOA->MODER &= ~(1<<1);	// PA0	// Display 2
    GPIOA->MODER &= ~(1<<15);	// PA7	// Display 3
    GPIOC->MODER &= ~(1<<1);	// PC0	// Display 4
    GPIOC->MODER &= ~(1<<15);	// PC7	// Display 5
    GPIOC->MODER &= ~(1<<3);	// PC1	// Display 6
    GPIOA->MODER &= ~(1<<3);	// PA1	// Display 7
    GPIOA->MODER &= ~(1<<19);	// PA9	// Display 8

    // SET SEGMENT PINS AS OUTPUTS
    GPIOB->MODER &= ~(1<<1);	// PB0	// A
    GPIOB->MODER &= ~(1<<19);	// PB9	// B
    GPIOB->MODER &= ~(1<<21);	// PB10	// C
    GPIOB->MODER &= ~(1<<7);	// PB3	// D
    GPIOB->MODER &= ~(1<<9);	// PB4	// E
    GPIOB->MODER &= ~(1<<11);	// PB5	// F
    GPIOB->MODER &= ~(1<<13);	// PB6	// G
    GPIOB->MODER &= ~(1<<17);	// PB8	// DP

	while(1) {

		uint8_t d;
		uint8_t n;

		for (d = 1; d < 9; d++){

			for (n = 0; n < 11; n++){

				enable_display(d);
				print_digit(n);
				delay_ms(500);
				turn_off();
				delay_ms(500);
			}
		}
	}
}

void turn_off(){

	GPIOA->BSRR |= 1<<(8+16);
	GPIOA->BSRR |= 1<<(0+16);
	GPIOA->BSRR |= 1<<(7+16);
	GPIOC->BSRR |= 1<<(0+16);
	GPIOC->BSRR |= 1<<(7+16);
	GPIOC->BSRR |= 1<<(1+16);
	GPIOA->BSRR |= 1<<(1+16);
	GPIOA->BSRR |= 1<<(9+16);

	GPIOB->BSRR |= 1<<(0+16);
	GPIOB->BSRR |= 1<<(9+16);
	GPIOB->BSRR |= 1<<(10+16);
	GPIOB->BSRR |= 1<<(3+16);
	GPIOB->BSRR |= 1<<(4+16);
	GPIOB->BSRR |= 1<<(5+16);
	GPIOB->BSRR |= 1<<(6+16);
	GPIOB->BSRR |= 1<<(8+16);
}

void delay_ms(uint16_t n) {

    uint16_t i;

    for (; n > 0; n--) {

        for (i = 0; i < 140; i++) {
        }
    }
}

void enable_display(uint8_t display){

	switch(display){

		case 1 :{
			GPIOA->BSRR |= 1<<8;
			break;
		}
		case 2 :{
			GPIOA->BSRR |= 1<<0;
			break;
		}
		case 3 :{
			GPIOA->BSRR |= 1<<7;
			break;
		}
		case 4 :{
			GPIOC->BSRR |= 1<<0;
			break;
		}
		case 5 :{
			GPIOC->BSRR |= 1<<7;
			break;
		}
		case 6 :{
			GPIOC->BSRR |= 1<<1;
			break;
		}
		case 7 :{
			GPIOA->BSRR |= 1<<1;
			break;
		}
		case 8 :{
			GPIOA->BSRR |= 1<<9;
			display = 1;
			break;
		}
		default:{
			break;
		}
	}
}

void print_digit(uint8_t value){

	switch(value){

		case 0 :{

			GPIOB->BSRR |= 1<<0;    // A
			GPIOB->BSRR |= 1<<9;    // B
			GPIOB->BSRR |= 1<<10;   // C
			GPIOB->BSRR |= 1<<3;    // D
			GPIOB->BSRR |= 1<<4;    // E
			GPIOB->BSRR |= 1<<5;    // F
			break;
		}
		case 1 :{

			GPIOB->BSRR |= 1<<9;    // B
			GPIOB->BSRR |= 1<<10;   // C
			break;
		}
		case 2 :{

			GPIOB->BSRR |= 1<<0;    // A
			GPIOB->BSRR |= 1<<9;    // B
			GPIOB->BSRR |= 1<<3;    // D
			GPIOB->BSRR |= 1<<4;    // E
			GPIOB->BSRR |= 1<<6;    // G
			break;
		}
		case 3 :{

			GPIOB->BSRR |= 1<<0;    // A
			GPIOB->BSRR |= 1<<9;    // B
			GPIOB->BSRR |= 1<<10;   // C
			GPIOB->BSRR |= 1<<3;    // D
			GPIOB->BSRR |= 1<<6;    // G
			break;
		}
		case 4 :{

			GPIOB->BSRR |= 1<<9;    // B
			GPIOB->BSRR |= 1<<10;   // C
			GPIOB->BSRR |= 1<<5;    // F
			GPIOB->BSRR |= 1<<6;    // G
			break;
		}
		case 5 :{

			GPIOB->BSRR |= 1<<0;    // A
			GPIOB->BSRR |= 1<<10;   // C
			GPIOB->BSRR |= 1<<3;    // D
			GPIOB->BSRR |= 1<<5;    // F
			GPIOB->BSRR |= 1<<6;    // G
			break;
		}
		case 6 :{

			GPIOB->BSRR |= 1<<0;    // A
			GPIOB->BSRR |= 1<<10;   // C
			GPIOB->BSRR |= 1<<3;    // D
			GPIOB->BSRR |= 1<<4;    // E
			GPIOB->BSRR |= 1<<5;    // F
			GPIOB->BSRR |= 1<<6;    // G
			break;
		}
		case 7 :{

			GPIOB->BSRR |= 1<<0;    // A
			GPIOB->BSRR |= 1<<9;    // B
			GPIOB->BSRR |= 1<<10;   // C
			break;
		}
		case 8 :{

			GPIOB->BSRR |= 1<<0;    // A
			GPIOB->BSRR |= 1<<9;    // B
			GPIOB->BSRR |= 1<<10;   // C
			GPIOB->BSRR |= 1<<3;    // D
			GPIOB->BSRR |= 1<<4;    // E
			GPIOB->BSRR |= 1<<5;    // F
			GPIOB->BSRR |= 1<<6;    // G
			break;
		}
		case 9 :{

			GPIOB->BSRR |= 1<<0;    // A
			GPIOB->BSRR |= 1<<9;    // B
			GPIOB->BSRR |= 1<<10;   // C
			GPIOB->BSRR |= 1<<3;    // D
			GPIOB->BSRR |= 1<<5;    // F
			GPIOB->BSRR |= 1<<6;    // G
			break;
		}
		case 10 :{

			GPIOB->BSRR |= 1<<8;    // DP
			value=0;
			break;
		}
		default:{
			break;
		}
	}
}
