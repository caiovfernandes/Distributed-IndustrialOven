#include <stdio.h>
#include <unistd.h>  // Used for UART
#include <fcntl.h>   // Used for UART
#include <termios.h> // Used for UART
#include <string.h>
#include <stdlib.h>

#include "modbus.h"
#include "crc16.h"

short read_uart(int uart_filestream, char type, void *p_out) {
    //----- CHECK FOR ANY RX BYTES -----
    if (uart_filestream != -1) {
        // Read up to 255 characters from the port if they are there
        unsigned char rx_buffer[256];
        int rx_length = read(uart_filestream, (void *) rx_buffer,
                             255); // Filestream, buffer to store in, number of bytes to read (max)

        if (rx_length < 0) {
            printf("Erro na leitura."); // An error occured (will occur if there are no bytes)
        } else if (rx_length == 0) {
            printf("Nenhum dado disponível."); // No data waiting

            if (type == VOID) {
                return 1;
            }
        } else {
            // Bytes received
            rx_buffer[rx_length] = '\0';

            short crc_buffer, crc_response;

            switch (type) {
                case INT: {
                    int response;

                    memcpy(&response, &rx_buffer[3], sizeof(response));

                    memcpy(&crc_buffer, &rx_buffer[7], sizeof(short));
                    crc_response = calcula_CRC(rx_buffer, 7);

                    *(int *) p_out = response;
                    break;
                }

                case FLOAT: {
                    float response;

                    memcpy(&response, &rx_buffer[3], sizeof(response));

                    memcpy(&crc_buffer, &rx_buffer[7], sizeof(short));
                    crc_response = calcula_CRC(rx_buffer, 7);

                    *(float *) p_out = response;
                    break;
                }

                case STR: {
                    char response[255];

                    memcpy(&response, &rx_buffer[4], rx_buffer[3]);

                    memcpy(&crc_buffer, &rx_buffer[5 + rx_buffer[3]], sizeof(short));
                    crc_response = calcula_CRC(rx_buffer, 5 + rx_buffer[3]);
                    break;
                }

                default:
                    printf("Erro na passagem do tipo de dado!");
            }

            if (crc_response == crc_buffer) {

                return 1;
            } else {
                return 0;
            }
        }
    }

    return 0;
}

int init_uart() {
    int uart_filestream = -1;
    uart_filestream = open(FILE_UART, O_RDWR | O_NOCTTY | O_NDELAY); // Open in non blocking read/write mode

    if (uart_filestream == -1) {
        printf("Erro - Não foi possível iniciar a UART.");
    } else {
        // printf("UART inicializada!");
    }

    struct termios options;

    tcgetattr(uart_filestream, &options);
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD; // Set baud rate
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart_filestream, TCIFLUSH);
    tcsetattr(uart_filestream, TCSANOW, &options);

    return uart_filestream;
}

void write_uart(unsigned char *tx_buffer, int size, int uart_filestream){
    if (uart_filestream != -1) {
        int count = write(uart_filestream, tx_buffer, size);
        if (count < 0) {
            printf("[ERRO] UART TX error\n");
        }
    } else {
        printf("[ERRO] Uart não inicializada!\n");
    }
}
