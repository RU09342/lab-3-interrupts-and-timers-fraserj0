#include <msp430.h>
/**
 * TimerABlink
 */
int TimerABlink(void)
{
      WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

      //Ports enabled
      P4DIR |= 0x80;                            // P4.7 output
      P1DIR |= 0x01;                            // P1.0 output

      //Timers are set
      TA0CCTL1  = CCIE;                         // CCR1 interrupt enabled
      TA0CCTL2  = CCIE;                         // CCR0 interrupt enabled
      TA0CCR1   = 10000;                        // TA0CCR1 is set
      TA0CCR2   = 35000;                        // TA0CCR2 is set
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
              case  2:                                  // CCR1
                {
                  P1OUT ^= 0x01;                        // Toggle P1.0
                  TA0CCR1  += 10000;                    // Add Offset to CCR1
                }
                        break;
              case  4:                                  // CCR2 not used
                {
                  P4OUT ^= 0x80;                        // Toggle P1.0
                  TA0CCR2  += 35000;
                }
                        break;
              case 10: break;                           // overflow not used
              }

}
*/




