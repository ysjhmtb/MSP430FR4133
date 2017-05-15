// 간이 전압 측정기 만들기


#include <msp430.h> 
#include <intrinsics.h>
/*
 * main.c
 */
unsigned int result[8],index,dvccResult,average;

unsigned int res=0;
const char digit [36]={0xFC,0x00,0xDB,0xF3,0x07,0xB7,0xBF,0xE4,0xFF,0xF7,0xEF,0xF1,0x9C,0xF0,0x9F,0x8F,0xBD,0x6F,0x90,0x88,0x00,0x1C,0x6C,0x6C,0xFC,0xCF,0xFC,0xCF,0x96,0x80,0x7C,0x60,0x7C,0X00,0x00,0X90};
const char digir [36]={0x28,0x50,0x00,0x00,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x50,0x00,0x50,0x00,0x00,0x00,0x00,0x50,0x48,0x72,0x00,0x40,0x82,0x00,0x00,0x02,0x02,0x02,0x50,0x00,0x82,0x50,0xAA,0xB0,0x28};
int numbet,number;

void lcd(int numbet,int number){
    switch (numbet){
    case 1 :
        LCDM4 = digit[number];
        LCDM5 = digir[number];
        break;
    case 2 :
        LCDM6 = digit[number];
        LCDM7 = digir[number];
        LCDM7|=0x0001;
        break;
    case 3 :
        LCDM8 = digit[number];
        LCDM9 = digir[number];

        break;
    case 4 :
        LCDM10 = digit[number];
        LCDM11 = digir[number];
        break;
    case 5 :
        LCDM2 = digit[number];
        LCDM3 = digir[number];
        break;
    case  6:
        LCDM18 = 0x0D;
        LCDM19 = 0x28;
        break;
    };
};

#pragma vector=ADC_VECTOR
__interrupt void ADC12_ISR(void)
{
    
    res+=ADCMEM0;
    if(index++>7)
    {
        average=res>>3;
        dvccResult=((unsigned long)1023*average)/330;
        lcd(2,dvccResult/1000);
        lcd(3,dvccResult%1000/100);
        lcd(4,dvccResult%100/10);
        lcd(5,dvccResult%10);
        lcd(6,6);
        index=0;
        res=0;

    }
    __no_operation();
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0=~LOCKLPM5;
    SYSCFG2|=0x1200;
    ADCCTL0 |=ADCON | ADCMSC;
    ADCCTL1 |=ADCCONSEQ_2 + ADCBUSY + ADCSHP;//repeat single ch.
    ADCCTL2 |=ADCRES;
    ADCMCTL0=ADCINCH_9;
    ADCIE |=ADCIE0;
    ADCCTL0|=ADCENC;
    ADCCTL0|=ADCSC;
    SYSCFG2 |=0x1000;
    LCDPCTL0=0xFFFF;
    LCDPCTL1=0x07FF;
    LCDPCTL2=0x00F0;
    LCDCTL0=0x385C;
    LCDVCTL=0xFFC0;//1111 1000 1100 0000
    LCDCSSEL0=0x000F;
    LCDM0=0x21;
    LCDM1=0x84;
    LCDCTL0 |=0x0001;
    __enable_interrupt();
    
    while(1)
    {
        __no_operation();
    }

    return 0;
}
