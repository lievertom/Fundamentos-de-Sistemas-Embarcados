#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#include "gpio.h"

#define FAN RPI_V2_GPIO_P1_40 // BCM 21
#define RESISTANCE RPI_V2_GPIO_P1_38 // BCM 20
#define ON 1
#define OFF 0

void configuration()
{
    bcm2835_gpio_fsel(FAN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(RESISTANCE, BCM2835_GPIO_FSEL_OUTP);
}

void shut_down(int signal)
{
    on_off(OFF, OFF);
    bcm2835_close();
    exit(0);
}

void gpio()
{
    if (!bcm2835_init())
      exit(1);
      
    configuration();

    signal(SIGINT, shut_down);
}

void on_off(int fan, int resistance)
{
    bcm_gpio_write(FAN, fan);
    bcm_gpio_write(RESISTANCE, resistance);
}
