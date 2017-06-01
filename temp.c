#include <msp430.h>
int main(void)
{
 WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer
 // Configure GPIO
P1DIR |= 0x01; //P1.0=UCA0TXD
P1SEL0 |= 0x01;
PM5CTL0 &= ~LOCKLPM5;
 // Configure UART
UCA0CTLW0 |= UCSWRST;
UCA0CTLW0 |= 0x0080; //8-bit data, no parity, 1 stop bit
 
// Baud Rate =9600
// User's Guide Table 14-4: UCBRx=6, UCBRFx=8, UCBRSx = 0x20 UCOS16=1
 UCA0BRW = 6;
UCA0MCTLW = 0x2081;
 UCA0CTLW0 &= ~UCSWRST; // Initialize eUSCI
 while(1) {
 //transmit one ASCII ‘K’ (0x4B)
 UCA0TXBUF = 'K';
__delay_cycles(100000);
 }
}
