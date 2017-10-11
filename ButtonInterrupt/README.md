### Jake Fraser

## Lab Exercise 3: Timers and Interrupts
## Button Interrupt

## Function
This program uses an interrupt linked to a button to blink an LED whenever a button on the MSP430 family of processors is pressed.
An interrupt is a piece of code that is triggered whenever a certain condition is true. In this case, the condition is linked to 
the button being pressed. This method is more efficient then conditional if and else statements because the processor enters low
power mode while in an interrupt, performing no other actions.   

## How it works
This program starts out by initializing the P1OUT and P1DIR registers. Since both LEDs are to be used, they are set as outputs but initialized to be off.
From there, the pull up resistor is set on the bit of the button. The line of code that reads P1REN = 0x08 places a resistor on the button, while
the line P1OUT = 0x08 sets it as a pull up. Next the interrupt delarations are initialized. The register P1IE is used to set the bit the interrupt is fired on.
Since we want the interrupt to fire when the button is pressed, it is set to 0x08. The next register used, is P1IES. This register sets the edge of the button that 
the interrupt will fire at. Since we want the interrupt to fire on the low to high edge of the button (when the button is pressed down), it is set to 0x08.
Next, the interrupt flag is set. The interrupt flag is the bit that will exit the interrupt. When this is cleared, the processor goes back to its normal functions.
In this case, it is set to ~BIT3. From here, the processor is put into low power mode. 

The next part of the program is the interrupt service report (ISR). This is the piece of code that the program runs through when the interrupt is triggered. 
While in the ISR, both of the LEDs are toggled, and a for loop is used as a delay to account for debouncing in the mechanical button switch.
 Once the interrupt flag is triggered (the button is not pressed down), the processor returns to its original routine. 

## Usage
Within this project, there are a multitude of files that all use interrupts in a certain manner. In order to run this file, the main.c file needs to be ran.
The user can decide which file they want to run here, and comment out any function that they dont wish to run, leaving the only file to be called, the one they want to run.
Obviously, an error will be given if more than one file is attempted to be called at once. Since there are multiple files in the project that use interrupts, all other files that use the same type of interrupt must be commented out. 
This is because the compiler will recognize both interrupt service routines and an error will ensue. Therefore all files that use the same type of interrupt must be commented out. 
Some of the processors used require various registers to be set. For example some of the processors have LEDs located in port 2, 4, or even 9. The button ports also need to be specified for each processor.


