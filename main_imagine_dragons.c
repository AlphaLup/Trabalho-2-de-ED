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
#include "./include/Record.h"

#define LOOP_TIME 4320



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


    /*#######################################
    ##        Iniciando a simulação        ##      
    #######################################*/


    // Mensagem de boas-vindas
    printf("#############################################\n##  Bem-vindo ao Hospital Imagine Dragons  ##\n#############################################\n\nRelatórios serão printados a cada %d unidades de tempo!", LOOP_TIME);

    // Loop de passagem de tempo
    for(int i = 0; i < LOOP_TIME; i++) {

        /*#######################################
        ##        Print do Relatório           ##      
        #######################################*/

        if (i % LOOP_TIME == 0) {
            // Ponha o report aqui
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
            patient = create_patient(pat_id, names[name_index], i);

            // Insere paciente na fila
            pq_insert(pq, patient);

            // Controle do ID do paciente
            pat_id ++;
        }

        /*########################################
        ##        Maquinas de Raio-X            ##      
        ########################################*/

        /*    Gera exame ao finalizar uso da máquina    */

        // Verifica se alguma máquina já terminou
        // Caso positivo, ele retornará um ponteiro para uma máquina na variável 'machine'
        // OBS: Apenas uma máquina por vez poderá finalizar a cada ciclo (devido a lógica do código)
        
        mach = xr_finished(xr, i);

        // Direciona o paciente para o exame com laudo de IA
        if (mach != NULL) {
            Patient *patient = xr_get_patient(mach);

            if (patient != NULL) {
                int patient_id = get_patient_id(patient);
                int xr_id = xr_get_id(mach);
                
                Exam *exam = create_exam(exam_id, patient_id, xr_id, i);
                if (exam != NULL) {
                    epq_insert(epq, exam);
                    exam_id++;
                    clear_machine(mach);
                } else {
                    printf("Erro ao criar exame!\n\n");
                    return 1;
                }
            } else {
                printf("Erro ao obter paciente!\n\n");
                return 1;
            }
        } else {
            printf("Nenhum exame pronto no momento!\n\n");
            return 1;
        }

        /*    Direciona um paciente a uma máquina    */

        // Verifica se há alguma máquina disponível
        mach = xr_available(xr);
        
        if (mach != NULL && !pq_is_empty(pq)) {
            // Adiciona um paciente à essa máquina
            patient = pq_remove(pq);
            xr_add_patient(mach, patient, i + 10);
        }

        // Espera para o próximo ciclo
    }

    printf("Fim da simulação!\n\n");

    // Libera a memória alocada
    epq_destroy(epq);
    xr_destroy(xr);
    pq_destroy(pq);
    free(mach);
    free(patient);

    return 0;
}
