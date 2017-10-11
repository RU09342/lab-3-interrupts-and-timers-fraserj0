#include <msp430.h>
/**
 * TimerABlink
 */
int TimerABlink(void)
{
      WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

      //Port 1 Initializations
      P1DIR |= 0x41;                            // LEDs are enabled

      //Timer Initializations
      CCTL1  = CCIE;                            // CCR1 interrupt enabled
      CCTL2  = CCIE;                            // CCR2 interrupt enabled
      CCR1   = 10000;                           // CCR1 initialized
      CCR2   = 35000;                           // CCR2 initialized
      TACTL  = TASSEL_2 + MC_2 + ID_3;          // timer A starts with SMCLK, Contmode

      __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

/** Timer A0 interrupt service routine
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer_A(void)
{

    //TimerABlinkInterrupt
    switch( TA0IV )
              {
              case  2:                         // CCR1
                {
                P1OUT ^= 0x01;                 // Toggle P1.0
                CCR1  += 10000;                // Add Offset to CCR1
                }
                        break;
              case  4:                         // CCR2 not used
                {
                  P1OUT ^= 0x40;               // Toggle P1.0
                  CCR2  += 35000;              // Add offset to CCR2
                }
                        break;
              case 10: break;                  // overflow not used
              }

}
*/




