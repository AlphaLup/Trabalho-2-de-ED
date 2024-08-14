#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>
#include "./include/Exam.h"
#include "./include/Patient.h"
#include "./include/PatientQueue.h"
#include "./include/XRMachineManager.h"
#include "./include/ExamPriorityQueue.h"
#include "./include/Report.h"

int main() {

    // Configuração de localidade
    setlocale(LC_ALL, "Portuguese.UTF8");

    /*#####################################
    ##        Iniciando variáveis        ##    
    #####################################*/


    // Gerando uma lista com 20 nomes diferentes
    char *names[20] = {"João","Maria","Pedro","Ana","Carlos","Mariana","Lucas","Julia","Fernando","Camila","Gustavo","Isabela","Rafael","Larissa","Rodrigo","Amanda","Diego","Natália","Marcelo","Letícia"};

    // Gerando contadores para o ID
    int pat_id = 1;
    int exam_id = 1;

    // Criando as variáveis de controle para as máquinas e pacientes
    XRMachine *mach;
    Patient *patient;

    // Fila de pacientes sem prioridade
    PatientQueue *pq = pq_create();

    // Gerenciador de máquinas de raio-x
    XRMachineManager *xr = xr_create();

    for (int k = 0; k < 5; k++) {
        xr_insert(xr, k);
    };
    // Fila de exames com prioridade
    ExamPriorityQueue *epq = epq_create();


    /*###################################
    ##        Biblioteca time.h        ##      
    ###################################*/
    

    // Seed para a função rand()
    srand(time(NULL));
    
    // Data e hora atual
    time_t current_time = time(NULL);
    struct tm *current = localtime(&current_time);    


    /*#######################################
    ##        Iniciando a simulação        ##      
    #######################################*/


    // Mensagem de boas-vindas
    printf("#############################################\n##  Bem-vindo ao Hospital Imagine Dragons  ##\n#############################################\n\nData: %d/%d/%d\tHora: %d:%d\n\n", current->tm_mday, current->tm_mon + 1, current->tm_year + 1900, current->tm_hour, current->tm_min);

    // Loop de passagem de tempo
    for(int i = 0; i < 200; i++) {

        
        /*#######################################
        ##        Fila de pacientes            ##      
        #######################################*/

        char *reception_message = "-----------------------------------------\n"
                             "\t\tRecepção\n"
                             "-----------------------------------------\n\n";
        printf("%s", reception_message);

        // 20% de chance de um paciente chegar
        printf("Verificando se há pacientes chegando...\n\n");

        if (rand() % 10 <= 1) {
            /*    Cadastro de Pacientes    */

            // Escolhe um dos nomes da lista aleatóriamente
            int name_index = rand() % 20;

            printf("%s chegou!\t\t\t\t\nAguardando... ", names[name_index]);

            // Cria um paciente com o ID, nome e data de registro
            patient = create_patient(pat_id, names[name_index]);

            // Insere paciente na fila
            pq_insert(pq, patient);

            // Controle do ID do paciente
            pat_id ++;

            printf("Paciente cadastrado e inserido na fila!\n\n");
            printf("Encaminhando para setor de raio-x...\n\n");
        
        }

        /*########################################
        ##        Maquinas de Raio-X            ##      
        ########################################*/

        /*    Mensagem de raio-x    */

        char *xray_message = "-----------------------------------------\n"
                             "\t\tSETOR DE RAIO-X\n"
                             "-----------------------------------------\n\n";
        printf("%s", xray_message);

        /*    Gera exame ao finalizar uso da máquina    */

        printf("---> Verificando se há exames prontos...\n\n");

        // Verifica se alguma máquina já terminou
        // Caso positivo, ele retornará um ponteiro para uma máquina na variável 'machine'
        // OBS: Apenas uma máquina por vez poderá finalizar a cada ciclo (devido a lógica do código)
        
        mach = xr_finished(xr, i);

        // Direciona o paciente para o exame com laudo de IA
        if (mach != NULL) {
            Patient *patient = xr_get_patient(mach);
            if (patient != NULL) {
                printf("Exame da máquina %d finalizado!\n", xr_get_id(mach));
                printf("antes do patid");
                int patient_id = get_patient_id(patient);
                printf("passou patid");
                int xr_id = xr_get_id(mach);
                printf("passou xrid");
                Exam *exam = create_exam(exam_id, patient_id, xr_id);
                if (exam != NULL) {
                    printf("Exame encaminhado para fila de exame com pré-laudo de IA!\n\n");
                    exam_id++;
                    epq_insert(epq, exam);
                    clear_machine(mach);
                    printf("Paciente encaminhado para fila de exame com pré-laudo de IA!\n\n");
                } else {
                    printf("Erro ao criar exame!\n\n");
                }
            } else {
                printf("Erro ao obter paciente!\n\n");
            }
        } else {
            printf("Nenhum exame pronto no momento!\n\n");
        }

        /*    Direciona um paciente a uma máquina    */

        printf("---> Verificando máquinas disponíveis...\n\n");

        // Verifica se há alguma máquina disponível
        mach = xr_available(xr);
        
        if (mach != NULL && !pq_is_empty(pq)) {
            // Adiciona um paciente à essa máquina
            patient = pq_remove(pq);
            xr_add_patient(mach, patient, i + 10);
            printf("Um paciente foi encaminhado!\n\nMáquina: %d\n\n", xr_get_id(mach));
        } else if (mach == NULL && !pq_is_empty(pq)) {
            printf("Nenhuma máquina disponível no momento!\n\n");
        } else {
            printf("Nenhum paciente na fila!\n\n");
        }

        printf("%d", i);

        // Espera para o próximo ciclo
        Sleep(500);
    }

    // Libera a memória alocada
    epq_destroy(epq);
    xr_destroy(xr);
    pq_destroy(pq);
    free(mach);
    free(patient);

    return 0;
}
