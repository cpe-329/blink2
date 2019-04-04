#ifndef __MY_WATCHDOG_H__
#define __MY_WATCHDOG_H__

#define DISABLE_WATCHDOG()  WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

#endif
