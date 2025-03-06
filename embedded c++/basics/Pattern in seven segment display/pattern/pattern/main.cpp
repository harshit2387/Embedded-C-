/*
 * pattern.cpp
 *
 * Created: 24-02-2025 07:48:55
 * Author : sharm
 */ 

#include <avr/io.h>
#include <util/delay.h>

// Define the patterns for the 7-segment display segments
const uint8_t segment_patterns[10] = {
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111  // 9
};

int main(void)
{
	// Set PORTB and PORTD as output
	DDRB = 0xFF;
	DDRD = 0xFF;

	while (1)
	{
		for (int i = 0; i < 10; i++)
		{
			PORTB = segment_patterns[i];
			_delay_ms(10000);

			PORTD = segment_patterns[9 - i]; // Display pattern in reverse on PORTD
			_delay_ms(10000);
		}
	}
}


