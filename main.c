#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #include <locale.h>
#include "Exam.h"
#include "Patient.h"
#include "PatientQueue.h"

int main(){
    // Definindo a padronização de string para o idioma português
    // setlocale(LC_ALL, "PORTUGUESE_BRAZIL.UTF-8");

    // Definindo uma data de nascimento fictícia para o paciente
    struct tm birthdate = {0}; // Inicializar a estrutura com zeros
    birthdate.tm_year = 90; // Ano 1990
    birthdate.tm_mon = 5; // Junho (0-indexed)
    birthdate.tm_mday = 15; // Dia 15

    // Criando um paciente
    Patient *patient = create_patient(1, "João Silva", &birthdate);

    // Imprimindo informações do paciente criado
    printf("Paciente criado:\n");
    printf("ID: %d\n", get_patient_id(patient));
    printf("Nome: %s\n", get_patient_name(patient));
    printf("Data de Nascimento: %s\n", asctime(get_patient_birthdate(patient)));

    // Definindo uma data e hora fictícias para o exame
    time_t current_time;
    struct tm *exam_time;

    // Tempo do exame é o tempo atual
    current_time = time(NULL); // Obter o tempo atual em segundos desde 01/01/1970
    exam_time = localtime(&current_time); // Converter o tempo atual para hora local

    // Criando um exame associado ao paciente criado
    Exam *exam = create_exam(101, get_patient_id(patient), 1, exam_time);

    // Imprimindo informações do exame criado
    printf("\nExame criado:\n");
    printf("ID: %d\n", get_exam_id(exam));
    printf("ID do Paciente: %d\n", get_exam_patient_id(exam));
    printf("ID do Aparelho de Raio-X: %d\n", get_exam_rx_id(exam));
    printf("Data e Hora do Exame: %s\n", asctime(get_exam_time(exam)));

    // Liberando a memória alocada
    destroy_exam(exam);
    destroy_patient(patient);

    return 0;
}