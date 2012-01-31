#include <msp430g2231.h>

void main()
{
	// Stop watchdog
	WDTCTL = WDTPW + WDTHOLD;

	// Make P1.0 and P1.6 outputs. SLAU144E p.8-3
	P1DIR |= BIT0 + BIT6;

	// Välj funktion på P1.6
	// P1.6 = TA0.1 (timer A's output). SLAS694C p.41
	P1SEL |= BIT6;  
	
	// Ställ in en klock med prescaler 8 till timern
	// SMCLK = 1 MHz / 8 = 125 KHz (SLAU144E p.5-15)
	BCSCTL2 |= DIVS_3;		

	// PWM period = 125 KHz / 65535 = 200 Hz
	TACCR0 = 0xFFFFF;

	// Source Timer A from SMCLK (TASSEL_2), up mode (MC_1).
	// Up mode counts up to TACCR0. SLAU144E p.12-20
	TACTL = TASSEL_2 | MC_1;

	// OUTMOD_4 = toggle output when the timer counts to TACCR1/TACCR0
	// OUTMOD_7 = Reset/set output when the timer counts to TACCR1/TACCR0
	// CCIE = Interrupt when timer counts to TACCR1
	TACCTL1 = OUTMOD_4;
  
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
		
	}	
}