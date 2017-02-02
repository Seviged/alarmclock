/*
 * alarmClock.c
 *
 * Created: 01.02.2017 13:39:01
 * Author : Seviged
 */ 

#include "defines.h"
#include <avr/io.h>
#include <util/delay.h>
#include "app.h"
#include "board.h"
#include "display.h"


int main(void)
{
	initialization();

    while (1) 
    {
		mainApp();
    }
}

