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
bool alarm_control(Data *data)
{
    bool auxiliary = false;

    for (int i; i < NOPEN_SENSOR; i++)
        if (!(data->open_sensor&1<<i))
            auxiliary = true;
    
    for (int i; i < NPRESENCE_SENSOR; i++)
        if (!(data->presence_sensor&1<<i))
            auxiliary = true;

    return auxiliary;
}


void *play_alarm(void *args)
{
    Data *data = (Data *) args;

    // if(alarm_control(data))
    {
        data->alarm = !data->alarm;
        if (!fork())
        {
            char *arguments[] = {
                COMMAND,
                PATH_AUDIO,
                NULL
            };

            execvp(COMMAND, arguments);
        }
    }

    return NULL;
}