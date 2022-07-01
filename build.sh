#!/bin/bash


CFILE="$1"

if [ "$(echo "$CFILE" | sed 's/.*\(\.c\)$/\1/')" != '.c' ]; then
  echo "File extension must be .c"
  echo "Example: test.c"
  exit 99
fi

BASEFILENAME="$(echo "$CFILE" | sed 's/\(.*\)\.c/\1/')"








avr-gcc -g -Os -mmcu=atmega328p -c "$CFILE" &&
avr-gcc -B/usr/avr/lib/avr25 -g -mmcu=atmega328p -o "$BASEFILENAME".elf "$BASEFILENAME".o &&
avr-objcopy -j .text -j .data -O ihex "$BASEFILENAME".elf "$BASEFILENAME".hex &&
avrdude -p atmega328p -c usbasp -B50 -U flash:w:"$BASEFILENAME".hex
