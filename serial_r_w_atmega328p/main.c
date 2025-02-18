#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// buffer and corresponding read/write pointers
#define SIZE 64
uint8_t buffer[SIZE];
uint8_t* buffer_w = buffer;
uint8_t* buffer_r = buffer;

uint8_t is_buffer_empty() {
    return buffer_r == buffer_w;
}

uint8_t read() {
    uint8_t c = *buffer_r;
    buffer_r++;
    if (buffer_r >= ((uint8_t*) buffer) + SIZE) {
        buffer_r = buffer;
    }
    return c;
}

void write(uint8_t c) {
    *buffer_w = c;
    buffer_w++;
    if (buffer_w >= ((uint8_t*) buffer) + SIZE) {
        buffer_w = buffer;
    }
}

void usartInit(unsigned int ubrr) {
    // Set baud rate
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    // Enable transmitter (TX) and receiver (RX)
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);

    // Set frame format: 8 data bits, 1 stop bit (8N1)
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// enable USART RX Complete Interrupt
void enableRXCInterapt(uint8_t enabled) {
    uint8_t mask = (1 << RXCIE0);
    UCSR0B = (UCSR0B & ~mask) | (enabled ? mask : 0);
}

// enable USART Data Register Empty Interrupt
void enableEmptyInterapt(uint8_t enabled) {
    uint8_t mask = (1 << UDRIE0);
    UCSR0B = (UCSR0B & ~mask) | (enabled ? mask : 0);
}

// USART Data Register Empty Interrupt Handler
ISR(USART_UDRE_vect) {
    if (is_buffer_empty()) {
        enableEmptyInterapt(0);
    }
    if (!is_buffer_empty()) {
        UDR0 = read();
    }
}

// USART RX Complete Interrupt Handler
ISR(USART_RX_vect) {
    write(UDR0);
}

void setup() {
    usartInit(103); // 103 corresponds to ~9600 baudrate
    sei(); // enable avr interrupts
    enableRXCInterapt(1);
}

void loop() {
    if (!is_buffer_empty()) {
        enableEmptyInterapt(1);
    }
}

int main(void) {
    setup();
    while(1) {
        loop();
    }
}

