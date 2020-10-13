#ifndef LCD_H_
#define LCD_H_

// /* Definitions to I2C communication */
#define I2C_ADDR          0x27          // I2C device address
#define LCD_CHR           1             // Mode - Sending data
#define LCD_CMD           0             // Mode - Sending command
#define LINE1             0x80          // 1st line
#define LINE2             0xC0          // 2nd line
#define ENABLE            0b00000100    // Enable bit
#define LCD_BACKLIGHT     0x08          // On
// // #define LCD_BACKLIGHT  0x00          // Off

// /*!
//  * @brief Function used to setup the initial states of the lcd display.
//  *
//  * @param[in]  fd     :   File descriptor to establish connection via i2c.
//  *
//  */
void initialize_lcd();

void print_lcd(float internal_temperature, float external_temperature, float reference_temperature, float hysteresis);


// /*!
//  * @brief Function used to send byte to data pins.
//  *
//  * @param[in]  fd       :   File descriptor to establish connection via i2c.
//  * @param[in]  bits     :   Bits to be toggled.
//  * @param[in]  mode     :   Operation mode (data or command)
//  *
//  * mode:
//  * - LCD_CHR (data): 0.
//  * - LCD_CHR (command): 1.
//  *
//  */
// void lcd_byte(int bits, int mode);

// /*!
//  * @brief Function used to toggle the enable pin on LCD display.
//  *
//  * @param[in]  fd       :   File descriptor to establish connection via i2c.
//  * @param[in]  bits     :   Bits to be toggled.
//  *
//  */
// void lcd_toggle_enable(int bits);

// /*!
//  * @brief Function used to convert integer to string and display on LCD.
//  *
//  * @param[in]  fd         :   File descriptor to establish connection via i2c.
//  * @param[in]  value      :   Integer value to write to LCD.
//  *
//  */
// void write_int(int value);

// /*!
//  * @brief Function used to convert float to string and display on LCD.
//  *
//  * @param[in]  fd         :   File descriptor to establish connection via i2c.
//  * @param[in]  value      :   Float value to write to LCD.
//  *
//  */
// void write_float(float value);

// /*!
//  * @brief Function used to set the cursor location.
//  *
//  * @param[in]  fd       :   File descriptor to establish connection via i2c.
//  * @param[in]  line     :   line to set the cursor location.
//  *
//  * line:
//  * - LINE1: 0.
//  * - LINE2: 1.
//  *
//  */
// void set_cursor_location(int line);

// /*!
//  * @brief Clear LCD display and go to row 0 column 0.
//  *
//  * @param[in]  fd       :   File descriptor to establish connection via i2c.
//  *
//  */
// void clear_lcd();

// /*!
//  * @brief Function used to write char to LCD.
//  *
//  * @param[in]  fd         :   File descriptor to establish connection via i2c.
//  * @param[in]  value      :   Char to write to LCD.
//  *
//  */
// void write_char(char value);

// /*!
//  * @brief Function used to write strings to LCD.
//  *
//  * @param[in]  fd       :   File descriptor to establish connection via i2c.
//  * @param[in]  str      :   String to write to LCD.
//  *
//  */
// void write_string(const char *str);

#endif /* LCD_H_ */