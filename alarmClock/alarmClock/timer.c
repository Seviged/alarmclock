/*
 * timer.c
 *
 * Created: 01.02.2017 17:03:38
 *  Author: Seviged
 */ 

  #include "timer.h"
  #include "board.h"
  #include "defines.h"
  #include "display.h"
  #include "beeper.h"
  #include <avr/io.h>
  #include <util/delay.h>
  #include <avr/interrupt.h>
  #include <stdlib.h>

  uint8_t sec = 0;
  uint8_t min = 0;
  uint8_t hour = 0;
  uint8_t dayFlag = 1;

  uint8_t alarmHour = 0;
  uint8_t alarmMin = 0;
  uint8_t alarmFlag = 0;


  static volatile uint16_t globalTime;
  uint16_t localTime = 0;
 
  void initTimer()
  {
	  DISABLE_TIMER_INT;														// Disable KNX timer interrupt

	  globalTime		= 0;													// Reset system time

	  OCR1A  += TICKS_PER_MSECOND;												// Set first clock period

	  TCCR1A	= 0;																// Set TimerMode to Normal
	  TCCR1B |= (1 << CS10);														// Select source clock: ClckIo, no pre-scaler; set TimerMode

	  ENABLE_INTERRUPTS;
	  ENABLE_TIMER_INT;														// Enable send timer interrupt (1 ms)
  }


void timerProcess()
{
	if (localTime % 199 == 0)
	{
		srand((unsigned int)globalTime);
		setBeepFreq(27 + rand() % 150);
	}
	if (localTime > 499)
	{
		CLR_D5;
	}
	if (localTime > 999)
	{
		dots();
		localTime = 0;
		sec++;
	}

	if (sec > 59)
	{
		sec = 0;
		min++;
	}
	if (min > 59)
	{
		min = 0;
		hour++;
	}
	if (hour > 23)
	{
		hour = 0;
		dayFlag = 1;
	}

	if (alarmFlag == 1)
	{
		if (hour >= alarmHour && min >= alarmMin && dayFlag == 1)
		{
			startBeep();
			alarmFlag = 0;
		}
	}
}

void stopAlarm()
{
	
	stopBeep();
	CLR_D6;

}

void startAlarm()
{
	alarmFlag = 1;
	if (hour >= alarmHour)
	{	
		if (min >= alarmMin)
		{
			dayFlag = 0;
		}
	}
	SET_D6;

	
}

void setTime(uint8_t lTime, uint8_t hl)
{
	sec = 0;
	if (hl == 0)
	{
		min = lTime;
	}
	else
	{
		hour = lTime;
	}
}

void setAlarmTime(uint8_t lTime, uint8_t hl)
{
	if (hl == 0)
	{
		alarmMin = lTime;
	}
	else
	{
		alarmHour = lTime;
	}
}

uint16_t getTime()
{
	return (hour * 100) + min;
}

uint16_t getAlarmTime()
{
	return (alarmHour * 100) + alarmMin;
}

  uint16_t getTimeMs()
  {
	  uint16_t nTime;																// Variable for time

	  DISABLE_TIMER_INT;														// Prevent from timer interrupt processing
	  nTime = (uint16_t)globalTime;											// Get actual time
	  ENABLE_TIMER_INT;														// Re-enable timer interrupt

	  return nTime;																// Return current time
  }


  uint16_t getDelayMs(uint16_t nOldTime)
  {
	  uint16_t nDelay;															// Variable for delay

	  DISABLE_TIMER_INT;														// Prevent from timer interrupt processing
	  nDelay = (uint16_t)globalTime - nOldTime;								// Calculate delay
	  ENABLE_TIMER_INT;														// Re-enable timer interrupt

	  return nDelay;																// Return delay
  }


  ISR(TIMER1_COMPA_vect)
  {
	  uint16_t nTemp;																// Temporary storage

	  nTemp  = TCNT1;																// Get current time
	  nTemp -= OCR1A;																// Subtract interrupt time

	  if (nTemp < (TICKS_PER_MSECOND/2))											// If more than half period left
	  {
		  OCR1A += (TICKS_PER_MSECOND);											// Add Offset to OCR1A relative
	  }
	  else
	  {
		  OCR1A = TCNT1 + (TICKS_PER_MSECOND);									// Set OCR1A to 1 ms absolute
	  }

	  globalTime++;															// Increment counter
	  localTime++;
  }