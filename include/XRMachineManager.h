#ifndef XRMACHINEMANAGER_H
#define XRMACHINEMANAGER_H

#include "Patient.h"

// define a estrutura da fila de pacientes
typedef struct xrMachineManager XRMachineManager;
typedef struct xrMachine XRMachine;

XRMachineManager *xr_create();

XRMachine * xr_available(XRMachineManager *xr);

XRMachine * xr_finished(XRMachineManager *xr, int time);

#endif
