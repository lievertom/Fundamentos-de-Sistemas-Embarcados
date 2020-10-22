#ifndef WINDOW_H_
#define WINDOW_H_

/******************************************************************************/
/*                       Header includes                                      */
#include <curses.h>

/****************************************************************************/
/*!                              Macros                                     */

#define ENTER                   10
#define ESCAPE                  27
 
#define NTEMPERATURE_VALUES     21
#define TEMPERATURE_FIRST_VALUE 10

#define NLINES_MENU             1
#define NCOLUMNS_MENU           80
#define FIRST_LINE_MENU         0
#define FIRST_COLUMN_MENU       0
#define FIRST_LINE_COMMANDS     2
#define FIRST_LINE_INSTRUCTIONS 15

#define NLAMPS                  4
#define NAIR                    2
#define BUTTON_SIZE             12

#define AIR_OFF                 0.0f

/****************************************************************************/
/*!                            Structs                                      */
typedef struct Windows
{
    WINDOW *menu_bar;
    WINDOW *message;
} Windows;

typedef struct Actuators
{
    unsigned char lamps[NLAMPS];
    unsigned char alarm;
    float air[NAIR];
} Actuators;

/****************************************************************************/
/*!                         Functions                                       */

/*!
 *  @brief function that initialize window
 *
 *  @return void
 *
 */
void initialize_window ();

/*!
 *  @brief Thread function that shows the values ​​on the screen
 *
 * @param[in] args       : Pointer to access the data structure
 *
 *  @return void
 *
 */
void *output_values ();

/*!
 *  @brief Thread function to user input 
 *
 * @param[in] args       : Pointer to access the data structure
 *
 *  @return void
 *
 */
void *input_values ();

/*!
 *  @brief Thread function that ends the window
 *
 *  @return void
 *
 */
void end_window(); 

#endif /* WINDOW_H_ */