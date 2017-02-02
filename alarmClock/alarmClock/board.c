/*
 * board.c
 *
 * Created: 01.02.2017 13:42:04
 *  Author: Seviged
 */ 


  #include "board.h"
  #include <avr/io.h>




  void initBoard()
  {
	  #ifdef PORTB_SETTING
	  DDRB  = DDRB_SETTING;														// Set PortB direction register
	  PORTB = PORTB_SETTING;														// Set PortB output register
	  #endif

	  #ifdef PORTC_SETTING
	  DDRC  = DDRC_SETTING;														// Set PortC direction register
	  PORTC = PORTC_SETTING;														// Set PortC output register
	  #endif

	  #ifdef PORTD_SETTING
	  DDRD  = DDRD_SETTING;														// Set PortD direction register
	  PORTD = PORTD_SETTING;														// Set PortD output register
	  #endif
  }