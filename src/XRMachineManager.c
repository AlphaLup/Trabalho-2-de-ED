#include <stdlib.h>
#include <stdio.h>
#include "../include/Patient.h"
#include "../include/XRMachineManager.h"

struct xrMachineManager {
    XRMachine *front;
    XRMachine *rear;
};

struct xrMachine {
    int id;
    Patient *patient;
    XRMachine *next;
    int finish_time;
};

<<<<<<< Updated upstream
int pq_is_empty(XRMachineManager *xr) {
=======
// ISSO TÁ SENDO USADO? ***************
XRMachine *xr_create_machine(int id) {
    XRMachine *machine = (XRMachine *)malloc(sizeof(XRMachine));
    if (machine == NULL) {
        perror("Falha ao alocar memória para a máquina de raio-x");
        exit(1);
    }

    machine->id = id;
    machine->patient = NULL;
    machine->next = NULL;
    machine->finish_time = 0;

    return machine;
};

int xr_is_empty(XRMachineManager *xr) {
>>>>>>> Stashed changes
    return xr->front == NULL;
};

void xr_insert(XRMachineManager *xr, int id) {
    XRMachine *machine = xr_create_machine(id);

    if (xr_is_empty(xr)) {
        xr->front = machine;
    } else {
        xr->rear->next = machine;
    }

    xr->rear = machine;
}

XRMachineManager *xr_create() {
    XRMachineManager *xr = (XRMachineManager *)malloc(sizeof(XRMachineManager));
    if (xr == NULL) {
        perror("Falha ao alocar memória para o gerenciador de máquinas de raio-x");
        exit(1);
    }

    for(int i = 0; i < 5; i++) {
        xr_insert(xr, i);
    }

    return xr;
}

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

void xr_add_patient(XRMachine *machine, Patient *patient, int time) {
    machine->patient = patient;
    machine->finish_time = time;
}

XRMachine * xr_finished(XRMachineManager *xr, int time) {
    XRMachine *machine = xr->front;
    while(machine != NULL) {
        if(machine->finish_time != 0 && machine->finish_time == time) {
<<<<<<< Updated upstream
            return machine;
=======
            machine->finish_time = 0;
            XRMachine *ret_mach = machine;
            machine->patient = NULL;
            return ret_mach;
>>>>>>> Stashed changes
        }
        machine = machine->next;
    }
    return NULL;
}

<<<<<<< Updated upstream
void clear_machine(XRMachine *machine) {
    machine->patient = NULL;
    machine->finish_time = 0;
}

void free_xr(XRMachineManager *xr) {
    XRMachine *machine = xr->front;
    XRMachine *next;
    while(machine != NULL) {
        next = machine->next;
        free(machine);
        machine = next;
    }
    free(xr);
}
=======
Patient *xr_get_patient(XRMachine *machine) {
    return machine->patient;
}

int xr_get_rx_id(XRMachine *machine) {
    return machine->id;
}

// CRIAR FUNÇÃO PARA LIBERAR MEMÓRIA DAS MÁQUINAS DE RAIO-X
>>>>>>> Stashed changes
