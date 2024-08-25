#include <stdlib.h>
#include <stdio.h>
#include "../include/Patient.h"
#include "../include/XRMachineManager.h"

// Define a estrutura da lista encadeada de máquinas de raio-x
struct xrMachineManager {
    XRMachine *front;
    XRMachine *rear;
};

// Define a estrutura de uma máquina de raio-x
struct xrMachine {
    int id;
    Patient *patient;
    XRMachine *next;
    int finish_time;
};

// Verifica se a lista de máquinas de raio-x está vazia
int xr_is_empty(XRMachineManager *xr) {
    return xr->front == NULL;
};

// Insere uma nova máquina de raio-x na lista
void xr_insert(XRMachineManager *xr, int id) {
    // Aloca memória para a nova máquina
    XRMachine *machine = (XRMachine *)malloc(sizeof(XRMachine));

    // Verifica se a alocação foi bem sucedida
    if (machine == NULL) {
        perror("Falha ao alocar memória para a máquina de raio-x");
        exit(1);
    }

    // Inicializa os campos da máquina
    machine->id = id;
    machine->patient = NULL;
    machine->next = NULL;
    machine->finish_time = 0;
    

    // Insere a máquina na lista
    if (xr_is_empty(xr)) {
        xr->front = machine;
    } else {
        xr->rear->next = machine;
    }

    xr->rear = machine; 
}

// Cria um novo gerenciador de máquinas de raio-x
XRMachineManager *xr_create() {
    XRMachineManager *xr = (XRMachineManager *)malloc(sizeof(XRMachineManager));
    if (xr == NULL) {
        perror("Falha ao alocar memória para o gerenciador de máquinas de raio-x");
        exit(1);
    }

    xr->front = NULL;
    xr->rear = NULL;

    return xr;
}

// Verifica se há alguma máquina de raio-x disponível e a retorna
XRMachine * xr_available(XRMachineManager *xr) {
    XRMachine *machine = xr->front;
    while(machine != NULL) {
        if(machine->finish_time == 0) {
            return machine;
        }
        machine = machine->next;
    }
    return NULL;
}

// Adiciona um paciente a uma máquina de raio-x
void xr_add_patient(XRMachine *machine, Patient *patient, int time) {
    machine->patient = patient;
    machine->finish_time = time;
}

// Retorna id da máquina
int xr_get_id(XRMachine *machine) {
    return machine->id;
}

// Retorna a máquina que terminou o exame
XRMachine * xr_finished(XRMachineManager *xr, int time) {
    XRMachine *machine = xr->front;
    while(machine != NULL) {
        if(machine->finish_time != 0 && machine->finish_time == time) {
            return machine;
        }
        machine = machine->next;
    }
    return NULL;
}

// Limpa os dados da máquina
void clear_machine(XRMachine *machine) {
    machine->patient = NULL;
    machine->finish_time = 0;
}

// Libera o espaço alocado para o gerenciador de máquinas de raio-x
void xr_destroy(XRMachineManager *xr) {
    XRMachine *machine = xr->front;
    XRMachine *next;
    while(machine != NULL) {
        next = machine->next;
        free(machine);
        machine = next;
    }
    free(xr);
}

// Retorna o paciente que está na máquina
Patient *xr_get_patient(XRMachine *machine) {
    return machine->patient;
}
