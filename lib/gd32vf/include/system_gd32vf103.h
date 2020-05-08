#ifndef SYSTEM_GD32VF103_H
#define SYSTEM_GD32VF103_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* system clock frequency (core clock) */
extern uint32_t SystemCoreClock;

/* function declarations */
/* initialize the system and update the SystemCoreClock variable */
extern void SystemInit(void);
/* update the SystemCoreClock with current core clock retrieved from cpu registers */
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_GD32VF103_H */