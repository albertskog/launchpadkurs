#include <msp430g2231.h>

// Delays in milliseconds
void delay( unsigned int ms )
{
	while ( ms-- )
	{
		__delay_cycles( 1000 ); //1ms = 1000 cycles for 1 Mhz
	}
}

void main()
{
	// Stop watchdog. SLAU144E p.380
	WDTCTL = WDTPW + WDTHOLD;

	// Make P1.6 (green led) an output. SLAU144E p.
	P1DIR |= BIT6;
  
	while ( 1 )
	{
		P1OUT ^= BIT6; //Output-registret XOR output 6
		delay( 1000 );
	}		
}