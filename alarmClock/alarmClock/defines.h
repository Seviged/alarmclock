/*
 * defines.h
 *
 * Created: 01.02.2017 13:41:17
 *  Author: Seviged
 */ 


#ifndef DEFINES_H_
#define DEFINES_H_

#ifndef F_CPU
#define F_CPU 14745600UL
#endif

// General defines
#ifndef NULL
#define NULL	0																// Used for pointer
#endif

#ifndef FALSE
#define FALSE	0																// Used for boolean
#endif

#ifndef TRUE
#define TRUE	1																// Used for boolean
#endif

// STANDARD BITS
#define BIT0	0x0001
#define BIT1	0x0002
#define BIT2	0x0004
#define BIT3	0x0008
#define BIT4	0x0010
#define BIT5	0x0020
#define BIT6	0x0040
#define BIT7	0x0080
#define BIT8	0x0100
#define BIT9	0x0200
#define BITA	0x0400
#define BITB	0x0800
#define BITC	0x1000
#define BITD	0x2000
#define BITE	0x4000
#define BITF	0x8000

#define ENABLE_INTERRUPTS asm volatile("sei"::)									// Enable all Interrupts
#define DISABLE_INTERRUPTS asm volatile("cli"::)								// Disable all Interrupts

typedef unsigned char		bool_t;												//	1 Bit variable



#endif /* DEFINES_H_ */