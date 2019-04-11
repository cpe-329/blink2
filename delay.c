#include "delay.h"

void init_dco(void){
    CS->KEY = CS_KEY_VAL;  // Unlock key
    CS->CTL0 = 0;  // Reset
    CS->CTL0 = CS_CTL0_DCORSEL_3;
    CS->CTL1 = CS_CTL1_SELA_2 | // Set ACLK to REFCLK
               CS_CTL1_SELS_3 | // Set SMCLK to DCO
               CS_CTL1_SELM_3;  // Set MCLK to DCO
    CS->KEY = LOCK_CS_KEY; // Lock key
}

void safe_48(){
    /* Transition to VCORE Level 1: AM0_LDO --> AM1_LDO */
    while ((PCM->CTL1 & PCM_CTL1_PMR_BUSY));
     PCM->CTL0 = PCM_CTL0_KEY_VAL | PCM_CTL0_AMR_1;
    while ((PCM->CTL1 & PCM_CTL1_PMR_BUSY));
    /* Configure Flash wait-state to 1 for both banks 0 & 1 */
    FLCTL->BANK0_RDCTL = (FLCTL->BANK0_RDCTL &
     ~(FLCTL_BANK0_RDCTL_WAIT_MASK)) | FLCTL_BANK0_RDCTL_WAIT_1;
    FLCTL->BANK1_RDCTL = (FLCTL->BANK0_RDCTL &
     ~(FLCTL_BANK1_RDCTL_WAIT_MASK)) | FLCTL_BANK1_RDCTL_WAIT_1;
}

void set_dco(unsigned int freq){
    CS->KEY = CS_KEY_VAL;
    CS->CTL0 = 0;
    switch(freq){
    case(FREQ_1_5_MHZ):
        CS->CTL0 = CS_CTL0_DCORSEL_0;
        break;
    case(FREQ_3_MHZ):
        CS->CTL0 = CS_CTL0_DCORSEL_1;
        break;
    case(FREQ_6_MHZ):
        CS->CTL0 = CS_CTL0_DCORSEL_2;
        break;
    case(FREQ_12_MHZ):
        CS->CTL0 = CS_CTL0_DCORSEL_3;
        break;
    case(FREQ_24_MHZ):
        CS->CTL0 = CS_CTL0_DCORSEL_4;
        break;
    case(FREQ_48_MHZ):
        safe_48();
        CS->CTL0 = CS_CTL0_DCORSEL_5;
        break;
    default:
        // Default to 1.5MHz
        CS->CTL0 = CS_CTL0_DCORSEL_0;
    }
    CS->KEY = 0;
}

static inline int one_msec(const unsigned int freq){
    switch(freq){
    case(FREQ_48_MHZ):
        return 3000;
    case(FREQ_24_MHZ):
        return 1711;
    case(FREQ_12_MHZ):
        return 852;
    case(FREQ_6_MHZ):
        return 421;
    case(FREQ_3_MHZ):
        return 207;
    default:
        // Default to 1.5MHz
        return 98;
    }
}

inline delay_one_ms(const unsigned int freq){
     unsigned int j = one_msec(freq);
     while(j-- > 0);
}

inline void delay_ms(unsigned int msec, const unsigned int freq){
    while (msec-- > 0){
        delay_one_ms(freq);
    }
}

inline void delay_one_us_at_48(){
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
}

inline void delay_us(unsigned int usec, const unsigned int freq){
    while(usec-- > 0){
        delay_one_us_at_48();
    }
}

void delay_for_loop(const int iterations){
    volatile int i;
    for(i = iterations; i> 0; i--);
}
