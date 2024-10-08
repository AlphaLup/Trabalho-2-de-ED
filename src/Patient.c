#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Patient.h"

// define a estrutura do paciente
struct patient 
{
    int id;
    char name[100];
    int register_time;
};

// cria um novo paciente e salva os dados no arquivo db_patient.txt
Patient *create_patient(int id, const char *name, int register_time) {
    Patient *new_patient;

    // aloca memória para o novo paciente
    new_patient = (Patient *)malloc(sizeof(Patient));
    if (new_patient == NULL) {
        perror("Falha ao alocar memória para o paciente");
        exit(1);
    }

    // define os valores do novo paciente
    new_patient->id = id;
    strcpy(new_patient->name, name);
    new_patient->register_time = register_time; 

    // salva os dados do paciente no arquivo
    save_patient(new_patient);

    return new_patient;
}

void save_patient(Patient *patient) {
    // abre o arquivo para escrita
    FILE *file = fopen("db_patient.txt", "a");
    if (!file) {
        perror("Falha ao abrir o arquivo");
        exit(1);
    }
    
    // escreve os dados do paciente no arquivo
    fprintf(file, "%d %s %d\n", patient->id, patient->name, patient->register_time);

    // fecha o arquivo
    fclose(file);
}

// destrói um paciente
void destroy_patient(Patient *patient) {
    // libera a memória alocada para a estrutura do paciente
    if (patient!=NULL) {
        free(patient);
    }
}

// obtém o ID de um paciente
int get_patient_id(Patient *patient) {
    return patient->id;
}

// obtém o nome de um paciente
char * get_patient_name(Patient *patient) {
    // retorna um ponteiro com o conteúdo do campo patient->name
    return patient->name;
}

// obtém a data de nascimento de um paciente
int get_patient_register_time(Patient *patient) {
    // retorna um ponteiro referenciando a estrutura tm de <time.h>
    return patient->register_time;
}

Patient *get_patient_by_id(int id) {
    // abre o arquivo para leitura
    FILE *file = fopen("db_patient.txt", "r");
    if (!file) {
        perror("Falha ao abrir o arquivo");
        exit(1);
    }

    // aloca memória para a estrutura do paciente
    Patient *patient = (Patient *)malloc(sizeof(Patient));
    if (patient == NULL) {
        perror("Falha ao alocar memória para o paciente");
        exit(1);
    }

    int id_aux;
    char line[100];

    // lê os dados do arquivo e salva na estrutura do paciente
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d", &id_aux);
        if (id_aux == id) {
            sscanf(line, "%d %s %d", &patient->id, patient->name, &patient->register_time);
            fclose(file);
            return patient;
        }

    }

    // fecha o arquivo e retorna NULL caso não encontre o paciente
    fclose(file);

    return NULL;
}