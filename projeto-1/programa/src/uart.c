/******************************************************************************/
/*                       Header includes                                      */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>         
#include <fcntl.h>          
#include <termios.h>        

#include "data.h"

/******************************************************************************/
/*! @file uart.c
 * @brief Interface for uart
 */
#include "uart.h"

/****************************************************************************/
/*!                         Functions                                       */

/*!
 * @brief Function used to uart setup.
 */
int setup_uart()
{
    int uart0_filestream = INT_ERROR;
    uart0_filestream = open(PATH, O_RDWR | O_NOCTTY | O_NDELAY);

    struct termios options;
    tcgetattr(uart0_filestream, &options);
    options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart0_filestream, TCIFLUSH);
    tcsetattr(uart0_filestream, TCSANOW, &options);

    return uart0_filestream;
}

/*!
 * @brief Function used to write in uart.
 */
ssize_t write_uart(int file_descriptor, const void *buf, size_t count)
{
    ssize_t message_size = write(file_descriptor, buf, count);
    return message_size;
}

/*!
 * @brief Function used to read from uart.
 */
ssize_t read_uart(int file_descriptor, void *buf, size_t count)
{
    ssize_t response_size = read(file_descriptor, buf, count);
    return response_size;
}

/*!
 * @brief Function used get the potentiometer value or internal temperature.
 */
float ask_float(int uart0_filestream, unsigned char * command)
{
    const unsigned char matricula[] = {9, 2, 5, 1};
    ssize_t message_size = write_uart(uart0_filestream, &command, sizeof(char));
    if(message_size < 0) return -1.0;
    message_size = write_uart(uart0_filestream, matricula, 4*sizeof(char));
    if(message_size < 0) return -1.0;

    usleep(10000);

    float response = FLOAT_ERROR;

    ssize_t response_size = read_uart(uart0_filestream, (void *) &response, sizeof(float));
    if(response_size < 0) return -1.0f;
    return response;
}

/*!
 *  @brief Thread function that access uart to update the internal temperature and potentiometer values
 */
void  *uart (void *args)
{
    float response;
    Data *data = (Data *) args;
    int uart0_filestream = setup_uart();
    response = ask_float(uart0_filestream, INTERNAL_TEMPERATURE);
    if (response > 0.0f)
    {
        data->internal_temperature = response;
    }
    close(uart0_filestream);  
    if (data->potentiometer)
    {
        int uart0_filestream = setup_uart();
        response = ask_float(uart0_filestream, REFERENCE_TEMPERATURE);
        if (response > 0.0f)
        {
            data->reference_temperature = response;
        }  
        close(uart0_filestream);  
    }
    return NULL;
}