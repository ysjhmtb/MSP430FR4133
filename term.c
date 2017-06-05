
#include <msp430.h>

int hour = 14, min = 10, sec = 55;


char mapping1[]={0xfc,0x00,0xdb,0xf3,0x07,0xb7,0xbf,0xe0,0xff,0xf7,0xef,0xfc,0x9e};//0~9
char mapping2[]={0x00,0x50,0x00,0x00,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x22};


char UCAmapping1[26] = {0xef,0x1e,0x9c,0x3b,0x9f,0x8e,0xbd,0x6f,0x90,0x88,0x0e,0x1c,0x6c,0x6c,0xfc,0xcf,0x86,0xcf,0xb7,0x80,0x7c,0x60,0x6c,0x00,0x00,0x90};
char UCAmapping2[26] = {0x00,0x82,0x00,0x00,0x00,0x00,0x00,0x00,0x50,0x48,0x22,0x00,0xa0,0x82,0x00,0x00,0x42,0x02,0x00,0x50,0x00,0x82,0x0a,0xaa,0xb0,0x28};


void init_LCD()
{

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

void display_char(int pos,int letter)
{
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
           LCDM9=mapping2[letter];
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


void delay(volatile int a)
{while(a--);}


#pragma vector=TIMER0_A0_VECTOR
__interrupt void timer0_handler(void)
{
        sec++;
        if(sec == 60)
        {
             sec = 0;
             min++;
        }

        if(min == 60)
        {
            min = 0;
            hour++;
        }

        if(hour == 24)
        {
            hour = 0;
        }
}



int main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer
    PM5CTL0&=~LOCKLPM5;

    P1DIR = 0x01;

    init_LCD();

    TA0CCTL0 = 0x0010;  //  0000 0000 0001 0000
    TA0CCR0 = 32767;   //
    TA0CTL = 0x0110;    //  0000 0001 0001 0000

    __enable_interrupt();

    while(1)
    {


            display_char(6,sec%10);
            display_char(5,sec/10);
            display_char(4,min%10);
            display_char(3,min/10);
            display_char(2,hour%10);
            display_char(1,hour/10);

        if(hour == 14 && min == 11 )
            {
                break;
            }

    }

    while(sec<30)
    {

    LCDM4=UCAmapping1[6];
    LCDM5=UCAmapping2[6];

    LCDM6=UCAmapping1[4];
    LCDM7=UCAmapping2[4];

    LCDM8=UCAmapping1[19];
    LCDM9=UCAmapping2[19];

    LCDM10=UCAmapping1[20];
    LCDM11=UCAmapping2[20];

    LCDM2=UCAmapping1[15];
    LCDM3=UCAmapping2[15];

    LCDM18=mapping1[sec%10];
    LCDM19=mapping2[sec%10];

    }

    while(1)
        {
                display_char(6,sec%10);
                display_char(5,sec/10);
                display_char(4,min%10);
                display_char(3,min/10);
                display_char(2,hour%10);
                display_char(1,hour/10);
        }

}


