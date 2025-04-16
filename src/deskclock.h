#include <16F877A.h>

#device ADC = 16

#FUSES NOWDT	  // No Watch Dog Timer
#FUSES NOBROWNOUT // No brownout reset
#FUSES NOLVP	  // No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal = 4000000)
#use STANDARD_IO(B, C, D)

#define LCD_ENABLE_PIN PIN_D0
#define LCD_RS_PIN PIN_D1
#define LCD_RW_PIN PIN_D2
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7

#define RTC_SCLK PIN_C0
#define RTC_IO PIN_C1
#define RTC_RST PIN_C2

#define INCREASE PIN_B1
#define DECRESASE PIN_B2
#define OK PIN_B3
