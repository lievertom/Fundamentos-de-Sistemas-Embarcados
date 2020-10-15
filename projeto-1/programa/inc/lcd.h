#ifndef LCD_H_
#define LCD_H_

/****************************************************************************/
/*!                              Macros                                     */

/* Definitions to I2C communication */
#define I2C_ADDR          0x27          // I2C device address
#define LCD_CHR           1             // Mode - Sending data
#define LCD_CMD           0             // Mode - Sending command
#define LINE1             0x80          // 1st line
#define LINE2             0xC0          // 2nd line
#define ENABLE            0b00000100    // Enable bit
#define LCD_BACKLIGHT     0x08          // On
// #define LCD_BACKLIGHT  0x00          // Off

/*!
 * @brief Function used to setup the initial states of the lcd display.
 *
 * @return void
 *
 */
void initialize_lcd();

/*!
 *  @brief Thread function that drawing in lcd
 *
 * @param[in] args       : Pointer to access the data structure
 *
 * @return void
 *
 */
void clear_lcd();

/*!
 *  @brief Thread function that drawing in lcd
 *
 * @param[in] args       : Pointer to access the data structure
 *
 * @return void
 *
 */
void *print_lcd (void *args);

#endif /* LCD_H_ */