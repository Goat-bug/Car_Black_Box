#ifndef MAIN_H
#define	MAIN_H

#include <xc.h>
void dashboard(char key);
void main_menu(char key);
unsigned int flag = 1 , event_count = 0;
unsigned char ptr[10][16];
void view_log(char key);
void clear_log(char key);
void download_log(char key);
void set_time(char key);
unsigned char clock_reg[3];
unsigned star_flag=0,log_index=0;
unsigned char time[9];
char read_addr = 0x00;
unsigned char write_address = 0x00;
void store_event(unsigned char time[], unsigned char gear[],unsigned short speed);
#endif	/* MAIN_H */

