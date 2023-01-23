#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "app.h"
#include "pid.h"
#include "gpio.h"
#include "uart.h"
#include "bme280_temperature.h"
#include "ui.h"


#include "modbus.h"
#include "crc16.h"

void handle_terminal_process() {
  int user_command = 0;

  double temperature;

  // printf("\nInforme o valor da temperatura que deseja que o forno alcance:\n");
  // scanf("%lf", &temperature);
  temperature = temperature_menu();

  // Atualizando a referencia do PID
  pid_update_reference(temperature);
  set_reference(temperature);

  sleep(1);

  send_system_status(1);
  set_status(1);

  // system("clear");

  handle_potentiometer_process();
}

void dashboard_process() {
  int user_command = 0;

  do {
    user_command = read_user_commands();
    handle_user_command(user_command);
    
    usleep(500000); // 0.5 seg
  } while (user_command != 162 && user_command != 164); // desligar ou parar o forno
}



static int uart_filestream = -1;

float get_internal_temperature(void) {
  float intern_temperature = -100.f;
  int uart0_filestream = init_uart();

  unsigned char *message = malloc(MESSAGE_REQUEST_SIZE + 1);
  message[0] = REQUEST_FLOAT_INTERN_TEMPERATURE_DATA_CODE;
  send_modbus_message(message, MESSAGE_REQUEST_SIZE, uart0_filestream, CALC_CRC_SIZE, '9', 201, 201);

  sleep(1);
  // exit(1);

  short is_crc_valid = read_uart(uart0_filestream, FLOAT, &intern_temperature);
  close(uart0_filestream);

  if (is_crc_valid == 0) {
    printf("[request_float_intern_temperature_message]: Erro na validacao do CSV ou validacao da uart, tentando novamente...\n");
    return get_internal_temperature();
  }

  return intern_temperature;
}

float get_reference_temperature(void) {
  float reference_temperature = -100.f;
  int uart0_filestream = init_uart();

  unsigned char *message = malloc(MESSAGE_REQUEST_SIZE + 1);
  message[0] = REQUEST_FLOAT_REFERENCE_TEMPERATURE_DATA_CODE;
  send_modbus_message(message, MESSAGE_REQUEST_SIZE, uart0_filestream, CALC_CRC_SIZE, '9', 201, 201);


  sleep(1);

  short is_crc_valid = read_uart(uart0_filestream, FLOAT, &reference_temperature);
  close(uart0_filestream);

  if (is_crc_valid == 0) {
    printf("[request_float_reference_temperature_message]: Erro na validacao do CSV ou validacao da uart, tentando novamente...\n");
    return get_reference_temperature();
  }

  return reference_temperature;
}

int read_user_commands(void) {
  int command = -1;
  int uart0_filestream = init_uart();

  unsigned char *message = malloc(MESSAGE_REQUEST_SIZE + 1);
  message[0] = REQUEST_READ_USER_COMMANDS_DATA_CODE;
  send_modbus_message(message, MESSAGE_REQUEST_SIZE, uart0_filestream, CALC_CRC_SIZE, '9', 201, 201);

  sleep(1);

  short is_crc_valid = read_uart(uart0_filestream, INT, &command);
  close(uart0_filestream);

  if (is_crc_valid == 0) {
    printf("read_user_commands]: Erro na validacao do CSV ou validacao da uart, tentando novamente...\n");
    return read_user_commands();
  }

  return command;
}

void set_control(int controller_sign) {
  int sign;
  int uart0_filestream = init_uart();
  unsigned char *message = malloc(MESSAGE_SEND_SIGNAL_SIZE + 1);
  message[0] = SEND_CONTROLLER_SIGN_DATA_CODE;
  send_modbus_message(message, MESSAGE_SEND_SIGNAL_SIZE, uart0_filestream, CALC_CRC_SIZE, '9', 201, controller_sign);


  sleep(1);
  
  short is_crc_valid = read_uart(uart0_filestream, VOID, &sign);
  close(uart0_filestream);
  

  if (is_crc_valid == 0) {
    printf("[send_controller_sign]: Erro na validacao do CSV ou validacao da uart, tentando novamente...\n");
    return set_control(controller_sign);
  }
}

