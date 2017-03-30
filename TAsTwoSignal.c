#include <msp430.h>
#include <intrinsics.h>
#define CCR1INTVAL 32768  // 1sec
#define CCR2INTVAL 32768/3	  // 0.3sec
#pragma vector = TIMER0_A1_VECTOR
__interrupt void isr(void){
	switch(TA0IV){
	case 10: break;
	case 2:
		P1OUT ^= 0x01;
		TA0CCR1 += CCR1INTVAL;
		break;
	case 4:
		P4OUT ^= 0x01;
		TA0CCR2 += CCR2INTVAL;
		break;
	}
}


void main(void){
	WDTCTL = WDTPW|WDTHOLD;
	PM5CTL0 &= ~LOCKLPM5;

	P1DIR |= 0x01;
	P1DIR &= ~0x04;
	P1OUT |= 0x04;
	P1REN |= 0x04;
	P4DIR |= 0x01;
	P4DIR &= ~0x04;
	P4OUT |= 0x04;
	P4REN |= 0x04;
	TA0CCTL1 = 0x0010;
	TA0CCR1 = 16384;
	TA0CCTL2 = 0x0010;
	TA0CCR2 = 4096;
	TA0CTL = 0x0120;
	__enable_interrupt();
	__low_power_mode_3();

}

