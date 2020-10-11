#ifndef UART_H_
#define UART_H_

#define INTERNAL_TEMPERATURE (unsigned char *) 0xA1
#define REFERENCE_TEMPERATURE (unsigned char *) 0xA2

int uart(unsigned char * command);

#endif /* UART_H_ */