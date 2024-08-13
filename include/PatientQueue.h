#ifndef PATIENTQUEUE_H
#define PATIENTQUEUE_H

// define a estrutura da fila de pacientes
typedef struct patientQueue PatientQueue;
typedef struct patientNode PatientNode;

// cria uma nova fila de pacientes vazia
// tipo de retorno: PatientQueue * pq --> (ponteiro para a estrutura da fila de pacientes)
PatientQueue *pq_create();

// verifica se a fila de pacientes está vazia
// tipo de retorno: int
int pq_is_empty(PatientQueue *pq);

// retorna o tamanho da fila de pacientes
// tipo de retorno: int
int pq_size(PatientQueue *pq);

// insere um paciente ao final da fila de pacientes
void pq_insert(PatientQueue *pq, Patient *patient);

// remove o primeiro paciente da fila de pacientes e retorna o paciente removido
// tipo de retorno: Patient * pq --> (ponteiro para a estrutura do paciente)
Patient *pq_remove(PatientQueue *pq);

// Libera a memória alocada para a fila de pacientes
void pq_destroy(PatientQueue *pq);

// Imprime os elementos da fila de pacientes
void pq_print(PatientQueue *pq);

#endif