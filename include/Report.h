#ifndef REPORT_H
#define REPORT_H

#include "Exam.h"

typedef struct report Report;

Report *create_report(int id, Exam *exam, int register_time);

void print_average_time_report();

char *get_report_condition(Report *report);

int get_report_register_time(Report *report);

int get_report_exam_id(Report *report);

#endif 