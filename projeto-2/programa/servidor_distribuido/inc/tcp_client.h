#ifndef TCP_CLIENT_H_
#define TCP_CLIENT_H_

/******************************************************************************/
/*                       Header includes                                      */

#include "data.h"

/****************************************************************************/
/*!                              Macros                                     */

#define SERVER_PORT (unsigned short)10027
#define SERVER_IP "192.168.0.52"

/****************************************************************************/
/*!                         Functions                                       */

void initialize_tcp_client(Data *data);

void *receive(void *args);

void *submit(void *args);

#endif /* TCP_CLIENT_H_ */
