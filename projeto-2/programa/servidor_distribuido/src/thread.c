/******************************************************************************/
/*                       Header includes                                      */

#include <pthread.h>
#include <bcm2835.h>
#include <unistd.h>

#include "data.h"
#include "gpio.h"
#include "sensor.h"
#include "tcp.h"

/******************************************************************************/
/*! @file thread.c
 * @brief Interface for threads
 */
#include "thread.h"

/****************************************************************************/
/*!                        Global Statements                                */

pthread_t ac_thread;
pthread_t lamp_thread;
pthread_t send_thread;
pthread_t alarm_thread;
pthread_t sensor_thread;
pthread_t receive_thread;

int count = 0;

Data data;

/****************************************************************************/
/*!                         Functions                                       */

/*!
 * @brief Function to handle program interuption.
 */
void alarm_handler(int signum)
{   
    count++;
    pthread_join(alarm_thread, NULL);
    pthread_create(&alarm_thread, NULL, sensor_control, (void *) &data);
    
    if (count == 5)
    {
        pthread_join(ac_thread, NULL);
        pthread_join(lamp_thread, NULL);
        pthread_join(sensor_thread, NULL);

        pthread_create(&ac_thread, NULL, ac_control, (void *) &data);
        pthread_create(&lamp_thread, NULL, lamp_control, (void *) &data);
        pthread_create(&sensor_thread, NULL, update_data_sensor, (void *) &data);
        count = 0;
    }
}

/*!
 * @brief Function to handle program interuption.
 */
void sig_handler (int signal)
{
    alarm(0);
    pthread_join(ac_thread, NULL);
    pthread_join(lamp_thread, NULL);
    pthread_join(sensor_thread, NULL);
    pthread_cancel(receive_thread);
    close(data.server_socket);    
    bcm2835_close();
    exit(0);
}

/*!
 * @brief Function to init the main thread.
 */
void initialize_threads()
{
    initialize_tcp_server(&data);

    pthread_create(&receive_thread, NULL, receive, (void *) &data);

    ualarm(200000, 200000);
    
    pthread_join(receive_thread, NULL);
}

void push()
{
    pthread_join(send_thread, NULL);
    pthread_create(&send_thread, NULL, submit, (void *) &data);
}