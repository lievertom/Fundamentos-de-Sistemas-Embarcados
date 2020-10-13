/* header includes */
#include "lcd.h"
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>

int fd;

/*!
 * @brief Function used to toggle the enable pin on LCD display.
 */
void lcd_toggle_enable(int bits)
{
  delayMicroseconds(500);
  wiringPiI2CReadReg8(fd, (bits | ENABLE));
  delayMicroseconds(500);
  wiringPiI2CReadReg8(fd, (bits & ~ENABLE));
  delayMicroseconds(500);
}

/*!
 * @brief Function used to send byte to data pins.
 */
void lcd_byte(int bits, int mode)   
{
    int bits_high;
    int bits_low;
    // uses the two half byte writes to LCD
    bits_high = mode | (bits & 0xF0) | LCD_BACKLIGHT ;
    bits_low = mode | ((bits << 4) & 0xF0) | LCD_BACKLIGHT ;

    // High bits
    wiringPiI2CReadReg8(fd, bits_high);
    lcd_toggle_enable(bits_high);

    // Low bits
    wiringPiI2CReadReg8(fd, bits_low);
    lcd_toggle_enable(bits_low);
}

/*!
 * @brief Function used to write strings to LCD.
 */
void write_string(const char *str)
{
    while (*str)
    {
      lcd_byte(*(str++), LCD_CHR);
    }
}
/*!
 * @brief Function used to convert float to string and display on LCD.
 */
void write_float (float value)
{
  char buffer[20];
  sprintf(buffer, "%.2f",  value);
  write_string(buffer);
}

/*!
 * @brief Function used to convert integer to string and display on LCD.
 */
void write_int (int value)
{
  char buffer[20];
  sprintf(buffer, "%d", value);
  write_string(buffer);
}

/*!
 * @brief Function used to write char to LCD.
 */
void write_char (char value)
{
  lcd_byte(value, LCD_CHR);
}

/*!
 * @brief Clear LCD display and go to row 0 column 0.
 */
void clear_lcd()
{
  lcd_byte(0x01, LCD_CMD);
  lcd_byte(0x02, LCD_CMD);
}

/*!
 * @brief Function used to set the cursor location.
 */
void set_cursor_location(int line)   
{
  lcd_byte(line, LCD_CMD);
}

/*!
 * @brief Function used to setup the initial states of the lcd display.
 */
void initialize_lcd()
{
  if (wiringPiSetup () == -1) exit (1);
  fd = wiringPiI2CSetup(I2C_ADDR);
  lcd_byte(0x33, LCD_CMD); // initialize
  lcd_byte(0x32, LCD_CMD); // initialize
  lcd_byte(0x06, LCD_CMD); // Cursor move direction
  lcd_byte(0x0C, LCD_CMD); // 0x0F On, Blink Off
  lcd_byte(0x28, LCD_CMD); // Data length, number of lines, font size
  lcd_byte(0x01, LCD_CMD); // Clear display
  delayMicroseconds(500);
}

void print_lcd(float internal_temperature, float external_temperature, float reference_temperature, float hysteresis)
{
  clear_lcd();
  set_cursor_location(LINE1);
  write_string("TI");
  write_float(internal_temperature);
  write_string(" TE");
  write_float(external_temperature);
  set_cursor_location(LINE2);
  write_string("TR");
  write_float(reference_temperature);
  write_string(" H");
  write_float(hysteresis);
}