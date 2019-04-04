#include "msp.h"

#include "watchdog.h"
#include "delay.h"
#include "led.h"

#define DELAY (10000)

void main(void)
{
   	DISABLE_WATCHDOG()

    init_led1();
    init_led_rgb();

    toggle_led1();

    volatile uint32_t i;
   uint32_t rgb_value = 0;

    while(1)
    {
        toggle_led1();

        if (rgb_value == LED_RGB_STATE_ON + 1){
            rgb_value = 0;
        }

        set_led_rgb_value(rgb_value);
        rgb_value = rgb_value + 1;
        delay_for_loop(DELAY);
        set_led_rgb_value(0);
        delay_for_loop(DELAY);
    }
}
