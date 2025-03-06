#include <avr/io.h>
#include <util/delay.h>

#define LED PB2

void switchon(int n) {
	DDRB = (1 << LED); // Set LED pin as an output

	for (int i = 0; i < n; ++i) {
		PORTB |= (1 << LED); // Turn on LED
		_delay_ms(1000);
		PORTB &= ~(1 << LED); // Turn off LED
		_delay_ms(1000);
	}

	// Ensure the LED remains off after finishing the loop
	PORTB &= ~(1 << LED);
}

int main(void) {
	int n;
	// Replace this with a suitable method for input if you're using a serial port or other input methods
	n = 5; // Example value, you can change this

	switchon(n);
	return 0;
}
