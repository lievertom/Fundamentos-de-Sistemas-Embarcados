#ifndef WINDOW_H_
#define WINDOW_H_

#include <curses.h>


//Constastes das teclas ENTER e ESCAPE.
#define ENTER                   10
#define ESCAPE                  27
 
#define NTEMPERATURE_VALUES     41
#define TEMPERATURE_FIRST_VALUE 10

#define NHYSTERESIS_VALUES      10
#define HYSTERESIS_FIRST_VALUE  1

#define NLINES_MENU             1
#define NCOLUMNS_MENU           80
#define FIRST_LINE_MENU         0
#define FIRST_COLUMN_MENU       0
#define FIRST_LINE_COMMANDS     2
#define FIRST_LINE_INSTRUCTIONS 11


typedef struct Windows
{
    WINDOW *menu_bar;
    WINDOW *message;
} Windows;

Windows windows;

void initialize_window ();
void *output_values (void *args);
void *input_values (void *args);
void end_window(); 
void menu ();

#endif /* WINDOW_H_ */