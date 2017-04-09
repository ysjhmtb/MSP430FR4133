#include <msp430.h>

int flag=1;
int i,b=0,a=0;
int hour=11,min=31,year=2017,month=3,day=26,mode=2,mon=1,m=1,longsw1=0,longsw2=0,longsw3=0,z=0,lsec=0,lmsec=0;
int msec=0,sec=0;
float lap=0;
char rd;

char mapping1[]={0xfc,0x00,0xdb,0xf3,0x07,0xb7,0xbf,0xe0,0xff,0xf7,0xef,0xfc,0x9e};//0~9
char mapping2[]={0x00,0x50,0x00,0x00,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x22};

//char mapping1[]={0xef,0x9e,0x9c,0xfc,0x9f,0x8f,0xbd,0x6f,0x90,0xe0,0x0e,0x1c,0x6c}; //A~M
//char mapping2[]={0x00,0x22,0x00,0x00,0x00,0x00,0x00,0x00,0x50,0x02,0x22,0x00,0xa0};
//char mapping1[]={0x6c,0xfc,0xcf,0xfc,0xcf,0x90,0x80,0x7c,0x60,0x7c,0x00,0x00,0x90}; //N~Z
//char mapping2[]={0x82,0x00,0x00,0x02,0x02,0x82,0x50,0x00,0x82,0x50,0xaa,0xb0,0x28};
//char mapping1[]={0x00,0xef,0x9e,0x9c,0xfc,0x9f,0x8f,0xbd,0x6f,0x90,0xe0,0x0e,0x1c,0x6c,0x6c,0xfc,0xcf,0xfc,0xcf,0x90,0x80,0x7c,0x60,0x7c,0x00,0x00,0x90,0x00}; // for 이름
//char mapping2[]={0x00,0x00,0x22,0x00,0x00,0x00,0x00,0x00,0x00,0x50,0x02,0x22,0x00,0xa0,0x82,0x00,0x00,0x02,0x02,0x82,0x50,0x00,0x82,0x50,0xaa,0xb0,0x28,0x00};


void display_char(int pos,int letter){
     if(pos==1){
          LCDM4=mapping1[letter];
          LCDM5=mapping2[letter];
     }
      else if(pos==2){
           LCDM6=mapping1[letter];
           LCDM7=mapping2[letter];
     }
      else if(pos==3){
           LCDM8=mapping1[letter];
           LCDM9=mapping2[letter]|0x01;
           }
      else if(pos==4){
           LCDM10=mapping1[letter];
           LCDM11=mapping2[letter];
           }
      else if(pos==5){
           LCDM2=mapping1[letter];
            LCDM3=mapping2[letter];
            }
      else{
          LCDM18=mapping1[letter];
          LCDM19=mapping2[letter];
          }
     }

//void display_char(int pos,int letter){
// if(pos==1){
// LCDM4=mapping1[letter];
// LCDM5=mapping2[letter];
// }
// else if(pos==2){
// LCDM6=mapping1[letter];
// if(mode==1) LCDM7=mapping2[letter]|0x04;
// else if(mode==2) LCDM7=mapping2[letter]|0x01;
// }
// else if(pos==3){
// LCDM8=mapping1[letter]|0x04;
// LCDM9=mapping2[letter];
// }
// else if(pos==4){
// LCDM10=mapping1[letter];
// if(mode==1) LCDM11=mapping2[letter]|0x04;
// else if(mode==2) LCDM11=mapping2[letter]|0x01;
// }
// else if(pos==5){
// LCDM2=mapping1[letter];
// LCDM3=mapping2[letter];
// }
// else{
// LCDM18=mapping1[letter];
// LCDM19=mapping2[letter];
// }
//}

void delay(volatile int a)
{while(a--);}

#pragma vector=PORT1_VECTOR
__interrupt void sw1(void)
{
     delay(1000);
     switch(P1IV)
     {
      case 6:
           delay(500);

      if((P1IN & 0x04) == 0)
      {
           if(mode==1) 
               mode=2;
           else if(mode==2) 
               mode=1;
      }
      
       break;
      }
}

/* P1IV
 * 
 * Port 1 interrupt vector value
 * 00h = No interrupt pending
 * 02h = Interrupt Source: Port 1.0 interrupt; Interrupt Flag: P1IFG.0; Interrupt
 * Priority: Highest
 * 04h = Interrupt Source: Port 1.1 interrupt; Interrupt Flag: P1IFG.1
 * 06h = Interrupt Source: Port 1.2 interrupt; Interrupt Flag: P1IFG.2
 * 08h = Interrupt Source: Port 1.3 interrupt; Interrupt Flag: P1IFG.3
 * 0Ah = Interrupt Source: Port 1.4 interrupt; Interrupt Flag: P1IFG.4
 * 0Ch = Interrupt Source: Port 1.5 interrupt; Interrupt Flag: P1IFG.5
 * 0Eh = Interrupt Source: Port 1.6 interrupt; Interrupt Flag: P1IFG.6
 * 10h = Interrupt Source: Port 1.7 interrupt; Interrupt Flag: P1IFG.7; Interrupt
 * Priority: Lowest
 * 
 * 
 * P1IN & 0x04 = ???? ???? & 0000 0100 = 0000 0?00
 * 
 * Port x input 
 * 0b = Input is low
 * 1b = Input is high
 * 
 */


