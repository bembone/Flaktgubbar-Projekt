#ifndef SENSOR_DRIVER_H
#define SENSOR_DRIVER_H

#include "gd32vf103_i2c.h"
#include "systick.h"

#define I2C_ADDR    0x39    // SENSOR I2C ADDRESS

#define ENABLE      0x80    // ENABLE REGISTER
#define ATIME       0x81    
#define WTIME       0x83
#define PPULSE      0x8E
#define PLIT        0x89    // PROXIMITY LOW THRESHOLD
#define PIHT        0x88    // PROXIMITY HIGH THRESHOLD

#define PON         0b00000001  // POWER ON
#define PEN         0b00000100  // PROXIMITY ENABLE
#define PIEN        0b00010000  // PROXIMITY INTERRUPT ENABLE

#define GEN         0b00100000  // GESTURE ENABLE
#define GPENTH      0xA0    // GESTURE PROXIMITY ENTRY THRESHOLD
#define GEXTH       0xA1    // GESTURE EXIT THRESHOLD
#define PPULSE      0x8E    // PPULSE REG
#define CONF1       0x8B    // CONFIG 1
#define CONF2       0x90    // CONFIG 2
#define CONF3       0x9F    // CONFIG 3
#define GCONF1      0xA2    // GESTURE CONFIG 1
#define GCONF2      0xA3    // GESTURE CONFIG 2
#define GOFFSET_U   0xA4    // GESTURE OFFSET, UP
#define GOFFSET_D   0xA5    // GESTURE OFFSET, DOWN
#define GOFFSET_L   0xA7    // GESTURE OFFSET, LEFT
#define GOFFSET_R   0xA9    // GESTURE OFFSET, RIGHT
#define GPULSE      0xA6    // PULSE COUNT <5:0>
#define GCONF3      0xAA    // GESTURE CONFIG 3
#define GCONF4      0xAB    // GESTURE CONFIG 4
#define GFLVL       0xAE    // GESTURE FIFO LEVEL
#define GSTATUS     0xAF    // GESTURE STATUS 
#define GFOV        0b00000010 // (GSTATUS) GESTURE FIFO OVERFLOW
#define GVALID      0b00000001 // (GSTATUS) GESTURE VALID
#define GFIFO_U     0xFC    // GESTURE FIFO DATA, UP
#define GFIFO_D     0xFD    // GESTURE FIFO DATA, DOWN
#define GFIFO_L     0xFE    // GESTURE FIFO DATA, LEFT
#define GFIFO_R     0xFF    // GESTURE FIFO DATA, RIGHT
#define CONTROL     0x8F    // PROXIMITY GAIN CONTROL <3:2>

// GESTURE GAIN VALUES
#define GGAIN_1X                0
#define GGAIN_2X                1
#define GGAIN_4X                2
#define GGAIN_8X                3

// GESTURE WAIT TIME VALUES
#define GWTIME_0MS              0
#define GWTIME_2_8MS            1
#define GWTIME_5_6MS            2
#define GWTIME_8_4MS            3
#define GWTIME_14_0MS           4
#define GWTIME_22_4MS           5
#define GWTIME_30_8MS           6
#define GWTIME_39_2MS           7

// PROXIMITY GAIN CONTROLL VALUES
#define PGAIN_1X                0
#define PGAIN_2X                1
#define PGAIN_4X                2
#define PGAIN_8X                3

// DEFAULT VALUES
#define DEFAULT_ATIME           219     // 103ms
#define DEFAULT_WTIME           246     // 27ms
#define DEFAULT_PROX_PPULSE     0x87    // 16us, 8 pulses
#define DEFAULT_GESTURE_PPULSE  0x89    // 16us, 10 pulses
#define DEFAULT_POFFSET_UDLR    0       // 0 offset
#define DEFAULT_CONFIG1         0x60    // No 12x wait (WTIME) factor
#define DEFAULT_PGAIN           PGAIN_4X
#define DEFAULT_PILT            0       // Low proximity threshold
#define DEFAULT_PIHT            50      // High proximity threshold
#define DEFAULT_CONFIG2         0x01    // No saturation interrupts or LED boost
#define DEFAULT_CONFIG3         0       // Enable all photodiodes, no SAI
#define DEFAULT_GPENTH          40      // Threshold for entering gesture mode
#define DEFAULT_GEXTH           30      // Threshold for exiting gesture mode
#define DEFAULT_GCONF1          0x40    // 4 gesture events for int., 1 for exit
#define DEFAULT_GGAIN           GGAIN_4X
#define DEFAULT_GOFFSET         0       // No offset scaling for gesture mode
#define DEFAULT_GPULSE          0xC9    // 32us, 10 pulses
#define DEFAULT_GCONF3          0       // All photodiodes active during gesture
#define DEFAULT_GIEN            0       // Disable gesture interrupts

#define OFF         0
#define ON          1

void i2c_read_register(int32_t port, uint8_t addr, uint8_t reg, uint8_t size, uint8_t *data);
void i2c_write_register(int32_t port, uint8_t addr, uint8_t reg, uint8_t size, uint8_t *data);

void initSensor(void);


#endif
