#include <msp430g2231.h>
#include <legacymsp430.h>

// Delays by the specified Milliseconds
void delay(unsigned int ms)
{
	while (ms--)
	{
		__delay_cycles(1000); //1000 for 1 Mhz
	}
}

void main()
{
	// Stop watchdog
	WDTCTL = WDTPW + WDTHOLD;

	// Make P1.0 (green led) an output. SLAU144E p.8-3
	P1DIR |= BIT0 + BIT6;
  
	while ( 1 )
	{
		if ( P1IN & BIT3 )
		{
			P1OUT &= ~BIT0;
		}
		else
		{
			P1OUT |= BIT0;
		}
		
		P1OUT ^= BIT6; //Output-registret XOR output 6
		delay( 1000 );
	}	
}