#include <deskclock.h>

#include <lcd.c>
#include <ds1302.c>

byte second, minute, hour, day, month, year, day_in_week;
int decade = 20;
int days_in_months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int day_count;

#INT_EXT

void EXT_isr()
{
    int1 datetime_setup = 0;
    int1 year_config = 0;
    int1 month_config = 0;
    int1 day_config = 0;
    int1 hour_config = 0;
    int1 minute_config = 0;
    delay_ms(100);
    rtc_get_date(day, month, year, day_in_week);

    while (!datetime_setup)
    {
        while (!year_config)
        {
            printf(lcd_putc, "\fyear\n%d%02d", decade, year);
            if (input(INCREASE))
            {
                while (input(INCREASE))
                {
                    if (year < 99)
                        year++;
                    else
                        year = 0;
                    delay_ms(100);
                    printf(lcd_putc, "\fyear\n%d%02d", decade, year);
                }
            }
            else if (input(DECREASE))
            {
                while (input(DECREASE))
                {
                    if (year > 0)
                        year--;
                    else
                        year = 99;
                    delay_ms(100);
                    printf(lcd_putc, "\fyear\n%d%02d", decade, year);
                }
            }
            else if (input(OK))
            {
                while (input(OK))
                    ;
                year_config = 1;
            }
            delay_ms(100);
        }

        while (!month_config)
        {
            printf(lcd_putc, "\fmonth\n%02d", month);
            if (input(INCREASE))
            {
                while (input(INCREASE))
                {
                    if (month < 12)
                        month++;
                    else
                        month = 1;
                    delay_ms(100);
                    printf(lcd_putc, "\fmonth\n%02d", month);
                }
            }
            if (input(DECREASE))
            {
                while (input(DECREASE))
                {
                    if (month > 1)
                        month--;
                    else
                        month = 12;
                    delay_ms(100);
                    printf(lcd_putc, "\fmonth\n%02d", month);
                }
            }
            else if (input(OK))
            {
                while (input(OK))
                    ;
                if (year % 4 == 0)
                    days_in_months[1] = 29;
                else
                    days_in_months[1] = 28;
                day_count = days_in_months[month - 1];
                month_config = 1;
            }
            delay_ms(100);
        }

        while (!day_config)
        {
            printf(lcd_putc, "\fday\n%02d", day);
            if (input(INCREASE))
            {
                while (input(INCREASE))
                {
                    if (day < day_count)
                        day++;
                    else
                        day = 1;
                    delay_ms(100);
                    printf(lcd_putc, "\fday\n%02d", day);
                }
            }
            else if (input(DECREASE))
            {
                while (input(DECREASE))
                {
                    if (day > 1)
                        day--;
                    else
                        day = day_count;
                    delay_ms(100);
                    printf(lcd_putc, "\fday\n%02d", day);
                }
            }
            else if (input(OK))
            {
                while (input(OK))
                    ;
                day_config = 1;
            }
            delay_ms(100);
        }

        while (!hour_config)
        {
            printf(lcd_putc, "\fhour\n%02d", hour);
            if (input(INCREASE))
            {
                while (input(INCREASE))
                {
                    if (hour < 23)
                        hour++;
                    else
                        hour = 0;
                    delay_ms(100);
                    printf(lcd_putc, "\fhour\n%02d", hour);
                }
            }
            else if (input(DECREASE))
            {
                while (input(DECREASE))
                {
                    if (hour > 0)
                        hour--;
                    else
                        hour = 23;
                    delay_ms(100);
                    printf(lcd_putc, "\fhour\n%02d", hour);
                }
            }
            else if (input(OK))
            {
                while (input(OK))
                    ;
                hour_config = 1;
            }
            delay_ms(100);
        }

        while (!minute_config)
        {
            printf(lcd_putc, "\fminute\n%02d", minute);
            if (input(INCREASE))
            {
                while (input(INCREASE))
                {
                    if (minute < 59)
                        minute++;
                    else
                        minute = 0;
                    delay_ms(100);
                    printf(lcd_putc, "\fminute\n%02d", minute);
                }
            }
            else if (input(DECREASE))
            {
                while (input(DECREASE))
                {
                    if (minute > 0)
                        minute--;
                    else
                        minute = 59;
                    delay_ms(100);
                    printf(lcd_putc, "\fminute\n%02d", minute);
                }
            }
            else if (input(OK))
            {
                while (input(OK))
                    ;
                minute_config = 1;
                datetime_setup = 1;
            }
            delay_ms(100);
        }
    }
    rtc_set_datetime(day, month, year, 1, hour, minute);
}

void main()
{
    setup_timer_1(T1_DISABLED);
    setup_timer_2(T2_DISABLED, 0, 1);
    setup_adc_ports(NO_ANALOGS);
    setup_adc(ADC_OFF);
    setup_CCP1(CCP_OFF);
    setup_CCP2(CCP_OFF);
    rtc_init();
    lcd_init();

    enable_interrupts(INT_EXT);
    ext_int_edge(H_to_L);
    enable_interrupts(GLOBAL);
    rtc_set_datetime(1, 1, 0, 1, 0, 0);
    while (TRUE)
    {
        rtc_get_time(hour, minute, second);
        rtc_get_date(day, month, year, day_in_week);
        printf(lcd_putc, "\f%02d/%02d/%d%02d", day, month, decade, year);
        printf(lcd_putc, "\n%02d:%02d:%02d", hour, minute, second);
        delay_ms(1000);
    }
}
