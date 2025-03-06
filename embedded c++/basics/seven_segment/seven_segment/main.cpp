#include <avr/io.h>
#include <util/delay.h>

// Segment patterns for digits 0-9
const char pattern[10]={
	0b10000000,
}

int main(void)
{
	// Set PORTB and PORTD as output
	DDRB = 0xFF;
	DDRD = 0xFF;

	while (1)
	{
	
			PORTB = PORTD = 0b10000000;
			_delay_ms(10000);
			

	}
}
