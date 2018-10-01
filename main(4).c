#include <msp430.h> 
#include <string.h>
#include "lcd_lib.h"
/*
 * main.c
 */
void LCDScrollMessage(const char *Message)
{
    char TempS[20];
    unsigned int  i=0,count;
    // set position 0xCO
    while(1)
    {
		 for(count=0;count<16;count++)
		 {
			  TempS[count]=Message[(i+count)%(strlen(Message))];
		 }
		 i++;
		 send_command(0xC0);
		 send_string(TempS); // send string to LCD.
		 delay(500);
    }
}

int main(void) {

	char a[10] = "Hello :)";
	char *b = "Hey, I'm scrolling, look!  " ;
	WDTCTL = WDTPW + WDTHOLD; // stop watchdog timer
	lcd_init();
	send_string(a);
	send_command(0xC0);

	LCDScrollMessage(b);


}
