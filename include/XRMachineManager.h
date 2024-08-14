#ifndef XRMACHINEMANAGER_H
#define XRMACHINEMANAGER_H

#include "Patient.h"

// define a estrutura da fila de pacientes
typedef struct xrMachineManager XRMachineManager;
typedef struct xrMachine XRMachine;

// cria uma nova fila de pacientes
XRMachineManager * xr_create();

// cria uma nova máquina de raio-x
void xr_insert(XRMachineManager *xr, int id);

// verifica se a máquina de raio-x está disponível
XRMachine * xr_available(XRMachineManager *xr);

// verifica e finaliza o uso da máquina de raio-x
XRMachine * xr_finished(XRMachineManager *xr, int time);

// relaciona um paciente a uma máquina de raio-x
void xr_add_patient(XRMachine *machine, Patient *patient, int time);

// cria uma nova máquina de raio-x
int xr_get_id(XRMachine *machine);

// esvazia a máquina de raio-x
void clear_machine(XRMachine *machine);

// libera a memória alocada para a lista de máquinas de raio-x
void xr_destroy(XRMachineManager *xr);

// obtém o paciente de uma máquina de raio-x
Patient *xr_get_patient(XRMachine *machine);

#endif
