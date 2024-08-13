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
    struct tm * register_time;
};

// cria um novo paciente e salva os dados no arquivo db_patient.txt
Patient *create_patient(int id, const char *name) {
    Patient *new_patient;
    time_t current_time = time(NULL);
    struct tm *register_time = localtime(&current_time);

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
    new_patient->register_time = register_time;

    // abre o arquivo para escrita
    FILE *file = fopen("db_patient.txt", "a");
    if (!file) {
        perror("Falha ao abrir o arquivo");
        exit(1);
    }

    // escreve os dados do paciente no arquivo
    fprintf(file, "%d\n", new_patient->id);
    fprintf(file, "%s\n", new_patient->name);
    fprintf(file, "%s", asctime(new_patient->register_time));

    // fecha o arquivo
    fclose(file);

    return new_patient;
}

// destrói um paciente
void destroy_patient(Patient *patient) {
    // libera a memória alocada para a estrutura do paciente
    if (patient!=NULL) {
        free(patient->name);
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
    return patient->register_time;
}
