#include "../include/Exam.h"
#include "../include/ExamPriorityQueue.h"
#include <stdlib.h>

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
}
