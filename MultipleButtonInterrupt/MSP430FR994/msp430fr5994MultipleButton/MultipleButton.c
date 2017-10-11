#include<msp430fr5994.h>

int MultipleButtonInterrupt(void){

      P1OUT &= 0x00;                    // Shut down everything
      P1DIR &= 0x00;
      P1DIR |= BIT0 + BIT1;             // P1.0 and P1.1 pins output the rest are input
      P5OUT &= 0x00;                    //Shut Port 5 Down
      P5DIR &= 0x00;
      P5OUT = BIT6 +BIT5;               //Select pull-up mode for P5.6
      P5REN |= BIT6 +BIT5;              // Enable internal pull-up/down resistors

      P5IE |= BIT6+BIT5;                // P5.6 interrupt enabled
      P5IES |= BIT6+BIT5;               // P5.6 Hi/lo edge
      P5IFG &= ~BIT6+(~BIT5);           // P5.6 IFG cleared
      _BIS_SR(CPUOFF + GIE);            // Enter LPM0 w/ interrupt

}

    // Port 5 interrupt service routine
    #pragma vector=PORT5_VECTOR
    __interrupt void Port_5(void)
    {
        unsigned int i;
       if(P5IFG & BIT6){                //Check if P5.6 was pressed
           P1OUT ^= BIT0;               //Toggle LED
           for(i=0;i<50000;i++);        //Delay
           P5IFG &= ~BIT6;              // P5.6 IFG cleared
       }
       if(P5IFG & BIT5){                //Check if P5.5 was pressed
           P1OUT ^= BIT1;               //Toggle LED
           for(i=0;i<50000;i++);        //Delay
           P5IFG &= ~BIT5;              // P5.6 IFG cleared
       }


    }




