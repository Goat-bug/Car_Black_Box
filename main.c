/*
 * File:   main.c
 * Author: saire
 *
 * Created on 30 December, 2024, 12:55 PM
 */


#include"main.h"
#include "AnalogDC.h"
#include "CLCD.h"
#include "MKP.h"
#include "DASHBOARD.h"
#include "I2C.h"
#include "DS1307.h"
#include "UART.h"

unsigned char key = 0;

void init_config(void) 
{
    init_clcd();
    init_adc();
    init_matrix_keypad();
    init_i2c();
    init_ds1307();
    init_uart();
}

void display_time(void) 
{
    clcd_print(time, LINE2(0));
}

static void get_time(void) 
{
    clock_reg[0] = read_ds1307(HOUR_ADDR);
    clock_reg[1] = read_ds1307(MIN_ADDR);
    clock_reg[2] = read_ds1307(SEC_ADDR);

    if (clock_reg[0] & 0x40) 
    {
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
        time[1] = '0' + (clock_reg[0] & 0x0F);
    }
    else 
    {
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
        time[1] = '0' + (clock_reg[0] & 0x0F);
    }
    time[2] = ':';
    time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
    time[4] = '0' + (clock_reg[1] & 0x0F);
    time[5] = ':';
    time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
    time[7] = '0' + (clock_reg[2] & 0x0F);
    time[8] = '\0';
}

void main(void) 
{
    init_config();

    while (1) 
    {
        char key = read_switches(STATE_CHANGE);
        get_time();
        if (flag == 1) 
        {
            dashboard(key);
            display_time();
            if (key == MK_SW11) 
            {
                flag = 2;
                CLEAR_DISP_SCREEN;
            }
        } 
        else if (flag == 2)
        {
            main_menu(key);
        } 
        else if (flag == 3) 
        {
            view_log(key);
        } 
        else if (flag == 4) 
        {
            clear_log(key);
        } 
        else if (flag == 5) 
        {
            download_log(key);
            flag = 1;
        } 
        else if (flag == 6) 
        {
            set_time(key);
        }
        if (event_count > 10) 
        {
            write_address = 0;
            event_count = 10;
        }
    }
    return;
}
