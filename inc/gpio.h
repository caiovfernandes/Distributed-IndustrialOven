#ifndef _GPIO_H_
#define _GPIO_H_

#define LOW   0
#define HIGH  1

// WiringPi values
#define RESISTOR_GPIO           4
#define COOLER_GPIO             5

void handle_temperature_power(double temp_power);
void handle_gpio_interrupt();
void config_gpio_outputs();

#endif