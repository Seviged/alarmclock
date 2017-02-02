/*
 * timer.h
 *
 * Created: 01.02.2017 17:03:29
 *  Author: Seviged
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>

#define ENABLE_TIMER_INT		TIMSK1 |=  (1 << OCIE1A)					// Enable timer interrupt
#define DISABLE_TIMER_INT		TIMSK1 &= ~(1 << OCIE1A)					// Disable timer interrupt

#define TICKS_PER_SECOND			14745600
#define TICKS_PER_MSECOND			(TICKS_PER_SECOND/1000)

void initTimer();
uint16_t getTimeMs();
uint16_t getDelayMs(uint16_t);
void timerProcess();
uint16_t getTime();
void setTime(uint8_t, uint8_t);

#endif /* TIMER_H_ */