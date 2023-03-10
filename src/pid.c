#include <stdio.h>
#include "pid.h"
#include "ui.h"

double sinal_de_controle;
double referencia = 0.0;
double Kp = 0.0;  // Ganho Proporcional
double Ki = 0.0;  // Ganho Integral
double Kd = 0.0;  // Ganho Derivativo
int T = 1.0;      // Período de Amostragem (ms)
double erro_total, erro_anterior = 0.0;
int sinal_de_controle_MAX = 100.0;
int sinal_de_controle_MIN = -100.0;

void pid_config() {

  print_pid_menu();
  Kp = kp_menu();
  Ki = ki_menu();
  Kd = kd_menu();

  printf("\n----------- PID CONFIGURADO -----------\n");
}

void pid_update_reference(float referencia_){
  referencia = (double) referencia_;
}

double get_reference_temperature_pid() {
  return referencia;
}


double pid_control(double saida_medida){

    double erro = referencia - saida_medida;

    erro_total += erro;

    if (erro_total >= sinal_de_controle_MAX) 
    {
        erro_total = sinal_de_controle_MAX;
    }
    else if (erro_total <= sinal_de_controle_MIN) 
    {
        erro_total = sinal_de_controle_MIN;
    }

    double delta_error = erro - erro_anterior;

    sinal_de_controle = Kp*erro + (Ki*T)*erro_total + (Kd/T)*delta_error;

    if (sinal_de_controle >= sinal_de_controle_MAX)
    {
        sinal_de_controle = sinal_de_controle_MAX;
    }
    else if (sinal_de_controle <= sinal_de_controle_MIN) 
    {
        sinal_de_controle = sinal_de_controle_MIN;
    }

    erro_anterior = erro;

    return sinal_de_controle;
}