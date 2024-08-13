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

int main() {

    // Configuração de localidade
    setlocale(LC_ALL, "Portuguese.UTF8");


    /*#####################################
    ##        Iniciando variáveis        ##    
    #####################################*/


    // Gerando uma lista com 20 nomes diferentes
    char* names[20] = {"João","Maria","Pedro","Ana","Carlos","Mariana","Lucas","Julia","Fernando","Camila","Gustavo","Isabela","Rafael","Larissa","Rodrigo","Amanda","Diego","Natália","Marcelo","Letícia"};

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
    
    // Fila de exames com prioridade
    ExamPriorityQueue *epq = epq_create();


    /*###################################
    ##        Biblioteca time.h        ##      
    ###################################*/


    // Seed para a função rand()
    srand(time(NULL));
    
    // Data e hora atual
    // ponteiro para struct que armazena data e hora  
    struct tm *data_hora_atual;     
  
    // variável do tipo time_t para armazenar o tempo em segundos  
    time_t segundos;

    // Obtendo o tempo atual em segundos
    time(&segundos);

    // Convertendo o tempo em segundos para a struct tm
    data_hora_atual = localtime(&segundos);


    /*#######################################
    ##        Iniciando a simulação        ##      
    #######################################*/


    // Mensagem de boas-vindas
    printf("#############################################\n##  Bem-vindo ao Hospital Imagine Dragons  ##\n#############################################\n\nData: %d/%d/%d\tHora: %d:%d\n\n", data_hora_atual->tm_mday, data_hora_atual->tm_mon + 1, data_hora_atual->tm_year + 1900, data_hora_atual->tm_hour, data_hora_atual->tm_min);

    // Loop de passagem de tempo
    for(int i = 0; i < 20; i++) {

        
        /*#######################################
        ##        Fila de pacientes            ##      
        #######################################*/

        // Mensagem de recepção
        char *reception_message = "-----------------------------------------\n"
                                  "\t\tRECEPÇÃO\n"
                                  "-----------------------------------------\n\n";
        printf("%s", reception_message);
        printf("---> Número de pacientes na fila agora: %d\n\n", pq_size(pq));

        // 20% de chance de um paciente chegar
        printf("Verificando se há pacientes chegando...\n\n");

        if (rand() % 10 <= 1) {

            /*   Obtendo Hora atual    */

            time(&segundos); 
            data_hora_atual = localtime(&segundos);

            /*    Cadastro de Pacientes    */

            // Escolhe um dos nomes da lista aleatóriamente
            int name_index = rand() % 20;

            printf("%s chegou!\t\t\t\t%d:%d:%d\nAguardando... ", names[name_index], data_hora_atual->tm_hour, data_hora_atual->tm_min, data_hora_atual->tm_sec);

            // Cria um paciente com o ID, nome e data de registro
            patient = create_patient(pat_id, names[name_index], data_hora_atual);

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
        printf("aqui!");
        patient = xr_get_patient(mach);
        printf("Não, aqui!");

        // Direciona o paciente para o exame com laudo de IA
        if(mach != NULL) {
            printf("Exame da máquina %d finalizado!\n", xr_id(mach));
            epq_insert(epq, create_exam(exam_id, get_patient_id(patient), xr_id(mach)));
            clear_machine(mach);
            printf("Paciente encaminhado para fila de exame com pré-laudo de IA!\n\n");
        } else {
            printf("Nenhum exame pronto no momento!\n\n");
        }

        /*    Direciona um paciente a uma máquina    */

        printf("---> Verificando máquinas disponíveis...\n\n");

        // Verifica se há alguma máquina disponível
        mach = xr_available(xr);

        if (mach != NULL) {
            // verficando hora atual
            time(&segundos); 
            data_hora_atual = localtime(&segundos);

            // Adiciona um paciente à essa máquina
            xr_add_patient(mach, pq_remove(pq), i + 10);
            printf("Um paciente foi encaminhado!\n\nMáquina: %d\t\t%d:%d:%d\n\n", xr_id(mach), data_hora_atual->tm_hour, data_hora_atual->tm_min, data_hora_atual->tm_sec);
        } else {
            printf("Nenhuma máquina disponível no momento!\n\n");
        }

        // Espera 50ms / 0.05s para o próximo ciclo
        Sleep(50);
    }

    // Libera a memória alocada
    epq_destroy(epq);
    xr_destroy(xr);
    pq_destroy(pq);

    return 0;
}
