/******************************************************************************/
/*                       Header includes                                      */

#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include "data.h"

/******************************************************************************/
/*! @file window.c
 * @brief Inteface to window
 */
#include "window.h"

/****************************************************************************/
/*!                        Global Statements                                */

Windows windows;

/****************************************************************************/
/*!                         Functions                                       */

/*!
 * @brief Function used to create the menu bar
 */  
void create_menu_bar()
{
    WINDOW *menu_bar = windows.menu_bar;
    menu_bar=subwin(stdscr,NLINES_MENU, COLS, FIRST_LINE_MENU, FIRST_COLUMN_MENU);
    wbkgd(menu_bar,COLOR_PAIR(2));    
    waddstr(menu_bar,"Temperature");  
    wattron(menu_bar,COLOR_PAIR(3));
    waddstr(menu_bar," F3 ");
    wattroff(menu_bar,COLOR_PAIR(3)); 
    wmove(menu_bar,0,20);       
    waddstr(menu_bar,"Hysteresis");
    wattron(menu_bar,COLOR_PAIR(3));
    waddstr(menu_bar," F4 ");
    wattroff(menu_bar,COLOR_PAIR(3));
    refresh();
}

/*!
 * @brief Function used to print the commands
 */ 
void print_commands(int line)
{
    move(line,1);
    printw("Commands:");
    move(++line,4);
    printw("F2: get potentiometer value for reference temperature");
    move(++line,4);
    printw("F3: set reference temperature");
    move(++line,4);
    printw("F4: set hysteresis");
    move(++line,5);
    printw("^: up");
    move(++line,5);
    printw("v: down");
    move(++line,1);
    printw("Enter: select");
    move(++line,3);
    printw("Esc: exit");
    refresh();
}

/*!
 * @brief Function used to print the instructions
 */ 
void print_instructions(int line)
{
    move(line,1);
    printw("Instructions:");
    move(++line,4);
    printw("1 - select f2 or f3 to set the reference temperature");
    move(++line,4);
    printw("2 - select f4 to set the hysteresis");
}

/*!
 * @brief Function used to draws menu items when the F3 or F4 keys are pressed
 */ 
WINDOW **create_items(int column, int number_items, int first_value)
{
    WINDOW **menu_items;
    menu_items=(WINDOW **)malloc((number_items+1)*sizeof(WINDOW *));
    menu_items[0]=newwin(number_items+2,20,1,column);

    wbkgd(menu_items[0],COLOR_PAIR(2));
    box(menu_items[0],ACS_VLINE,ACS_HLINE);

    for (int i = 1; i <= number_items; i++)
    {
        menu_items[i]=subwin(menu_items[0],1,17,i+1,column+1);
    }

    for (int i = 0; i < number_items; i++)
    {
        wprintw(menu_items[i+1],"   %.2f oC",(float)(i+first_value));
    }
    wbkgd(menu_items[1],COLOR_PAIR(1));
    wrefresh(menu_items[0]);
    return menu_items;
}

/*!
 * @brief Function that delet the menu items 
 */ 
void deletaritensmenu(WINDOW **menu_items, int number_items)
{
    for (int i = 0; i <= number_items; i++)
    {
        delwin(menu_items[i]);
    }
    free(menu_items);
}

/*!
 * @brief Function used to scroll
 */ 
float scrollmenu(WINDOW **menu_items, int number_items, int column, int first_value) 
{
    int key;
    int selected=0;
    while (1)
    {
        key=getch();
        if (key==KEY_DOWN || key==KEY_UP)
        {
            wbkgd(menu_items[selected+1],COLOR_PAIR(2));
            wnoutrefresh(menu_items[selected+1]);
            if (key==KEY_DOWN)
            {
                selected=(selected+1) % number_items;
            } else
            {
                selected=(selected+number_items-1) % number_items;
            }
            wbkgd(menu_items[selected+1],COLOR_PAIR(1));
            wnoutrefresh(menu_items[selected+1]);
            doupdate();
        }
        else if (key==ENTER)
        {
            return (float)(selected+first_value);
        }
    }
}

/*!
 * @brief Function that create the menu 
 */ 
void menu ()
{
    create_menu_bar();
    print_commands(FIRST_LINE_COMMANDS);
    print_instructions(FIRST_LINE_INSTRUCTIONS);
}

/*!
 * @brief Function that initialize the window 
 */ 
void initialize_window ()
{
    initscr();      //Init the ncurses
    start_color();
    /* Definition color pairs*/
    init_pair(1,COLOR_CYAN,COLOR_BLACK);
    init_pair(2,COLOR_BLACK,COLOR_CYAN);
    init_pair(3,COLOR_RED,COLOR_CYAN);  

    cbreak(); // Disable line buffering, gimme every thing
    curs_set(0);  // invisible cursor
    noecho();   
    keypad(stdscr,TRUE);  // active the function keypads 
    bkgd(COLOR_PAIR(1));

    menu();
    windows.message=subwin(stdscr,1,COLS/2,23,1);
}

/*!
 *  @brief Thread function to user input 
 */
void *input_values (void *args)
{
    Data *data = (Data *)args;
    WINDOW **temperature_values, **hysteresis_values;
    int key;
    while (1)
    {
        key = getch();
        werase(windows.message);
        wrefresh(windows.message);
        switch (key)
        {
        case KEY_F(2):
            data->potentiometer = 1;
            wprintw(windows.message,"Get potentiometer value mode",data->reference_temperature);
            touchwin(stdscr);
            refresh();
            break;
        case KEY_F(3):
            data->potentiometer = 0;
            temperature_values = create_items(0, NTEMPERATURE_VALUES, TEMPERATURE_FIRST_VALUE);
            data->reference_temperature = scrollmenu(temperature_values, NTEMPERATURE_VALUES, FIRST_COLUMN_MENU, TEMPERATURE_FIRST_VALUE);
            deletaritensmenu(temperature_values, NTEMPERATURE_VALUES);
            wprintw(windows.message,"Updated Reference Temperature: %.2f oC",data->reference_temperature);
            touchwin(stdscr);
            refresh();
            break;
        
        case KEY_F(4):
            hysteresis_values = create_items(20, NHYSTERESIS_VALUES, HYSTERESIS_FIRST_VALUE);
            data->hysteresis = scrollmenu(hysteresis_values, NHYSTERESIS_VALUES, 20, HYSTERESIS_FIRST_VALUE);
            deletaritensmenu(hysteresis_values, NHYSTERESIS_VALUES);
            wprintw(windows.message,"Updated Hysteresis: %.2f oC", data->hysteresis);
            touchwin(stdscr);
            refresh();
            break;
        case ESCAPE:
            return NULL;
            break;
        }
    }
}

/*!
 *  @brief Thread function that shows the values ​​on the screen
 */
void *output_values (void *args)
{
    Data *data = (Data *)args;
    int line = 2;
    
    move(line,COLS/2);
    printw("Internal Temperature: %.2f oC", data->internal_temperature);
    move(++line,COLS/2);
    printw("External Temperature: %.2f oC", data->external_temperature);
    move(++line,COLS/2);
    move(line,COLS/2);
    printw("Reference Temperature: %.2f oC", data->reference_temperature);
    move(++line,COLS/2);
    printw("Hysteresis: %.2f oC", data->hysteresis);
    refresh();
    return NULL;
}

/*!
 *  @brief Thread function that ends the window
 */
void end_window() 
{
    delwin(windows.menu_bar);
    delwin(windows.message);
    endwin();
}