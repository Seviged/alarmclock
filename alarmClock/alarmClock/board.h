/*
 * board.h
 *
 * Created: 01.02.2017 13:42:15
 *  Author: Seviged
 */ 


#ifndef BOARD_H_
#define BOARD_H_

#include "defines.h"


// Port B
// Usage Port B.0: button 1
// Usage Port B.1: button 2
// Usage Port B.2: not used
// Usage Port B.3: ISP/DebugWire/output
// Usage Port B.4: ISP/DebugWire/output
// Usage Port B.5: ISP/DebugWire
// Usage Port B.6: crystal
// Usage Port B.7: crystal

#define DDRB_SETTING	0x1C													// B.0 - B.7 inputs
#define PORTB_SETTING	0xFB													// pull up



// Port C

#define DDRC_SETTING			0x3F											// C.0 - C.7 inputs
#define PORTC_SETTING			0xC0											// pull up



// Port D
// Usage Port D.0: led
// Usage Port D.1: led
// Usage Port D.2: led
// Usage Port D.3: led
// Usage Port D.4: led
// Usage Port D.5: led
// Usage Port D.6: led
// Usage Port D.7: beeper

#define DDRD_SETTING	0xFF													// set d1, d4-d7 as output
#define PORTD_SETTING	0x1F													// pull up, d0 d2 d3

//leds to power
#define SET_D1					PORTC |=  BIT0									// Switch on
#define CLR_D1					PORTC &= ~BIT0									// Switch off
#define TGL_D1					PORTC ^=  BIT0									// Toggle
#define IS_D1_ON				((PINC & BIT0) == BIT0)

#define SET_D2					PORTC |=  BIT1									// Switch on
#define CLR_D2					PORTC &= ~BIT1									// Switch off
#define TGL_D2					PORTC ^=  BIT1									// Toggle
#define IS_D2_ON				((PINC & BIT1) == BIT1)

#define SET_D3					PORTC |=  BIT2									// Switch on
#define CLR_D3					PORTC &= ~BIT2									// Switch off
#define TGL_D3					PORTC ^=  BIT2									// Toggle
#define IS_D3_ON				((PINC & BIT2) == BIT2)

#define SET_D4					PORTC |=  BIT3									// Switch on
#define CLR_D4					PORTC &= ~BIT3									// Switch off
#define TGL_D4					PORTC ^=  BIT3									// Toggle
#define IS_D4_ON				((PINC & BIT3) == BIT3)

#define SET_D5					PORTC |=  BIT4									// Switch on
#define CLR_D5					PORTC &= ~BIT4									// Switch off
#define TGL_D5					PORTC ^=  BIT4									// Toggle
#define IS_D5_ON				((PINC & BIT4) == BIT4)

#define SET_D6					PORTC |=  BIT5									// Switch on
#define CLR_D6					PORTC &= ~BIT5									// Switch off
#define TGL_D6					PORTC ^=  BIT5									// Toggle
#define IS_D6_ON				((PINC & BIT5) == BIT5)

//zero leds to ground
#define SET_L1					PORTD |=  BIT0									// Switch on
#define CLR_L1					PORTD &= ~BIT0									// Switch off
#define TGL_L1					PORTD ^=  BIT0									// Toggle
#define IS_L1_ON				((PIND & BIT0) == BIT0)

#define SET_L2					PORTD |=  BIT1									// Switch on
#define CLR_L2					PORTD &= ~BIT1								// Switch off
#define TGL_L2					PORTD ^=  BIT1									// Toggle
#define IS_L2_ON				((PIND & BIT1) == BIT1)

#define SET_L3					PORTD |=  BIT2									// Switch on
#define CLR_L3					PORTD &= ~BIT2									// Switch off
#define TGL_L3					PORTD ^=  BIT2									// Toggle
#define IS_L3_ON				((PIND & BIT2) == BIT2)

#define SET_L4					PORTD |=  BIT3									// Switch on
#define CLR_L4					PORTD &= ~BIT3									// Switch off
#define TGL_L4					PORTD ^=  BIT3									// Toggle
#define IS_L4_ON				((PIND & BIT3) == BIT3)

#define SET_L5					PORTD |=  BIT4									// Switch on
#define CLR_L5					PORTD &= ~BIT4									// Switch off
#define TGL_L5					PORTD ^=  BIT4									// Toggle
#define IS_L5_ON				((PIND & BIT4) == BIT4)

#define SET_L6					PORTB |=  BIT3									// Switch on
#define CLR_L6					PORTB &= ~BIT3									// Switch off
#define TGL_L6					PORTB ^=  BIT3									// Toggle
#define IS_L6_ON				((PINB & BIT3) == BIT3)

#define SET_L7					PORTB |=  BIT4									// Switch on
#define CLR_L7					PORTB &= ~BIT4									// Switch off
#define TGL_L7					PORTB ^=  BIT4									// Toggle
#define IS_L7_ON				((PINB & BIT4) == BIT4)

//relays
#define SET_R1					PORTD |=  BIT5									// Switch on
#define CLR_R1					PORTD &= ~BIT5									// Switch off
#define TGL_R1					PORTD ^=  BIT5									// Toggle
#define IS_R1_ON				((PIND & BIT5) == BIT5)

#define SET_R2					PORTD |=  BIT6									// Switch on
#define CLR_R2					PORTD &= ~BIT6									// Switch off
#define TGL_R2					PORTD ^=  BIT6									// Toggle
#define IS_R2_ON				((PIND & BIT6) == BIT6)

//beeper
#define SET_PWM					PORTD |=  BIT7									// Switch on
#define CLR_PWM					PORTD &= ~BIT7									// Switch off
#define TGL_PWM					PORTD ^=  BIT7									// Toggle
#define IS_PWM_ON				((PIND & BIT7) == BIT7)

#define SET_PWM2					PORTB |=  BIT2									// Switch on
#define CLR_PWM2					PORTB &= ~BIT2									// Switch off
#define TGL_PWM2					PORTB ^=  BIT2									// Toggle
#define IS_PWM2				((PINB & BIT2) == BIT2)

#define GET_KEY_S0				((PINB & BIT0) == 0x00)
#define GET_KEY_S1				((PINB & BIT1) == 0x00)


void initBoard();


#endif /* BOARD_H_ */