#include <avr/io.h>
#include <util/delay.h>

void setup() {
    // initialize digital pin LED_BUILTIN as an output.
    DDRB |= (1 << DDB5);
}

void loop() {
  PORTB |= (1 << PORTB5);   // turn the LED on (HIGH is the voltage level)
  _delay_ms(1000);          // wait for a second
  PORTB &= ~(1 << PORTB5);  // turn the LED off by making the voltage LOW
  _delay_ms(1000);          // wait for a second
}

int main(void) {
    setup();

    while(1) {
        loop();
    }
}

