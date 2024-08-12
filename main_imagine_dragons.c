#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "./include/Exam.h"
#include "./include/Patient.h"
#include "./include/PatientQueue.h"
#include "./include/XRMachineManager.h"
#include "./include/ExamPriorityQueue.h"

int main(){
    // Gerando uma lista com 20 nomes diferentes
    char* names[20] = {"João","Maria","Pedro","Ana","Carlos","Mariana","Lucas","Julia","Fernando","Camila","Gustavo","Isabela","Rafael","Larissa","Rodrigo","Amanda","Diego","Natália","Marcelo","Letícia"};

    // Gerando o contador para o ID
    int pat_id = 1;
    int exam_id = 1;

    // Criando as variáveis de controle
    XRMachine *mach;
    Patient *patient;
    
    // Seed para a função rand()
    srand(time(NULL));

    // Criando a fila de pacientes sem prioridade
    PatientQueue *pq = pq_create();

    // Criando o gerenciador de máquinas de raio-x
    XRMachineManager *xr = xr_create();
    
    // Criando a fila de exames com prioridade
    ExamPriorityQueue *epq = epq_create();

    // Loop de passagem de tempo
    for(int i = 0; i < 43200; i++) {
        // Escolhe um dos nomes da lista aleatóriamente
        int name_index = rand() % 20;

        /*    Fila de Pacientes    */
        if(rand() % 10 <= 1){ // 20%
            // Cria um paciente
            Patient *patient = create_patient(pat_id, names[name_index]);
            // Insere paciente na fila
            pq_insert(pq, patient);
            // Controle do ID do paciente
            pat_id ++;
        };

        /*    Maquinas de Raio X    */

        // Verifica se há alguma máquina disponível
        mach = xr_available(xr);
        if(mach != NULL) {
            // Adiciona um paciente à essa máquina
            xr_add_patient(mach, pq_remove(pq), i + 10);
        };

        // Verifica se alguma máquina já terminou
        // Caso positivo, ele retornará um ponteiro para uma máquina na variável 'mach'
        mach = xr_finished(xr, i);
        patient = get_patient(mach);
        // Direciona o paciente para o exame com laudo de IA
        if(mach != NULL) {
            epq_insert(epq, create_exam(exam_id, get_patient_id(patient), get_rx_id(mach)));
        };
    }

    return 0;
}
