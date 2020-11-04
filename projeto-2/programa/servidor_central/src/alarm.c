/******************************************************************************/
/*                       Header includes                                      */

#include <stdlib.h>
#include <unistd.h>

#include "data.h"

/******************************************************************************/
/*! @file alarm.c
 * @brief Interface for tcp server
 */
#include "alarm.h"

/****************************************************************************/
/*!                         Functions                                       */

/*!
 * @brief Function to control the alarm.
 */
unsigned char alarm_control(Data *data)
{
    for (int i = 0; i < NOPEN_SENSOR; i++)
        if (data->open_sensor&1<<i)
            return 1;

    for (int i = 0; i < NPRESENCE_SENSOR; i++)
        if (data->presence_sensor&1<<i)
            return 1;

    return 0;
}


void *play_alarm(void *args)
{
    Data *data = (Data *) args;

    if(data->alarm && alarm_control(data))
    {
        // data->alarm = !data->alarm;
        // if (!fork())
        // {
        //     char *arguments[] = {
        //         COMMAND,
        //         PATH_AUDIO,
        //         NULL
        //     };

        //     execvp(COMMAND, arguments);
        // }
    }

    return NULL;
}