/*                                                                *
 *  reference demonstration for enabling and disabling hardware   *
 *  assisted pulse width modulation on atmel atmega328p for       *
 *  controlling dimming, brightening, and state of LEDs.          *
 *  (in this case an RGB LED).                                    *
 *                                                                *
 *      Blue LED is on PD6 / OC0A and uses a 200 ohm resistor     *
 *     Green LED is on PD5 / OC0B and uses a 200 ohm resistor     *
 *       Red LED is on PB3 / OC2A and uses a 200 ohm resistor     *
 *                                                                *
 *     Licensed under the GNU General Public License Version 3    *
 *                                                                */

#define F_CPU 12000000UL
#include <avr/io.h>
#include <util/delay.h>

#define sleep {_delay_ms(12);}

/* set PD6 as input and set as normally low (disable pullup) */
#define disable_OC0A {DDRD &= ~(1 << PD6); PORTD |= (0 << PD6);}

/* set PD5 as input and set as normally low (disable pullup) */
#define disable_OC0B {DDRD &= ~(1 << PD5); PORTD |= (0 << PD5);}

/* set PB3 as input and set as normally low (disable pullup) */
#define disable_OC2A {DDRB &= ~(1 << PB3); PORTB |= (0 << PB3);}

/* set PD6 as output for pwm */
#define enable_OC0A {DDRD |= (1 << DDD6);}

/* set PD5 as output for pwm */
#define enable_OC0B {DDRD |= (1 << DDD5);}

/* set PB3 as output for pwm */
#define enable_OC2A {DDRB |= (1 << DDB3);}

int main(void)
{

  /* define initial PWM for OCR0A (0 - 255) */
  OCR0A = 0;
  /* enable OC0A, set as none-inverting mode */
  TCCR0A |= (1 << COM0A1);

  /* define initial PWM for OCR0B (0 - 255) */
  OCR0B = 0;
  /* enable OC0B, set as none-inverting mode */
  TCCR0A |= (1 << COM0B1);

  /* define initial PWM for OCR2A (0 - 255) */
  OCR2A = 0;
  /* enable OC2A, set as none-inverting mode */
  TCCR2A |= (1 << COM2A1);

  /* set fast PWM Mode for OCR0A & OCR0B */
  TCCR0A |= (1 << WGM01) | (1 << WGM00);
  /* set prescaler to 8 and start PWM for OCR0A & OCR0B */
  TCCR0B |= (1 << CS01);

  /* set fast PWM Mode for OCR2A & OCR2B */
  TCCR2A |= (1 << WGM01) | (1 << WGM00);
  /* set prescaler to 8 and start PWM for OCR2A & OCR2B */
  TCCR2B |= (1 << CS01);

  while(1)
  {

    /* cycle blue */
    enable_OC0A;
    while (OCR0A < 255) 
    {
      sleep;
      OCR0A++;
    }
    while (OCR0A > 0)
    {
      sleep;
      OCR0A--;
    }
    disable_OC0A;
    _delay_ms(1000);

    /* cycle green */
    enable_OC0B;
    while (OCR0B < 255)
    {
      sleep;
      OCR0B++;
    }
    while (OCR0B > 0)
    {
      sleep;
      OCR0B = OCR0B - 1;
    }
    disable_OC0B;
    _delay_ms(1000);

    /* cycle red */
    enable_OC2A;
    while (OCR2A < 255)
    {
      sleep;
      OCR2A++;
    }
    while (OCR2A > 0)
    {
      sleep;
      OCR2A--;
    }
    disable_OC2A;
    _delay_ms(1000);

    /* cycle all on */
    enable_OC0A;
    enable_OC0B;
    enable_OC2A;
    while (OCR0A < 255 && OCR0B < 255 && OCR2A < 255 )
    {
      sleep;
      OCR0A++;
      OCR0B++;
      OCR2A++;
    }
    while (OCR0A > 0 && OCR0B > 0 && OCR2A > 0)
    {
      sleep;
      OCR0A--;
      OCR0B--;
      OCR2A--;
    }
    disable_OC0A;
    disable_OC0B;
    disable_OC2A;

    /* cycle all off */
    _delay_ms(4000);
  }
}

