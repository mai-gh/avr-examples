#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main()
{
  DDRB |= (1 << PB5); // LED output
  while(1) {
    PORTB |= (1 << PB5); // PB5 goes high 
    _delay_ms(100);
    PORTB &= ~(1 << PB5); // PB5 goes low
    _delay_ms(100);
  }

}
