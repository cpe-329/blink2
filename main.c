#include "msp.h"

#include "watchdog.h"
#include "delay.h"
#include "led.h"

#define DELAY (100)
#define FREQ FREQ_24_MHZ
void main(void)
{
   	DISABLE_WATCHDOG()

    init_dco();

   	set_dco(FREQ);

    init_led1();
//    init_led_rgb();

    toggle_led1();

    volatile int i;
//    int rgb_value = 0;

    while(1)
    {
        toggle_led1();

//        if (rgb_value == LED_RGB_STATE_ON + 1){
//            rgb_value = 01;
//        }

//        set_led_rgb_value(rgb_value);
//        rgb_value = rgb_value + 1;
        delay_ms(DELAY, FREQ);
//
//        set_led_rgb_value(0);
//        delay_ms(DELAY, FREQ);
    }
}
