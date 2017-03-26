#include <msp430.h> 
#include <intrinsics.h>


/*  A   0
 *  B   1
 *  C   2
 *  D   3
 *  E   4
 *  F   5
 *  G   6
 *  H   7
 *  I   8
 *  J   9
 *  K   10
 *  L   11
 *  M   12
 *  N   13
 *  O   14
 *  P   15
 *  Q   16
 *  R   17
 *  S   18
 *  T   19
 *  U   20
 *  V   21
 *  W   22
 *  X   23
 *  Y   24
 *  Z   25
 */


char UCAmapping1[26] = {0xef,0x1e,0x9c,0x3b,0x9f,0x8e,0xbd,0x6f,0x90,0x88,0x0e,0x1c,0x6c,0x6c,0xfc,0xcf,0x86,0xcf,0xb7,0x80,0x7c,0x60,0x6c,0x00,0x00,0x90};
char UCAmapping2[26] = {0x00,0x82,0x00,0x00,0x00,0x00,0x00,0x00,0x50,0x48,0x22,0x00,0xa0,0x82,0x00,0x00,0x42,0x02,0x00,0x50,0x00,0x82,0x0a,0xaa,0xb0,0x28};


void display_char(int pos, int letter)
{
    if(pos==1){
        LCDM4=UCAmapping1[letter];
        LCDM5=UCAmapping2[letter];

        /*
         * LCDMEM   COM3    COM2    COM1    COM0    C0M3    COM2    COM1    COM0
         * LCDM4    A1A     A1B     A1C     A1D     A1E     A1F     A1G     A1M
         * LCDM5    A1H     A1J     A1K     A1P     A1Q     NEG     A1N     A1DP
         */
    }
    else if(pos==2){
        LCDM6=UCAmapping1[letter];
        LCDM7=UCAmapping2[letter];

        /*
         * LCDMEM   COM3    COM2    COM1    COM0    COM3    COM2    COM1    COM0
         * LCDM6    A2A     A2B     A2C     A2D     A2E     A2F     A2G     A2M
         * LCDM7    A2H     A2J     A2K     A2P     A2Q     A2COL   A2N     A2DP
         *
         */

        }

    else if(pos==3){
        LCDM8=UCAmapping1[letter];
        LCDM9=UCAmapping2[letter];

        /*
         * LCDMMEM    COM3    COM2    COM1    COM0    COM3    COM2    COM1    COM0
         * LCDM8      A3A     A3B     A3C     A3D     A3R     A3F     A3G     A3M
         * LCDM9      A3H     A3J     A3K     A3P     A3Q     ANT     A3N     A3DP
         */
        }
    else if(pos==4){
        LCDM10=UCAmapping1[letter];
        LCDM11=UCAmapping2[letter];

        /*
         * LCDMEM   COM3    COM2    COM1    COM0    COM3    COM2    COM1    COM0
         * LCDM10   A4A     A4B     A4C     A4D     A4R     A4F     A4G     A4M
         * LCDM11   A4H     A4J     A4K     A4P     A4Q     A4COL   A4N     A4DP
         */

        }
    else if(pos==5){
        LCDM2=UCAmapping1[letter];
        LCDM3=UCAmapping2[letter];
        /*
         * LCDMEM   COM3    COM2    COM1    COM0    COM3    COM2    COM1    COM0
         * LCDM2    A5A     A5B     A5C     A5D     A5E     A5F     A5G     A5M
         * LCDM3    A5H     A5J     A5K     A5P     A5Q     DEG     A5N     A5DP
         */
        }
    else{
        LCDM18=UCAmapping1[letter];
        LCDM19=UCAmapping2[letter];

        }
    }


