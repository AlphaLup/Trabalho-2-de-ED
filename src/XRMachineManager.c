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

int xr_is_empty(XRMachineManager *xr) {
    return xr->front == NULL;
};

void xr_insert(XRMachineManager *xr, int id) {
    XRMachine *machine = (XRMachine *)malloc(sizeof(XRMachine));

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

int xr_id(XRMachine *machine) {
    return machine->id;
}

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

void clear_machine(XRMachine *machine) {
    machine->patient = NULL;
    machine->finish_time = 0;
}

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

Patient *xr_get_patient(XRMachine *machine) {
    return machine->patient;
}
