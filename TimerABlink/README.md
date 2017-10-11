### Jake Fraser

## Lab Exercise 3: Timers and Interrupts
## Timer A Blink

## Function
This program uses a timer interrupt to blink two LEDs at different speeds on the MSP430 family of processors.
A timer is a peripheral on the MSP430 that is used to count. It has three different modes, up mode, up/down mode, and continuous mode. 
In up mode, the timer will count up to FFFF and then start back down at 0000. In continuus mode, 
the timer will count up the number specified by value of the the CCR (capture/compare register), roll over to 0 and continue counting. 
In up/down mode, the timer will count to the value in CCR and then count back down to 0000. In the case of this program, the timer will be in continuous mode.   

## How it works
This program starts out by initializing the P1OUT and P1DIR registers. Since both LEDs are to be used, they are set as outputs but initialized to be off.
From there, the timer is initialized. Since the LEDs are to be blinked at two different speeds, two capture compares will be used. To enable these, CCTL1 and CCTL2 are set to CCIE.
Now the two capture compares can be set. In this case, CCR1 is set at 10000 and CCR2 is set at 35000. These are the two values that the LEDs will blink at when the timer is running. 
The next line of code starts the timer. 

 TACTL  = TASSEL_2 + MC_2 + ID_3;

The first part of this line (TASSEL_2) selects the clock to be used, in this case sm_clock. Next, MC_2 selects the mode of the timer. This timer runs in continuous mode.
If MC_1 was chosen, the timer would run in up mode and if MC_0 was chosen, the timer would run in up/down mode. The ID selection descides how much the clock will be divided by.

Once the timer reaches the values of CCR1 and CCR2, the timer ISR is triggered. In this part of the program, there is a case statement with multiple cases set.
Since the TA0IV register is used, case 2 is automatically set to CCR1 and case 4 is set to CCR2. In each case, one of the LEDs is toggled and the CCR is offset. Because each CCR is different,
the LEDs are blinking at different speeds.   


## Usage
Within this project, there are a multitude of files that all use interrupts in a certain manner. In order to run this file, the main.c file needs to be ran.
The user can decide which file they want to run here, and comment out any function that they dont wish to run, leaving the only file to be called, the one they want to run.
Obviously, an error will be given if more than one file is attempted to be called at once. Since there are multiple files in the project that use interrupts, all other files that use the same type of interrupt must be commented out. 
This is because the compiler will recognize both interrupt service routines and an error will ensue. Therefore all files that use the same type of interrupt must be commented out. 
Some of the processors used require various registers to be set. For example some of the processors have LEDs located in port 2, 4, or even 9. The button ports also need to be specified for each processor. Depending on the processor, the timer may also need to be changed.
This information can be found on the datasheet of each processor. 


