/******************************************************************************/
/*                       Header includes                                      */

#include <pthread.h>
#include <bcm2835.h>
#include <unistd.h>

#include "actuator.h"
#include "sensor.h"
#include "data.h"

/******************************************************************************/
/*! @file thread.c
 * @brief Interface for threads
 */
#include "thread.h"

/****************************************************************************/
/*!                        Global Statements                                */

pthread_t actuator_thread;
pthread_t sensor_thread;

int count = 0;

Data data;

/****************************************************************************/
/*!                         Functions                                       */

/*!
 * @brief Function to handle program interuption.
 */
void alarm_handler(int signum)
{   
    if ((data.reference_temperature || data.potentiometer) && (data.hysteresis))
    {
        count++;
        pthread_join(actuator_thread, NULL);
        pthread_join(sensor_thread, NULL);

        if(pthread_create(&actuator_thread, NULL, actuators_control, (void *) &data))
        {
            printf("actuator_thread\n");
            reset();
        }
        
        if (count == 5)
        {
            pthread_create(&sensor_thread, NULL, update_data_sensor, (void *) &data);
            count = 0;
        }
    }
}

/*!
 * @brief Function to handle program interuption.
 */
void sig_handler (int signal)
{
    alarm(0);
    pthread_join(actuator_thread, NULL);
    pthread_join(sensor_thread, NULL);
    bcm2835_close();
    exit(0);
}

/*!
 * @brief Function to init the main thread.
 */
void initialize_threads()
{
    data.temperature = 0.0f;

    ualarm(500000, 500000);
}
