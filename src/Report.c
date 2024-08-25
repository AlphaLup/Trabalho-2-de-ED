#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../include/Report.h"
#include "../include/Exam.h"

// define a estrutura do report
struct report {
    int id;
    int exam_id;
    char condition[20];
    int register_time;
};

void add_condition(Report *report, Exam *exam) {
    // gera um número aleatório entre 0 e 99
    int ran_number = rand() % 100;
    // define a condição do paciente baseado no número aleatório gerado
    if (ran_number >= 0 && ran_number <= 29) {
        strcpy(report->condition, "Saúde Normal");
    } else if (ran_number >= 30 && ran_number <= 49) {
        strcpy(report->condition, "Bronquite");
    } else if (ran_number >= 50 && ran_number <= 59) {
        strcpy(report->condition, "Pneumonia");
    } else if (ran_number >= 60 && ran_number <= 69) {
        strcpy(report->condition, "COVID");
    } else if (ran_number >= 70 && ran_number <= 74) {
        strcpy(report->condition, "Embolia pulmonar");
    } else if (ran_number >= 75 && ran_number <= 79) {
        strcpy(report->condition, "Derrame pleural");
    } else if (ran_number >= 80 && ran_number <= 84) {
        strcpy(report->condition, "Fibrose pulmonar");
    } else if (ran_number >= 85 && ran_number <= 89) {
        strcpy(report->condition, "Turbeculose");
    } else if (ran_number >= 90 && ran_number <= 99) {
        strcpy(report->condition, "Câncer de pulmão");
    }

    // se a condição gerada for a mesma do exame, gera outra condição
    if (report->condition == get_exam_condition(exam)) {
        add_condition(report, exam);
    }
}

// salva o report no arquivo
void save_report(Report *report) {
    FILE *file = fopen("db_report.txt", "a");
    // verifica se o arquivo foi aberto corretamente
    if (file == NULL) {
        perror("Falha ao abrir o arquivo");
        exit(1);
    }

    // escreve os dados do paciente no arquivo
    // fprintf(file, "%d\n", report->id);
    // fprintf(file, "%d\n", report->exam_id);
    // fprintf(file, "%s\n", report->condition);
    // fprintf(file, "%d\n", report->register_time);
    fprintf(file, "%d %d %d %s\n", report->id, report->exam_id, report->register_time, report->condition);

    // fecha o arquivo
    fclose(file);
}

// cria um report
Report *create_report(int id, Exam *exam, int register_time) {
    // aloca memória para o report
    Report *rep = (Report *)malloc(sizeof(Report));
    
    // verifica se a alocação foi bem sucedida
    if (rep == NULL) {
        perror("Falha ao alocar memória para o relatório");
        exit(1);
    }

    // define os valores do report
    rep->id = id;
    rep->exam_id = get_exam_id(exam);
    rep->register_time = register_time;

    double p = (double)rand() / (double)RAND_MAX;

    if(p < 0.8) {
        strcpy(rep->condition, get_exam_condition(exam));
    } else {
        add_condition(rep, exam);
    }

    // salva o report no arquivo
    save_report(rep);

    return rep;
}

// lê os reports do arquivo e imprime os tempos médios de espera de cada condição
void print_average_time_report() {
    float normal_time = 0, bronquite_time = 0, pneumonia_time = 0, covid_time = 0, embolia_time = 0, derrame_time = 0, fibrose_time = 0, tuberculose_time = 0, cancer_time = 0;
    int normal_count = 0, bronquite_count = 0, pneumonia_count = 0, covid_count = 0, embolia_count = 0, derrame_count = 0, fibrose_count = 0, tuberculose_count = 0, cancer_count = 0;

    FILE *file = fopen("db_report.txt", "r");
    if (file == NULL) {
        printf("0\n");
        return;
    }

    int rep_id, exam_id, register_time;
    char condition[25];
    char line[100];

    while (fgets(line, 100, file) != NULL) {
        sscanf(line, "%d %d %d %[^\n]", &rep_id, &exam_id, &register_time, condition);

        // printf("%d %d %s %d\n", rep_id, exam_id, condition, register_time); // TIRA

        Exam *exam = get_exam_by_id(exam_id);

        int exam_time = get_exam_time(exam);

        if (strcmp(condition, "Saúde Normal") == 0) {
            normal_time += register_time - exam_time;
            normal_count++;
        } else if (strcmp(condition, "Bronquite") == 0) {
            bronquite_time += register_time - exam_time;
            bronquite_count++;
        } else if (strcmp(condition, "Pneumonia") == 0) {
            pneumonia_time += register_time - exam_time;
            pneumonia_count++;
        } else if (strcmp(condition, "COVID") == 0) {
            covid_time += register_time - exam_time;
            covid_count++;
        } else if (strcmp(condition, "Embolia pulmonar") == 0) {
            embolia_time += register_time - exam_time;
            embolia_count++;
        } else if (strcmp(condition, "Derrame pleural") == 0) {
            derrame_time += register_time - exam_time;
            derrame_count++;
        } else if (strcmp(condition, "Fibrose pulmonar") == 0) {
            fibrose_time += register_time - exam_time;
            fibrose_count++;
        } else if (strcmp(condition, "Turbeculose") == 0) {
            tuberculose_time += register_time - exam_time;
            tuberculose_count++;
        } else if (strcmp(condition, "Câncer de pulmão") == 0) {
            cancer_time += register_time - exam_time;
            cancer_count++;
        }
    }

    fclose(file);

    // Print average times
    if (normal_count > 0) {
        printf("\tSaúde Normal: %.2f\n", normal_time / normal_count);
    }
    if (bronquite_count > 0) {
        printf("\tBronquite: %.2f\n", bronquite_time / bronquite_count);
    }
    if (pneumonia_count > 0) {
        printf("\tPneumonia: %.2f\n", pneumonia_time / pneumonia_count);
    }
    if (covid_count > 0) { 
        printf("\tCOVID: %.2f\n", covid_time / covid_count);
    }
    if (embolia_count > 0) {
        printf("\tEmbolia pulmonar: %.2f\n", embolia_time / embolia_count);
    }
    if (derrame_count > 0) {
        printf("\tDerrame pleural: %.2f\n", derrame_time / derrame_count);
    }
    if (fibrose_count > 0) {
        printf("\tFibrose pulmonar: %.2f\n", fibrose_time / fibrose_count);
    }
    if (tuberculose_count > 0) {
        printf("\tTuberculose: %.2f\n", tuberculose_time / tuberculose_count);
    }
    if (cancer_count > 0) {
        printf("\tCâncer de pulmão: %.2f\n", cancer_time / cancer_count);
    }
}

// retorna a condição do report
char *get_report_condition(Report *report) {
    return report->condition;
}

// retorna o momento de registro do report
int get_report_register_time(Report *report) {
    return report->register_time;
}

// retorna o id do exame cadastrado no report
int get_report_exam_id(Report *report) {
    return get_exam_id(get_exam_by_id(report->exam_id));
}