/*
 * ButtonBasedDelay.c
 *
 *  Created on: Sep 27, 2017
 *      Author: Jake
 */


#include <msp430fr2311.h>


void ButtonBasedDelay(void)
{

        //Port 2 initialized
        P2OUT &= 0x00;                      //Shut everything down
        P2DIR &= 0x00;                      // port 2 directions are set
        P2DIR |= 0x01;                      // Set P2.0 to output direction

        //Port 1 initialized
        P1OUT &= 0x00;                      //Shut everything down
        P1DIR &= 0x00;                      // port 1 directions are set
        P1DIR |= 0x01;                      // Set P1.0 to output direction
        P1REN |= 0x02;                      // resistor placed on button
        P1OUT |= 0x02;                      // resistor set to pull up

        //Timer 1 is initialized
        P1IE  |= 0x02;                      // P1.1 interrupt enabled
        P1IES |= 0x02;                      // Interrupt edge is set
        P1IFG &= ~BIT1;                     // P1.1 IFG cleared


      //Timer B
      TB0CCTL0 = CCIE;                      // TB0CCR0 interrupt enabled
      TB1CCTL1 = CCIE;                      //TB1CCR0 interrupt enabled
      TB0CCR0 = 0;                          //Sets TB0CCR0 to 0
      TB0CTL = TBSSEL_1 + MC_1+ID_1;        //Start TimerB_0

      __bis_SR_register(LPM0_bits + GIE);   // Enter LPM0 w/ interrupt
}
// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{

    unsigned int i;
    unsigned int recTime = 0;
    if(P1IES & 0x02){
        P1OUT |= BIT0 ;                     // Toggle P1.0
        TB1CTL = TBSSEL_1 + MC_2+ID_1;      //Start TimerB_1
        P1IES &= 0x00;                      //Flip Edge of Button interrupt
    }
    else{
        recTime = TB1R;                     //Set TimerB_1 counter to recTime
        TB0CCR0 = recTime;                  //Set recTime to TB0CCR0
        TB1CTL = TBCLR;                     //Turn off TimerB_1
        P1OUT &= ~BIT0;                     //Toggle P1.6
        P1IES |= 0x02;                      //Flip Edge of Button interrupt
    }

   for(i=0;i<5000;i++);                     //Delay
   P1IFG &= ~BIT1;                          // P1.3 IFG cleared



}

#pragma vector=TIMER0_B0_VECTOR
__interrupt void Timer_B(void)
{
  P2OUT ^= BIT0;

}
