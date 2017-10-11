#include <msp430.h>

/**
 * TimerABlink
 */
int ButtonBasedDelay(void)
{
        WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

        // P1 initialized
        P1OUT &= 0x00;                      // Port 1 output is 0
        P1DIR &= 0x00;                      // Port direction set
        P1DIR |= 0x01;                      // Set P1.0 to output direction
        P1REN |= 0x02;                      // resistor placed on button
        P1OUT |= 0x02;                      // P1 out sets resistor to pull up

        //P4 Initialized
        P4DIR |= 0x90;                      // Port 4 direction is set

        // Timers initalized
        TA0CCTL0  = CCIE;                   // CCR0 interrupt enabled
        TA1CCTL1  = CCIE;                   // CCR1 interrupt enabled

        //Button Interrupt initialized
        P1IE   = 0x02;                      // P1.3 interrupt enabled, interrupt is enabled here, as well as interrupt clear
        P1IES |= 0x02;                      // Interrupt edge select is set
        P1IFG &= ~BIT1;                     // P1.3 IFG cleared

        TA0CCR0 = 0;                        // TA0CCR0 is initialized to 0, interrupt starts right away
        TA0CTL  = TASSEL_1 + MC_1;
      __bis_SR_register(LPM0_bits + GIE);   // Enter LPM0 w/ interrupt
}

#pragma vector=PORT1_VECTOR                 //This is what happens when you enter the interrupt
__interrupt void Port_1(void)
{
    unsigned int i;
        unsigned int time = 0;
        if(P1IES & 0x02){
            P1OUT |= BIT0 ;                 // Toggle P1.6 and P1.0
            TA1CTL  = TASSEL_1 + MC_2;      // Timer 1 starts, aclck, cont mode
            P1IES &= 0xFC;
        }
        else
        {
            time = TA1R;                    // Time gets timer1 value
            TA0CCR0 = time;                 // TA0CCR0 gets time
            TA1CTL = TACLR;                 // Timer 1 is cleared
            P1OUT &= ~BIT0;                 // P1OUT is cleared
            P1IES |= 0x02;                  // interrupt edge select is flipped
        }

       for(i=0;i<5000;i++);                 //Delay
       P1IFG &= ~BIT1;                      // P1.3 IFG cleared
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    P4OUT ^= 0x80;
}




