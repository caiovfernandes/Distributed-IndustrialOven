#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "main.h"
#include "gpio.h"

#include "ui.h"
#include "pid.h"
#include "modbus.h"
#include "bme280_temperature.h"
#include "app.h"


int main(int argc, char **argv) {
  signal(SIGINT, handle_interrupt);

    // GPIO pin outputs
    config_gpio_outputs();

    // Config Kp, Ki and Kd constants
    pid_config();

    // BME 280
    init_bme280();

    // Reset dashboard values
    send_system_status(0);
    set_status(0);
    set_control_mode(0);
  
  int menu = control_mode_menu();

  if (menu == 1) 
  {
    set_control_mode(1); 
    
    handle_terminal_process();
  } 
  else if (menu == 2) 
  { // Dashboard
      dashboard_process();
  }

  return 0;
}
void handle_interrupt(int signal) {
  handle_gpio_interrupt();
  bme280_driver_close();
  send_system_status(0);
  set_status(0);
  set_control_mode(0);

  print_interruption();
  exit(0);
}