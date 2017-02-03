/*
* beeper.c
*
* Created: 02.02.2017 19:48:08
*  Author: Seviged
*/ 


#include "beeper.h"
#include "board.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t beepFlag = 0;

void beepTimerInit()
{
	TCCR0A = 2;
	OCR0A = 255;
	TIMSK0 = 2;
	TCCR0B = 3;
}

void startBeep()
{
	beepFlag = 1;
}

void stopBeep()
{
	beepFlag = 0;
	_delay_ms(1);
	CLR_PWM;
	CLR_PWM2;
}

void setBeepFreq(uint8_t freq)
{
	OCR0A = freq;
}


ISR(TIMER0_COMPA_vect)
{
	if (beepFlag == 1)
	{
		if (IS_PWM_ON)
		{
			CLR_PWM;
			CLR_PWM2;
			SET_PWM2;
		}
		else
		{
			CLR_PWM2;
			CLR_PWM;
			SET_PWM;
		}
	}
}