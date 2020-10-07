#ifndef DATA_H_
#define DATA_H_

#include <stdio.h>

#include "bme280.h"
#include "uart.h"

#define POTENTIOMETER 0xA1
#define TERMINATOR 0x00

struct Data
{
    char * date;
    char * hour;
    float internal_temperature;
    float external_temperature;
    float input_temperature;
};


/****************************************************************************/
/*!                         Functions                                       */

/*!
 *  @brief Function that 
 *
 * @param[in] period              : Delay in microseconds.
 * @param[in, out] intf_ptr       : Void pointer that can enable the linking of descriptors
 *                                  for interface related call backs
 *  @return void.
 *
 */
float input_temperature()
{
    float temperature;
    int control_input = 0;

    if (control_input)
    {
        scanf("%f", &temperature); 
    }
    else
    {
        unsigned char command[] = {POTENTIOMETER, TERMINATOR};
        temperature = uart(command);
    }
    return temperature;
}


#endif /* DATA_H_ */
