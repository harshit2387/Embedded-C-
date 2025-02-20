/*
 * LED.cpp
 *
 * Created: 20-02-2025 19:41:16
 * Author : sharm
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define LED PB2

void switchon(int n) {
	DDRB = (1 << LED);

	for (int i = 0; i < n; ++i) {
		PORTB |= (1 << LED); // Turn on LED
		_delay_ms(1000);
		PORTB &= ~(1 << LED); // Turn off LED
		_delay_ms(1000);
	}
}

int main(void) {
	int n;
	// Replace this with a suitable method for input if you're using a serial port or other input methods
	n = 5; // Example value, you can change this

	switchon(n);
	return 0;
}


