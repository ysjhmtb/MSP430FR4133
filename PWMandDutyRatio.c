#include <msp430.h>

void main(void){
	WDTCTL = WDTPW | WDTHOLD;
	PM5CTL0 &= ~LOCKLPM5;
	P1DIR |= 0xc0;
	P1SEL0 |= 0Xc0;
	TA0CCR0 = 1024;
	TA0CCTL1 = 0x00E0;
	TA0CCR1 = 921;
	TA0CTL = 0x0210;
	
	/*
	 * TA0CCR1 = 102;	10%
	 * TA0CCR1 = 307;	30%
	 * TA0CCR1 = 768;	75%
	 * TA0CCR1 = 921;	90%
	 */
}
