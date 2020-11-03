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
/*! @file tcp.c
 * @brief Interface for tcp server
 */
#include "tcp.h"

/****************************************************************************/
/*!                         Functions                                       */

void *receive(void *args)
{
    Data *data = (Data *) args;
    Receive data_receive;
    int client_socket;
    struct sockaddr_in client_address;
    unsigned int client_Length = sizeof(client_address);

    while(1)
    {
        if((client_socket = accept(data->server_socket, (struct sockaddr *) &client_address, &client_Length)) < 0)
        {
            printf("Error in client socket\n");
        }
        else
        {
            recv(client_socket, &data_receive, sizeof(data_receive), 0);
            
            data->lamp = data_receive.lamp;
            data->air_reference_temperature = data_receive.air_reference_temperature;

            close(client_socket);
        }
    }    
}

void *submit(void *args)
{
    struct sockaddr_in server_address;
    int client_socket;

    if ((client_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("Error in client socket\n");
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_address.sin_port = htons(CENTRAL_SERVER_PORT);

    if(connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
    {
        printf("Error in connect\n");
    }

    Data *data = (Data *) args;
    Send data_send;

    data_send.air_turn = data->air_turn;
    data_send.humidity = data->humidity;
    data_send.temperature = data->temperature;
    data_send.open_sensor = data->open_sensor;
    data_send.presence_sensor = data->presence_sensor;

    send(client_socket, &data_send, sizeof(data_send), 0);

    close(client_socket);

    return NULL;
}

/*!
 * @brief Function to init the tcp server.
 */
void initialize_tcp_server(Data *data)
{
    struct sockaddr_in server_address;

    if ((data->server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("Error in sever socket\n");
        exit(1);
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(DISTRIBUTED_SERVER_PORT);
 
    if(bind(data->server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
    {
        printf("Error in blind\n");
        exit(2);
    }

	if(listen(data->server_socket, 10) < 0)
    {
		printf("Falha no Listen\n");
        exit(3);
    }
}


