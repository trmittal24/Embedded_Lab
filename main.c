#include <msp430.h> 

/*
 * main.c
 */
void ghum(int i)
{
   	 if(i%2)
   	 {
   		 TA0CCR1 = 500; //0degrees

   		 __delay_cycles(800000);
   	 }
   	 else
   	 {
   		 TA0CCR1 = 2500; //180degrees
   		 __delay_cycles(800000);
   	 }

   	 return;
 }

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{

	 P1OUT |= BIT0;
	ghum(1);



   //__delay_cycles(800000);
   P1IFG &=~BIT3;                        // P1.3 IFG cleared
}



int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    P1DIR = 0x00;
    P1REN |= BIT3;                 // Enable internal pull-up/down resistors
    P1OUT |= BIT3;

    P1DIR |= BIT6;             // P1.6 to output
    P1SEL |= BIT6;             // P1.6 to TA0.1
    P1DIR |= BIT0;						// P1.0 to output
   // P1SEL2 &= ~BIT6;             // P1.6 to TA0.1

    TA0CCR0 = 20000; // Set maximum count value (PWM Period)
    TA0CCTL1 = OUTMOD_7; // set output on counter reset, clear output on CCR1
    TA0CCR1 = 1000; // initialise counter compare value
    TA0CTL = TASSEL_2 + MC_1; // Use the SMCLK to clock the counter and set to count up mode

    P1IE |= BIT3;                    // P1.3 interrupt enabled
    P1IES |= BIT3;                  // P1.3 Hi/lo edge
    P1IFG &= ~BIT3;               // P1.3 IFG cleared

    __enable_interrupt();

	while(1)
	{
		ghum(0);
		P1OUT &= ~BIT0;
	}


}





