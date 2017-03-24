
#include <msp430.h>
#include <intrinsics.h>

const char seg1[] = {0x80,0xf1,0x48,0x60,0x31,0x22,0x02,0xb0,0x00,0x20,0x10,0x03,0x8a,0x41,0x0a,0x1a};
const char seg2[] = {0x20};
void find_display(int index, int digit);

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;
    volatile int i=0;
    volatile int sw1,keyin;
    volatile int flag=1;
    P1DIR |= 0xfb;
    P1OUT |= 0xfb;
    P2DIR |= 0x20;//P2.5 자릿수
    P2OUT |= 0x00;
    P5DIR |= 0x00;//ROW 부분 연결
    P5OUT |= 0x0f;
    P5REN |= 0x0f;
    P8DIR |= 0x0f;//COL   부분 연결1
    P8OUT |= 0x0f;
    while(1){
       for(i=0;i<3;i++)
       {
6          P8OUT &= ~(0x01<<i);
          P8OUT &= 0x07;
          sw1 = P5IN & 0x0f;
          if(sw1!=0x0f)
          {
             if(flag==1)
             {
                flag=0;
                if(sw1==0x0e)
                {
                   keyin=1+i;
                   find_display(keyin,0);
                }
                else if(sw1==0x0d)
                {
                   keyin=4+i;
                   find_display(keyin,0);
                }
                else if(sw1==0x0b)
                {
                   keyin=7+i;
                   find_display(keyin,0);
                }
                else if(sw1==0x07)
                {
                   keyin=0x0a+i;
                      if(keyin==0x0b)
                      {
                         keyin = 0;
                      }
                      if(keyin==0x0c)
                      {
                         keyin = 0x0b;
                      }
                   find_display(keyin,0);
                }

             }
          }
          else
          {
             flag = 1;
             P8OUT = 0x07;
          }
       }

    }
}
void find_display(int index, int digit)
{
   P1OUT = seg1[index];
   P2OUT = seg2[digit];
}

