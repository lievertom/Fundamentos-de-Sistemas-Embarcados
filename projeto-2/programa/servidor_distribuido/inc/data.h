#ifndef DATA_H_
#define DATA_H_

/******************************************************************************/
/*                       Header includes                                      */

#include <stdbool.h>

/****************************************************************************/
/*!                              Macros                                     */
#define HOUR_SIZE               9

#define NAC                     2
#define NLAMP                   4
#define NOPEN_SENSOR            6
#define NPRESENCE_SENSOR        2

#define AIR_OFF                 0.0f

#define DELAY_ALARM             10

/****************************************************************************/
/*!                            Structs                                      */

typedef struct Data 
{
    bool alarm;
    unsigned char lamp;
    unsigned char air_turn;
    unsigned char open_sensor;
    unsigned char presence_sensor;
    float humidity;
    float temperature;
    float air_reference_temperature;
    int server_socket;
} Data;

typedef struct Receive
{
    unsigned char lamp;
    float air_reference_temperature;
} Receive;

typedef struct Send
{
    unsigned char air_turn;
    unsigned char open_sensor;
    unsigned char presence_sensor;
    float humidity;
    float temperature;
} Send;

#endif /* DATA_H_ */
