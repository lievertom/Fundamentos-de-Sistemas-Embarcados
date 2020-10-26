/******************************************************************************/
/*                       Header includes                                      */

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include "tcp_server.h"
#include "window.h"
#include "data.h"

/******************************************************************************/
/*! @file thread.c
 * @brief Interface for threads
 */
#include "thread.h"

/****************************************************************************/
/*!                        Global Statements                                */

pthread_t output_thread;
pthread_t input_thread;
pthread_t receive_thread;
pthread_t send_thread;

Data data;

/****************************************************************************/
/*!                         Functions                                       */

/*!
 * @brief Function used to reset the threads.
 */
// void reset ()
// {
//     pthread_cancel(output_thread);
// }

/*!
 * @brief Function to handle program interuption.
 */
void alarm_handler(int signum)
{   
    pthread_join(output_thread, NULL);
    pthread_join(send_thread, NULL);

    pthread_create(&output_thread, NULL, output_values, (void *) &data);        
    pthread_create(&send_thread, NULL, submit, (void *) &data);        
}

/*!
 * @brief Function to handle program interuption.
 */
void sig_handler (int signal)
{
    alarm(0);
    pthread_cancel(receive_thread);
    pthread_join(send_thread, NULL);
    pthread_join(output_thread, NULL);
    end_window();
    close(data.client_socket);    
    close(data.server_socket);
    exit(0);
}

/*!
 * @brief Function to init the main thread.
 */
void initialize_threads()
{
    data.alarm[0] = 1;
    data.alarm[1] = 1;
    data.lamp = 255;
    data.air_turn = 255;
    data.open_sensor = 255;
    data.presence_sensor = 255;
    data.client_socket = 0;


    printf("waiting connection ...\n");

    initialize_tcp_server(&data);
    initialize_window();
    
    if (pthread_create(&input_thread, NULL, input_values, (void *) &data))
    {
        printf("Fail to create input thread\n");
        exit(1);
    }

    if(pthread_create(&receive_thread, NULL, receive, (void *) &data))
    {
        printf("Fail to create receive_thread\n");
        exit(2);
    }

    alarm(1);

    pthread_join(input_thread, NULL);
}
