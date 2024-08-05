#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Patient.h"

// define a estrutura do paciente
struct patient 
{
    int id;
    char * name;
    struct tm * register_date;
};

// cria um novo paciente
Patient *create_patient(int id, const char *name, struct tm *register_date) {
    Patient *new_patient;

    // aloca memória para o novo paciente
    new_patient = (Patient *)malloc(sizeof(Patient));
    new_patient->name = (char *)malloc(strlen(name));
    if (new_patient == NULL) {
        perror("Falha ao alocar memória para o paciente");
        exit(1);
    }

    // define os valores do novo paciente
    new_patient->id = id;
    new_patient->name = strdup(name);
    new_patient->register_date = register_date;

    return new_patient;
}

// destrói um paciente
void destroy_patient(Patient *patient) {
    // libera a memória alocada para a estrutura do paciente
    if (patient!=NULL) {
        // free(patient->name);
        // free(patient->register_date);
        free(patient);
    }
}

// obtém o ID de um paciente
int get_patient_id(const Patient *patient) {
    // retorna o ID do paciente
    return patient->id;
}

// obtém o nome de um paciente
char * get_patient_name(const Patient *patient) {
    // retorna um ponteiro contendo uma cópia do campo name da estrutura patient
    return patient->name;
}

// obtém a data de nascimento de um paciente
struct tm * get_patient_register_date(const Patient *patient) {
    // retorna um ponteiro referenciando a estrutura tm de <time.h>
    return patient->register_date;
}
