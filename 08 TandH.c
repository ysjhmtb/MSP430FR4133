#include <msp430.h> 

/*
 * main.c
 */
int flag = 0, TIndex = 0, HIndex = 0, Tem, Hum;
int DisplayMod = 1;
int TemperatureResult = 0, HumidityResult = 0;

#pragma vector = PORT1_VECTOR
__interrupt void p1_isr() {
   if(P1IV == 6) {
      if((P1IN&0x04)==0){
         if (DisplayMod == 1)
            DisplayMod = 0;

         else if(DisplayMod == 0)
            DisplayMod = 1;
      }
   }
}

#pragma vector = ADC_VECTOR
__interrupt void adc_isr(){
   if(flag == 1){
      ADCCTL0 &= ~0x0002; // set ADCENC 0
      ADCMCTL0 = 0x00; // A0,
      ADCCTL0 |= 0x0002; // set ADCENC 1
      TemperatureResult += ADCMEM0;
      TIndex++;
      flag = 0;
      if(TIndex == 8){
         TIndex = 0;
         TemperatureResult /= 8;
         //Tem = (unsigned long)TemperatureResult*22-6687;
         Tem = (unsigned long)TemperatureResult*1023/330;
         Tem*=1.5;
         TemperatureResult = 0;
      }
   }else if(flag == 0){
      ADCCTL0 &= ~0x0002; // set ADCENC 0
      ADCMCTL0 = 0x01; // A1
      ADCCTL0 |= 0x0002; // set ADCENC 1
      HumidityResult += ADCMEM0;
      HIndex++;
      flag = 1;
      if(HIndex == 8){
         HIndex = 0;
         HumidityResult /= 8;
         //Hum = (unsigned long)HumidityResult*5250/484-1250;
         Hum = (unsigned long)HumidityResult*1023/330;
         HumidityResult = 0;
         Hum*=4;

      }
   }
}

const char digit_a[12] = {0xfc, 0x60, 0xdb, 0xf3, 0x67, 0xb7, 0xbf, 0xe4, 0xff, 0xf7, 0x00, 0x00};
const char digit_b[12] = {0X82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void display_char(unsigned int pos, unsigned int letter){
   switch(pos){
      case 1:
         LCDM4 = digit_a[letter];
         LCDM5 = digit_b[letter];
         break;
      case 2:
         LCDM6 = digit_a[letter];
         LCDM7 = digit_b[letter];
         break;
      case 3:
         LCDM8 = digit_a[letter];
         LCDM9 = digit_b[letter];
         break;
      case 4:
         LCDM10 = digit_a[letter];
         LCDM11 = digit_b[letter] | 0x01;
         break;
      case 5:
         LCDM2 = digit_a[letter];
         LCDM3 = digit_b[letter];
         break;
      case 6:
         LCDM18 = digit_a[letter];
         LCDM19 = digit_b[letter];
         break;
      default:
         break;
   }
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer
    SYSCFG2|=0x1003;
    PM5CTL0 &= ~LOCKLPM5;

    ADCCTL0 |= 0x0c10;
    ADCCTL1 |= 0x0213;
    ADCCTL2 |= 0x0010;
    ADCMCTL0 |= 0x10;
    ADCIE |= 0x0001;
    ADCCTL0 |=0x0003;

   LCDPCTL0 = 0xffff;
   LCDPCTL1 = 0x07ff;
   LCDPCTL2 = 0x00f0;
   LCDCTL0 = 0x385c;
   LCDVCTL = 0xf8c0;
   LCDMEMCTL |= 0x0002;
   LCDCSSEL0 = 0x000f;
   LCDCSSEL1 = 0x0000;
   LCDCSSEL2 = 0x0000;
   LCDM0 = 0x21;
   LCDM1 = 0x84;
   LCDCTL0 |= 0x0001;

   P1DIR = ~0X04;
   P1REN = 0X04;
   P1OUT = 0X04;
   P1IE = 0X04;
   P1IES = 0X04;
   __enable_interrupt();
   while(1){
      if(DisplayMod == 0){
         display_char(3, Hum/1000);
         display_char(4, (Hum%1000)/100);
         display_char(5, (Hum%100)/10);
         display_char(6, Hum%10);
      }if (DisplayMod == 1){
         display_char(3, Tem/1000);
         display_char(4, (Tem%1000)/100);
         display_char(5, (Tem%100)/10);
         display_char(6, Tem%10);
      }
      __delay_cycles(1000);
      ADCCTL0 |= 0x0003;
   }
}
