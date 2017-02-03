/*
 * beeper.h
 *
 * Created: 02.02.2017 19:48:31
 *  Author: Seviged
 */ 


#ifndef BEEPER_H_
#define BEEPER_H_

#include <avr/io.h>


void beepTimerInit();
void startBeep();
void stopBeep();
void setBeepFreq(uint8_t);



#endif /* BEEPER_H_ */