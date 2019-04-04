#include "led.h"


// Setup LED1
void init_led1(void){
    P1->SEL0 &= ~BIT_0;
    P1->SEL1 &= ~BIT_0;
    P1->DIR |= GPIO_1_MODE_OUTPUT;
    P1->OUT &= ~LED1_STATE_ON;
}

// Toggle LED1
void toggle_led1(void){
    P1->OUT ^= LED1_STATE_ON;
}


// Setup RGB LED
void init_led_rgb(void){
    P1->SEL0 &= ~PIN_RGB_SEL0_GPIO;
    P1->SEL1 &= ~PIN_RGB_SEL1_GPIO;
    P2->DIR |= GPIO_RGB_MODE_OUTPUT;
    P2->OUT &= ~LED_RGB_STATE_ON;
}

// Set 3 bits of RGB LED
void set_led_rgb_value(int value){
    P2->OUT &= ~LED_RGB_STATE_ON;
    P2->OUT |= (value & LED_RGB_STATE_ON);
}


