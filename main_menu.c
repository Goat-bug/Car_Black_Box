#include "main.h"
#include "MKP.h"
#include "CLCD.h"
#include "AnalogDC.h"

unsigned char *log[] = {"View log ", "Clear log", "Download log", "Set time"};

void main_menu(char key) 
{
    //Display the current and next menu options in the LCD screen
    clcd_print(log[log_index], LINE1(2));
    clcd_print(log[log_index + 1], LINE2(2));
    clcd_putch(log_index + 48, LINE1(14));
    clcd_putch(star_flag + 48, LINE1(15));
    if (star_flag == 0) 
    {
        clcd_putch('>', LINE1(0));       
        clcd_putch(' ', LINE2(0));
    } 
    else 
    {
        clcd_putch('>', LINE2(0));      
        clcd_putch(' ', LINE1(0));
    }
    if (key == MK_SW12) 
    {
        if (star_flag == 1) 
        {
            if (log_index < 2) 
            {
                log_index++; // move to the next pair of menu options
            }
        }
        star_flag = 1; // move the '*' to the bottom option
    } 
    else if (key == MK_SW11) 
    {
        if (star_flag == 0) 
        {
            if (log_index > 0)
            {
                log_index--;
            }
        }
        star_flag = 0;
    }
    if (key == MK_SW1) 
    {                          
        if (log_index == 0 && star_flag == 0) 
        {
            flag = 3; //view
            CLEAR_DISP_SCREEN;
            return;
        } 
        else if((log_index == 0 && star_flag == 1) || (log_index == 1 && star_flag == 0)) 
        {
            flag = 4;
            CLEAR_DISP_SCREEN;
            return;
        } 
        else if ((log_index == 1 && star_flag == 1) || (log_index == 2 && star_flag == 0))
        {

            flag = 5; //download
            CLEAR_DISP_SCREEN;
            return;
        } 
        else if (log_index == 2 && star_flag == 1) 
        {
            flag = 6; 
            CLEAR_DISP_SCREEN;
            return;
        }
    } 
    else if (key == MK_SW2) 
    {           
        flag = 1;
        log_index = 0;
        star_flag = 0;
        CLEAR_DISP_SCREEN;
    }
}
