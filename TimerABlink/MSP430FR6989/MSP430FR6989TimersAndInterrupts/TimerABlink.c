#include <msp430.h>
/**
 * TimerABlink
 */
int TimerABlink(void)
{
      WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
      PM5CTL0 &= ~LOCKLPM5;

      //Ports enabled
      P9DIR |= 0x80;                            // P9 Output
      P1DIR |= 0x01;                            // P1.0 output

      //Timers initialized
      TA0CCTL1  = CCIE;                         // CCR1 interrupt enabled
      TA0CCTL2  = CCIE;                         // CCR2 interrupt enabled
      TA0CCR1   = 10000;                        // CCR1 initialized
      TA0CCR2   = 35000;                        // CCR2 initialized
      TA0CTL  = TASSEL_2 + MC_2 + ID_3;         // SMCLK, Contmode

      __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

/**
// Timer A0 interrupt service routine
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A(void)
{

    //TimerABlinkInterrupt
    switch( TA0IV )
              {
              case  2:                           // CCR1
                {
                  P1OUT ^= 0x01;                 // Toggle P1.0
                  TA0CCR1  += 10000;             // Add Offset to CCR1
                }
                        break;
              case  4:                           // CCR2 not used
                {
                  P9OUT ^= 0x80;                 // Toggle P1.0
                  TA0CCR2  += 35000;
                }
                        break;
              case 10: break;                    // overflow not used
              }

}

*/

