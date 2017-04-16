#include <msp430.h>

int r_flag=1, r_time, f_time, on_time;

#pragma vector = TIMER1_A1_VECTOR
__interrupt void ccr2_isr()
{
    if(TA1IV == 4) // TA1CCR2 CCIFG
    {
        if(r_flag)
        {
            r_time = TA1CCR2;
            r_flag = 0;
            TA1CCTL2 = 0x8910;  // 1000 1001 0001 0000 falling
        }
        else
        {
            f_time = TA1CCR2;
            on_time = f_time - r_time;
            r_flag = 1;
            TA1CCTL2 = 0x4910;  // 0100 1001 0001 0000 rising
        }
    }
}



int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;
    PM5CTL0 &= ~LOCKLPM5;
    
    P1DIR |= 0x80;  // 1000 0000
    P1SEL0 |= 0x80; // 1000 0000
    
    P8DIR &= 0xf7;  // 1111 0111
    P8SEL0 |= 0x08; // 0000 1000
    
    TA0CTL = 0x0210;    // 0000 0010 0001 0000  SMCLK/1 Up mode
    TA0CCTL1 = 0x00e0;  // 0000 0000 1110 0000  Reset/set
    TA0CCR0 = 100 - 1;  // 0-99     100 / 1,000,000 = 0.1ms 10kHz
    TA0CCR1 = 60 - 1;   // 0-59
    
    TA1CTL = 0x0220;    // 0000 0010 0010 0000  SMCLK/1 Continuous
    TA1CCTL2 = 0x4910;  // 0100 1001 0001 0000 rising capture
    TA1CCR2 = 0;
    
    __enable_interrupt();
    
}



 /*
  * 60으로 설정되어 있는데,  이게 40 이하로 떨어지면 캡쳐가 안됨.
  * 인터럽트하는 시간이 40마이크로세컨 넘어가면 캡쳐가 안됨.
  *
  */
