#include "msp.h"

#include "watchdog.h"
#include "delay.h"
#include "led.h"

#define DELAY (1000)  // Millisecond delay value
#define FREQ FREQ_1_5_MHZ  // DCO frequency to use for main clock


void main(void)
{
   	DISABLE_WATCHDOG  // Watchdog disable macro from watchdog.h

    init_dco();  // Initial the DCO and other clocks to initial values

    init_led1();  // Initialize LED1 for use at GPIO output

    volatile int i;  // Volatile value to prevent shenanigans 


    // Assignment sections, comment out as needed

    // Fastest possible pulse
    set_dco(FREQ_48_MHZ);
    toggle_led1();
    toggle_led1();


    // Two 1 us pulses
    set_dco(FREQ_48_MHZ);
    toggle_led1();
    delay_one_us_at_48();
    toggle_led1();
    delay_one_us_at_48();

    toggle_led1();
    delay_one_us_at_48();
    toggle_led1();
    delay_one_us_at_48();


    // Loop for 1 s blinking
    set_dco(FREQ);
    while(1)
    {
       toggle_led1();
       delay_ms(DELAY, FREQ);
    }
}
