#include <stdio.h>
#include "bme280_interface.h"
#include "data.h"


/*!
 * @brief This function starts execution of the program.
 */
int main(int argc, char* argv[])
{
    struct Data data;
    data.input_temperature = input_temperature();


    if (data.input_temperature > data.internal_temperature)
    {
        // ligar resistencia
        // desligar ventilador
    }
    else
        // desligar resistencia
        

    return 0;
}