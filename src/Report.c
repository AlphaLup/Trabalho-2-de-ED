#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/Report.h"
#include "../include/Exam.h"

struct report {
    int id;
    int exam_id;
    char condition[20];
    int register_time;
};

void add_condition(Report *report, Exam *exam) {
    int ran_number = rand() % 100;
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

    if (report->condition == get_exam_condition(exam)) {
        add_condition(report, exam);
    }
}

void save_report(Report *report) {
    FILE *file = fopen("db_report.txt", "a");
    if (file == NULL) {
        perror("Falha ao abrir o arquivo");
        exit(1);
    }

    // escreve os dados do paciente no arquivo
    fprintf(file, "%d\n", report->id);
    fprintf(file, "%d\n", report->exam_id);
    fprintf(file, "%s\n", get_report_condition(report));
    fprintf(file, "%d\n", report->register_time);

    // fecha o arquivo
    fclose(file);
}

Report *create_report(int id, Exam *exam, int register_time) {
    Report *rep;

    rep = (Report *)malloc(sizeof(Report));
    if (rep == NULL) {
        perror("Falha ao alocar memória para o relatório");
        exit(1);
    }

    rep->id = id;
    rep->exam_id = get_exam_id(exam);
    rep->register_time = register_time;

    double p = (double) rand() / (double)RAND_MAX;

    if(p < 0.8) {
        strcpy(rep->condition, get_exam_condition(exam));
    } else {
        add_condition(rep, exam);
    }

    save_report(rep);

    return rep;
}

void print_average_time_report() {
    float normal_time, bronquite_time, pneumonia_time, covid_time, embolia_time, derrame_time, fibrose_time, tuberculose_time, cancer_time = 0;
    int normal_count, bronquite_count, pneumonia_count, covid_count, embolia_count, derrame_count, fibrose_count, tuberculose_count, cancer_count = 0;

    FILE *file = fopen("db_report.txt", "r");
    if (file == NULL) {
        printf("0\n");
    } else {

        int rep_id, exam_id, register_time;
        char condition[20];

        while (!feof(file)) {
            fscanf(file, "%d", &rep_id);
            fscanf(file, "%d", &exam_id);
            fscanf(file, "%s", condition);
            fscanf(file, "%d", &register_time);

            Exam *exam = get_exam_by_id(exam_id);

            if (strcmp(condition, "Saúde Normal") == 0) {
                normal_time += (register_time - get_exam_time(exam));
                normal_count++;
            } else if (strcmp(condition, "Bronquite") == 0) {
                bronquite_time += (register_time - get_exam_time(exam));
                bronquite_count++;
            } else if (strcmp(condition, "Pneumonia") == 0) {
                pneumonia_time += (register_time - get_exam_time(exam));
                pneumonia_count++;
            } else if (strcmp(condition, "COVID") == 0) {
                covid_time += (register_time - get_exam_time(exam));
                covid_count++;
            } else if (strcmp(condition, "Embolia pulmonar") == 0) {
                embolia_time += (register_time - get_exam_time(exam));
                embolia_count++;
            } else if (strcmp(condition, "Derrame pleural") == 0) {
                derrame_time += (register_time - get_exam_time(exam));
                derrame_count++;
            } else if (strcmp(condition, "Fibrose pulmonar") == 0) {
                fibrose_time += (register_time - get_exam_time(exam));
                fibrose_count++;
            } else if (strcmp(condition, "Turbeculose") == 0) {
                tuberculose_time += (register_time - get_exam_time(exam));
                tuberculose_count++;
            } else if (strcmp(condition, "Câncer de pulmão") == 0) {
                cancer_time += (register_time - get_exam_time(exam));
                cancer_count++;
            }
        }

        printf("\tSaúde Normal: %.2f\n", normal_time / normal_count);
        printf("\tBronquite: %.2f\n", bronquite_time / bronquite_count);
        printf("\tPneumonia: %.2f\n", pneumonia_time / pneumonia_count);
        printf("\tCOVID: %.2f\n", covid_time / covid_count);
        printf("\tEmbolia pulmonar: %.2f\n", embolia_time / embolia_count);
        printf("\tDerrame pleural: %.2f\n", derrame_time / derrame_count);
        printf("\tFibrose pulmonar: %.2f\n", fibrose_time / fibrose_count);
        printf("\tTurbeculose: %.2f\n", tuberculose_time / tuberculose_count);
        printf("\tCâncer de pulmão: %.2f\n", cancer_time / cancer_count);

        fclose(file);
    }    
}

char *get_report_condition(Report *report) {
    return report->condition;
}

int get_report_register_time(Report *report) {
    return report->register_time;
}

int get_report_exam_id(Report *report) {
    return get_exam_id(get_exam_by_id(report->exam_id));
}