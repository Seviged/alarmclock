/*
 * display.h
 *
 * Created: 01.02.2017 15:01:50
 *  Author: Seviged
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <avr/io.h>


enum
{
	SYM_0		= 0,
	SYM_1		= 1,
	SYM_2		= 2,
	SYM_3		= 3,
	SYM_4		= 4,
	SYM_5		= 5,
	SYM_6		= 6,
	SYM_7		= 7,
	SYM_8		= 8,
	SYM_9		= 9,
	SYM_A		= 10,
	SYM_C		= 11,
	SYM_L		= 12,
	SYM_T		= 13,
	SYM_I		= 14,
	NONE		= 15
};




void initDisplay();
void setSymbol(uint8_t);
void displayProcess();
void updateTimer();
void displayTime(uint16_t);
void displayMenu(uint8_t, uint8_t);
void dots();
void getFlag(uint8_t);





#endif /* DISPLAY_H_ */