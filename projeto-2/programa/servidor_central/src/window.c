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
WINDOW *menu_bar;

const char *key_function[] = {
    " F0 ",
    " F1 ",
    " F2 ",
    " F3 ",
    " F4 ",
    " F5 ",
    " F6 ",
    " F7 ",
    " F8 "
};

const char *message[] = 
{
    "on",
    "off",
    "open",
    "closed",
    "enabled",
    "disabled"
};

/****************************************************************************/
/*!                         Functions                                       */


void create_button_lamp ()
{
    for (int i = 1; i <= NLAMP; i++)
    {
        char string[] = "lamp x";
        string[5] = '0'+i;
        wattron(menu_bar,COLOR_PAIR(2));
        waddstr(menu_bar, string);
        wattron(menu_bar,COLOR_PAIR(3));
        waddstr(menu_bar, key_function[i+1]);
        wattroff(menu_bar,COLOR_PAIR(3));
        wmove(menu_bar,0,i*BUTTON_SIZE);
    }
}

void create_button_air()
{
    for (int i = 1; i <= NAIR; i++)
    {
        char string[] = "air x ";
        string[4] = '0'+i;
        wattron(menu_bar,COLOR_PAIR(2));
        waddstr(menu_bar, string);
        wattron(menu_bar,COLOR_PAIR(5));
        waddstr(menu_bar, key_function[i+1+NLAMP]);
        wattroff(menu_bar,COLOR_PAIR(5));
        wmove(menu_bar,0,(NLAMP+i)*BUTTON_SIZE);
    }
} 

void create_button_alarm()
{
    wattron(menu_bar,COLOR_PAIR(2));
    waddstr(menu_bar, "alarm ");
    wattron(menu_bar,COLOR_PAIR(3));
    waddstr(menu_bar, key_function[8]);
    wattroff(menu_bar,COLOR_PAIR(3));
}

bool turn_button(unsigned char key, Data *data)
{
    bool auxiliary;
    wmove(menu_bar,FIRST_LINE_MENU,key*BUTTON_SIZE+6);
    if (key == 6) 
    {
        data->alarm[0] = !data->alarm[0];
        auxiliary = data->alarm;
    }
    else
    {
        data->lamp ^= (1<<key);
        auxiliary = data->lamp & (1<<key);
    }
    
    if (auxiliary)
    {
        wattron(menu_bar,COLOR_PAIR(3));
        waddstr(menu_bar, key_function[key+2]);
        wattroff(menu_bar,COLOR_PAIR(3));
    }
    else
    {
        wattron(menu_bar,COLOR_PAIR(4));
        waddstr(menu_bar, key_function[key+2]);
        wattroff(menu_bar,COLOR_PAIR(4));
    }
    return auxiliary;
}

/*!
 * @brief Function used to create the menu bar
 */  
void create_menu_bar()
{
    menu_bar=subwin(stdscr,NLINES_MENU, COLS, FIRST_LINE_MENU, FIRST_COLUMN_MENU);
    create_button_lamp(); 
    create_button_air(); 
    create_button_alarm();
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
    printw("F2: turn on or off kitchen lamp");
    move(++line,4);
    printw("F3: turn on or off room lamp");
    move(++line,4);
    printw("F4: turn on or off bedroom 1 lamp");
    move(++line,4);
    printw("F5: turn on or off bedroom 2 lamp");
    move(++line,4);
    printw("F6: set bedroom 1 temperature or Del to turn off");
    move(++line,4);
    printw("F7: set bedroom 2 temperature or Del to turn off");
    move(++line,4);
    printw("F8: turn on or off alarm");
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
    move(++line,3);
    printw("red: switched off");
    move(++line,1);
    printw("green: switched on");
}

/*!
 * @brief Function used to draws menu items when the F3 or F4 keys are pressed
 */ 