void set_reference(float reference_sign) {
  int sign;
  int uart0_filestream = init_uart();

  unsigned char tx_buffer[20];
  unsigned char *p_message_buffer;

  // Send a float
  p_message_buffer = &tx_buffer[0];
  *p_message_buffer++ = DEVICE_ADDRESS_CODE;
  *p_message_buffer++ = FUNCTION_SEND_CODE;
  *p_message_buffer++ = SEND_REFERENCE_SIGN_DATA_CODE;

  // Last four digits of the registration number
  *p_message_buffer++ = 2;
  *p_message_buffer++ = 2;
  *p_message_buffer++ = 0;
  *p_message_buffer++ = 0;

  memcpy(p_message_buffer, &reference_sign, sizeof(reference_sign));
  p_message_buffer+=sizeof(reference_sign);
  
  short crc_value = calcula_CRC(tx_buffer, CALC_CRC_SEND_SIZE);
  memcpy(p_message_buffer, &crc_value, sizeof(crc_value));
  
  p_message_buffer += sizeof(crc_value);

  printf("Buffers de memória criados!");

  if (uart0_filestream != -1) {
    printf("Escrevendo caracteres na UART ...");
    int count = write(uart0_filestream, &tx_buffer[0], (p_message_buffer - &tx_buffer[0]));
    
    if (count < 0) {
      printf("UART TX error");
    } else {
      printf("escrito.");
    }
  }
  sleep(1);

  short is_crc_valid = read_uart(uart0_filestream, VOID, &sign);
  
  close(uart0_filestream);

  if (is_crc_valid == 0) {
    printf("[send_reference_sign]: Erro na validacao do CSV ou validacao da uart, tentando novamente...\n");
    return set_reference(reference_sign);
  }
}

int send_system_status(char state) {
  int system_state = -1;
  int uart0_filestream = init_uart();

  unsigned char *message = malloc(MESSAGE_SYSTEM_STATE_SIZE + 1);
  message[0] = SEND_SYSTEM_STATE_DATA_CODE;
  message[1] = state;
  send_modbus_message(message, MESSAGE_SYSTEM_STATE_SIZE, uart0_filestream, CALC_CRC_SEND_SIZE - 3, state, 201, 201);

  // exit(1);
  sleep(1);

  short is_crc_valid = read_uart(uart0_filestream, INT, &system_state);
  close(uart0_filestream);

  if (is_crc_valid == 0) {
    printf("[send_system_state]: Erro na validacao do CSV ou validacao da uart, tentando novamente...\n");
    return send_system_status(state);
  }

  return system_state;
}

int set_control_mode(char mode) {
  int controller_mode = -1;
  int uart0_filestream = init_uart();

  unsigned char *message = malloc(MESSAGE_SYSTEM_STATE_SIZE + 1);
  message[0] = SEND_CONTROLLER_MODE_DATA_CODE;
  send_modbus_message(message, MESSAGE_SYSTEM_STATE_SIZE, uart0_filestream, CALC_CRC_SEND_SIZE - 3, mode, 201, 201);


  sleep(1);

  short is_crc_valid = read_uart(uart0_filestream, INT, &controller_mode);
  close(uart0_filestream);

  if (is_crc_valid == 0) {
    printf("[send_controller_mode]: Erro na validacao do CSV ou validacao da uart, tentando novamente...\n");
    return set_control_mode(mode);
  }

  return controller_mode;
}

