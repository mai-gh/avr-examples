#!/bin/sh

avrdude -v -p atmega328p -c usbasp -B50 -U lfuse:w:0xDF:m -U hfuse:w:0xDF:m -U efuse:w:0xF9:m -U lock:w:0xFF:m
