#ifndef EXAM_H
#define EXAM_H

// define a estrutura do exame
typedef struct exam Exam;

// criar um novo exame
// tipo de retorno: Exam * --> um ponteiro para a estrutura do exame
Exam *create_exam(int id, int patient_id, int rx_id, int register_time);

// destruir um exame
// liberar a memória alocada para a estrutura do exame
// tipo de retorno: void
void destroy_exam(Exam *exam);

// obter o id de um exame
// tipo de retorno: int
int get_exam_id(Exam *exam);

// obter o id do paciente de um exame
// tipo de retorno: int
int get_exam_patient_id(Exam *exam);

// obter o id da máquina de raio-x de um exame
// tipo de retorno: int
int get_exam_rx_id(Exam *exam);

// obter o horário do exame
// tipo de retorno: int
int get_exam_time(Exam *exam);

// obter a prioridade do exame
// tipo de retorno: int
int get_exam_priority(Exam *exam);

// obter a condição do exame
// tipo de retorno: char *
char *get_exam_condition(Exam *exam);

#endif