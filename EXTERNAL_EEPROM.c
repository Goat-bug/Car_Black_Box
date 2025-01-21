/*
 * File:   EXTERNAL_EEPROM.c
 * Author: saire
 *
 * Created on 1 January, 2025, 12:37 PM
 */



#include<xc.h>
#include"I2C.h"
#include"main.h"
#include"EXTERNAL_EEPROM.h"

void write_EXT_EEPROM(unsigned char address, unsigned char data) {
    i2c_start();
    i2c_write(SLAVE_WRITE_E);
    i2c_write(address);
    i2c_write(data);
    i2c_stop();
    for (unsigned int i = 3000; i--;);
}

unsigned char read_EXT_EEPROM(unsigned char address) {
    unsigned char data;

    i2c_start();
    i2c_write(SLAVE_WRITE_E);
    i2c_write(address);
    i2c_rep_start();
    i2c_write(SLAVE_READ_E);
    data = i2c_read();
    i2c_stop();

    return data;
}
