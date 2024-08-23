#include "../include/Exam.h"
#include "../include/ExamPriorityQueue.h"
#include <stdlib.h>
#include <stdio.h>

struct examPriorityQueue
{
    ExamPriorityNode *front; // ponteiro para o primeiro nó da fila
    ExamPriorityNode *rear; // ponteiro para o último nó da fila
};

struct examPriorityNode
{
    Exam *data_exam; // ponteiro para a estrutura do paciente
    ExamPriorityNode *next; // ponteiro para o próximo nó da fila
    ExamPriorityNode *prev; // ponteiro para o nó anterior da fila
};

// Cria uma nova fila de pacientes vazia
ExamPriorityQueue *epq_create() {
    ExamPriorityQueue *epq = (ExamPriorityQueue *)malloc(sizeof(ExamPriorityQueue));
    
    if(epq == NULL) {
        perror("Falha ao alocar memória para a fila de pacientes");
        exit(1);
    }

    epq->front = NULL;
    epq->rear = NULL;
    return epq;
};

// Verifica se a fila de pacientes está vazia
int epq_is_empty(ExamPriorityQueue *epq) {
    return epq->front == NULL;
};

// Insere um paciente ao final da fila de pacientes (prioridade)
void epq_insert(ExamPriorityQueue *epq, Exam *exam) {
    ExamPriorityNode *node = (ExamPriorityNode *)malloc(sizeof(ExamPriorityNode));
    ExamPriorityNode *current = epq->front;
    ExamPriorityNode *previous = NULL;

    node->data_exam = exam;
    node->next = NULL;
    node->prev = NULL;

    if (epq_is_empty(epq)) {
        epq->front = node;
        epq->rear = node;
    } else {
        while (current != NULL && get_exam_priority(current->data_exam) > get_exam_priority(exam)) {
            previous = current;
            current = current->next;
        }

        if (previous == NULL) {
            // Insert at the front of the queue
            node->next = epq->front;
            epq->front->prev = node;
            epq->front = node;
        } else if (current == NULL) {
            // Insert at the end of the queue
            previous->next = node;
            node->prev = previous;
            epq->rear = node;
        } else {
            // Insert in the middle of the queue
            previous->next = node;
            node->prev = previous;
            node->next = current;
            current->prev = node;
        }
    }
    
    free(current);
    free(previous);
}

// Remove o paciente do início da fila de pacientes (prioridade)
Exam *epq_remove(ExamPriorityQueue *epq) {
    ExamPriorityNode *node = epq->front;
    Exam *exam = node->data_exam;

    if (epq->front == epq->rear) {
        epq->front = NULL;
        epq->rear = NULL;
    } else {
        epq->front = epq->front->next;
        epq->front->prev = NULL;
    }

    free(node);
    return exam;
}

void epq_destroy(ExamPriorityQueue *epq) {
    if(epq == NULL) {
        perror("A fila exame não foi inicializada");
        return;
    }
    
    ExamPriorityNode *current = epq->front;

    while (current != NULL) {
        current = current->next;
        destroy_exam(current->prev->data_exam);
        free(current->prev);
    }

    free(epq);
}