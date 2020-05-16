#include "sensordriver.h"
#include "gd32vf103_gpio.h"
#include <string.h>
#include "PWM.h"

int main(void){

    initSensor();
    int32_t duty = 0;
    int32_t diff = 0;

    init_PWM_example();
    
    uint8_t read_buffer[64] = {0};
    uint8_t write_buffer[64] = {33, 0};

    delay_1ms(100);

     /* Start the different clocks needed for the I2C bus */
    rcu_periph_clock_enable(RCU_I2C0);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_AF);

    /* Initialize the GPIO connected to the I2C0 bus */
    gpio_init(GPIOB, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_6 | GPIO_PIN_7);
    
    /* Configure i2c clock speed and dutycycle */
    i2c_clock_config(I2C0, 100000, I2C_DTCY_2);

    /* Enable i2c */
    i2c_enable(I2C0);

    uint8_t state=1;
    //char flakt[3];
    //uint8_t styrka=0;
    uint8_t gest; // RIGHT = 1, LEFT = 2, DOWN = 3, UP = 4

    while(1){
        for(int i=0;i<4;i++){
            /* Read a register on the i2c bus */
            i2c_read_register(I2C0, I2C_ADDR, 0xFF-i, 8, read_buffer);
            // kolla om det finns nånting i 0xFF-i, om det finns så är det motsvarande gest som har hänt
            if(read_buffer != 0){
                switch(0xFF-i){        
                    case 0xFF: 
                        gest=1;
                        i2c_write_register(I2C0,I2C_ADDR,0xFF,8,0x00);
                    break;
                    case 0xFE: 
                        gest=2;
                        i2c_write_register(I2C0,I2C_ADDR,0xFE,8,0x00);
                    break;
                    case 0xFD: 
                        gest=3;
                        i2c_write_register(I2C0,I2C_ADDR,0xFD,8,0x00);
                    break;
                    case 0xFC:
                        gest=4;
                        i2c_write_register(I2C0,I2C_ADDR,0xFC,8,0x00);
                    break;
                    default: break;
                 }

            }

        } // här är gesten som gjorts lagrad i programmet

        switch(state){
                case 1:
                    if(gest == 1 || gest == 2){
                        timer_initpara.period = 4095/4;
                        timer_init(TIMER4, &timer_initpara);
                        duty = 256;     // har satt styrka på motor till 25%
                        timer_channel_output_pulse_value_config(TIMER4,TIMER_CH_1,(int)duty); 
                        state++;
                     }
                break;
                case 2:
                    if(gest == 1 || gest == 2){
                        timer_initpara.period = 0;
                        timer_init(TIMER4, &timer_initpara);
                        duty = 0;     // har satt styrka på motor till 0%
                        timer_channel_output_pulse_value_config(TIMER4,TIMER_CH_1,(int)duty);
                        state=1;
                    }
                    else if(gest == 4){
                        timer_initpara.period = 4095/2;
                        timer_init(TIMER4, &timer_initpara);
                        duty = 1024;     // har satt styrka på motor till 50%
                        timer_channel_output_pulse_value_config(TIMER4,TIMER_CH_1,(int)duty);
                        state++;
                    }
                break;
                case 3:
                    if(gest == 1 || gest == 2){
                        timer_initpara.period = 0;
                        timer_init(TIMER4, &timer_initpara);
                        duty = 0;     // har satt styrka på motor till 0%
                        timer_channel_output_pulse_value_config(TIMER4,TIMER_CH_1,(int)duty);
                        state=1;
                    }
                    else if(gest == 4){
                        timer_initpara.period = 4095*0.75;
                        timer_init(TIMER4, &timer_initpara);
                        duty = 2304;     // har satt styrka på motor till 75%
                        timer_channel_output_pulse_value_config(TIMER4,TIMER_CH_1,(int)duty);
                        state++;
                    }
                    else if(gest == 3){
                        timer_initpara.period = 4095/4;
                        timer_init(TIMER4, &timer_initpara);
                        duty = 256;     // har satt styrka på motor till 25%
                        timer_channel_output_pulse_value_config(TIMER4,TIMER_CH_1,(int)duty);
                        state--;
                    }
                break;
                case 4:
                    if(gest == 1 || gest == 2){
                        timer_initpara.period = 0;
                        timer_init(TIMER4, &timer_initpara);
                        duty = 0;     // har satt styrka på motor till 0%
                        timer_channel_output_pulse_value_config(TIMER4,TIMER_CH_1,(int)duty);
                        state=1;
                    }
                    else if(gest == 3){
                        timer_initpara.period = 4095/2;
                        timer_init(TIMER4, &timer_initpara);
                        duty = 1024;     // har satt styrka på motor till 50%
                        timer_channel_output_pulse_value_config(TIMER4,TIMER_CH_1,(int)duty);
                        state--;
                    }
                break;
                default: break;
            }
    }
    return 0;
}
