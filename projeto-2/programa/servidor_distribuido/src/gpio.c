/******************************************************************************/
/*                       Header includes                                      */

#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <bcm2835.h>
#include <sys/mman.h>

#include "data.h"
#include "control.h"

/******************************************************************************/
/*! @file gpio.c
 * @brief Interface for actuator in GPIO
 */
#include "gpio.h"

/****************************************************************************/
/*!                         Functions                                       */

/*!
 * @brief This function configure the gpio ports.
 */
void configuration()
{
    bcm2835_gpio_fsel(AC_1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(AC_2, BCM2835_GPIO_FSEL_OUTP);

    bcm2835_gpio_fsel(LAMP_1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LAMP_2, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LAMP_3, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LAMP_4, BCM2835_GPIO_FSEL_OUTP);

    bcm2835_gpio_fsel(OPEN_SENSOR_1, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(OPEN_SENSOR_2, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(OPEN_SENSOR_3, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(OPEN_SENSOR_4, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(OPEN_SENSOR_5, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(OPEN_SENSOR_6, BCM2835_GPIO_FSEL_INPT);

    bcm2835_gpio_fsel(PRESENCE_SENSOR_1, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(PRESENCE_SENSOR_2, BCM2835_GPIO_FSEL_INPT);
}

/*!
 * @brief This function initialize the actuators.
 */
void initialize_gpio()
{
    // const struct sched_param priority = {1};
    // sched_setscheduler(0, SCHED_FIFO, &priority);
    // mlockall(MCL_CURRENT | MCL_FUTURE);

    if (!bcm2835_init())
    {
        printf("Error in bcm2835_init");
        exit(1);
    }
    configuration();
}

/*!
 * @brief This function turn on or off.
 */
void turn_on_off(int device, int turn)
{
    bcm2835_gpio_write(device, turn);
}

/*!
 * @brief Thread function that controls the actuators.
 */
void *ac_control (void *args)
{
    Data *data = (Data *) args;

    if (data->air_reference_temperature > 0.0f &&
        data->air_reference_temperature+HYSTERERIS/2 <= data->temperature)
    {
        data->air_turn |= 1<<8;
    }
    else
    {
        data->air_turn &= 0<<8;
    }

    if (data->air_reference_temperature > 0.0f && 
        data->air_reference_temperature-HYSTERERIS/2 <= data->temperature &&
        data->air_turn ^ 1<<8)
    {
        if (data->air_turn ^ 1<<0)
        {
            turn_on_off(AC_1, ON);
            turn_on_off(AC_2, ON);
            for(int i = 0; i < NAC; i++)
                data->air_turn |= 1<<i;
        }
    }
    else
    {
        if (data->air_turn & 1<<0)
        {
            turn_on_off(AC_1, OFF);
            turn_on_off(AC_2, OFF);
            for(int i = 0; i < NAC; i++)
                data->air_turn &= 0<<i;
        }
    }
    return NULL;
}

/*!
 * @brief Thread function that controls the actuators.
 */
void *lamp_control (void *args)
{
    Data *data = (Data *) args;
    turn_on_off(LAMP_1, data->lamp & 1<<0);
    turn_on_off(LAMP_2, data->lamp & 1<<1);
    turn_on_off(LAMP_3, data->lamp & 1<<2);
    turn_on_off(LAMP_4, data->lamp & 1<<3);
    return NULL;
}

void *sensor_control (void *args)
{
    Data *data = (Data *) args;
    Send data_send;

    data_send.open_sensor = 0;

    data_send.open_sensor |= bcm2835_gpio_lev(OPEN_SENSOR_1)<<0;
    data_send.open_sensor |= bcm2835_gpio_lev(OPEN_SENSOR_2)<<1;
    data_send.open_sensor |= bcm2835_gpio_lev(OPEN_SENSOR_3)<<2;
    data_send.open_sensor |= bcm2835_gpio_lev(OPEN_SENSOR_4)<<3;
    data_send.open_sensor |= bcm2835_gpio_lev(OPEN_SENSOR_5)<<4;
    data_send.open_sensor |= bcm2835_gpio_lev(OPEN_SENSOR_6)<<5;

    data_send.presence_sensor = 0;

    data_send.presence_sensor |= bcm2835_gpio_lev(PRESENCE_SENSOR_1)<<0;
    data_send.presence_sensor |= bcm2835_gpio_lev(PRESENCE_SENSOR_2)<<1;

    if (data_send.open_sensor != data->open_sensor ||
            data_send.presence_sensor != data->presence_sensor)
    {
        data->open_sensor = data_send.open_sensor;
        data->presence_sensor = data_send.presence_sensor;
        push();
    }
    return NULL;
}