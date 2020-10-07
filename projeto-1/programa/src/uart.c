#include <stdlib.h>
#include <string.h>
#include <unistd.h>         // Used for UART
#include <fcntl.h>          // Used for UART
#include <termios.h>        // Used for UART

#include "uart.h"

int setupUART(const char *uart_path) {
    int uart0_filestream = -1;
    uart0_filestream = open(uart_path, O_RDWR | O_NOCTTY | O_NDELAY);

    if (uart0_filestream == -1) {
        printf("Erro - Não foi possível iniciar a UART.\n");
    }
    else {
        printf("UART inicializada!\n");
    }

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

ssize_t writeUART(int fd, const void *buf, size_t count) {
    ssize_t message_size = write(fd, buf, count);
    if(message_size < 0) {
        printf("Houve um erro no envio da mensagem à UART!\n");
    } else {
        printf("%03d bytes escritos na UART!\n", message_size);
    }

    return message_size;
}

ssize_t readUART(int fd, void *buf, size_t count) {
    ssize_t response_size = read(fd, buf, count);
    if(response_size < 0) {
        printf("Houve um erro na leitura da mensagem da UART!\n");
    } else {
        printf("%03d bytes lidos da UART!\n", response_size);
    }

    return response_size;
}

float ask_float(int uart0_filestream, unsigned char * command) {
    const char matricula[5] = {9, 2, 5, 1, '\0'};
    ssize_t message_size = writeUART(uart0_filestream, &command[0], strlen((char*)command));
    if(message_size < 0) return;
    message_size = writeUART(uart0_filestream, &matricula[0], strlen(matricula));
    if(message_size < 0) return;

    sleep(1);

    float response = -1.0f;

    ssize_t response_size = readUART(uart0_filestream, (void*) &response, sizeof(float));
    if(response_size > 0) {
        return response;
    }
}

int uart(unsigned char * command) {
    const char uart_path[] = "/dev/serial0";
    int user_choice = -1;
    int uart0_filestream = -1;
    uart0_filestream = setupUART(uart_path);
    float response = ask_float(uart0_filestream, command);
    close(uart0_filestream);
    
    return response;
}