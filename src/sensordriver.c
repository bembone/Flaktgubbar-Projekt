#include "sensordriver.h"
#include "gd32vf103_gpio.h"
#include <stdlib.h>

/* You can copy this function to be able to read from most i2c devices */
void i2c_read_register(int32_t port, uint8_t addr, uint8_t reg, uint8_t size, uint8_t *data){

    /* send a start condition to I2C bus */
    i2c_start_on_bus(port);
    while(!i2c_flag_get(port, I2C_FLAG_SBSEND));

    /* send slave address to I2C bus with write flag */
    i2c_master_addressing(port, addr << 1, I2C_TRANSMITTER);
    /* Wait for sending address to finish */
    while(!i2c_flag_get(port, I2C_FLAG_ADDSEND));
    i2c_flag_clear(port, I2C_FLAG_ADDSEND);

    /* Send which register to read */
    i2c_data_transmit(port, reg);
    /* wait until the data has been sent */
    while(!i2c_flag_get(port, I2C_FLAG_TBE));

    /* Send new start condition */
    i2c_start_on_bus(port);
    while( ! i2c_flag_get(port, I2C_FLAG_SBSEND) );

    /* Now send address with read flag */
    i2c_master_addressing(port, addr << 1, I2C_RECEIVER);
    while( ! i2c_flag_get(port, I2C_FLAG_ADDSEND) );
    i2c_flag_clear(port, I2C_FLAG_ADDSEND);

    /* Enable acknowledge for receiving multiple bytes */
    i2c_ack_config(port, I2C_ACK_ENABLE);

    /* Receive bytes, read into buffer. */
    for(int i = 0; i < size; i++) {
        if(i == size - 1) {
            /* If last byte, do not send ack */
            i2c_ack_config(port, I2C_ACK_DISABLE);
        }
        while(!i2c_flag_get(port, I2C_FLAG_RBNE));
        *data++ = i2c_data_receive(port);
    }

    i2c_stop_on_bus(port);
    while( I2C_CTL0(port) & I2C_CTL0_STOP );
}

/* You can copy this function to be able to write most i2c devices */
void i2c_write_register(int32_t port, uint8_t addr, uint8_t reg, uint8_t size, uint8_t *data)
{    
    /* send a NACK for the next data byte which will be received into the shift register */
    while(i2c_flag_get(port, I2C_FLAG_I2CBSY));

    /* send a start condition to I2C bus */
    i2c_start_on_bus(port);
    while(!i2c_flag_get(port, I2C_FLAG_SBSEND));

    /* send slave address to I2C bus */
    i2c_master_addressing(port, addr << 1, I2C_TRANSMITTER);
    while(!i2c_flag_get(port, I2C_FLAG_ADDSEND));
    i2c_flag_clear(port, I2C_FLAG_ADDSEND);

    
    /* Send which register to write */
    i2c_data_transmit(port, reg);
    /* wait until the TBE bit is set */
    while(!i2c_flag_get(port, I2C_FLAG_TBE));

    /* Send data */
    for(int i = 0; i < size; i++){
        i2c_data_transmit(port, *data++);
        /* wait until the TBE bit is set */
        while(!i2c_flag_get(port, I2C_FLAG_TBE));
    }

    /* Send stop condition */
    i2c_stop_on_bus(port);
    while( I2C_CTL0(port) & I2C_CTL0_STOP );
}

void initSensor(void)
{
    i2c_write_register(I2C0,I2C_ADDR,ATIME,8,DEFAULT_ATIME);
    i2c_write_register(I2C0,I2C_ADDR,WTIME,8,DEFAULT_WTIME);
    i2c_write_register(I2C0,I2C_ADDR,PPULSE,8,DEFAULT_PROX_PPULSE);
    i2c_write_register(I2C0,I2C_ADDR,GPULSE,8,DEFAULT_GPULSE);
    i2c_write_register(I2C0,I2C_ADDR,GOFFSET_D,1,DEFAULT_POFFSET_UDLR);
    i2c_write_register(I2C0,I2C_ADDR,CONF1,8,DEFAULT_CONFIG1);
    i2c_write_register(I2C0,I2C_ADDR,CONTROL,4,DEFAULT_PGAIN);
    i2c_write_register(I2C0,I2C_ADDR,PLIT,1,DEFAULT_PILT);
    i2c_write_register(I2C0,I2C_ADDR,PIHT,1,DEFAULT_PIHT);
    i2c_write_register(I2C0,I2C_ADDR,CONF2,8,DEFAULT_CONFIG2);
    i2c_write_register(I2C0,I2C_ADDR,CONF3,1,DEFAULT_CONFIG3);
    i2c_write_register(I2C0,I2C_ADDR,GPENTH,5,DEFAULT_GPENTH);
    i2c_write_register(I2C0,I2C_ADDR,GEXTH,5,DEFAULT_GEXTH);
    i2c_write_register(I2C0,I2C_ADDR,GCONF1,8,DEFAULT_GCONF1);
    i2c_write_register(I2C0,I2C_ADDR,GCONF2,4,DEFAULT_GGAIN);
    i2c_write_register(I2C0,I2C_ADDR,PPULSE,8,DEFAULT_GESTURE_PPULSE);
    i2c_write_register(I2C0,I2C_ADDR,GCONF3,1,DEFAULT_GCONF3);
    i2c_write_register(I2C0,I2C_ADDR,0xFF,8,0x00);
    i2c_write_register(I2C0,I2C_ADDR,0xFE,8,0x00);
    i2c_write_register(I2C0,I2C_ADDR,0xFD,8,0x00);
    i2c_write_register(I2C0,I2C_ADDR,0xFC,8,0x00);

};