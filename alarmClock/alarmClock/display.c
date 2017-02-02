/*
 * display.c
 *
 * Created: 01.02.2017 15:01:34
 *  Author: Seviged
 */ 

 #include "display.h"
 #include "defines.h"
 #include "board.h"
 #include <avr/io.h>
 #include <util/delay.h>

 uint8_t symbols[16] = {126, 24, 107, 91, 29, 87, 119, 26, 127, 95, 63, 102, 100, 101, 36, 0};
 uint8_t regValue[4] = {0, 0, 0, 0};
 uint8_t flag = 7;


 void initDisplay()
 {
	SET_L1;
	SET_L2;
	SET_L3;
	SET_L4;
	SET_L5;
	SET_L6;
	SET_L7;
	
	SET_D1;
	SET_D2;
	SET_D3;
	SET_D4;

	SET_D5;
	SET_D6;

	CLR_PWM;
 }

 void setSymbol(uint8_t num)
 {
	if (symbols[num] & BIT0) CLR_L1;
	else SET_L1;

	if (symbols[num] & BIT1) CLR_L2;
	else SET_L2;

	if (symbols[num] & BIT2) CLR_L3;
	else SET_L3;

	if (symbols[num] & BIT3) CLR_L4;
	else SET_L4;

	if (symbols[num] & BIT4) CLR_L5;
	else SET_L5;

	if (symbols[num] & BIT5) CLR_L6;
	else SET_L6;

	if (symbols[num] & BIT6) CLR_L7;
	else SET_L7;
 }

 void dots()
 {
	if (flag & BIT2)
	{
		SET_D5;
	}
 }

 void getFlag(uint8_t fl)
 {
	flag = fl;
 }

void displayProcess()
{
	
	
	setSymbol(regValue[0]);
	if (flag & BIT0)
	{
		CLR_D1;
	}
	_delay_us(90);

	SET_D1;
	setSymbol(regValue[1]);
	if (flag & BIT0)
	{
		CLR_D2;
	}
	_delay_us(90);

	SET_D2;
	setSymbol(regValue[2]);
	if (flag & BIT1)
	{
		CLR_D3;
	}
	_delay_us(90);

	SET_D3;
	setSymbol(regValue[3]);
	if (flag & BIT1)
	{
		CLR_D4;
	}
	_delay_us(90);
	
	SET_D4;
	_delay_us(900);
}


void displayTime(uint16_t lTime)
{
	regValue[0] = lTime % 10;
	lTime /= 10;
	regValue[1] = lTime % 10;
	lTime /= 10;
	regValue[2] = lTime % 10;
	regValue[3] = lTime / 10;
}

void displayMenu(uint8_t sym, uint8_t pos)
{
	regValue[pos] = sym;
}

