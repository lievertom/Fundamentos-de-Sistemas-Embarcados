#include <signal.h>
#include <stdio.h>

#include "external_sensor.h"
#include "uart.h"
#include "actuator.h"
#include "data.h"
#include "lcd.h"

/*!
 * @brief This function starts execution of the program.
 */
int main(int argc, char* argv[])
{   
    signal(SIGINT, shut_down);
    initialize_lcd();
    initialize_actuators();
    initialize_external_sensor();
    struct Data data;
    while(1)
    {   
        int a;
        scanf("%d", &a);
        if (a == 2) on_off_actuators(ON, OFF);
        else on_off_actuators(OFF, ON);
        float te = get_external_temperature();
        float ti = uart(INTERNAL_TEMPERATURE);
        float tr = uart(REFERENCE_TEMPERATURE);

        save_data(&ti, &te, &tr);
        print_lcd(ti, te, tr, 1);


        printf ("TE: %.2f\n", te);
        printf ("TI: %.2f\n", ti);
        printf ("TR: %.2f\n", tr);
    }


    return 0;
}
