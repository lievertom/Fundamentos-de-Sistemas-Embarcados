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

void *print_lcd (void *args);

void clear_lcd();


#endif /* LCD_H_ */