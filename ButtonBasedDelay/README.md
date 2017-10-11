### Jake Fraser

## Lab Exercise 3: Timers and Interrupts
## Button Based Delay 

## Function
This program uses a combination of timer and interrupts to allow the user to set the blink time of an LED by holding down a button. 
Once the button is pressed, a timer a will start that stops when the button is let go. When the timer stops, the time is recorded
 and that time is used as the blink time of the other LED. The button essentially acts as an input in which the user inputs a time 
that they want the LED to blink for. 

## How it works
This program starts out by initializing the port 1 registers. The LED is selected as an output and a button is being used so 
a pull up resistor is placed on bit 3 of port 1. The LED is initialized to be off. This program will use two separate timers ( referred to as Timer0 and Timer1), one to count and record time, and the other to blink the LED.
 In this case, timer0 will be used to blink the LED, and timer1 will be used to count the length of the button press.
 Since only Timer0 is performing an action, it is the only timer that needs a timer interrupt. Therefore, the next part of the program will initialize this. Timer0's capture/compare register is set 0 in order to immediately start blinking the LED.
The timer initializations for the MSP430G2553 can be seen below. 

	TA0CCTL0  = CCIE;                       
        TA1CCTL1  = CCIE;                       
        TA0CCR0 = 0;

From here, the button interrupt needs to be initialized. Because the interrupt is to be triggered when the button is pressed down, P1IE is set to bit 3 (the button), and 
P1IES is set to 0x08. The interrupt flag is set to ~BIT3, which is cleared when the button is let go of. Then timer0 is started in up mode which counts to FFFF, rolls over at 0, and repeats. 
This will place a limit on how long the user can hold the button for. If the user holds the button long enough for the timer to roll over, then the cycle will start over and the LED will blink at a rate of the value of the timer, not FFFF plus the value of the timer. 

The next part of the program is where the bulk of the processing gets done. Inside the button interrupt, two integers, time and i are set. The integer 'time' will be used as the value that timer1 counts to while the button is pressed, while 'i' is just used in the as a placeholder in a fr loop delay.
Once these variables are declared, some conditional statements are set. The first one checks to see if the button is pressed. If it is, then timer1 is started, the interrupt edge select is flipped so that the interrupt will stop when the button is let go, and another LED is turned on to let the user know that this is going on. 
If the button is not being pressed, then it was just let go of and the interrupt has not yet been exited. At this point, 'time' gets the value of TA1R. This register holds the current value of the timer. Then CCR0 is set to the variable time. Next, the timer is cleared so that the user can perform the action later on, and the second LED is turned off. The edge select of 
the button is also flipped so that the interrupt is entered again when the user presses the button down. After all of this takes place, there is a 5000 count delay to account for any mechanical debouncing in the button, and the interrupt flag is cleared.   

Inside the timer interrupt, which triggers whenever timer0 counts up to the value in CCR0, the LED is toggled. Since CCR0 is now the value that the timer counted up to when the user was holding down the button, the LED will blink at a rate identical to the length of time that the button was pressed for. 

The button ISR as well as the timer0 ISR for the MSP430G2553 can be seen below. 

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

## Usage
Within this project, there are a multitude of files that all use interrupts in a certain manner. In order to run this file, the main.c file needs to be ran.
The user can decide which file they want to run here, and comment out any function that they dont wish to run, leaving the only file to be called, the one they want to run.
Obviously, an error will be given if more than one file is attempted to be called at once. Since there are multiple files in the project that use interrupts, all other files that use the same type of interrupt must be commented out. 
This is because the compiler will recognize both interrupt service routines and an error will ensue. Therefore all files that use the same type of interrupt must be commented out. 
Some of the processors used require various registers to be set. For example some of the processors have LEDs located in port 2, 4, or even 9. The button ports also need to be specified for each processor. Depending on the processor, the timer may also need to be changed.
This information can be found on the datasheet of each processor. 