WINDOW **create_items(int column, int number_items, int first_value)
{
    WINDOW **menu_items;
    menu_items=(WINDOW **)malloc((number_items+1)*sizeof(WINDOW *));
    menu_items[0]=newwin(number_items+2,BUTTON_SIZE-2,1,column);

    wbkgd(menu_items[0],COLOR_PAIR(2));
    box(menu_items[0],ACS_VLINE,ACS_HLINE);

    for (int i = 1; i <= number_items; i++)
    {
        menu_items[i]=subwin(menu_items[0],1,BUTTON_SIZE-4,i+1,column+1);
    }

    for (int i = 0; i < number_items; i++)
    {
        wprintw(menu_items[i+1]," %.d oC",i+first_value);
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
        else if (key==KEY_DC)
        {
            return AIR_OFF;
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
    init_pair(3,COLOR_WHITE,COLOR_RED);  
    init_pair(4,COLOR_WHITE,COLOR_GREEN);  
    init_pair(5,COLOR_WHITE,COLOR_BLUE);  

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
    Data *data = (Data *) args;
    WINDOW **air_1, **air_2;
    int key;
    bool auxiliary;
    while (1)
    {
        key = getch();
        werase(windows.message);
        wrefresh(windows.message);
        switch (key)
        {
        case KEY_F(2):
            auxiliary = turn_button(0, data);
            wprintw(windows.message,"kitchen lamp %s", message[auxiliary ? 1 : 0]);
            touchwin(stdscr);
            refresh();
            break;
        case KEY_F(3):
            auxiliary = turn_button(1, data);
            wprintw(windows.message,"room lamp %s", message[auxiliary ? 1 : 0]);
            touchwin(stdscr);
            refresh();
            break;
        case KEY_F(4):
            auxiliary = turn_button(2, data);
            wprintw(windows.message,"bedroom 1 lamp %s", message[auxiliary ? 1 : 0]);
            touchwin(stdscr);
            refresh();
            break;
        case KEY_F(5):
            auxiliary = turn_button(3, data);
            wprintw(windows.message,"bedroom 2 lamp %s", message[auxiliary ? 1 : 0]);
            touchwin(stdscr);
            refresh();
            break;
        case KEY_F(6):
            air_1 = create_items(NLAMP*BUTTON_SIZE, NTEMPERATURE_VALUES, TEMPERATURE_FIRST_VALUE);
            data->air_reference_temperature[0] = scrollmenu(air_1, NTEMPERATURE_VALUES, FIRST_COLUMN_MENU, TEMPERATURE_FIRST_VALUE);
            deletaritensmenu(air_1, NTEMPERATURE_VALUES);
            wprintw(windows.message,"Updated Reference Temperature: %.2f oC",data->air_reference_temperature[0]);
            touchwin(stdscr);
            refresh();
            break;
        case KEY_F(7):
            air_2 = create_items((NLAMP+1)*BUTTON_SIZE, NTEMPERATURE_VALUES, TEMPERATURE_FIRST_VALUE);
            data->air_reference_temperature[1] = scrollmenu(air_2, NTEMPERATURE_VALUES, FIRST_COLUMN_MENU, TEMPERATURE_FIRST_VALUE);
            deletaritensmenu(air_2, NTEMPERATURE_VALUES);
            wprintw(windows.message,"Updated Reference Temperature: %.2f oC",data->air_reference_temperature[1]);
            touchwin(stdscr);
            refresh();
            break;
        case KEY_F(8):
            auxiliary = turn_button(6, data);
            wprintw(windows.message,"alarm %s", message[auxiliary ? 1 : 0]);
            touchwin(stdscr);
            refresh();
            break;
        case ESCAPE:
            return NULL;
        }
    }
}

/*!
 *  @brief Thread function that shows the values ​​on the screen
 */
void *output_values (void *args)
{
    Data *data = (Data *) args;
    while (1)
    {
    int line = 2;
    
    move(line,BUTTON_SIZE*6);
    printw("Room");
    move(++line,BUTTON_SIZE*6+2);
    printw("Temperature: %.2f oC", data->temperature[1]);
    move(++line,BUTTON_SIZE*6+2);
    printw("Humidity: %.2f", data->humidity[1]);
    move(++line,BUTTON_SIZE*6+2);
    printw("Presence Sensor: %s", message[4+(data->presence_sensor&1 ? 1 : 0)]);
    move(++line,BUTTON_SIZE*6+2);
    printw("Window: %s", message[2+(data->open_sensor&(1<<3) ? 1 : 0)]);
    move(++line,BUTTON_SIZE*6+2);
    printw("Door: %s", message[2+(data->open_sensor&(1<<2) ? 1 : 0)]);
    
    line += 2;
    move(line,BUTTON_SIZE*6);
    printw("Kitchen");
    move(++line,BUTTON_SIZE*6+2);
    printw("Temperature: %.2f oC", data->temperature[0]);
    move(++line,BUTTON_SIZE*6+2);
    printw("Humidity: %.2f", data->humidity[0]);
    move(++line,BUTTON_SIZE*6+2);
    printw("Presence Sensor: %s", message[4+(data->presence_sensor&(1<<1) ? 1 : 0)]);
    move(++line,BUTTON_SIZE*6+2);
    printw("Window: %s", message[2+(data->open_sensor&(1<<1) ? 1 : 0)]);
    move(++line,BUTTON_SIZE*6+2);
    printw("Door: %s", message[2+(data->open_sensor&1 ? 1 : 0)]);
    
    line += 2;
    move(line,BUTTON_SIZE*6);
    printw("Bedroom 1");
    move(++line,BUTTON_SIZE*6+2);
    printw("air conditioning: %s", message[(data->air_turn&1 ? 1 : 0)]);
    move(++line,BUTTON_SIZE*6+2);
    printw("Temperature: %.2f oC", data->temperature[2]);
    move(++line,BUTTON_SIZE*6+2);
    printw("Humidity: %.2f", data->humidity[2]);
    move(++line,BUTTON_SIZE*6+2);
    printw("Window: %s", message[2+(data->open_sensor&(1<<4) ? 1 : 0)]);
    
    line += 2;
    move(line,BUTTON_SIZE*6);
    printw("Bedroom 2");
    move(++line,BUTTON_SIZE*6+2);
    printw("air conditioning: %s", message[(data->air_turn&(1<<1) ? 1 : 0)]);
    move(++line,BUTTON_SIZE*6+2);
    printw("Temperature: %.2f oC", data->temperature[3]);
    move(++line,BUTTON_SIZE*6+2);
    printw("Humidity: %.2f", data->humidity[3]);
    move(++line,BUTTON_SIZE*6+2);
    printw("Window: %s", message[2+(data->open_sensor&(1<<5) ? 1 : 0)]);
    sleep(1);
    refresh();
    }
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