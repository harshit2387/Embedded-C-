#include <avr/io.h>
#include <avr/boot.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#define BAUD_RATE 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUD_RATE)) - 1)

void uart_init() {
	// Set baud rate
	UBRR0H = (UBRR_VALUE >> 8);
	UBRR0L = UBRR_VALUE;
	// Enable transmitter and receiver
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	// Set data frame: 8 data bits, 1 stop bit, no parity
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

char uart_receive() {
	while (!(UCSR0A & (1 << RXC0))) ; // Wait for data
	return UDR0; // Read received data
}

void uart_transmit(char data) {
	while (!(UCSR0A & (1 << UDRE0))) ; // Wait for empty transmit buffer
	UDR0 = data; // Send data
}

void write_flash_page(uint32_t address, uint8_t *data) {
	boot_page_erase(address); // Erase the flash page
	boot_spm_busy_wait(); // Wait until the erase is complete

	for (uint16_t i = 0; i < SPM_PAGESIZE; i += 2) {
		uint16_t word = data[i] | (data[i + 1] << 8); // Combine two bytes into a word
		boot_page_fill(address + i, word); // Write the word
	}

	boot_page_write(address); // Write the page to flash
	boot_spm_busy_wait(); // Wait until the write is complete
}

int main(void) {
	uart_init(); // Initialize UART

	uint32_t address = 0x0000; // Start writing from address 0
	uint8_t buffer[SPM_PAGESIZE]; // Buffer to store data to write per page
	uint16_t buffer_index = 0;

	while (1) {
		char data = uart_receive(); // Receive a byte via UART

		if (data == '\0') { // End of transmission (custom protocol)
			break;
		}

		buffer[buffer_index++] = data; // Store received data in the buffer

		if (buffer_index == SPM_PAGESIZE) { // If buffer is full, write to flash
			write_flash_page(address, buffer);
			address += SPM_PAGESIZE; // Move to the next page
			buffer_index = 0; // Reset buffer index
		}
	}

	// Optional: Jump to the start of the application
	((void (*)(void))0x0000)();

	return 0;
}



