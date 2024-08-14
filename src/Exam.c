#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Exam.h"

// define a estrutura do exame
struct exam {
    int id;
    int patient_id;
    int rx_id;
    struct tm *register_time;
    char condition_IA[20];
    int priority;
};

void ai_report(Exam *exam) {
    int ran_number = rand() % 100;
    if (ran_number >= 0 && ran_number <= 29) {
        strcpy(exam->condition_IA, "Saúde Normal");
        exam->priority = 1;
    } else if (ran_number >= 30 && ran_number <= 49) {
        strcpy(exam->condition_IA, "Bronquite");
        exam->priority = 2;
    } else if (ran_number >= 50 && ran_number <= 59) {
        strcpy(exam->condition_IA, "Pneumonia");
        exam->priority = 3;
    } else if (ran_number >= 60 && ran_number <= 69) {
        strcpy(exam->condition_IA, "COVID");
        exam->priority = 4;
    } else if (ran_number >= 70 && ran_number <= 74) {
        strcpy(exam->condition_IA, "Embolia pulmonar");
        exam->priority = 4;
    } else if (ran_number >= 75 && ran_number <= 79) {
        strcpy(exam->condition_IA, "Derrame pleural");
        exam->priority = 4;
    } else if (ran_number >= 80 && ran_number <= 84) {
        strcpy(exam->condition_IA, "Fibrose pulmonar");
        exam->priority = 5;
    } else if (ran_number >= 85 && ran_number <= 89) {
        strcpy(exam->condition_IA, "Turbeculose");
        exam->priority = 5;
    } else if (ran_number >= 90 && ran_number <= 99) {
        strcpy(exam->condition_IA, "Câncer de pulmão");
        exam->priority = 6;
    }
}

void save_exam(Exam *exam) {
    FILE *file = fopen("db_exam.txt", "w");
    if (file == NULL) {
        perror("Falha ao abrir o arquivo");
        exit(1);
    }

    // escreve os dados do paciente no arquivo
    fprintf(file, "%d\n", exam->id);
    fprintf(file, "%d\n", exam->patient_id);
    fprintf(file, "%d\n", exam->rx_id);
    fprintf(file, "%s\n", asctime(exam->register_time));
    fprintf(file, "%s\n", exam->condition_IA);
    fprintf(file, "%d\n", exam->priority);

    // fecha o arquivo
    fclose(file);
}

// cria um novo exame
Exam * create_exam (int id, int patient_id, int rx_id) {
    printf("pre current time");
    time_t current_time = time(NULL);
    struct tm *register_time = localtime(&current_time);
    printf("current time\n");

    // aloca memória para o novo exame
    Exam *exam = (Exam *) malloc (sizeof(Exam));
    printf("malloc\n");
    
    if(exam == NULL) {
        perror("Falha ao alocar memória para o exame");
        exit(1);
    }

    // define os valores do novo exame
    printf("1\n");
    exam->id = id;
    printf("2\n");
    exam->patient_id = patient_id;
    printf("3\n");
    exam->rx_id = rx_id;
    printf("4\n");
    exam->register_time = register_time;
    printf("5\n");
    // Faz o pré-diagnóstico com "IA"
    ai_report(exam);
    printf("6\n");
    // Salva o exame em um arquivo
    save_exam(exam);
    printf("7\n");

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

// obtém a condição do exame
char *get_exam_condition(Exam *exam) {
    // retorna a condição do exame
    return exam->condition_IA;
}

// obtém a prioridade do exame
int get_exam_priority(Exam *exam) {
    // retorna a prioridade do exame
    return exam->priority;
}
