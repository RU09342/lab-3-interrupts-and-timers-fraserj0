/*
 * ButtonInterrupt.c
 *
 *  Created on: Sep 26, 2017
 *      Author: tomas
 */

/**#include<msp430fr5994.h>

int ButtonInterrupt(void){


      //Port 1 initialized
      P1OUT &= 0x00;                   // Shut down everything
      P1DIR &= 0x00;                   // Port 1 direction set
      P1DIR |= BIT0 + BIT1;            // P1.0 and P1.1 pins output the rest are input

      //Port 5 initialized
      P5OUT &= 0x00;                   // Shut Port 5 Down
      P5DIR &= 0x00;                   // Port 5 direction set
      P5OUT = BIT6;                    // Select pull-up mode for P5.6
      P5REN |= BIT6;                   // Enable internal pull-up/down resistors

      //Button interrupt initialized
      P5IE |= BIT6;                    // P5.6 interrupt enabled
      P5IES |= BIT6;                   // P5.6 Hi/lo edge
      P5IFG &= ~BIT6;                  // P5.6 IFG cleared
      _BIS_SR(CPUOFF + GIE);           // Enter LPM0 w/ interrupt

}

    // Port 5 interrupt service routine
    #pragma vector=PORT5_VECTOR
    __interrupt void Port_5(void)
    {
        unsigned int i;
       P1OUT ^= BIT1 +BIT0;                // Toggle P1.1 and P1.0
       for(i=0;i<50000;i++);               //Delay
       P5IFG &= ~BIT6;                     // P5.6 IFG cleared


    }
*/



