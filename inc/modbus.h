#ifndef _UART_MODBUS_H_
#define _UART_MODBUS_H_

#define FILE_UART "/dev/serial0"
#define CALC_CRC_SIZE 7
#define CALC_CRC_SEND_SIZE 11

#define INT 'd'
#define FLOAT 'f'
#define STR 's'
#define VOID 'v'


#define DEVICE_ADDRESS_CODE 0x01
#define FUNCTION_SEND_CODE 0x16

#define REQUEST_FLOAT_INTERN_TEMPERATURE_DATA_CODE 0xC1
#define REQUEST_FLOAT_REFERENCE_TEMPERATURE_DATA_CODE 0xC2
#define REQUEST_READ_USER_COMMANDS_DATA_CODE 0xC3

#define SEND_CONTROLLER_SIGN_DATA_CODE 0xD1
#define SEND_REFERENCE_SIGN_DATA_CODE 0xD2
#define SEND_SYSTEM_STATE_DATA_CODE 0xD3
#define SEND_CONTROLLER_MODE_DATA_CODE 0xD4
#define SEND_WORKING_STATUS_DATA_CODE 0xD5
#define SEND_ROOM_TEMPERATURE_DATA_CODE 0xD6



#define SEND_CODE_MODBUS 0x16
#define REQUEST_CODE_MODBUS 0x23



#define SEND_CTRL_SIG 0xD1
#define MESSAGE_REQUEST_SIZE 0
#define MESSAGE_SYSTEM_STATE_SIZE 1
#define MESSAGE_SEND_SIGNAL_SIZE 4


void send_modbus_message (unsigned char *message, int message_size, int uart_filestream, int crc_size, char send_char, float send_float, int send_int);

int get_modbus_code_from_option(int option);

#endif