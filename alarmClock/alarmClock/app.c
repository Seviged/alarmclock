/*
 * app.c
 *
 * Created: 01.02.2017 13:40:51
 *  Author: Seviged
 */ 


 #include "app.h"
 #include "defines.h"
 //#include "board.h"
 #include "display.h"
 #include "timer.h"
 #include "buttons.h"
 #include <avr/io.h>
 #include <util/delay.h>

 uint8_t nEvent1;
 uint8_t nEvent2;

 uint16_t menu = 0;
 uint16_t par = 0;
 uint8_t orientation = 0;

 uint8_t tempHour;
 uint8_t tempMin;

 uint16_t cycle = LONG_DELAY + 10;


 void initialization()
 {
	initBoard();
	initDisplay();
	initTimer();
	AppKey_Init();
 }


void mainApp()
{
	timerProcess();
	displayProcess();

	switch (menu)
	{
		case 0 :
			getFlag(7);
			displayTime(getTime());
			break;

		case 10 :
			getFlag(3);
			displayMenu(SYM_A, 3);
			displayMenu(SYM_L, 2);
			displayMenu(NONE, 1);
			displayMenu(NONE, 0);
			break;

		case 20 :
			displayMenu(SYM_C, 3);
			displayMenu(SYM_L, 2);
			displayMenu(NONE, 1);
			displayMenu(NONE, 0);
			break;

		case 100 :
			break;

		case 200 :
			if (orientation == 0)
			{
				getFlag(1);
				if (par == 1)
				{
					par = 0;
					if (cycle > LONG_DELAY)
					{
						cycle = LONG_DELAY + 10;
						tempMin++;
					}
					else cycle++;
					
					if (tempMin > 59)
					{
						tempMin = 0;
					}
				}
				displayTime((uint16_t)tempMin);
				setTime(tempMin, 0);
			}
			else
			{
				getFlag(2);
				if (par == 1)
				{
					par = 0;
					if (cycle > LONG_DELAY) 
					{
						cycle = LONG_DELAY + 10;
						tempHour++;
					}
					else cycle++;
					if (tempHour > 23)
					{
						tempHour = 0;
					}
				}
				displayTime((uint16_t)tempHour * 100);
				setTime(tempHour, 1);
			}
			break;

	}
	
	
	
	
	AppKey_Process();
	keyProcess();
}

void keyProcess()
{
	nEvent1 = AppKey_GetKeyEvent(0);
	nEvent2 = AppKey_GetKeyEvent(1);

	uint16_t tmp;

	if (nEvent1 == KEY_EV_LONG && nEvent2 == KEY_EV_LONG)
	{
		//disable ALARM
	}
	else
	{
		if (nEvent1 == KEY_EV_SHORT)
		{
			if (menu == 0)
			{
				menu = 10;
			}
			else if (menu == 10 || menu == 20)
			{
				menu =  menu * 10;
				switch (menu)
				{
					case 100 :
						break;

					case 200 :
						tmp = getTime();
						tempHour = tmp / 100;
						tempMin = tmp % 100;
						break;
				}
			}
			else
			{
				if (orientation == 1)
				{
					orientation = 0;
				}
				else
				{
					orientation = 1;
				}
			}
		}
		if (nEvent1 == KEY_EV_LONG)
		{
			menu = 0;
		}

		if (nEvent2 == KEY_EV_SHORT)
		{
			if (menu == 0)
			{
				//show alarm
			}
			else if (menu == 10)
			{
				menu = menu + 10;
			}
			else if (menu == 20)
			{
				menu = 10;
			}
			else
			{
				par = 1;
				cycle = LONG_DELAY + 10;
			}
		}

		if (nEvent2 == KEY_EV_LONG)
		{
			if (menu == 0)
			{
				//set alarm
			}
			else if (menu == 10)
			{
				menu = menu + 10;
			}
			else if (menu == 20)
			{
				menu = 10;
			}
			else
			{
				par = 1;
				if (cycle > LONG_DELAY + 5)
				{
					cycle = 0;
				}
			}
		}

	}

	
}