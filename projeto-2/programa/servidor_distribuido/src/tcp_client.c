/******************************************************************************/
/*                       Header includes                                      */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "thread.h"

/******************************************************************************/
/*! @file tcp_client.c
 * @brief Interface for tcp server
 */
#include "tcp_client.h"

/****************************************************************************/
/*!                         Functions                                       */

void *receive(void *args)
{
    Data *data = (Data *) args;
    Receive data_receive;

    while (1)
    {
        recv(data->client_socket, &data_receive, sizeof(data_receive), 0);
        
        data->lamp = data_receive.lamp;
        data->air_reference_temperature = data_receive.air_reference_temperature;
    }
    
}

void *submit(void *args)
{
    Data *data = (Data *) args;
    Send data_send;
    
    data_send.air_turn = data->air_turn;
    data_send.humidity = data->humidity;
    data_send.temperature = data->temperature;
    data_send.open_sensor = data->open_sensor;
    data_send.presence_sensor = data->presence_sensor;

    if (send(data->client_socket, &data_send, sizeof(data_send), 0) != sizeof(data_send))
        sig_handler(SIGINT);

    return NULL;
}

/*!
 * @brief Function to init the tcp server.
 */
void initialize_tcp_client(Data *data)
{
    struct sockaddr_in server_address;

    if ((data->client_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("Error in client socket\n");
        exit(1);
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_address.sin_port = htons(SERVER_PORT);

    if(connect(data->client_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
    {
        printf("Error in connect\n");
        exit(2);
    }
}
