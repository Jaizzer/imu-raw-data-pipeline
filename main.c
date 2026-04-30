#include "stm32f411xe.h"
#include <stdint.h>

int main(void) {
    // Enable GPIOB and I2C1
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->AHB1ENR |= RCC_APB1ENR_I2C1EN;
  
    // First, "erase" the current Job Description for PB6 and PB7.
    // GPIO_MODER_MODE6_Msk is 0b11. Using &= ~ forces both bits to 00 (Input mode).
    // This ensures we have a clean slate before assigning a new mode.
    GPIOB->MODER &= ~(GPIO_MODER_MODE6_Msk | GPIO_MODER_MODE7_Msk);

    // Now, assign the 'Alternate Function' job description (Binary 10).
    // We use the _1 suffix because it targets the "left-hand" bit of the 2-bit pair.
    // This tells the pins: "You are no longer general GPIO; you are now specialists."
    GPIOB->MODER |= (GPIO_MODER_MODE6_1 | GPIO_MODER_MODE7_1);

    // Map to AF4 (I2C), clear the bits though.
    GPIOB->AFR[0] &= ~(0xF << 24 | 0xF << 28);

    // PB6 takes the second "4-bits" starting at bit 4, PB7 takes the third "4-bits" starting
    // at bit 8
    GPIOB->AFR[0] |= (4 << 24) | (4 << 28);
}

void __libc_init_array(void) {}