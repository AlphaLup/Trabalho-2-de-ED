#ifndef PATIENT_H
#define PATIENT_H

#include <time.h>

// define a estrutura do paciente
typedef struct patient Patient;

// criar um novo paciente
// tipo de retorno: Patient * p --> (ponteiro para a estrutura do paciente)
Patient *create_patient(int id, const char *name, int register_time);

// salvar os dados de um paciente no arquivo db_patient.txt
void save_patient(Patient *patient);

// destruir um paciente
// liberar a memória alocada para a estrutura do paciente
void destroy_patient(Patient *patient);

// obter o ID de um paciente
// tipo de retorno: int
int get_patient_id(Patient *patient);

// obter o nome de um paciente
// retorna um ponteiro contendo uma cópia do campo patient->name (char *)
char * get_patient_name(Patient *patient);

// obter o horário de registro de um paciente
// retorna um inteiro referente ao horário de registro do paciente
int get_patient_register_time(Patient *patient);

// obet patient por id
// retorna um ponteiro para a estrutura do paciente
Patient *get_patient_by_id(int id);

#endif