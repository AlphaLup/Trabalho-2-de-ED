#ifndef REPORT_H
#define REPORT_H

#include "Exam.h"

typedef struct report Report;

Report *create_report(int id, Exam *exam, int register_time);

char *get_report_condition(Report *report);

#endif 