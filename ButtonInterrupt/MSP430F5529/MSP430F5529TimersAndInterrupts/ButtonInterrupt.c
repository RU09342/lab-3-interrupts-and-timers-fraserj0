#include <msp430.h>
/**
 * ButtonInterrupt
 */
int ButtonInterrupt(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    //P1 initializations
    P1OUT &= 0x00;                  // P1 utputs nothing
    P1DIR &= 0x00;                  // P1 direction is set
    P1DIR |= 0x01;                  // Set P1.0 to output direction
    P1REN |= 0x02;                  // Resistor is placed on button
    P1OUT |= 0x02;                  // Resistor is set to pull up

    //P4 initializations
    P4OUT &= 0x00;                  // P4 outputs nothing
    P4DIR &= 0x80;                  // P4 direction is set
    P4DIR |= 0x80;                  // P4 direction is set

    //Button interrupt is set
    P1IE  = 0x02;                   // P1.3 interrupt enabled
    P1IES |= 0x02;                  // P1 interrupt edge select is set
    P1IFG &= ~BIT1;                 // P1.3 IFG cleared
    _BIS_SR(LPM4_bits + GIE);       // Enter LPM4 w/interrupt

}

/**
// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR             //This is what happens when you enter the interrupt
__interrupt void Port_1(void)
{

    //ButtonInterrupt
    unsigned int i;
    P1OUT  ^=  0x01;                // P1.0 = toggle
    P4OUT  ^=  0x80;                // P4.7 = toggle
    for(i = 0; i<50000; i++);       // Delay
    P1IFG  &= ~BIT1;                // P1.3 IFG cleared

}
*/
