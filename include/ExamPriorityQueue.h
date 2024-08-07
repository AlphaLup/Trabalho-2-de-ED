#ifndef EXAMPRIORITYQUEUE_H
#define EXAMPRIORITYQUEUE_H

// define a estrutura da fila de pacientes
typedef struct examPriorityQueue ExamPriorityQueue;
typedef struct examPriorityNode ExamPriorityNode;

// criar uma nova fila de pacientes
// tipo de retorno: ExamPriorityQueue * --> um ponteiro para a estrutura da fila de pacientes
ExamPriorityQueue *epq_create();

// destruir uma fila de pacientes
// liberar a memória alocada para a estrutura da fila de pacientes
// tipo de retorno: void
void epq_destroy(ExamPriorityQueue *epq);

// inserir um paciente na fila de pacientes
// tipo de retorno: void
void epq_insert(ExamPriorityQueue *epq, Exam *exam);

// remover um paciente da fila de pacientes
// tipo de retorno: Exam *
Exam * epq_remove(ExamPriorityQueue *epq);


#endif