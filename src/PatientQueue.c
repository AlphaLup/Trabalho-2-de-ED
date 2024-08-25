#include "../include/Patient.h"
#include "../include/PatientQueue.h"
#include <stdlib.h>
#include <stdio.h>

// Estrutura da fila de pacientes
struct patientQueue
{
    PatientNode *front; // ponteiro para o primeiro nó da fila
    PatientNode *rear; // ponteiro para o último nó da fila
    int size; // tamanho da fila
};

// Estrutura de um nó da fila de pacientes
struct patientNode
{
    Patient *data_patient; // ponteiro para a estrutura do paciente
    PatientNode *next; // ponteiro para o próximo nó da fila
};

// Cria uma nova fila de pacientes vazia
PatientQueue *pq_create() {
    PatientQueue *pq = (PatientQueue *)malloc(sizeof(PatientQueue));
    
    if(pq == NULL) {
        perror("Falha ao alocar memória para a fila de pacientes");
        exit(1);
    }

    pq->front = NULL;
    pq->rear = NULL;
    pq->size = 0;
    return pq;
};

// Verifica se a fila de pacientes está vazia
int pq_is_empty(PatientQueue *pq) {
    return pq->front == NULL;
};

int pq_size(PatientQueue *pq) {
    return pq->size;
}

// Insere um paciente ao final da fila de pacientes
void pq_insert(PatientQueue *pq, Patient *patient) {
    PatientNode *node = (PatientNode *)malloc(sizeof(PatientNode));

    node->data_patient = patient;
    node->next = NULL;

    if (pq_is_empty(pq)) {
        pq->front = node;
    } else {
        pq->rear->next = node;
    }

    pq->rear = node;
    pq->size ++;
}

// Remove o primeiro paciente da fila de pacientes
Patient *pq_remove(PatientQueue *pq) {
    if(pq == NULL || pq_is_empty(pq)) {
        perror("A fila de pacientes está vazia ou não foi inicializada");
        return NULL;
    }

    PatientNode *node = pq->front;

    if(pq->front == pq->rear){
        pq->front = pq->rear = NULL;
    } else {
        pq->front = node->next;
    }

    pq->size --;

    return node->data_patient;
}

// Libera a memória alocada para a fila de pacientes
void pq_destroy(PatientQueue *pq) {
    if(pq == NULL) {
        perror("A fila de pacientes não foi inicializada");
        return;
    }

    PatientNode *node = pq->front;

    while(node != NULL) {
        PatientNode *temp = node;
        node = node->next;
        free(temp);
    }
}
