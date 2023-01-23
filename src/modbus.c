
#include <string.h>
#include "modbus.h"
#include "crc16.h"
#include "uart.h"

void send_modbus_message (unsigned char *message, int message_size, int uart_filestream, int crc_size, char send_char, float send_float, int send_int) {
    int pos = 0;
    short crc;

    unsigned char message_buffer[20];
    unsigned char *p_message_buffer;

    p_message_buffer = &message_buffer[0];
    *p_message_buffer++ = DEVICE_ADDRESS_CODE;
    *p_message_buffer++ = get_modbus_code_from_option(message[0]);
    *p_message_buffer++ = message[0];

    *p_message_buffer++ = 8;
    *p_message_buffer++ = 7;
    *p_message_buffer++ = 9;
    *p_message_buffer++ = 8;


    if (send_char != '9'){
      memcpy(p_message_buffer, &send_char, sizeof(send_char));
      p_message_buffer+=sizeof(send_char);
    }
    else if (send_float < 200) {
      memcpy(p_message_buffer, &send_float, sizeof(send_float));
      p_message_buffer+=sizeof(send_float);
    }
    else if (send_int < 200) {
      memcpy(p_message_buffer, &send_int, sizeof(send_int));
      p_message_buffer+=sizeof(send_int);
    }
    

    short crc_value = calcula_CRC(message_buffer, crc_size);
    memcpy(p_message_buffer, &crc_value, sizeof(crc_value));
    p_message_buffer += sizeof(crc_value);

    write_uart(message_buffer, (p_message_buffer - &message_buffer[0]), uart_filestream);
}

int get_modbus_code_from_option(int option){
  int code = REQUEST_CODE_MODBUS;
  if (option >= SEND_CTRL_SIG)
    code = SEND_CODE_MODBUS;

  return code;
}