// 간이 전압 측정기 만들기


#include <msp430.h>
#include <intrinsics.h>
/*
 * main.c
 */
unsigned int result[8], index, dvccResult, average;

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

int main(void)
{
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







// 가. 센서 ETH-01DV 이용하여 온습도 측정기 만들기

#pragma vector=ADC_VECTOR
__interrupt void ADC12_ISR(void)
{

    if(flag){
        ADCCTL0&=~ADCENC; //ADC  레지스터 설정을 위해 꺼두는 것이다.
        ADCMCTL0&=~ADCINCH_3; //A0로 채널을 설정 하였다.
        ADCCTL0|=ADCENC; //ADC를 ON시켜주는 코드이다.
        ADCCTL0|=ADCSC;
        flag=0; //FLAG를 0으로 만든다.
        res+=ADCMEM0;//8번 값을 받고
        if(index++==6){ //이게8번 받았을 경우
            index=0;
            Taverage=res>>3 //8로 나누고;
            TdvccResult=Taverage*22-6687;//이값을 우리가 알아볼수 있는 형태로 만듬

            res=0;
        }


    }
    else{
        ADCCTL0&=~ADCENC;//ADC를ON시켜줌
        ADCMCTL0|=ADCINCH_3;//A3채널로 설정
        ADCCTL0|=ADCENC;
        ADCCTL0|=ADCSC;
        flag=1;
        tes+=ADCMEM0;//8번 받는다.
        if(nindex++==6){//8번받으면 8로 나눈다.
            nindex=0;
            Haverage=tes>>3;
            HdvccResult=Haverage*5250/484-1250;//우리가 볼 수 있는 형태로 바꾼다.

            tes=0;
        }


    }
}



/*
#pragma vector=ADC_VECTOR
__interrupt void ADC12_ISR(void)
{
    switch(flag){
    case 0:
    flag++;
    res+=ADCMEM0;
    if(index++==6){
        index=0;
        Taverage=res>>3;
        TdvccResult=Taverage*22-6687;
        res=0;
        break;
    case 1: flag++; break;
    case 2: flag++; break;
    case 3:
        flag=0;
        tes+=ADCMEM0;
        if(nindex++==6){
            nindex=0;
            Haverage=tes>>3;
            HdvccResult=Haverage*5250/484-1250;
            tes=0;
            break;
        }
    }
    }
}
ADCCTL1 |=0x02B7;//ADCCONSEQ_3 + ADCBUSY + ADCSHP;//repeat sequence ch.

*/


void lcd(int numbet,int number){  //LCD에 표시하기 위한 함수
    switch (numbet){
    case 1 :
        LCDM4 = digit[number];
        LCDM5 = digir[number];
        break;
    case 2 :
        LCDM6 = digit[number];
        LCDM7 = digir[number];
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
    case  6:
        LCDM18 = digit[number];
        LCDM19 = digir[number];
        break;
    }
}
#pragma vector=PORT1_VECTOR
__interrupt void p1_handler(void){
    if(P1IV==6){
        if((P1IN&0x04)==0){
            disflag^=0x01; //스위치를 통해 무엇을 보여줄지 결정하는 변수
        }

    }
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0&=~LOCKLPM5;
    SYSCFG2|=0x1009;
    ADCCTL0 |=ADCON + ADCMSC; 
    ADCCTL1 |=0x02B5;//ADCCONSEQ_3 + ADCBUSY + ADCSHP;//repeat SINGLE CHAN
    ADCCTL2 |=ADCRES;
    ADCMCTL0=ADCINCH_3; //A3설정
    ADCIE |=ADCIE0;
    ADCCTL0|=ADCENC;
    ADCCTL0|=ADCSC;
    LCDPCTL0=0xFFFF;
    LCDPCTL1=0x07FF;
    LCDPCTL2=0x00F0;
    LCDCTL0=0x385C;
    LCDVCTL=0xFFC0;//1111 1000 1100 0000
    LCDCSSEL0=0x000F;
    LCDM0=0x21;
    LCDM1=0x84;
    LCDCTL0 |=0x0001;
    ADCMEM0=0;
    P1DIR&=~0x04;
    P1REN |= 0x04;
    P1OUT |= 0x04;
    P1IES |=0x04;
    P1IE |=0x04;
    disflag=0;
    __enable_interrupt();

    while(1){

        ADCCTL0&=~ADCENC;
        if(disflag){  //DISFLAG가 1일때는 온도를 보여준다.
                lcd(2,TdvccResult/1000);
                lcd(3,TdvccResult%1000/100);
                lcd(4,TdvccResult%100/10);
                lcd(5,TdvccResult%10);
                lcd(6,11);
                __delay_cycles(3000);
            }
            else{ //DISFLAG가 0일때는 습도를 보여준다.
                lcd(2,HdvccResult/1000);
                lcd(3,HdvccResult%1000/100);
                lcd(4,HdvccResult%100/10);
                lcd(5,HdvccResult%10);
                lcd(6,10);
                __delay_cycles(3000);
            }
    ADCCTL0|=ADCENC; //항상 실행을 시켜주기 위한 코드이다.
    ADCCTL0|=ADCSC;


        __no_operation();
    }

}
















// 나. MCU 내장 온도센서 사용 하기

volatile long temp;
volatile long IntDegF;
volatile long IntDegC;
unsigned int s, result[16],ss,i;

void dis(int a, int b)
{
    switch(a){
    case 6:
        LCDMEM[4]=dig3[b];
        LCDMEM[5]=dig4[b];  //A1
        break;
    case 5:
        LCDMEM[6]=dig3[b];
        LCDMEM[7]=dig4[b];  //A2
        break;
    case 4:
        LCDMEM[8]=dig3[b];
        LCDMEM[9]=dig4[b];  //A3
        break;
    case 3:
        LCDMEM[10]=dig3[b];
        LCDMEM[11]=dig4[b];  //A4
        break;
    case 2:
        LCDMEM[2]=dig3[b];
        LCDMEM[3]=dig4[b];   //A5
        break;
    case 1:
        LCDMEM[18]=dig3[b];
        LCDMEM[19]=dig4[b]; //A6
        break;
    default :
        break;
    }
}


void lnit_LCD(){
    SYSCFG2|=0x1000;
    LCDPCTL0=0xffff;
    LCDPCTL1=0x07ff;
    LCDPCTL2=0x00f0;
    LCDCTL0=0x385c;
    LCDVCTL=0xf8c0;
    LCDMEMCTL|=0x0002;
    LCDCSSEL0=0x000f;
    LCDCSSEL1=0x0000;
    LCDCSSEL2=0x0000;
    LCDM0=0x21;
    LCDM1=0x84;
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                                     // Stop WDT
    PM5CTL0 &=~LOCKLPM5;

    lnit_LCD();

    P1DIR&=~0x04;
    P1OUT|=0x04;
    P1REN|=0x04;
    P1IE|=0x04;
    P1IES|=0x04;

    // Configure ADC - Pulse sample mode; ADCSC trigger

    ADCCTL0|=0x0810; // ADC ON,temperature sample period>30us
    ADCCTL1|=0x0204; // s/w trig, Repeat-single ch/conv, MODOSC
    ADCCTL2|=0x0010; // 10-bit conversion results
    ADCMCTL0 |= 0x1c;                           // ADC input ch A12 => temp sense
    ADCIE |=0x0001;                                               // Enable the Interrupt request for a completed ADC_B conversion

    // Configure reference
    PMMCTL0_H = PMMPW_H;                                          // Unlock the PMM registers
    PMMCTL2 |= INTREFEN | TSENSOREN;          // Enable internal reference and temperature sensor
    __delay_cycles(400);                                          // Delay for reference settling
    __bis_SR_register(LPM3_bits | GIE);                           // LPM3 with interrupts enabled
    __no_operation();                                             // Only for debugger
}

#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void)
{
            result[ss++]=ADCMEM0;
            // Temperature in Celsius
            // The temperature (Temp, C)=
            if(s==1){
            if(ss==16){
                ss=0;
                for(i=0;i<16;i++){
                    temp+=result[i];
                }
                temp=temp>>4;
                IntDegC = (temp-CALADC_15V_30C)*(85-30)/(CALADC_15V_85C-CALADC_15V_30C)+30;
                temp=0;
                dis(1,12); dis(2,IntDegC%10); dis(3,IntDegC/10); LCDM3|=0x04;
                LCDCTL0|=0x0001;
                __delay_cycles(500);
            }
            else{
                ADCCTL0 |= ADCENC | ADCSC;
            }}

            // Temperature in Fahrenheit
            // Tf = (9/5)*Tc | 32
            //IntDegF = 9*IntDegC/5+32;
            //__bic_SR_register_on_exit(LPM3_bits);               // Exit LPM3
}


#pragma vector = PORT1_VECTOR
__interrupt void p1_isr (void)
{
    if(P1IV==6){
    ADCCTL0 |= ADCENC | ADCSC;
    s=1;}                         // Sampling and conversion start
} 
