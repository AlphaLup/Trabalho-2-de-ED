#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "Exam.h"

// define a estrutura do exame
struct exam {
    int id;
    int patient_id;
    int rx_id;
    struct tm *time;
};

// cria um novo exame
Exam * create_exam (int id, int patient_id, int rx_id, struct tm *time) {

    // aloca memória para o novo exame
    Exam *exam;

    exam = (Exam *) malloc (sizeof(Exam));
    if(exam == NULL) {
        perror("Falha ao alocar memória para o exame");
        exit(1);
    }

    // define os valores do novo exame
    exam->id = id;
    exam->patient_id = patient_id;
    exam->rx_id = rx_id;
    exam-> time = time;

    // retorna o novo exame
    return exam;
}

// destrói um exame
void destroy_exam(Exam *exam) {
    // libera a memória alocada para a estrutura do exame
    if (exam != NULL) {
        free(exam->time);
        free(exam);
    }
}

// obtém o id de um exame
int get_exam_id(Exam *exam) {
    // retorna o id do exame
    return exam->id;
}

// obtém o id do paciente de um exame
int get_exam_patient_id(Exam *exam) {
    // retorna o id do paciente do exame
    return exam->patient_id;
}

// obtém o id da máquina de raio-x de um exame
int get_exam_rx_id(Exam *exam) {
    // retorna o id da máquina de raio-x do exame
    return exam->rx_id;
}

// obtém o horário do exame
struct tm * get_exam_time(Exam *exam) {
    // retorna o horário do exame
    return exam->time;
}
