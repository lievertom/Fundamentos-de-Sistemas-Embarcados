/******************************************************************************/
/*                       Header includes                                      */

#include <bcm2835.h>
#include <stdlib.h>
#include <stdio.h>

#include "data.h"

/******************************************************************************/
/*! @file gpio.c
 * @brief Interface for actuator in GPIO
 */
#include "gpio.h"

/****************************************************************************/
/*!                         Functions                                       */

/*!
 * @brief This function configure gpio ports as an outlet for the fan and resistance.
 */
void configuration()
{
    bcm2835_gpio_fsel(FAN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(RESISTANCE, BCM2835_GPIO_FSEL_OUTP);
}

/*!
 * @brief This function initialize the actuators.
 */
void initialize_actuators()
{
    if (!bcm2835_init())
    {
        exit(1);
    }
    configuration();
}

/*!
 * @brief This function turn on or off the actuators.
 */
void on_off_actuators(int fan, int resistance)
{
    bcm2835_gpio_write(FAN, fan);
    bcm2835_gpio_write(RESISTANCE, resistance);
}

/*!
 * @brief Thread function that controls the actuators.
 */
void *actuators_control (void *args)
{
    Data *data = (Data *) args;
    if (data->reference_temperature && data->hysteresis)
    {
        if (data->internal_temperature <= data->external_temperature)
        {
            on_off_actuators(OFF, OFF);
        }
        else if (data->internal_temperature > (data->reference_temperature+data->hysteresis/2))
        {
            on_off_actuators(ON, OFF);
        }
        else if (data->internal_temperature < (data->reference_temperature-data->hysteresis/2))
        {
            on_off_actuators(OFF, ON);
        }
        else
        {
            on_off_actuators(OFF, OFF);
        }
    }
    return NULL;
}