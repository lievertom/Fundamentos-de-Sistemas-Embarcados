#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>         // Used for UART
#include <fcntl.h>          // Used for UART
#include <termios.h>        // Used for UART

#include "data.h"
#include "uart.h"

#define INT_ERROR -1
#define FLOAT_ERROR -1.0f
#define BUS "/dev/serial0"

int setup_uart()
{
    int uart0_filestream = INT_ERROR;
    uart0_filestream = open(BUS, O_RDWR | O_NOCTTY | O_NDELAY);

    // if (uart0_filestream == INT_ERROR)
    // {
    //     printf("Erro - Não foi possível iniciar a UART.\n");
    // }
    // else
    // {
    //     printf("UART inicializada!\n");
    // }

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

ssize_t write_uart(int file_descriptor, const void *buf, size_t count)
{
    ssize_t message_size = write(file_descriptor, buf, count);
    // if(message_size < 0)
    // {
    //     printf("Houve um erro no envio da mensagem à UART!\n");
    // } 
    // else 
    // {
    //     printf("%03d bytes escritos na UART!\n", message_size);
    // }

    return message_size;
}

ssize_t read_uart(int file_descriptor, void *buf, size_t count)
{
    ssize_t response_size = read(file_descriptor, buf, count);
    // if(response_size == INT_ERROR)
    // {
    //     printf("Houve um erro na leitura da mensagem da UART!\n");
    // }
    // else 
    // {
    //     printf("%03d bytes lidos da UART!\n", response_size);
    // }

    return response_size;
}

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