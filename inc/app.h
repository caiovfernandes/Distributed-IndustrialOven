#ifndef _ROUTINE_CONTROLLER_H_
#define _ROUTINE_CONTROLLER_H_

#define DEFAULT_TEMPERATURE 20
#define IS_CSV_CURVE_FILE 1
#define IS_MANUAL 0

void handle_terminal_process();
void dashboard_process();

float get_internal_temperature();

float get_reference_temperature();

int read_user_commands(void);

void set_control(int controller_sign);

void set_reference(float reference_sign);

int send_system_status(char state);

int set_control_mode(char mode);

int set_status(char status);

float set_temperature(float room_temperature);
int handle_potentiometer_process();
void handle_user_command(int command);
#endif