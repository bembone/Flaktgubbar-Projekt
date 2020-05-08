#ifndef PWM_H
#define PWM_H

#include "gd32vf103.h"
#include "systick.h"
#include <stdlib.h>
#include "math.h"
#include "gd32vf103_timer.h"

#define PWMC1_PORT     GPIOB
#define PWMC1_PIN      GPIO_PIN_0
#define PWM_CHANNEL    

#define RED_LED_PIN    GPIO_PIN_13
#define RED_LED_PORT   GPIOC

#define PI  3.14

    /* These structs are used for configuring the timer */
    timer_oc_parameter_struct timer_ocinitpara;
    timer_parameter_struct timer_initpara;

void init_PWM_example();
#endif