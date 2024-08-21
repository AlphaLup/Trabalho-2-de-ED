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
    FILE *file = fopen("db_report.txt", "wa");
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

char *get_report_condition(Report *report) {
    return report->condition;
}