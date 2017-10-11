#include <msp430.h>

/**
 * TimerABlink
 */
int ButtonBasedDelay(void)
{
        WDTCTL = WDTPW + WDTHOLD;               // Stop watchdog timer
        PM5CTL0 &= ~LOCKLPM5;                   //enables this processor

        //Port 1 initialization
        P1OUT &= 0x00;                          // Clears port 1
        P1DIR &= 0x00;                          // sets directions
        P1DIR |= 0x01;                          // Set P1.0 to output direction
        P1REN |= 0x02;                          // enables resistor on button
        P1OUT |= 0x02;                          // sets resistor to pull up

        //Port 9 initialized
        P9DIR |= 0x90;                          //sets port 9 directions

        //Timers initialized
        TA0CCTL0  = CCIE;                       // CCR0 interrupt enabled
        TA1CCTL1  = CCIE;                       // CCR1 interrupt enabled
        P1IE   = 0x02;                          // P1.3 interrupt enabled, interrupt is enabled here, as well as interrupt clear
        P1IES |= 0x02;                          // Port 1 interrupt edge select
        P1IFG &= ~BIT1;                         // P1.3 IFG cleared
        TA0CCR0 = 0;                            // CCR0 initialized to 0, interrupt starts right away

        TA0CTL  = TASSEL_1 + MC_1;
      __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    unsigned int i;                             // initializes i
        unsigned int time = 0;                  // initializes unsigned int time to be 0
        if(P1IES & 0x02){                       // If button is pressed
            P1OUT |= BIT0 ;                     // Toggle P1.6 and P1.0
            TA1CTL  = TASSEL_1 + MC_2;          // Start timer 1
            P1IES &= 0xFC;                      // Flip interrupt edge select
        }
        else
        {
            time = TA1R;                        // time gets value of timer1
            TA0CCR0 = time;                     // TA0CCR0 gets time
            TA1CTL = TACLR;                     // TA1 gets cleared
            P1OUT &= ~BIT0;                     // P1OUT is cleared
            P1IES |= 0x02;                      // edge select is flipped
        }

       for(i=0;i<5000;i++);                     //Delay
       P1IFG &= ~BIT1;                          // P1.3 IFG cleared
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    P9OUT ^= 0x80;
}