void init(void){
    SYSCFG2|=0x1000;
    /*
     * 0x1000 = 0001 0000 0000 0000
     *
     * 12   LCDPCTL
     * LCD power pin (LCDCAP0, LCDCAP1, R13, R23, R33) control.
     * 0b = LCD power pin disabled
     * 1b = LCD power pin enabled
     *
     * 9    ADCPCTL9
     * ADC input A9 pin select
     * 0b = ADC input A9 disabled
     * 1b = ADC input A9 enabled
     *
     */

    LCDPCTL0=0xffff;
    LCDPCTL1=0x07ff;
    LCDPCTL2=0x00f0;
    //어떤 라인에 LCD 기능 핀으로 설정할지

    /*
     * LCDPCTL0 = 0xffff = 1111 1111 1111 1111
     *
     * 15   LCDS15
     * LCD pin 15 enable. This bit affects only pins with multiplexed functions.
     * Dedicated LCD pins are always LCD function.
     * 0b = Multiplexed pins are port functions.
     * 1b = Pins are LCD functions.
     */

    LCDCTL0=0x385d;

    /* 0x385d = 0011 1000 0101 1101
     *
     *
     * 15-11    LCDDIVx     0011 1      Divede by 7
     * LCD frequency divider. Together with LCDMXx, the LCD frequency fLCD is
     * calculated as fLCD = fSOURCE / ((LCDDIVx + 1) × Value[LCDMXx]). Should be
     * changed only while LCDON = 0.
     *
     * 00000b = Divide by 1
     * 00001b = Divide by 2
     *
     * 11110b = Divide by 31
     * 11111b = Divide by 32
     *
     *
     * 7-6      LCDSSEL     01      ACLK
     * Clock source fSOURCE select for LCD and blinking frequency. Should be changed
     * only while LCDON = 0.
     *
     * 00b = XT1CLK
     * 01b = ACLK (30 kHz to 40 kHz)
     * 10b = VLOCLK
     * 11b = Reserved
     *
     *
     * 5-3      LCDMXx      01 1    4 mux
     * LCD mux rate. These bits select the LCD mode. Should be changed only while
     * LCDON = 0.
     *
     * 000b = Static
     * 001b = 2-mux
     * 010b = 3-mux
     * 011b = 4-mux
     * 100b = 5-mux
     * 101b = 6-mux
     * 110b = 7-mux
     * 111b = 8-mux
     *
     *
     * 2        LCDSON      1
     * LCD segments on. This bit supports flashing LCD applications by turning off all
     * segment lines, while leaving the LCD timing generator and R33 enabled.
     *
     * 0b = All LCD segments are off.
     * 1b = All LCD segments are enabled and on or off according to their
     * corresponding memory location.
     *
     *
     * 1        LCDLP       0
     * LCD low-power waveform
     *
     * 0b = Standard LCD waveforms on segment and common lines selected.
     * 1b = Low-power LCD waveforms on segment and common lines selected.
     *
     *
     * 0        LCDON       1
     * LCD on. This bit turns the LCD_E module on or off.
     *
     * 0b = LCD_E module off
     * 1b = LCD_E module on
     *
     */


    LCDVCTL=0xf8c0;

    /*
     * 0xf80c = 1111 1000 0000 1100
     *
     * 15-12    LCDCPFSELx      1111    256Hz
     * Charge pump frequency selection. Clock source can be XT1, ACLK, VLO (4-bit,
     * if fSOURCE = fACLK = 32.768 kHz )
     *
     * 0000b = 32.768 kHz / 1 / 8 = 4.096 kHz
     * 0001b = 32.768 kHz / 2 / 8 = 2.048 kHz
     * 0010b = 32.768 kHz / 3 / 8 = 1.365 kHz
     * 0011b = 32.768 kHz / 4 / 8 = 1.024 kHz
     * 0100b = 32.768 kHz / 5 / 8 = 819 Hz
     * 0101b = 32.768 kHz / 6 / 8 = 682 Hz
     * 0110b = 32.768 kHz / 7 / 8 = 585 Hz
     * 0111b = 32.768 kHz / 8 / 8 = 512 Hz
     * 1000b = 32.768 kHz / 9 / 8 = 455 Hz
     * 1001b = 32.768 kHz / 10 / 8 = 409 Hz
     * 1010b = 32.768 kHz / 11 / 8 = 372 Hz
     * 1011b = 32.768 kHz / 12 / 8 = 341 Hz
     * 1100b = 32.768 kHz / 13 / 8 = 315 Hz
     * 1101b = 32.768 kHz / 14 / 8 = 292 Hz
     * 1110b = 32.768 kHz / 15 / 8 = 273 Hz
     * 1111b = 32.768 kHz / 16 / 8 = 256 Hz
     *
     *
     * 11-8     VLCDx       1000    3.08V
     * Internal reference voltage select on R13. Only valuable when LCDCPEN = 1 and
     * LCDREFEN = 1.
     *
     * 0000b = 2.60 V
     * 0001b = 2.66 V
     * 0010b = 2.72 V
     * 0011b = 2.78 V
     * 0100b = 2.84 V
     * 0101b = 2.90 V
     * 0110b = 2.96 V
     * 0111b = 3.02 V
     * 1000b = 3.08 V
     * 1001b = 3.14 V
     * 1010b = 3.20 V
     * 1011b = 3.26 V
     * 1100b = 3.32 V
     * 1101b = 3.38 V
     * 1110b = 3.44 V
     * 1111b = 3.50 V
     *
     *
     * 7    LCDCPEN     0
     * Charge pump enable
     *
     * 0b = Charge pump disabled
     * 1b = Charge pump enabled when VLCD is generated internally (VLCDEXT = 0)
     *      and VLCDx > 0 or VLCDREFx > 0.
     *
     *
     * 6    LCDREFEN    0
     * Internal reference voltage enable on R13
     *
     * 0b = Internal reference voltage disabled
     * 1b = Internal reference voltage enabled
     *
     *
     * 5    LCDSELVDD   0
     * Selects if R33 is supplied either from VCC internally or from charge pump
     *
     * 0b = R33 connected to external supply
     * 1b = R33 internally connected to VCC
     *
     *
     * 0    LCDREFMODE  0
     * Selects whether R13 voltage is switched or in static mode
     *
     * 0b = Static mode
     * 1b = Switched mode
     */

    LCDMEMCTL|=0x0002; // 클리어

    /* 0x0002 = 0000 0000 0000 0010
     *
     * 2    LCDCLRBM    0
     * Clear LCD blinking memory
     * Clears all blinking memory registers LCDBMx. The bit is automatically reset
     * when the blinking memory is cleared.
     * Setting this bit in 5-mux mode and above has no effect. It is immediately reset
     * again.
     *
     * 0b = Contents of blinking memory registers LCDBMx remain unchanged
     * 1b = Clear content of all blinking memory registers LCDBMx
     *
     *
     * 1    LCDCLRM     1
     * Clear LCD memory
     * Clears all LCD memory registers LCDMx. The bit is automatically reset when the
     * LCD memory is cleared.
     *
     * 0b = Contents of LCD memory registers LCDMx remain unchanged
     * 1b = Clear content of all LCD memory registers LCDMx
     *
     *
     * 0    LCDDISP     0
     * Select LCD memory registers for display
     * When LCDBLKMODx = 00, LCDDISP can be set by software.
     * The bit is cleared in LCDBLKMODx = 01 and LCDBLKMODx = 10 or if a mux
     * mode ≥5 is selected and cannot be changed by software.
     * When LCDBLKMODx = 11, this bit reflects the currently displayed memory but
     * cannot be changed by software. When returning to LCDBLKMODx = 00 the bit is
     * cleared.
     *
     * 0b = Display content of LCD memory registers LCDMx
     * 1b = Display content of LCD blinking memory registers LCDBMx
     */

    LCDCSSEL0=0x000f;
    //어떤 라인을 com으로 쓸지

    /*  0000 0000 0000 1111
     *
     * 15   LCDCSS15
     * Selects pin L15 as either common or segment line.
     *
     * 0b = Segment line
     * 1b = Common line
     *
     */

    LCDM0=0x21;
    LCDM1=0x84;

    /*
     * LCDM0 = 0x21 = 0010 0001     COM0, COM1 선택
     * LCDM1 = 0x84 = 1000 0100     COM2, COM3 선택
     *
     *
     */
}



/*
 * main.c
 */


int main(void) {
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer
    PM5CTL0&=~LOCKLPM5;

    P4SEL0|=0x06;//XT1핀 set
    do{
        CSCTL7&=~(XT1OFFG|DCOFFG);
        SFRIFG1&=~OFIFG;
        }while(SFRIFG1&OFIFG);

    init();

    while(1){
        display_char(1,24);
        display_char(2,18);
        display_char(3,9);
     }
}
