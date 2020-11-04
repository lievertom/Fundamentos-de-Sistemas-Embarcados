#ifndef TCP_H_
#define TCP_H_

/******************************************************************************/
/*                       Header includes                                      */

#include "data.h"

/****************************************************************************/
/*!                              Macros                                     */

#define CENTRAL_SERVER_IP        "192.168.0.53"
#define CENTRAL_SERVER_PORT      (unsigned short)10027
#define DISTRIBUTED_SERVER_IP    "192.168.0.52"
#define DISTRIBUTED_SERVER_PORT  (unsigned short)10127

/****************************************************************************/
/*!                         Functions                                       */

void initialize_tcp_server(Data *data);

void *receive(void *args);

void *submit(void *args);

#endif /* TCP_H_ */
