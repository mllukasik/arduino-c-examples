#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

char* buffor;

/**
 * Check datasheet for example code and how to caclutate ubrr value
 * https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf
 */
void usartInit(unsigned int ubrr) {
    // Set baud rate
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    // Enable transmitter (TX) and receiver (RX)
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);

    // Set frame format: 8 data bits, 1 stop bit (8N1)
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// enable USART Data Register
void enableEmptyInterapt(uint8_t enabled) {
    uint8_t mask = (1 << UDRIE0);
    UCSR0B = (UCSR0B & ~mask) | (enabled ? mask : 0);
}

// USART Data Register Empty Interrupt Handler
ISR(USART_UDRE_vect) {
    if(!*buffor) {
        enableEmptyInterapt(0);
        return;
    }
    UDR0 = *buffor++;
}

void send(char* c) {
    buffor = c;
    UDR0 = *buffor++;
    enableEmptyInterapt(1);
    while (!(UCSR0B & (1 << UDRIE0))); //waits untile empty interapt is disabled
}

void setup() {
    usartInit(103); // 103 corresponds to ~9600 baudrate
    sei(); // enable avr interrupts
}

void loop() {
    send("Hello world\n");
    _delay_ms(2000);
}

int main(void) {
    setup();
    while(1) {
        loop();
    }
}

