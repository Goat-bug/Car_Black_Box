#include"main.h"
#include "AnalogDC.h"
#include "CLCD.h"
#include "MKP.h"
#include "DASHBOARD.h"
#include "I2C.h"
#include "DS1307.h"
#include "EEPROM.h"
#include"EXTERNAL_EEPROM.h"

unsigned int view_index;

//unsigned int flag = 0, count = 0;
int r_flag = 0;
int delay = 0;

void view_log(char key) 
{
    static int index = 0;
    if (event_count == 0) 
    {
        clcd_print("   NO LOGS      ", LINE1(0)); // display  when their is no logs
        clcd_print("    DISPLAY     ", LINE2(0));
        if (delay++ != 1000) 
        {
            //for (unsigned long int wait = 500000; wait--;);
            flag = 2;
            index = 0;
            r_flag = 0;
            read_addr = 0x00;
            delay = 0;
            CLEAR_DISP_SCREEN;// clear display screen
        }
        return;
    }
    clcd_print("# Time     EV SP   ", LINE1(0));
    if (r_flag == 0) 
    {
        view_index = 0;

        if (view_index < event_count - 1) 
        {
            view_index++;
        } 
        else 
        {
            view_index = event_count;
            if (view_index < 9)
                view_index++;
        }

        for (int i = 0; i < event_count; i++) 
        {
            for (int j = 0; j < 16; j++) 
            {
                if (j == 0) 
                {
                    ptr[i][j] = (i + '0');
                } 
                else if ((j == 1) || (j == 10) || (j == 13))// spaces for alignment  
                {
                    ptr[i][j] = ' ';
                } 
                else if ((j == 4) || (j == 7)) 
                {
                    ptr[i][j] = ':';
                } 
                else 
                {
                    ptr[i][j] = read_EXT_EEPROM(read_addr);
                    read_addr++;
                }
            }
            ptr[i][15] = '\0';
        }
        r_flag = 1;
    }

    clcd_print(ptr[index], LINE2(0));
    if (key == MK_SW11) 
    {                  
        if (index < event_count - 1) 
        {
            index++;
        }
    } 
    else if (key == MK_SW12) 
    {      
        if (index > 0) 
        {
            index--;
        }
    }
    if (key == MK_SW2) // Exit menu and return to the main dashboard
    { // Reset variables and exit log view when SW12 is pressed.
        index = 0;
        r_flag = 0;
        read_addr = 0x00;
        flag = 2;
        CLEAR_DISP_SCREEN;// clear display screen
    }
}
