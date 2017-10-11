#include <msp430.h>

/**
 * TimerABlink
 */
int ButtonBasedDelay(void)
{
        WDTCTL = WDTPW + WDTHOLD;               // Stop watchdog timer

        //Port 1/Button initializations
        P1OUT &= 0x00;                          // P1OUT initializations
        P1DIR &= 0x00;                          // P1DIR initializations
        P1DIR |= 0x41;                          // Set P1.0 to output direction
        P1REN |= 0x08;                          // Resistor placed on button
        P1OUT |= 0x08;                          // Resistor is set to pull up

        //Timer Initializations
        TA0CCTL0  = CCIE;                       // CCR0 interrupt enabled
        TA1CCTL1  = CCIE;                       // CCR1 interrupt enabled
        TA0CCR0 = 0;                            // CCR0 set to 0, immediately enter interrupt

        //Button Interrupt initializations
        P1IE   = 0x08;                          // P1.3 interrupt enabled, interrupt is enabled here, as well as interrupt clear
        P1IES |= 0x08;                          // Edge select of interrupt is posedge
        P1IFG &= ~BIT3;                         // P1.3 IFG cleared


        TA0CTL  = TASSEL_1 + MC_1;              // Timer A0 starts, AClock,up mode
      __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

#pragma vector=PORT1_VECTOR                     //This is what happens when you enter the interrupt
__interrupt void Port_1(void)
{
        unsigned int i;                         // define int i
        unsigned int time = 0;                  // define int time to be 0
        if(P1IES & 0x08){                       // if button is pressed
            P1OUT |= BIT0 ;                     // Toggle P1.6 and P1.0
            TA1CTL  = TASSEL_1 + MC_2;          // start timer 1, a_clock, cont mode
            P1IES &= 0xF7;                      // change edge of button interrupt
        }
        else
        {
            time = TA1R;                        // int time gets value of timer 1
            TA0CCR0 = time;                     // TACCR0 gets value of int time
            TA1CTL = TACLR;                     // Clear timer 1
            P1OUT &= ~BIT0;                     // Toggle LED 1
            P1IES |= 0x08;                      // Flip edge of button interrupt again
        }

       for(i=0;i<5000;i++);                     //Delay
       P1IFG &= ~BIT3;                          // P1.3 IFG cleared
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    P1OUT ^= 0x40;                              //Toggle green LED at speed of timer 0
}

