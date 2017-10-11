#include <msp430.h>
/**
 * ButtonInterrupt
 */
int ButtonInterrupt(void)
{
    WDTCTL = WDTPW + WDTHOLD;           // Stop watchdog timer

    //Port1 Initialize
    P1OUT &= 0x00;                      // Port 1 output set to 0
    P1DIR &= 0x00;                      // Port 1 direction set to out
    P1DIR |= 0x41;                      // Set P1.0 to output direction

    //BUTTON Initialize
    P1REN |= 0x08;                      //Resistor set on bit 3 of Port 1
    P1OUT |= 0x08;                      //Resistor is set to pull up

    //Interrupt Initialize
    P1IE  = 0x08;                       // P1.3 interrupt enabled
    P1IES |= 0x08;
    P1IFG &= ~BIT3;                     // P1.3 IFG cleared

    _BIS_SR(LPM4_bits + GIE);           // Enter LPM4 w/interrupt

}

/**
// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR             //Button ISR (Interrupt service report
__interrupt void Port_1(void)
{
    unsigned int i;
    P1OUT  ^=  0x41;                    // P1.0 = toggle
    for(i = 0; i<50000; i++);           //for loop delay
    P1IFG  &= ~BIT3;                    // P1.3 Interrup flag cleared

}
*/

