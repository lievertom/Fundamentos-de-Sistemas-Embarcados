#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

/******************************************************************************/
/*                       Header includes                                      */

#include "data.h"

/****************************************************************************/
/*!                              Macros                                     */

#define SERVER_PORT (unsigned short)4001

/****************************************************************************/
/*!                         Functions                                       */

void initialize_tcp_server(Data *data);

void *receive(void *args);

void *submit(void *args);

#endif /* TCP_SERVER_H_ */
