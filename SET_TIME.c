#include <xc.h>
#include "main.h"
#include "CLCD.h"
#include "DS1307.h"
#include "MKP.h"

unsigned int set_flag, set = 1;
int delay = 0;
unsigned int blink=0;
unsigned int direction=0;
unsigned int hour, minute, second;

void set_time(char key) {
    if (set_flag == 1) {
        set_flag = !set_flag;
        hour = ((time[0] - 48) * 10) + (time[1] - 48); //extract hour
        minute = ((time[3] - 48) * 10) + (time[4] - 48); //extract minute
        second = ((time[6] - 48) * 10) + (time[7] - 48); //extract seconds
    }
    clcd_print("HH:MM:SS", LINE1(0)); //display the formate on LCD
    if(delay++<=200)
    blink = 1; //toggle the blink state
    else if (delay <= 400)
        blink = 0;
    else
        delay = 0;
    if (key == MK_SW12) //changes the field
    {
        if (direction >= 0 && direction < 2) {
            direction++;
        } else
        {
            direction = 0;
        }
    } else if (key == MK_SW11) //increment the value of the selected field
    {
        if (direction == 0) {
            if (hour < 23)//upto 24 hours modify
            {
                hour++;
            } else {
                hour = 0;
            }
        }
        if (direction == 1) {
            if (minute < 59) {
                minute++; //modify minutes
            } else {
                minute = 0;
            }
        }
        if (direction == 2) {
            if (second < 59) //modify seconds
            {
                second++;
            } else {
                second = 0;
            }
        }
    }

    //updated time to print clcd
    clcd_putch('0' + (hour / 10), LINE2(0)); // Hours
    clcd_putch('0' + (hour % 10), LINE2(1)); // Hours
    clcd_putch(' ', LINE2(2)); // Space

    clcd_putch('0' + (minute / 10), LINE2(3)); // Minutes
    clcd_putch('0' + (minute % 10), LINE2(4)); // Minutes
    clcd_putch(' ', LINE2(5)); // Space

    clcd_putch('0' + (second / 10), LINE2(6)); // seconds
    clcd_putch('0' + (second % 10), LINE2(7)); // seconds
    clcd_putch(' ', LINE2(8)); //save the time when sw11 is pressed 

    if (direction == 0) {
        if (blink) {
            clcd_putch(':', LINE2(0)); // Hide hours if blinking
            clcd_putch(':', LINE2(1)); // Hide hours if blinking
        }
    } else if (direction == 1) {
        if (blink) {
            clcd_putch(':', LINE2(3)); // Hide minutes if blinking
            clcd_putch(':', LINE2(4)); // Hide minutes if blinking
        }
    } else if (direction == 2) {
        if (blink) {
            clcd_putch(':', LINE2(6)); //Hide seconds if blinking
            clcd_putch(':', LINE2(7)); //Hide seconds if blinking
        }
    }
    //   for (unsigned long i = 50000; i--;);
    //save the time when sw11 is pressed

    if (key == MK_SW1) {       
        write_ds1307(HOUR_ADDR, ((hour / 10) << 4) | (hour % 10));
        write_ds1307(MIN_ADDR, (minute / 10) << 4 | (minute % 10));
        write_ds1307(SEC_ADDR, (second / 10) << 4 | (second % 10));
        direction = 0;
        CLEAR_DISP_SCREEN;
        flag = 1;
        set_flag = 0;
        log_index = 0;
        star_flag = 0;
        direction = 0;
        clcd_print("   TIME   EV  SP", LINE1(0));
        return;
    } else if (key == MK_SW2) {     
        flag = 1;
        direction = 0;
        log_index = 0;
        star_flag = 0;
        CLEAR_DISP_SCREEN;
    }
}