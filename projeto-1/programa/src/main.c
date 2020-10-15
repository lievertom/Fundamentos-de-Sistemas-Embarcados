/******************************************************************************/
/*                       Header includes                                      */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>

#include "external_sensor.h"
#include "actuator.h"
#include "window.h"
#include "thread.h"
#include "uart.h"
#include "lcd.h"

/****************************************************************************/
/*                            Main                                          */

/*!
 * @brief This function starts execution of the program.
 */
int main(int argc, char* argv[])
{   
    signal(SIGALRM, alarm_handler); 
    signal(SIGTERM, sig_handler);
    signal(SIGKILL, sig_handler);
    signal(SIGSTOP, sig_handler);
    signal(SIGINT, sig_handler);

    initialize_external_sensor();
    initialize_actuators();
    initialize_window();
    initialize_lcd();
    
    initialize_threads();

    sig_handler(SIGINT);

    return 0;
}
