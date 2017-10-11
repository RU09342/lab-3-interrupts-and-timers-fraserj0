/*
 * ButtonBasedDelay.c
 *
 *  Created on: Sep 27, 2017
 *      Author: tomas
 */


#include <msp430fr5994.h>


void ButtonBasedDelay(void)
{

        //Port 1 initialized
        P1OUT &= 0x00;                          // Shut everything down
        P1DIR &= 0x00;                          // Port 1 direction set
        P1DIR |= 0x03;                          // Set P1.0 and P1.6 to output direction

        //Port 5 initialized
        P5OUT &= 0x00;                          // Shut Port 5 Down
        P5DIR &= 0x00;                          // Port 5 direction set
        P5OUT |= BIT6;                          // Select pull-up mode for P5.6
        P5REN |= BIT6;                          // Enable internal pull-up/down resistors

        //Interrupt initialized
        P5IE |= BIT6;                           // P5.6 interrupt enabled
        P5IES |= BIT6;                          // P5.6 Hi/lo edge
        P5IFG &= ~BIT6;                         // P5.6 IFG cleared





      //Timer A
      TA0CCTL0 = CCIE;                          // TA0CCR0 interrupt enabled
      TA1CCTL1 = CCIE;                          // TA1CCR0 interrupt enabled
      TA0CCR0 = 0;                              // Sets TA0CCR0 to 0
      TA0CTL = TASSEL_1 + MC_1;                 // Start TimerA_0

      __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}
// Port 5 interrupt service routine
#pragma vector=PORT5_VECTOR
__interrupt void Port_5(void)
{

    unsigned int i;
    unsigned int recTime = 0;
    if(P5IES & 0x40){
        P1OUT |= BIT1 ;                         // Toggle P1.1
        TA1CTL = TASSEL_1 + MC_2;               // Start TimerA_1
        P5IES &= 0xB7;                          // Flip Edge of Button interrupt
    }
    else{
        recTime = TA1R;                         // Set TimerA_1 counter to recTime
        TA0CCR0 = recTime;                      // Set recTime to TA0CCR0
        TA1CTL = TACLR;                         // Turn off TimerA_1
        P1OUT &= ~BIT1;                         // Toggle P1.1
        P5IES |= BIT6;                          // Flip Edge of Button interrupt
    }

   for(i=0;i<10000;i++);                        // Delay
   P5IFG &= ~BIT6;                              // P5.6 IFG cleared



}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
  P1OUT ^= BIT0;

}