#pragma vector=PORT2_VECTOR
__interrupt void sw2(void)
{
     delay(500);
     switch(P2IV)
     {

      case 14:      //P2.6sw4
          delay(500);
          
      if((P2IN & 0x40) == 0)
      {
          if(mode==2) 
              msec=0,sec=0;
          else if(mode==1) 
              lsec=sec,lmsec=msec;
      }

      break;
     }
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void timer0_handler(void)
{
    if(mode==1)
    {
        msec++;
        if(msec == 1000)
        {
             msec=0;
             sec++;

             if(sec==1000) 
                 sec=0;
        }
    }
     if(mode==2)
         __no_operation();
     
     if((P2IN & 0x40)==0) 
         longsw1++;
}

void init_LCD(){

 P8DIR|=0x07;//col output 세로

 P5DIR&=~0x0f;//row input 가로
 P5REN|=0x0f;
 P5OUT|=0x0f;

 SYSCFG2|=0x1000;

 LCDPCTL0=0xffff;
 LCDPCTL1=0x07ff;
 LCDPCTL2=0x00f0;//어떤 라인에 LCD 기능 핀으로 설정할지

 LCDCTL0= 0x385d;
 LCDVCTL=0xf0c0;

 LCDMEMCTL|=0x0002; // 클리어
 LCDCSSEL0=0x000f;//어떤 라인을 com으로 쓸지

 LCDM0=0x21;
 LCDM1=0x84;
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer
    PM5CTL0&=~LOCKLPM5;

    init_LCD();

    P1DIR |= 0xfb;  // 1111 1011
    P2DIR |= 0xbf;  // 1011 1111

    P1REN |= 0x04;  // 0000 0100
    P2REN |= 0x40;  // 0100 0000

    P1OUT |= 0x04;  // 0000 0100
    P2OUT |= 0x40;  // 0100 0000

    P1IES |= 0x04;  // 0000 0100
    P2IES |= 0x40;  // 0100 0000

    P1IE |= 0x04;   // 0000 0100
    P2IE |= 0x40;   // 0100 0000


    TA0CCTL0 = 0x0010;  //  0000 0000 0001 0000
    TA0CCR0 = 1000-1;   //  1000 - 1 = 999
    TA0CTL = 0x0210;    //  0000 0010 0001 0000
    
    /* TAxCCTLn
     * 15-14    00      00b = No capture
     * 13-12    00      00b = CCIxA
     * 11       0       0b = Asynchronous capture
     * 10       0       Synchronized capture/compare input.
     * 8        0       0b = Compare mode
     * 7-5      000     000b = OUT bit value
     * 4        0       0b = Interrupt disabled
     * 3        0       Capture/compare input. The selected input signal can be read by this bit.
     * 2        0       0b = Output low
     * 1        0       0b = No capture overflow occurred
     * 0        0       0b = No interrupt pending
     * 
     * 
     * TAxCTL
     * 9-8      10b = SMCLK
     * 7-6      00b = /1
     * 5-4      01b = Up mode: Timer counts up to TAxCCR0 
     * 
     */

    __enable_interrupt();
    
    while(1)
    {
        if(longsw1>=1000)
        {
            longsw1=0;
            if(z==0) 
                z=1;
            else if(z==1) 
                z=0;
        }

        for(i=0;i<3;i++)
        {
            P8OUT = 0x07;   //p8세로 p5가로
            P8OUT &= ~(0x01<<i);
            /*
             *  0000 0111 & ~(0000 0001 << 0) = 0000 0111 & 1111 1110 = 0000 0110
             */

            if(rd != 0x0f)
            {
                if(flag==1)
                {
                    flag=0;
                    if(rd==0x0e) 
                        b=1+i;
                    else if(rd==0x0d) 
                        b=4+i;
                    else if(rd==0x0b) 
                        b=7+i;
                    else if(rd==0x07)
                        b=10+i;
                }
            }
            else 
                flag=1;
        }

        if(z==0)
        {
            display_char(1,sec/100);
            display_char(2,(sec%100)/10);
            display_char(3,sec%10);
            display_char(4,msec/100);
            display_char(5,(msec%100)/10);
            display_char(6,msec%10);
        }
        else if(z==1)
        {
            display_char(1,lsec/100);
            display_char(2,(lsec%100)/10);
            display_char(3,lsec%10);
            display_char(4,lmsec/100);
            display_char(5,(lmsec%100)/10);
            display_char(6,lmsec%10);
        }
    }
}
