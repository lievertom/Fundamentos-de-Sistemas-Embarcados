/******************************************************************************/
/*                       Header includes                                      */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>

#include "sensor.h"
#include "thread.h"
#include "gpio.h"

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

    initialize_gpio();
    initialize_sensor();
    
    initialize_threads();

    sig_handler(SIGINT);

    return 0;
}
