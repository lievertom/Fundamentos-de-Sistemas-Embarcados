#ifndef TCP_H_
#define TCP_H_

/******************************************************************************/
/*                       Header includes                                      */

#include "data.h"

/****************************************************************************/
/*!                              Macros                                     */

// Servidor Distribuído:
// - IP: 192.168.0.52;
// - Porta pessoal: 10123.

// Servidor Central:
// - IP: 192.168.0.53;
// - Porta pessoal: 10023.

#define CENTRAL_SERVER_PORT (unsigned short)10027
#define DISTRIBUTED_SERVER_PORT (unsigned short)10127
#define SERVER_IP "192.168.0.52"

/****************************************************************************/
/*!                         Functions                                       */

void initialize_tcp_server(Data *data);

void *receive(void *args);

void *submit(void *args);

#endif /* TCP_H_ */
