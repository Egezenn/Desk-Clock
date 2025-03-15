# Desk Clock

Simple desk clock that displays date&time.

## Software

### KiCad

Designed with DIY PCB production methods in mind. Has DS1302 symbol&footprint that I could've just used pin headers, didn't, ¯\\\_(ツ)\_/¯.

### Proteus

To test, link the compiled hex file to PIC16F877A component.

### CCS C Compiler

Compile contents of [src](src) with the compiler.

## Components

- PIC16F877a
- 1602 LCD
- DS1302
- 4mHz crystal oscillator (only one that was in stock, shouldn't matter all that much)
- 4x buttons (dual, because I already had them)
- 2x 22pF ceramic disc capacitor
- 6x 10k ohm resistors
- 5V power source
- CR2032 lithium battery (for DS1302)

## Acknowledgements of stuff that could've been better section

- Usage of a more reliable RTC module like DS1307
- A smaller & cheaper PIC, PIC16F877A is a bit of an overkill here (school project ¯\\\_(ツ)\_/¯)
- Interrupt section of the C source file could've been condensed via functions and whatnot
- `day_in_week` could also be displayed, there's space for it in the LCD
