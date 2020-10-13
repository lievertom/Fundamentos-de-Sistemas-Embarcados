#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

//Constastes das teclas ENTER e ESCAPE.
#define ENTER          10
#define ESCAPE         27
 
#define NTEMPERATURE_VALUES 41
#define TEMPERATURE_FIRST_VALUE 10

#define NHYSTERESIS_VALUES 10
#define HYSTERESIS_FIRST_VALUE 0

#define NLINES_MENU    1
#define NCOLUMNS_MENU  80
#define FIRST_LINE     0
#define FIRST_COLUMN   0

void create_menu_bar(WINDOW *menu_bar)  //Função encarregada de criar um menu em nosso sistema
{
    wbkgd(menu_bar,COLOR_PAIR(2));    //Alterando a cor de fundo do menu
    waddstr(menu_bar,"Temperature");    //Esta função escreve os nomes dos menus
    wattron(menu_bar,COLOR_PAIR(3));  //Alterando o par de cores para 3
    waddstr(menu_bar," F3 ");
    wattroff(menu_bar,COLOR_PAIR(3)); //Retornando para o par de cor 2.
    wmove(menu_bar,0,20);            // Posiciona o cursor na linha 0, coluna 20
    waddstr(menu_bar,"Hysteresis");
    wattron(menu_bar,COLOR_PAIR(3));
    waddstr(menu_bar," F4 ");
    wattroff(menu_bar,COLOR_PAIR(3));
    refresh();
}

void print_commands()
{
    move(2,1);
    printw("Commands:");
    move(3,3);
    printw("F2: get potentiometer value for reference temperature");
    move(4,3);
    printw("F3: set reference temperature");
    move(5,3);
    printw("F4: set hysteresis");
    move(6,2);
    printw("ESC: exit");
    refresh();
}

WINDOW **create_items(int column, int number_items, int first_value)  //Desenha os ítens do menu quando as teclas F1 ou F2 for pressionada
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

void deletaritensmenu(WINDOW **menu_items, int number_items) //Apaga os ítens da menu criado pela função acima
{
    for (int i = 0; i <= number_items; i++)
    {
        delwin(menu_items[i]);
    }
    free(menu_items);
}


float scrollmenu(WINDOW **menu_items, int number_items, int column, int first_value) //Permite fazer scroll entre e dentro dos menus
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
        else if (key==ESCAPE)
        {
            return -1.0f;
        }
        else if (key==ENTER)
        {
            return (float)(selected+first_value);
        }
    }
}

int main()
{
    //Inicializações---------------------------------------------
    initscr();      //Inicializando a ncurses
    start_color();  //Tornando o uso das cores possíveis

    //Definição dos pares de cores
    init_pair(1,COLOR_CYAN,COLOR_BLACK);
    init_pair(2,COLOR_BLACK,COLOR_CYAN);
    init_pair(3,COLOR_RED,COLOR_CYAN);  

    cbreak(); // Disable line buffering, gimme every thing
    curs_set(0);  //Faz com que o cursor físico fique invisível.
    noecho();     //Impede que as teclas apareçam na tela
    keypad(stdscr,TRUE);  //Ativa as teclas de função
    //-----------------------------------------------------------
 
    WINDOW **temperature_values, **hysteresis_values;
    WINDOW *menu_bar,*mensagem;
    
    bkgd(COLOR_PAIR(1));

    menu_bar=subwin(stdscr,NLINES_MENU, COLS, FIRST_LINE, FIRST_COLUMN);
    create_menu_bar(menu_bar);


    mensagem=subwin(stdscr,1,79,23,1);

    print_commands();

    float reference_temperature = 30.0f;
    float hysteresis;
    int key;


    do {
        key=getch();
        werase(mensagem);
        wrefresh(mensagem);
        if (key==KEY_F(3))
        {
            temperature_values = create_items(0, NTEMPERATURE_VALUES, TEMPERATURE_FIRST_VALUE);
            reference_temperature = scrollmenu(temperature_values, NTEMPERATURE_VALUES, FIRST_COLUMN, TEMPERATURE_FIRST_VALUE);
            deletaritensmenu(temperature_values, NTEMPERATURE_VALUES);
            if (reference_temperature<0.0f)
                wprintw(mensagem,"Invalid Reference Temperature");
            else
                wprintw(mensagem,"Reference Temperature: %.2f",reference_temperature);
            touchwin(stdscr);
            refresh();
        }
        else if (key==KEY_F(4))
        {
            hysteresis_values = create_items(20, NHYSTERESIS_VALUES, HYSTERESIS_FIRST_VALUE);
            hysteresis = scrollmenu(hysteresis_values, NHYSTERESIS_VALUES, 20, HYSTERESIS_FIRST_VALUE);
            deletaritensmenu(hysteresis_values, NHYSTERESIS_VALUES);
            if (hysteresis < 0.0f)
                wprintw(mensagem,"Invalid Hysteresis");
            else
                wprintw(mensagem,"Hysteresis: %.2f", hysteresis);
            touchwin(stdscr);
            refresh();
        }
    } while (key!=ESCAPE);

    delwin(menu_bar);
    delwin(mensagem);
    endwin();
    return 0;
}