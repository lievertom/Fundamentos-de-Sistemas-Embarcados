#ifndef DATA_H_
#define DATA_H_

#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#define PATH_DATA "dat/data.csv"
#define DATE_SIZE 11
#define HOUR_SIZE 9


/****************************************************************************/
/*!                            Structs                                      */
typedef struct Data 
{
    float internal_temperature;
    float external_temperature;
    float reference_temperature;
    float hysteresis;
    int potentiometer;
} Data;

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
void *save_data (void *args);



#endif /* DATA_H_ */
