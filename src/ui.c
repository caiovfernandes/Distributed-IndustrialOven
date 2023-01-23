#include <stdio.h>
#include<stdlib.h> 
#include <ui.h>

void print_pid_menu(){
    system("clear");
    printf("\t\t\t***********************************\n"); 
    printf("\t\t\t** Trabalho 2 **\n"); 
    printf("\t\t\t***********************************\n"); 
    printf("\t\t\t   Fundamento de sistemas Embarcados \n"); 
    printf("\t\t\t***********************************\n"); 
    printf("\t\t\t\t\tMENU\n\n\n"); 
    printf("\t\tPara iniciarmos o programa, defina os valores de Ki, Kp e Kd\n\n\n"); 
}
double kp_menu(){
    double choosen_value;
    printf("\t\tInsira o valor para Kp (Controle Proporcional): \n\n\n"); 
    printf("\t\t\t***********************************\n\n\n"); 
    scanf("%d", &choosen_value);
    // return choosen_value;
    return 30.0;
}
double ki_menu(){
    double choosen_value;
    system("clear");
    printf("\t\t\t***********************************\n"); 
    printf("\t\t\t** Trabalho 2 **\n"); 
    printf("\t\t\t***********************************\n"); 
    printf("\t\t\t   Fundamento de sistemas Embarcados \n"); 
    printf("\t\t\t***********************************\n"); 
    printf("\t\t\t\t\tMENU\n\n\n"); 
    printf("\t\tInsira o valor para Ki (Controle Integral): \n\n\n"); 
    printf("\t\t\t***********************************\n\n\n"); 
    scanf("%lf", &choosen_value);
    // return choosen_value;
    return 0.2;
}
double kd_menu(){
    double choosen_value;
    system("clear");
    printf("\t\t\t***********************************\n"); 
    printf("\t\t\t** Trabalho 2 **\n"); 
    printf("\t\t\t***********************************\n"); 
    printf("\t\t\t   Fundamento de sistemas Embarcados \n"); 
    printf("\t\t\t***********************************\n"); 
    printf("\t\t\t\t\tMENU\n\n\n"); 
    printf("\t\tInsira o valor para Kd (Controle Derivativo): \n\n\n"); 
    printf("\t\t\t***********************************\n\n\n"); 
    scanf("%lf", &choosen_value);
    // return choosen_value;
    return 400;
}
int control_mode_menu(){
    int selected_mode;
        /*print menu screen*/ 
    system("clear");
    printf("\t\t\t***********************************\n"); 
    printf("\t\t\t** Trabalho 2 **\n"); 
    printf("\t\t\t***********************************\n"); 
    printf("\t\t\t   Fundamento de sistemas Embarcados \n"); 
    printf("\t\t\t***********************************\n"); 
    printf("\t\t\t\t\tMENU\n\n\n"); 
    printf("\t\t\t\t\tSelecione um opção:\n\n\n"); 
    printf("\t\t\t\t1 - Terminal mode\n"); 
    printf("\t\t\t\t2 - UART mode\n"); 
    printf("\t\t\t\tCtrl+c-to exit at any time.\n\n\n"); 
    printf("\t\t\t***********************************\n\n\n"); 

  scanf("%d", &selected_mode);
  return selected_mode;
}

double temperature_menu(){
    double selected_mode;
        /*print menu screen*/ 
    system("clear");
    printf("\t\t\t***********************************\n"); 
    printf("\t\t\t** Trabalho 2 **\n"); 
    printf("\t\t\t***********************************\n"); 
    printf("\t\t\t   Fundamento de sistemas Embarcados \n"); 
    printf("\t\t\t***********************************\n"); 
    printf("\t\t\t\t\tMENU\n\n\n"); 
    printf("\t\tInforme o valor da temperatura que deseja que o forno alcance:\n\n\n"); 
    printf("\t\t\t***********************************\n\n\n"); 

  scanf("%lf", &selected_mode);
  return selected_mode;
}


void print_oven_on(){
    system("clear");
    printf("\t\t\t***********************************\n"); 
    printf("\t\t\t** Trabalho 2 **\n"); 
    printf("\t\t\t***********************************\n"); 
    printf("\t\t\t   Fundamento de sistemas Embarcados \n"); 
    printf("\t\t\t***********************************\n"); 
    printf("\t\tLIGA FORNO\n\n\n"); 
    printf("\t\t\t***********************************\n\n\n"); 
}
void print_oven_off(){
    system("clear");
    printf("\t\t\t***********************************\n"); 
    printf("\t\t\t** Trabalho 2 **\n"); 
    printf("\t\t\t***********************************\n"); 
    printf("\t\t\t   Fundamento de sistemas Embarcados \n"); 
    printf("\t\t\t***********************************\n"); 
    printf("\t\t DESLIGA FORNO\n\n\n"); 
    printf("\t\t\t***********************************\n\n\n"); 
}
void print_heating_on(){
    system("clear");
    printf("\t\t\t***********************************\n"); 
    printf("\t\t\t** Trabalho 2 **\n"); 
    printf("\t\t\t***********************************\n"); 
    printf("\t\t\t   Fundamento de sistemas Embarcados \n"); 
    printf("\t\t\t***********************************\n"); 
    printf("\t\tLIGA AQUECIMENTO\n\n\n"); 
    printf("\t\t\t***********************************\n\n\n"); 
}
void print_cancel(){
    system("clear");
    printf("\t\t\t***********************************\n"); 
    printf("\t\t\t** Trabalho 2 **\n"); 
    printf("\t\t\t***********************************\n"); 
    printf("\t\t\t   Fundamento de sistemas Embarcados \n"); 
    printf("\t\t\t***********************************\n"); 
    printf("\t\tCANCELA\n\n\n"); 
    printf("\t\t\t***********************************\n\n\n"); 
}

void print_interruption(){
    system("clear");
    printf("\t\t\t***********************************\n");
    printf("\t\t\t** Trabalho 2 **\n");
    printf("\t\t\t***********************************\n");
    printf("\t\t\t   Fundamento de sistemas Embarcados \n");
    printf("\t\t\t***********************************\n");
    printf("\t\tDESLIGANDO O SISTEMA\n\n\n");
    printf("\t\tTodos os processos utilizados pelo programa foram finalizados com sucesso!\n\n\n");
    printf("\t\t\t***********************************\n\n\n");

}