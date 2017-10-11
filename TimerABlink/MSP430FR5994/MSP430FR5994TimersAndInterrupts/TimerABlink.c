/*
 * TimerABlink.c
 *
 *  Created on: Sep 26, 2017
 *      Author: tomas
 */
/**#include<msp430fr5994.h>
void TimerABlink(void){

  //Ports enabled
  P1DIR |= 0x03;                            // P1.0 output

  //Timer B initialized
  TB0CCTL1 = CCIE;                          // CCR1 interrupt enabled
  TB0CCR1 = 50000;                          // CCR1 initialized
  TB0CCTL2 = CCIE;                          // CCR2 interrupt enabled
  TB0CCR2 = 10000;                          // CCR2 initalized
  TBCTL = TASSEL_2 + MC_2+ID_3;             // SMCLK, Contmode

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer_A3 Interrupt Vector (TA0IV) handler
#pragma vector=TIMER0_B1_VECTOR
__interrupt void Timer_B(void)
{
  switch( TB0IV )
  {
  case  2:                                  // CCR1
    {
    P1OUT ^= 0x01;                          // Toggle P1.0
    TB0CCR1 += 50000;                       // Add Offset to CCR1
    }
           break;
  case  4:
      {
          P1OUT ^= 0x02;                    //Toggle P1.1
          TB0CCR2 += 25000;                 //Add Offset to CCR2
      }
      break;

  case 10: break;                           // overflow not used
 }
}
*/



