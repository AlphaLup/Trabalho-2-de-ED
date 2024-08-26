#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>
//#include <windows.h> -> for windows
#include "./include/Exam.h"
#include "./include/Patient.h"
#include "./include/PatientQueue.h"
#include "./include/XRMachineManager.h"
#include "./include/ExamPriorityQueue.h"
#include "./include/Report.h"

#define LOOP_TIME 43200

void hospital_record();

int main() {

    // Configuração de localidade
    setlocale(LC_ALL, "Portuguese.UTF8");


    /* Iniciando Variáveis */


    // Gerando uma lista com 20 nomes diferentes
    char *names[20] = {"João","Maria","Pedro","Ana","Carlos","Mariana","Lucas","Julia","Fernando","Camila","Gustavo","Isabela","Rafael","Larissa","Rodrigo","Amanda","Diego","Natália","Marcelo","Letícia"};

    // Variáveis
    int pat_id = 1;
    int exam_id = 1;
    int rep_id = 1;
    int count_exam = 0;
    int count_reports = 0;
    int count_limit = 0; 
    int epq_time = 0;
    int wait_time;


    // Criando as variáveis de controle para as máquinas e pacientes
    XRMachine *mach_aux = NULL;
    Patient *patient_aux = NULL;
    Exam *exam_aux = NULL;

    // Fila de pacientes sem prioridade
    PatientQueue *pq = pq_create();

    // Gerenciador de máquinas de raio-x
    XRMachineManager *xr = xr_create();

    for (int k = 0; k < 5; k++) {
        xr_insert(xr, k);
    };

    // Fila de exames com prioridade
    ExamPriorityQueue *epq = epq_create();    

    // Seed para a função rand()
    srand(time(NULL));

    /* Inicia a Simulação */

    // Cria os arquivos de banco de dados ou os limpa dos dados prévios
    FILE *file;
    file = fopen("db_exam.txt", "w");
    fclose(file);
    file = fopen("db_report.txt", "w");
    fclose(file);
    file = fopen("db_patient.txt", "w");
    fclose(file);

    printf("#############################################\n##  Bem-vindo ao Hospital Imagine Dragons  ##\n#############################################\n\nRelatórios serão impressos a cada %d unidades de tempo!\n\n", 4320);

    // Loop principal de passagem de tempo
    for(int i = 1; i <= LOOP_TIME; i++) {
        /* Impressão do Relatório */

        if (i % 4320 == 0) {
            hospital_record(pat_id, count_exam, count_reports, epq_time, count_limit);
        }
        
        /* Fila de Pacientes */

        if (rand() % 10 <= 1) {
            /* Cadastro de Pacientes */

            int name_index = rand() % 20;
            patient_aux = create_patient(pat_id, names[name_index], i);
            if (patient_aux == NULL) {
                printf("Erro ao criar paciente!\n\n");
                return 1;
            }
            
            // Incrementa o id do paciente
            pat_id ++;

            // Adiciona o paciente à fila
            pq_insert(pq, patient_aux);            
        }

        /* Máquinas de Raio-X */

        /*    Gera exame ao finalizar uso da máquina    */

        // Verifica se a máquina está disponível
        mach_aux = xr_finished(xr, i);

        if (mach_aux != NULL) {
            // Obtem o paciente da máquina
            Patient *patient = xr_get_patient(mach_aux);
            // Verifica se o paciente realmente existe
            if (patient != NULL) {
                // Cria o exame
                int patient_id = get_patient_id(patient);
                int xr_id = xr_get_id(mach_aux);

                Exam *exam = create_exam(exam_id, patient_id, xr_id, i);

                // Incrementa o contador de exames
                count_exam++;
                if (exam != NULL) {
                    // Adiciona o exame à fila de prioridade
                    epq_insert(epq, exam);
                    // Incrementa o id do exame
                    exam_id++;
                    // Limpa a máquina
                    clear_machine(mach_aux);
                } else {
                    printf("Erro ao criar exame!\n\n");
                    return 1;
                }                
            } else {
                printf("Erro ao obter paciente!\n\n");
                return 1;
            }
        }

        /* Direciona um paciente a uma máquina */

        // Verifica se a máquina está disponível e se há pacientes na fila
        mach_aux = xr_available(xr);
        
        if (mach_aux != NULL && !pq_is_empty(pq)) {
            // Remove o paciente da fila
            patient_aux = pq_remove(pq);
            // Atribui o paciente à máquina
            xr_add_patient(mach_aux, patient_aux, i + 10);
        }

        /* Laudo Médico */

        if (exam_aux == NULL) {
            if (!epq_is_empty(epq)) {
                // Se a fila de prioridade não estiver vazia, remove o exame
                exam_aux = epq_remove(epq);
                // Define o tempo de espera para o laudo (report)
                wait_time = i + 30;
            }
        } else {
            if (i == wait_time) {
                // Cria o laudo
                Report * r = create_report(rep_id, exam_aux, i);

                // Verifica se o laudo foi criado com sucesso
                if (r == NULL) {
                    printf("Erro ao criar laudo!\n\n");
                    return 1;
                }
                // Incrementa o id do laudo
                rep_id++;
                // Incrementa o contador de laudos
                count_reports++;
                // Incrementa o tempo de espera geral da fila de prioridade
                epq_time += i - get_exam_time(exam_aux);
                
                // Variáveis auxiliares
                int rp_rt = get_report_register_time(r);
                int id = get_exam_patient_id(exam_aux);
                int rt_p = get_patient_register_time(get_patient_by_id(id));               
                                
                // Verifica se o paciente esperou mais de 7200 unidades de tempo e incrementa o contador, em caso positivo
                if (rp_rt - rt_p > 7200) {
                    count_limit++;
                }
                exam_aux = NULL;
            }
        }
        
    }

    printf("Fim da simulação!\n\n");

    // Libera a memória alocada
    epq_destroy(epq);
    xr_destroy(xr);
    pq_destroy(pq);

    return 0;
}


// Relatório do hospital
void hospital_record(int num_patients, int num_exam, int num_reports, int epq_time, int count_limit) {
    printf("--> Relatório do Hospital <--\n\n");
    printf("Número de pacientes cadastrados: %d\n", num_patients);
    printf("Número de pacientes na fila aguardando o exame: %d\n", num_patients - num_exam);
    printf("Número de pacientes que realizaram exame: %d\n", num_exam);
    printf("Porcentagem de pacientes que realizaram exame e receberam laudo: %.2f%%\n", ((float)num_reports / num_exam * 100));
    printf("Tempo médio para receber o laudo: %d\n", num_reports == 0 ? 0 : epq_time / num_reports);
    printf("Tempo médio por condição:\n");
    // Imprime o tempo médio por condição
    print_average_time_report();    
    printf("Número de pacientes que esperaram mais de 7200 unidades de tempo: %d\n\n", count_limit);

    // Aguarda 10 segundos para a continuação da simulação
    sleep(10);
}

