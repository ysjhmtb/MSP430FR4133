#include <msp430.h>

#define CCR1INTVAL 1048575

#pragma vector = TIMER0_A0_VECTOR
__interrupt void ccr0_isr(void)
{
	P2OUT^=0x80;
}

int main(void)
{
	WDTCTL = WDTPW|WDTHOLD;
	PM5CTL0&=~LOCKLPM5;
	P2DIR |= 0x80;
	TA0CCTL0 = 0x0010;
	TA0CCR0=2620;
	TA0CTL=0x250;
	__enable_interrupt();

}

