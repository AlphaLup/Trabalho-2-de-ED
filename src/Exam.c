#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Exam.h"

// define a estrutura do exame
struct exam {
    int id;
    int patient_id;
    int rx_id;
    int register_time;
    char condition_IA[20];
    int priority;
};

// faz o pré-diagnóstico do exame com "IA"
void ai_report(Exam *exam) {
    // Gera um número aleatório para simular o diagnóstico da IA
    int ran_number = rand() % 100;

    // Atribui uma condição ao exame de acordo com o número gerado
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

// salva um exame em um arquivo .txt
void save_exam(Exam *exam) {
    // abre o arquivo para escrita
    FILE *file = fopen("db_exam.txt", "a");

    // verifica se o arquivo foi aberto corretamente
    if (file == NULL) {
        perror("Falha ao abrir o arquivo");
        exit(1);
    }

    // escreve os dados do paciente no arquivo
    fprintf(file, "%d %d %d %d %d %s\n", exam->id, exam->patient_id, exam->rx_id, exam->register_time, exam->priority, exam->condition_IA);
    // fecha o arquivo
    fclose(file);
}

// cria um novo exame
Exam * create_exam (int id, int patient_id, int rx_id, int register_time) {
    // aloca memória para o novo exame
    Exam *exam = (Exam *) malloc (sizeof(Exam));
    
    // verifica se a alocação de memória foi bem sucedida
    if(exam == NULL) {
        perror("Falha ao alocar memória para o exame");
        exit(1);
    }

    // define os valores do novo exame
    exam->id = id;
    exam->patient_id = patient_id;
    exam->rx_id = rx_id;
    exam->register_time = register_time;
    // Faz o pré-diagnóstico com "IA"
    ai_report(exam);
    // Salva o exame em um arquivo
    save_exam(exam);

    // retorna o novo exame
    return exam;
}

// destrói um exame
void destroy_exam(Exam *exam) {
    // libera a memória alocada para a estrutura do exame
    if (exam != NULL) {
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
int get_exam_time(Exam *exam) {
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


// obtém um exame pelo id
Exam * get_exam_by_id(int id) {
    // abre o arquivo para leitura
    FILE *file = fopen("db_exam.txt", "r");
    
    // verifica se o arquivo foi aberto corretamente
    if (file == NULL) {
        perror("Falha ao abrir o arquivo");
        exit(1);
    }

    // aloca memória para o exame
    Exam *exam = (Exam *) malloc (sizeof(Exam));

    // verifica se a alocação de memória foi bem sucedida
    if(exam == NULL) {
        perror("Falha ao alocar memória para o exame");
        exit(1);
    }

    // declara as variáveis para armazenar os dados do exame
    char line[100];
    int exam_id, patient_id, rx_id, register_time, priority;
    char condition[25];

    // lê os dados do exame
    while (fgets(line, 100, file) != NULL) {
        // lê os dados do exame
        sscanf(line, "%d %d %d %d %d %[^\n]", &exam_id, &patient_id, &rx_id, &register_time, &priority, condition);
        if (exam_id == id) {
            // define os valores do exame e sai do loop
            exam->id = exam_id;
            exam->patient_id = patient_id;
            exam->rx_id = rx_id;
            exam->register_time = register_time;
            strcpy(exam->condition_IA, condition);
            exam->priority = priority;
            break;
        } 
    }
    
    // fecha o arquivo
    fclose(file);

    // retorna o exame
    return exam;
}

// imprime os dados de um exame
void print_exam(Exam *exam) {
    printf("ID: %d\n", get_exam_id(exam));
    printf("Patient ID: %d\n", get_exam_patient_id(exam));
    printf("RX ID: %d\n", get_exam_rx_id(exam));
    printf("Register Time: %d\n", get_exam_time(exam));
    printf("Condition: %s\n", get_exam_condition(exam));
    printf("Priority: %d\n\n", get_exam_priority(exam));
}