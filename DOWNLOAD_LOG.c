#include "DS1307.h"
#include "EEPROM.h"
#include "EXTERNAL_EEPROM.h"
#include "UART.h"
#include "CLCD.h"
#include "MKP.h"
#include "main.h"



void download_log(char key) 
{
    if (event_count == 0) 
    {
        puts("LOG EMPTY !!!\n\r");
        clcd_print(" NO logs  ", LINE1(0));
        clcd_print(" Available  ", LINE2(0));
        for (unsigned int i = 50000; i--;);
        flag = 2;
    }
    else 
    {
        clcd_print("Downloading...", LINE1(0));
        for (unsigned long int i = 500000; i--;);
        CLEAR_DISP_SCREEN;// clear display screen
        puts("#  TIME  EV  SP");
        puts("\n\r");

        int read_addr = 0x00;

        for (int i = 0; i < event_count; i++) 
        {
            for (int j = 0; j < 16; j++) 
            {
                if (j == 0) 
                {
                    ptr[i][j] = i + '0';
                } 
                else if (j == 4 || j == 7) 
                {
                    ptr[i][j] = ':';
                }
                else if (j == 1 || j == 10 || j == 13) 
                {
                    ptr[i][j] = ' ';
                }
                else 
                {
                    ptr[i][j] = read_EXT_EEPROM(read_addr);
                    read_addr++;
                }
            }

            ptr[i][15] = '\0';
        }

        int i = 0;
        while (i < event_count) 
        {
            puts(ptr[i]);
            puts("\n\r");
            i++;
        }
        CLEAR_DISP_SCREEN;
        for (unsigned int wait = 500000; wait--;);


        if (key == MK_SW2) //Exit menu, return to the main dashboard
        {

            read_addr = 0x00;
            flag = 2;
            CLEAR_DISP_SCREEN;
        }
    }
}