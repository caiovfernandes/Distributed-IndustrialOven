#ifndef PID_H_
#define PID_H_


void pid_config();

void pid_update_reference(float referencia_);
double pid_control(double saida_medida);

#endif /* PID_H_ */