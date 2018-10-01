#include <msp430.h> 
#define LED0  BIT0 //red LED
#define LED1 BIT6 //green LED
unsigned int value=0;
float input_voltage = 0;


void main (void)
{
	WDTCTL = WDTPW + WDTHOLD;            // Disable Watchdog timer
	BCSCTL1 = CALBC1_16MHZ;                    // Set Clock Frequencies
	DCOCTL = CALDCO_16MHZ;
	P1DIR |= LED0 + LED1;
	P2DIR |= 0x0F;

	P1SEL |= BIT1;                             //ADC Input pin P1.1
	P1OUT &= ~(LED0 + LED1);
	P2OUT &= ~0x0F;
	ADC10CTL1 = INCH_1;          // Channel 1
	ADC10CTL0 = SREF_0 + ADC10SHT_3 + ADC10ON + ADC10IE ;
	ADC10AE0 |= BIT1;                         //P1.1 ADC option
	value=0;
	
	while(1)
	{
		__delay_cycles(2000);                   // Delay for ADC
		ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
		value = ADC10MEM;
		input_voltage = (float)value*3.3/1023; //Convert back to voltage

		if
		(input_voltage >3)
		{
			P1OUT &= ~LED1;
			P1OUT |= LED0;
		}
		else
		//input_voltage less than or equal to 1.5 V
		{
			P1OUT &= ~LED0;
			P1OUT |= LED1;
			__delay_cycles(10000);
		}


		if(value > 0x1FF)
		{
			P2OUT |= 0x0F;
		}
		else if(value > 0x0FF)
		{
			P2OUT |= 0x07;
			P2OUT &= ~0x08;
		}
		else if(value > 0x07F)
		{
			P2OUT |= 0x03;
			P2OUT &= ~0x0C;
		}
		else if(value > 0x03F)
		{
			P2OUT |= 0x01;
			P2OUT &= ~0x0E;
		}
		else
		{
			P2OUT &= ~0x0F;
		}

//		value &= 0x3C0;
//
//		P2OUT = value >> 6;
	}
//end while
} //end main
