/*
 * buttons.h
 *
 * Created: 01.02.2017 13:41:37
 *  Author: Seviged
 */ 


#ifndef BUTTONS_H_
#define BUTTONS_H_

 #include "defines.h"
 #include "board.h"
 #include <avr/io.h>


 #define APP_KEY_COUNT		3													// Count of application keys
 #define IS_KEY_PRESSED_0	GET_KEY_S0											// Port pin for channel 1
 #define IS_KEY_PRESSED_1	GET_KEY_S1											// Port pin for channel 2

 // States of key
 #define	KEY_ST_OFF			0x00												// Key is released
 #define	KEY_ST_NEW			0x10												// Key is just pressed
 #define	KEY_ST_SHORT		0x30												// Key is pressed short
 #define	KEY_ST_LONG			0x40												// Key is pressed long
 #define	KEY_ST_MASK			0xF0												// Key state mask

 // Events of key
 #define	KEY_EV_NONE			0x00												// No new event on key
 #define	KEY_EV_SHORT		0x01												// Event: Key is pressed short
 #define	KEY_EV_LONG			0x02												// Event: Key is pressed long
 #define	KEY_EV_RELEASE		0x03												// Event: Key is released
 #define	KEY_EV_MASK			0x0F												// Event state mask

 // Key timing
 #define	KEY_TIME_SHORT		60													// Debounce time before pressed short
 #define	KEY_TIME_LONG		1000													// Time before pressed long

 /// This structure is used to define a key channel
 typedef struct KeyChannel_tag
 {
	 uint16_t	nLastTime;														// Time stamp of last event
	 uint8_t		nState;															// State of key
 } KeyChannel_t;


 bool_t	AppKey_Init();
 uint8_t AppKey_GetKeyEvent(uint8_t nKeyNo);
 void	AppKey_Process();

 void		AppKey_ProcessChannel(uint8_t nChannel);
 bool_t	AppKey_IsKeyPressed(uint8_t nChannel);


#endif /* BUTTONS_H_ */