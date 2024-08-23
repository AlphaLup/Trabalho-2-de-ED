#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>
#include "./include/Exam.h"
#include "./include/Patient.h"
#include "./include/PatientQueue.h"
#include "./include/XRMachineManager.h"
#include "./include/ExamPriorityQueue.h"
#include "./include/Report.h"

#define LOOP_TIME 4320

void hospital_record();

int main() {

    // Configuração de localidade
    setlocale(LC_ALL, "Portuguese.UTF8");

    /*#####################################
    ##        Iniciando variáveis        ##    
    #####################################*/


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
    int cooldown;


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

    /*#######################################
    ##        Iniciando a simulação        ##      
    #######################################*/

    // Mensagem de boas-vindas
    printf("#############################################\n##  Bem-vindo ao Hospital Imagine Dragons  ##\n#############################################\n\nRelatórios serão impressos a cada %d unidades de tempo!\n\n", LOOP_TIME);

    // Loop de passagem de tempo
    for(int i = 0; i < 43200; i++) {

        /*#######################################
        ##        Print do Relatório           ##      
        #######################################*/

        if (i % 4320 == 0 && i != 0) {
            hospital_record(pat_id, count_exam, count_reports, epq_time, count_limit);
        }
        
        /*#######################################
        ##        Fila de pacientes            ##      
        #######################################*/

        // 20% de chance de um paciente chegar
        if (rand() % 10 <= 1) {
            /*    Cadastro de Pacientes    */

            // Escolhe um dos nomes da lista aleatóriamente
            // Cria um paciente com o ID, nome e data de registro
            int name_index = rand() % 20;
            patient_aux = create_patient(pat_id, names[name_index], i);
            
            // Controle do ID do paciente
            pat_id ++;

            // Insere paciente na fila
            pq_insert(pq, patient_aux);            
        }

        /*########################################
        ##        Maquinas de Raio-X            ##      
        ########################################*/

        /*    Gera exame ao finalizar uso da máquina    */

        // Verifica se alguma máquina já terminou
        // Caso positivo, ele retornará um ponteiro para uma máquina na variável 'machine'
        // OBS: Apenas uma máquina por vez poderá finalizar a cada ciclo (devido a lógica do código)
        
        mach_aux = xr_finished(xr, i);

        // Direciona o paciente para o exame com pré-diagnístico de IA
        if (mach_aux != NULL) {
            Patient *patient = xr_get_patient(mach_aux);

            if (patient != NULL) {
                int patient_id = get_patient_id(patient);
                int xr_id = xr_get_id(mach_aux);

                Exam *exam = create_exam(exam_id, patient_id, xr_id, i);
                count_exam++;
                if (exam != NULL) {
                    epq_insert(epq, exam);
                    exam_id++;
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

        /*    Direciona um paciente a uma máquina    */

        // Verifica se há alguma máquina disponível
        mach_aux = xr_available(xr);
        
        if (mach_aux != NULL && !pq_is_empty(pq)) {
            // Adiciona um paciente à essa máquina
            patient_aux = pq_remove(pq);
            xr_add_patient(mach_aux, patient_aux, i + 10);
        }

        /*######################
        ##    Medic Report    ##
        ######################*/    

        // Verifica se há algum exame pronto
        if (exam_aux == NULL) {

            // Verifica se há algum exame pronto
            if (!epq_is_empty(epq)) {
                exam_aux = epq_remove(epq);
                cooldown = i + 30;
            }
        } else {
            if (i == cooldown) {
                // Cria um laudo médico
                Report * r = create_report(rep_id, exam_aux, i);
                if (r == NULL) {
                    printf("Erro ao criar laudo!\n\n");
                    return 1;
                }
                rep_id++;
                count_reports++;
                epq_time += i - get_exam_time(exam_aux);
                
                // Variaveis auxiliares para achar o patient id pelo report
                int ex_id = get_report_exam_id(r);
                printf("ex_id %d\n", ex_id);
                int pa_id = get_exam_patient_id(get_exam_by_id(ex_id));
                printf("pa_id %d\n", pa_id);
                int rp_rt = get_report_register_time(r);
                printf("rp_rt %d\n", rp_rt);
                int rt_p = get_patient_register_time(get_patient_by_id(pa_id));
                printf("rt_p %d\n\n", rt_p);
                
                // Verifica se o paciente esperou mais de 7200 unidades de tempo
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
    free(mach_aux);
    free(patient_aux);
    free(exam_aux);

    return 0;
}


// Relatório do hospital
void hospital_record(int num_patients, int num_exam, int num_reports, int epq_time, int count_limit) {
    printf("--> Relatório do Hospital <--\n\n");
    printf("Número de pacientes cadastrados: %d\n", num_patients);
    printf("Número de pacientes na fila de exame: %d\n", num_patients - num_exam);
    printf("Número de pacientes que realizaram exame: %d\n", num_exam);
    printf("Porcentagem de pacientes que realizaram exame e receberam laudo: %.2f%%\n", ((float)num_reports / num_exam * 100));
    printf("Tempo médio para receber o laudo: %d\n", num_reports == 0 ? 0 : epq_time / num_reports);
    printf("Tempo médio por condição:\n");
    print_average_time_report();    
    printf("Número de pacientes que esperaram mais de 7200 unidades de tempo: %d\n\n", count_limit);

    sleep(10);
}

