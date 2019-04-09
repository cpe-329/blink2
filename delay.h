#ifndef __DELAY_H__
#define __DELAY_H__

#include "msp.h"

#include "types.h"


#define LOCK_CS_KEY 0
#define CLK_PER_LOOP 4

#define FREQ_1_5_MHZ 0
#define FREQ_3_MHZ 1
#define FREQ_6_MHZ 2
#define FREQ_12_MHZ 3
#define FREQ_24_MHZ 4
#define FREQ_48_MHZ 5

#define NOP asm(" NOP");

void init_dco(void);

void set_dco(unsigned int freq);

inline delay_one_ms(const unsigned int freq);

inline void delay_ms(unsigned int msec, unsigned int freq);
inline void delay_one_us_at_48();
inline void delay_us(unsigned int usec, unsigned int freq);

inline void delay_for_loop(const int iterations);

#endif
