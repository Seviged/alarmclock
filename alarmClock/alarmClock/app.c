/*
 * app.c
 *
 * Created: 01.02.2017 13:40:51
 *  Author: Seviged
 */ 


 #include "app.h"
 #include "defines.h"
 #include "board.h"
 #include "display.h"
 #include "timer.h"
 #include "buttons.h"
 #include <avr/io.h>
 #include <util/delay.h>

 uint8_t nEvent1;
 uint8_t nEvent2;

 uint8_t menu = 0;
 uint8_t subMenu = 0;
 uint8_t par = 0;

 uint8_t tempHour;
 uint8_t tempMin;


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

		case 1 :
			getFlag(3);
			switch (par)
			{
				case 0 :
					displayMenu(SYM_A, 3);
					displayMenu(SYM_L, 2);
					displayMenu(NONE, 1);
					displayMenu(NONE, 0);
					break;

				case 1 :
					displayMenu(SYM_T, 3);
					displayMenu(SYM_I, 2);
					displayMenu(NONE, 1);
					displayMenu(NONE, 0);
					break;

				case 2 :
					displayMenu(SYM_C, 3);
					displayMenu(SYM_L, 2);
					displayMenu(NONE, 1);
					displayMenu(NONE, 0);
					break;
			}
			break;

		case 2 :
			if (subMenu == 0)
			{
				getFlag(1);
				displayTime((uint16_t)tempMin);
				setTime(tempMin, 0);
			}
			else
			{
				getFlag(2);
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

	if (nEvent1 == KEY_EV_LONG && nEvent2 == KEY_EV_LONG)
	{
		//disable ALARM
	}
	else
	{
		if (nEvent1 == KEY_EV_SHORT)
		{
			menu++;
			if (menu > 2)
			{
				menu = 2;
				subMenu++;
				if (subMenu > 1)
				{
					subMenu = 0;
				}
			}
		}
		else if (nEvent1 == KEY_EV_LONG)
		{
			menu = 0;
			subMenu = 0;
		}

		if (nEvent2 == KEY_EV_SHORT)
		{
			if (menu == 1)
			{
				par++;
				if (par > 2)
				{
					par = 0;
				}
			}
			else if (menu == 2)
			{
				if (subMenu == 1)
				{
					tempHour++;
					if (tempHour > 23)
					{
						tempHour = 0;
					}
				}
				else
				{
					tempMin++;
					if (tempMin > 59)
					{
						tempMin = 0;
					}
				}
			}
		}

		if (nEvent2 == KEY_EV_LONG)
		{
			if (menu == 2)
			{
				if (subMenu == 1)
				{
					tempHour += 5;
					if (tempHour > 23)
					{
						tempHour = 0;
					}
				}
				else
				{
					tempMin += 5;
					if (tempMin > 59)
					{
						tempMin = 0;
					}
				}
			}
		}

	}

	
}