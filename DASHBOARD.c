/*
 * File:   DASHBOARD.c
 * Author: saire
 *
 * Created on 30 December, 2024, 12:34 PM
 */


#include "main.h"
#include "MKP.h"
#include "CLCD.h"
#include "AnalogDC.h"
#include "EEPROM.h"
#include "DASHBOARD.h"
// global variables 
unsigned int index, speed;
unsigned char *gear[] = {"ON", "GN", "GR", "G1", "G2", "G3", "G4", "G5", "C "};
//unsigned char write_address = 0x00;

void dashboard(char key) {
    speed = read_adc(CHANNEL4) / 10.24;     // The division by 10.24 converts the ADC value to a speed in the range 0-99
    clcd_putch((speed % 10) + 48, LINE2(15));
    clcd_putch((speed / 10) + 48, LINE2(14));
    //Handle key press events to update the gear
    if (key == MK_SW2) {
        if (index < 7) {
            index++; //  Increment the gear index
            store_event(time, gear[index], speed);
        } else if (index == 8) {
            index = 1; // Reset to gear 1 if in the special state "C"
            store_event(time, gear[index], speed);
        }
    } else if (key == MK_SW3) // If SW2 is pressed: Decrease gear/state 
    {
        if (index == 8) {
            index = 1;
            store_event(time, gear[index], speed);
        } else if (index > 1) {
            index--;
            store_event(time, gear[index], speed);
        }
    } else if (key == MK_SW1) {
        index = 8;
        store_event(time, gear[index], speed);
    }                                                                                                                                                                             
    // LCD display:
    clcd_print("TIME     EV   SP", LINE1(0));
    clcd_print(gear[index], LINE2(9));
}
