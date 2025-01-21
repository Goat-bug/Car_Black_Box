#include "main.h"
#include "MKP.h"

void init_matrix_keypad(void) {
    //configure rows as output
    TRISB = TRISB & 0x1F;
    //configure cols as input
    TRISB = TRISB | 0x1E;

    //portb pull up
    RBPU = 0;
}

unsigned char scan_key(void) {
    //scan SW1, SW4, SW7, SW10
    ROW1 = 0;
    ROW2 = 1;
    ROW3 = 1;

    if (COL1 == 0) return MK_SW1;
    if (COL2 == 0) return MK_SW4;
    if (COL3 == 0) return MK_SW7;
    if (COL4 == 0) return MK_SW10;

    //scan SW2, SW4, SW8, SW11
    ROW1 = 1;
    ROW2 = 0;
    ROW3 = 1;

    if (COL1 == 0) return MK_SW2;
    if (COL2 == 0) return MK_SW5;
    if (COL3 == 0) return MK_SW8;
    if (COL4 == 0) return MK_SW11;

    //scan SW3, SW6, SW9, SW12
    ROW1 = 1;
    ROW3 = 0;
    ROW2 = 1;
    ROW2 = 1;

    if (COL1 == 0) return MK_SW3;
    if (COL2 == 0) return MK_SW6;
    if (COL3 == 0) return MK_SW9;
    if (COL4 == 0) return MK_SW12;
    return ALL_RELEASED;
}

unsigned char read_switches(unsigned char detection_type) {
    static int once = 1;
    unsigned char key;
    if (detection_type == LEVEL) {
        return scan_key();
    } else if (detection_type == STATE_CHANGE) {
        key = scan_key();
        if (key != ALL_RELEASED && once) {
            once = 0;
            return key;
        }
        if (key == ALL_RELEASED)
            once = 1;
    }
    return ALL_RELEASED;
}
