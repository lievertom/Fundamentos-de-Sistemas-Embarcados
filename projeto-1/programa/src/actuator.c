#include <stdio.h>
#include <stdlib.h>
/* Header includes */
#include <bcm2835.h>

#include "actuator.h"

void configuration()
{
    bcm2835_gpio_fsel(FAN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(RESISTANCE, BCM2835_GPIO_FSEL_OUTP);
}

void shut_down(int signal)
{
    on_off_actuators(OFF, OFF);
    bcm2835_close();
    exit(0);
}

void initialize_actuators()
{
    if (!bcm2835_init())
      exit(1);
      
    configuration();

}

void on_off_actuators(int fan, int resistance)
{
    bcm2835_gpio_write(FAN, fan);
    bcm2835_gpio_write(RESISTANCE, resistance);
}
