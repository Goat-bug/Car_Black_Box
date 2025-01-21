#include "main.h"
#include "MKP.h"
#include "CLCD.h"
#include "AnalogDC.h"
#include "EEPROM.h"
#include "EXTERNAL_EEPROM.h"

//unsigned char write_address = 0x00;
void store_event(unsigned char time[], unsigned char gear[], unsigned short speed);

void store_event(unsigned char time[], unsigned char gear[], unsigned short speed) {
    int j = 0;
    for (int i = 0; i < 12; i++)//the loop iteration of gear,speed,time and it is stored in external EEPROM
    {
        if (i < 8) {
            if (i == 2 || i == 5)
                continue; //to skip : 
            write_EXT_EEPROM(write_address, time[i]);
        } else if (i < 10) {
            write_EXT_EEPROM(write_address, gear[j]);
            j++; //writing the gaer information into the EEPROM
        } else {
            if (i == 10) {
                write_EXT_EEPROM(write_address, (speed / 10) + 48);
            } else if (i == 11) {
                write_EXT_EEPROM(write_address, (speed % 10) + 48);
            }
        }
        write_address++;
    }
    event_count++; //INCREMEMT EVENT COUNT
    if (event_count > 10) {
        event_count = 10;
    }
}
