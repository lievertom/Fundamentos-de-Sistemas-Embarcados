/******************************************************************************/
/*                       Header includes                                      */

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/******************************************************************************/
/*! @file tcp_server.c
 * @brief Interface for tcp server
 */
#include "tcp_server.h"

/****************************************************************************/
/*!                        Global Statements                                */


/****************************************************************************/
/*!                         Functions                                       */

void *receive(void *args)
{
    Data *data = (Data *) args;
    Receive data_receive;

    while (1)
    {
        recv(data->client_socket, &data_receive, sizeof(data_receive), 0);
        
        data->alarm[1] = data_receive.alarm;
        data->air_turn = data_receive.air_turn;
        data->open_sensor = data_receive.open_sensor;
        data->presence_sensor = data_receive.presence_sensor;
        for (int i = 0; i < NSENSOR; i++)
        {
            data->humidity[i] = data_receive.humidity[i];
            data->temperature[i] = data_receive.temperature[i];
        }
    }
    
}

void *submit(void *args)
{
    Data *data = (Data *) args;
    Send data_send;

    data_send.lamp = data->lamp;
    data_send.alarm = data->alarm[0];
    for (int i = 0; i < NAIR; i++)
        data_send.air_reference_temperature[i] = data->air_reference_temperature[i];

    send(data->client_socket, &data_send, sizeof(data_send), 0);
    return NULL;
}

/*!
 * @brief Function to init the tcp server.
 */
void initialize_tcp_server(Data *data)
{
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    if ((data->server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("Error in sever socket\n");
        exit(1);
    }

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(SERVER_PORT);

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

    unsigned int client_Length = sizeof(client_address);

    while(1)
    {
        if((data->client_socket = accept(data->server_socket, (struct sockaddr *) &client_address, &client_Length)) < 0)
        {
            printf("Error in client socket\n");
            exit(4);
        }
        else break;
    }
}
