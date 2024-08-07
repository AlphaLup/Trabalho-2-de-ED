#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "Exam.h"

// define a estrutura do exame
struct exam {
    int id;
    int patient_id;
    int rx_id;
    struct tm *register_time;
    char condition_IA;
    int priority;
};

// cria um novo exame
Exam * create_exam (int id, int patient_id, int rx_id) {
    time_t current_time = time(NULL);
    struct tm *register_time = localtime(&current_time);

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
    exam->register_time = register_time;

    int ran_number = rand() % 100;
    switch (ran_number)
    {
    case 0 ... 29:
        exam->condition_IA = 'Saúde Normal';
        exam->priority = 1;
        break;
    case 30 ... 49:
        exam->condition_IA = 'Bronquite';
        exam->priority = 2;
        break;
    case 50 ... 59:
        exam->condition_IA = 'Pneumonia';
        exam->priority = 3;
        break;
    case 60 ... 69:
        exam->condition_IA = 'COVID';
        exam->priority = 4;
        break;
    case 70 ... 74:
        exam->condition_IA = 'Embolia pulmonar';
        exam->priority = 4;
        break;
    case 75 ... 79:
        exam->condition_IA = 'Derrame pleural';
        exam->priority = 4;
        break;
    case 80 ... 84:
        exam->condition_IA = 'Fibrose pulmonar';
        exam->priority = 5;
        break;
    case 85 ... 89:
        exam->condition_IA = 'Turbeculose';
        exam->priority = 5;
        break;
    case 90 ... 99:
        exam->condition_IA = 'Câncer de pulmão';
        exam->priority = 6;
        break;
    }

    FILE *file = fopen("db_exam.txt", "w");
    if (file == NULL) {
        perror("Falha ao abrir o arquivo");
        exit(1);
    }

    // escreve os dados do paciente no arquivo
    fprintf(file, "%d\n", exam->id);
    fprintf(file, "%s\n", exam->patient_id);
    fprintf(file, "%s\n", exam->rx_id);
    fprintf(file, "%s\n", asctime(exam->register_time));
    fprintf(file, "%s\n", exam->condition_IA);
    fprintf(file, "%s\n", exam->priority);

    // fecha o arquivo
    fclose(file);

    // retorna o novo exame
    return exam;
}

// destrói um exame
void destroy_exam(Exam *exam) {
    // libera a memória alocada para a estrutura do exame
    if (exam != NULL) {
        free(exam->register_time);
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
    return exam->register_time;
}
