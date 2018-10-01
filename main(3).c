#include <msp430.h> 

/*
 * main.c
 */
int lookup_table(int i, int scan){

	int x, key;

	x = 0x10 << i;

	key = x + scan;

	if(key == 0x11)
		return 0 ;
	else if(key == 0x12)
		return 1 ;
	else if(key == 0x14)
		return 2 ;
	else if(key == 0x18)
		return 3 ;
	else if(key == 0x21)
		return 4 ;
	else if(key == 0x22)
		return 5 ;
	else if(key == 0x24)
		return 6 ;
	else if(key == 0x28)
		return 7 ;
	else if(key == 0x41)
		return 8 ;
	else if(key == 0x42)
		return 9 ;
	else if(key == 0x44)
		return 10 ;
	else if(key == 0x48)
		return 11 ;
	else if(key == 0x81)
		return 12 ;
	else if(key == 0x82)
		return 13 ;
	else if(key == 0x84)
		return 14 ;
	else if(key == 0x88)
		return 15 ;
	else return 0;

}
void blink(int x)
{	int j;

	for(j=0; j<x ;j++)
	{
	int i;
	P1OUT ^= 0x40;

	for(i=0 ; i< 20000 ; i ++);

	P1OUT ^=  0x40;
	for(i=0 ; i< 20000 ; i ++);


	}
}



int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	int i, scan;
	int c;
	c = 0;
    P1DIR = 0xFF;
    P2DIR = 0x00;
    P2REN |= 0x00;

    P1OUT = 0x00;
    P1OUT |= 0x0F;


    while(1)
    {
    	for(i = 0; i<4; i++)
    	{
    		P1OUT = 0x01 << i;
    		scan = P2IN;
    		scan &= 0x0F ;

    		c = lookup_table(i,scan);

    		blink(c);

    	}
    }
	return 0;
}
