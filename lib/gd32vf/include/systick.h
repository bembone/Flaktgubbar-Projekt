#ifndef SYS_TICK_H
#define SYS_TICK_H

#include <stdint.h>
/** 
 * Delay one millisecond * count
 * @param count miliseconds to delay for
*/
void delay_1ms(uint32_t count);

/** 
 * Delay one millisecond * count
 * @param count miliseconds to delay for
*/
void delay_1us(uint32_t count);

#endif /* SYS_TICK_H */