int set_status(char status) {
  int working_status = -1;
  int uart0_filestream = init_uart();

  unsigned char *message = malloc(MESSAGE_SYSTEM_STATE_SIZE + 1);
  message[0] = SEND_WORKING_STATUS_DATA_CODE;
  send_modbus_message(message, MESSAGE_SYSTEM_STATE_SIZE, uart0_filestream, CALC_CRC_SEND_SIZE - 3, status, 201, 201);

  sleep(1);

  short is_crc_valid = read_uart(uart0_filestream, INT, &working_status);
  close(uart0_filestream);

  if (is_crc_valid == 0) {
    printf("[send_working_status]: Erro na validacao do CSV ou validacao da uart, tentando novamente...\n");
    return set_status(status);
  }

  return working_status;

}

float set_temperature(float room_temperature) {
   float temperature = 0.f;
  int uart0_filestream = init_uart();

  unsigned char tx_buffer[20];
  unsigned char *p_message_buffer;

  // Send controller sign (int)
  p_message_buffer = &tx_buffer[0];
  *p_message_buffer++ = DEVICE_ADDRESS_CODE;
  *p_message_buffer++ = FUNCTION_SEND_CODE;
  *p_message_buffer++ = SEND_ROOM_TEMPERATURE_DATA_CODE;

  // Last four digits of the registration number
  *p_message_buffer++ = 2;
  *p_message_buffer++ = 2;
  *p_message_buffer++ = 0;
  *p_message_buffer++ = 0;

  memcpy(p_message_buffer, &room_temperature, sizeof(room_temperature));
  p_message_buffer+=sizeof(room_temperature);

  short crc_value = calcula_CRC(tx_buffer, CALC_CRC_SEND_SIZE);
  memcpy(p_message_buffer, &crc_value, sizeof(crc_value));
  
  p_message_buffer += sizeof(crc_value);

  printf("TEMP");

  if (uart0_filestream != -1) {
    printf("Escrevendo caracteres na UART ...");
    int count = write(uart0_filestream, &tx_buffer[0], (p_message_buffer - &tx_buffer[0]));
    
    if (count < 0) {
      printf("UART TX error");
    } else {
      printf("escrito.");
    }
  }

  sleep(1);

  short is_crc_valid = read_uart(uart0_filestream, FLOAT, &temperature);
  close(uart0_filestream);

  if (is_crc_valid == 0) {
    printf("[send_room_temperature]: Erro na validacao do CSV ou validacao da uart, tentando novamente...\n");
    return set_temperature(room_temperature);
  }

  return temperature;
}

void handle_user_command(int command) {
  if(command>1){
    printf("Comando: %d\n", command);
    
    if (command = 161){
      send_system_status(1);
      print_oven_on();
    }
    else if (command = 162)
    {
        send_system_status(0);
        set_status(0);
        print_oven_off();
    }
    else if (command = 163)
    {
        set_status(1);
        handle_potentiometer_process();
        print_heating_on();
    }
    else if (command = 164)
    {
      set_status(0);
      print_cancel();

    }

  }
}

int handle_potentiometer_process() {
  int user_command = 0;

  double temperature;
  int result = get_temperature(&temperature);

  if (result != BME280_RESPONSE_SUCCESS) {
      printf("Erro na leitura do bme280");
      exit(1);
  }

  // get_temperature
  float reference_temperature;

  do {
        reference_temperature = get_reference_temperature();

        set_reference(reference_temperature);

        float internal_temperature = get_reference_temperature();

        if (internal_temperature < 0 || internal_temperature > 100) {
            internal_temperature = 25;
        }

        float cooler_power, resistor_power;
        float power = pid_control(internal_temperature);

        if (power >= 0) {
            cooler_power = 0;
            resistor_power = power;
        } else {
            cooler_power = power * (-1);

            if (cooler_power < 40) {
                cooler_power = 40;
            }

            resistor_power = 0;
        }

        set_control((int) power);
        handle_temperature_power(power);


        sleep(0.5); // 0.5 seg
        user_command = read_user_commands();
        handle_user_command(user_command);
  } while (user_command != 162 && user_command != 164); // desligar ou parar o forno

  return user_command;
}

