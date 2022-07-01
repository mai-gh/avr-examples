
/*

using the reset switch on the arduino duemilanove hacky way 
it still resets the program, but the cont variable is kept its state

https://sites.google.com/site/wayneholder/using-the-avr-reset-pin-as-an-input


*/



#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

volatile unsigned char count __attribute__((section(".noinit"))); // Not cleared on RESET

int main()
{

  MCUSR=0;
  DDRB |= (1 << PB5); // LED output

  if (count >= 128) {
    count = 0;
  }

  for(int i=0;i<count;i++){
    PORTB |= (1 << PB5); // PB5 goes high 
    _delay_ms(300);
    PORTB &= ~(1 << PB5); // PB5 goes low
    _delay_ms(300);
  }

  count++;

  while(1) {}

}


