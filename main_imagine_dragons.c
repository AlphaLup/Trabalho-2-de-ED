#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "./include/Exam.h"
#include "./include/Patient.h"
#include "./include/PatientQueue.h"
#include "./include/XRMachineManager.h"

int main(){
    // Gerando uma lista com 20 nomes diferentes
    char* names[20] = {"João","Maria","Pedro","Ana","Carlos","Mariana","Lucas","Julia","Fernando","Camila","Gustavo","Isabela","Rafael","Larissa","Rodrigo","Amanda","Diego","Natália","Marcelo","Letícia"};

    // Gerando o contador para o ID do paciente
    int count = 0;
    XRMachine *mach;
    Patient *pat;

    // Seed para a função rand()
    srand(time(NULL));

    // Criando a fila de pacientes sem prioridade
    PatientQueue *pq = pq_create();

    // Criando o gerenciador de máquinas de raio-x
    XRMachineManager *xr = xr_create();

    // Loop de passagem de tempo
    for(int i = 0; i < 43200; i++) {
        int name_index = rand() % 20;

        if(rand() % 10 <= 1){
            Patient *patient = create_patient(count, names[name_index]);
            pq_insert(pq, patient);
            count ++;
        };

        mach = xr_available(xr);
        if(mach != NULL) {
            xr_add_patient(mach, pq_remove(pq), i + 10);
        };

        pat = xr_finished(xr, i);
        if(pat != NULL) {
            // TODO: Implementar a função de exame
        };
    }

    return 0;
}