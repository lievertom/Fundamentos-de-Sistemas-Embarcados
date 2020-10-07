#ifndef UART_H_
#define UART_H_

#include <stdio.h>

int setupUART(const char *uart_path);

ssize_t writeUART(int fd, const void *buf, size_t count);

ssize_t readUART(int fd, void *buf, size_t count);

float ask_float(int uart0_filestream, unsigned char * command);

int uart(unsigned char * command);

#endif /* UART_H_ */