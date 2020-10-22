/******************************************************************************/
/*                       Header includes                                      */

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include "window.h"

/******************************************************************************/
/*! @file thread.c
 * @brief Interface for threads
 */
#include "thread.h"

/****************************************************************************/
/*!                        Global Statements                                */

pthread_t output_thread;
pthread_t input_thread;

/****************************************************************************/
/*!                         Functions                                       */

/*!
 * @brief Function used to reset the threads.
 */
void reset ()
{
    pthread_cancel(output_thread);
}

/*!
 * @brief Function to handle program interuption.
 */
void alarm_handler(int signum)
{   
    pthread_join(output_thread, NULL);
    
    if(pthread_create(&output_thread, NULL, output_values, NULL))
    {
        printf("output_thread\n");
        reset();
    }        
}

/*!
 * @brief Function to handle program interuption.
 */
void sig_handler (int signal)
{
    alarm(0);
    pthread_join(output_thread, NULL);
    end_window();
    exit(0);
}

/*!
 * @brief Function to init the main thread.
 */
void initialize_threads()
{
    if (pthread_create(&input_thread, NULL, input_values, NULL))
    {
        printf("Fail to create input thread\n");
        exit(1);
    }

    alarm(1);

    pthread_join(input_thread, NULL);
}
