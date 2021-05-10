#include "lm4f120h5qr.h"

#define LED_RED   (1U << 1)
#define LED_BLUE  (1U << 2)
#define LED_GREEN (1U << 3)

int main(){
    SYSCTL_RCGCGPIO_R |= (1U << 5);     // enable clock for GPIOF
    GPIO_PORTF_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN);     // set pins 1,2 and 3 as outputs
    GPIO_PORTF_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN);

    GPIO_PORTF_DATA_R |= LED_BLUE;      // turn blue led on
    while(1){
        GPIO_PORTF_DATA_R |= LED_RED;   // turn red on

        int volatile counter = 0;
        while (counter < 1000000){      // delay
            ++counter;
        }

        GPIO_PORTF_DATA_R &= ~LED_RED;  // turn red off
        counter = 0;
        while (counter < 1000000){
            ++counter;
        }
    }
    return 0;
}

/*
    c = a | b;    // OR
    c = a & b;    // AND
    c = a ^ b;    // exclusive OR
    c = ~b;       // NOT
    c = b >> 1;   // right=shift
    c = b << 3;   // left-shift
*/