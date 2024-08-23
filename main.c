#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "./include/Exam.h"
#include "./include/Patient.h"
#include "./include/PatientQueue.h"
#include "./include/XRMachineManager.h"
#include "./include/ExamPriorityQueue.h"



// Main function
int main(){
    // Gerando uma lista com 20 nomes diferentes
    char* names[20] = {"João","Maria","Pedro","Ana","Carlos","Mariana","Lucas","Julia","Fernando","Camila","Gustavo","Isabela","Rafael","Larissa","Rodrigo","Amanda","Diego","Natália","Marcelo","Letícia"};

    // Gerando o contador para o ID
    int pat_id = 1;
    // int exam_id = 1;

    // Criando as variáveis de controle
    XRMachine *mach;
    // Patient *patient;
    
    // Seed para a função rand()
    srand(time(NULL));

    // Criando a fila de pacientes sem prioridade
    PatientQueue *pq = pq_create();

    // Criando o gerenciador de máquinas de raio-x
    XRMachineManager *xr = xr_create();
    
    // // Criando a fila de exames com prioridade
    // ExamPriorityQueue *epq = epq_create();

    // Loop de passagem de tempo
    for(int i = 0; i < 200; i++) {
        int name_index = rand() % 20;

        if(rand() % 10 <= 1){
            Patient *patient = create_patient(pat_id, names[name_index]);
            pq_insert(pq, patient);
            pat_id ++;
        };

        // mach = xr_available(xr);
        // if(mach != NULL) {
        //     xr_add_patient(mach, pq_remove(pq), i + 10);
        // };

    //     // Verifica se alguma máquina já terminou
    //     mach = xr_finished(xr, i);
    //     patient = xr_get_patient(mach);
    //     // Direciona o paciente para o exame com laudo de IA
    //     if(patient != NULL) {
    //         epq_insert(epq, create_exam(exam_id, get_patient_id(patient), xr_get_rx_id(mach)));
    //     };
    }

    return 0;
}