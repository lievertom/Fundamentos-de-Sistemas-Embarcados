#include <stdio.h>
#include <stdlib.h>
/* Header includes */
#include <bcm2835.h>

#include "data.h"

#include "actuator.h"

void configuration()
{
    bcm2835_gpio_fsel(FAN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(RESISTANCE, BCM2835_GPIO_FSEL_OUTP);
}

void initialize_actuators()
{
    if (!bcm2835_init())
    {
        exit(1);
    }
    configuration();
}

void on_off_actuators(int fan, int resistance)
{
    bcm2835_gpio_write(FAN, fan);
    bcm2835_gpio_write(RESISTANCE, resistance);
}

void *actuators_control (void *args)
{
    Data *data = (Data *) args;
    while(1)
    {
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
    }
    // return NULL;
}