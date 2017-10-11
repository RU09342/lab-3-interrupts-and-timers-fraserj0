#include <msp430.h>
/**
 * ButtonInterrupt
 */
int ButtonInterrupt(void)
{
    WDTCTL = WDTPW + WDTHOLD;       // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    //Port 1 initializes
    P1OUT &= 0x00;                  // set P1OUT to 0
    P1DIR &= 0x00;                  // Set P1.0 t output direction
    P1DIR |= 0x01;                  // Set P1.0 to output direction

    //Port 9 initalizes
    P9OUT &= 0x00;                  // Port 9 initialzes to 0
    P9DIR &= 0x80;                  // Port 9 Direction is set
    P9DIR |= 0x80;                  // Port 9 direction is set

    //Button/timer initializes
    P1REN |= 0x02;                  // resistor is placed on button
    P1OUT |= 0x02;                  // P1OUT sets resistor to pull up
    P1IE  = 0x02;                   // P1.3 interrupt enabled
    P1IES |= 0x02;                  // P1 interrupt edge select
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
    P1OUT  ^=  0x01;                    // P1.0 = toggle
    P9OUT  ^=  0x80;                    // LED2 is toggled
    for(i = 0; i<50000; i++);           // Delay
    P1IFG  &= ~BIT1;                    // P1.3 IFG cleared

}
*/
