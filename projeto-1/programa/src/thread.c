#include <pthread.h>
#include <bcm2835.h>
#include <unistd.h>


#include "external_sensor.h"
#include "actuator.h"
#include "window.h"
#include "thread.h"
#include "uart.h"
#include "lcd.h"


/****************************************************************************/
/*!                        Global Statements                                */

pthread_t actuator_thread;
pthread_t sensor_thread;
pthread_t output_thread;
pthread_t input_thread;
pthread_t save_thread;
pthread_t uart_thread;
pthread_t lcd_thread;
int count = 0;
Data data;

void reset ()
{
    pthread_cancel(output_thread);
    pthread_cancel(sensor_thread);
    pthread_cancel(uart_thread);
    pthread_cancel(lcd_thread);
    pthread_join(save_thread, NULL);
}
void alarm_handler(int signum)
{   
    if ((data.reference_temperature || data.potentiometer) && (data.hysteresis))
    {
        count++;
        // pthread_join(actuator_thread, NULL);
        // if(pthread_create(&actuator_thread, NULL, actuators_control, (void *) &data))
        // {
        //     printf("actuator_thread\n");
        //     reset();
        // }
        pthread_join(uart_thread, NULL);
        if(pthread_create(&uart_thread, NULL, uart, (void *) &data))
        {
            printf("uart_thread\n");
            reset();
        }

        pthread_join(sensor_thread, NULL);
        if(pthread_create(&sensor_thread, NULL, get_external_temperature, (void *) &data))
        {
            printf("sensor_thread\n");
            reset();
        }
        
        
        pthread_join(output_thread, NULL);
        if(pthread_create(&output_thread, NULL, output_values, (void *) &data))
        {
            printf("output_thread\n");
            reset();
        }
        
        if (count == 4)
        {
            pthread_join(lcd_thread, NULL);
            if(pthread_create(&lcd_thread, NULL, print_lcd, (void *) &data))
            {
                printf("lcd_thread\n");
                reset(); 
            }

            pthread_join(save_thread, NULL);
            if(pthread_create(&save_thread, NULL, save_data, (void *) &data))
            {
                printf("save_tread\n");
                reset();
            }
            count = 0;
        }
    }
}

void sig_handler (int signal)
{
    alarm(0);
    pthread_join(output_thread, NULL);
    pthread_join(actuator_thread, NULL);
    pthread_join(sensor_thread, NULL);
    pthread_join(uart_thread, NULL);
    pthread_join(lcd_thread, NULL);
    pthread_join(save_thread, NULL);
    on_off_actuators(OFF, OFF);
    bcm2835_close();
    clear_lcd();
    end_window();
    exit(0);
}

void initialize_threads()
{
    data.reference_temperature = 0.0f;
    data.hysteresis = 0.0f;
    data.potentiometer = 0;

    if (pthread_create(&input_thread, NULL, input_values, (void *) &data))
    {
        printf("Fail to create input thread\n");
        exit(1);
    }

    if(pthread_create(&actuator_thread, NULL, actuators_control, (void *) &data))
    {
        printf("Fail to create actuator thread\n");
        exit(2);
    }

    ualarm(500000, 500000);

    pthread_join(input_thread, NULL);
}
