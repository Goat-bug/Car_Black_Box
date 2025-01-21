
#include"main.h"
#include "AnalogDC.h"
#include "CLCD.h"
#include "mkp.h"
#include "DASHBOARD.h"
#include "I2C.h"
#include "DS1307.h"
#include "EEPROM.h"

unsigned int clear_index = 0;

void clear_log(char key) 
{
    // Reset the event log data
    {
        event_count = 0; //Reset the count of logged events to 0
        write_address = 0x00; // Reset the write address for log storage to the beginning
    }
    CLEAR_DISP_SCREEN; // clear display screen
    clcd_print("CLEARING ", LINE1(0)); // Display a clearing logs message on the LCD
    clcd_print("   LOGS    ", LINE2(0));
    for (unsigned long int k = 500000; k--;);
    flag = 2; // Set the flag to the main menu state after clearing logs
    CLEAR_DISP_SCREEN;
}