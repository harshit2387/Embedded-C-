/*
 * 1blue.cpp
 *
 * Created: 26-02-2025 16:08:15
 * Author : sharm
 */ 

#include <avr/io.h>
#include <util/delay.h>

// Function to initialize UART communication
void uart_init(unsigned int baudrate) {
	unsigned int ubrr = F_CPU/16/baudrate - 1;
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Function to transmit data via UART
void uart_transmit(unsigned char data) {
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

// Function to receive data via UART
unsigned char uart_receive(void) {
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

// Main function
int main(void) {
	uart_init(9600); // Initialize UART with 9600 baud rate

	while (1) {
		uart_transmit('H'); // Transmit 'H'
		_delay_ms(1000);
		uart_transmit('i'); // Transmit 'i'
		_delay_ms(1000);
	}
}

