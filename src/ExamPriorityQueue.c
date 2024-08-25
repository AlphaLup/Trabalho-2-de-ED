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
    Exam *data_exam; // ponteiro para a estrutura do exame
    ExamPriorityNode *next; // ponteiro para o próximo nó da fila
    ExamPriorityNode *prev; // ponteiro para o nó anterior da fila
};

// Cria uma nova fila de exames vazia
ExamPriorityQueue *epq_create() {
    ExamPriorityQueue *epq = (ExamPriorityQueue *)malloc(sizeof(ExamPriorityQueue));
    
    if(epq == NULL) {
        perror("Falha ao alocar memória para a fila de exames");
        exit(1);
    }

    epq->front = NULL;
    epq->rear = NULL;
    return epq;
};

// Verifica se a fila de exames está vazia
int epq_is_empty(ExamPriorityQueue *epq) {
    return epq->front == NULL;
};

// Insere um exame ao final da fila de exames (prioridade)
void epq_insert(ExamPriorityQueue *epq, Exam *exam) {
    // aloca memória para o novo nó
    ExamPriorityNode *node = (ExamPriorityNode *)malloc(sizeof(ExamPriorityNode));

    // verifica se a alocação foi bem sucedida
    if(node == NULL) {
        perror("Falha ao alocar memória para o nó da fila de exames");
        exit(1);
    }

    // define os valores do novo nó
    ExamPriorityNode *current = epq->front;
    ExamPriorityNode *previous = NULL;

    node->data_exam = exam;
    node->next = NULL;
    node->prev = NULL;

    // verifica se a fila está vazia e insere o nó no início
    if (current == NULL) {
        epq->front = node;
        epq->rear = node;
    } else {
        // percorre a fila até encontrar a posição correta para inserir o nó
        while (current != NULL && get_exam_priority(current->data_exam) >= get_exam_priority(exam)) {
            previous = current;
            current = current->next;
        }

        if (previous == NULL) {
            // Insere no início da fila
            node->next = epq->front;
            epq->front->prev = node;
            epq->front = node;
        } else if (current == NULL) {
            // Insere no final da fila
            previous->next = node;
            node->prev = previous;
            epq->rear = node;
        } else {
            // Insere no meio da fila
            previous->next = node;
            node->prev = previous;
            node->next = current;
            current->prev = node;
        }
    }
}

// Remove o exame do início da fila de exames (prioridade)
Exam *epq_remove(ExamPriorityQueue *epq) {
    
    if (epq_is_empty(epq)) {
        perror("A fila de exames está vazia");
        return NULL;
    }

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
        perror("A fila de exames não foi inicializada");
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