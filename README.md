# Hospital Management System

## Overview
This project is a Hospital Management System designed to simulate the management of patients, exams, and X-ray machines in a hospital. It includes functionalities for creating and managing patients, scheduling and prioritizing exams, and managing the availability and usage of X-ray machines.

## Features
- **Patient Management**: Create, save, and retrieve patient information.
- **Exam Management**: Schedule exams, assign priorities, and .
- **X-ray Machine Management**: Track the availability and usage of X-ray machines.
- **Priority Queue**: Manage exams based on priority using a priority queue.
- **Reports**: Generate reports for the exam.

## Project Structure
- `src/`: Contains the source code files.
- `include/`: Contains the header files.
- `Makefile`: Build configuration for the project.
- `db_exam.txt`, `db_patient.txt`, `db_report.txt`: Data files for storing exams, patients, and reports.

## Dependencies
- GCC (GNU Compiler Collection)
- Standard C Libraries

## Build and Run

### Building the Project
1. Clone the repository:

```bash
git clone <repository-url>
cd <repository-directory>
```
```bash
git clone <repository-url>
cd <repository-directory>
```
2. Compile the project:

```bash
make
```
3. Run the project:

```bash
./output
```

4. Clean the build files:

```bash
make clean
```
### Running the Simulation
The main simulation is run through the `main_imagine_dragons.c` file. It initializes the system, creates patients, manages the X-ray machines, schedule exams, create reports and periodicaly prints the current record for the hospital.

## Code Structure
### Headers
- `Patient.h`: Defines the structure and functions for managing patients.
- `Exam.h`: Defines the structure and functions for managing exams.
- `PatientQueue.h`: Defines the structure and functions for managing a queue of patients.
- `XRMachineManager.h`: Defines the structure and functions for managing X-ray machines.
- `ExamPriorityQueue.h`: Defines the structure and functions for managing a priority queue of exams.
### Source Files
- `Patient.c`: Implements the functions for managing patients.
- `Exam.c`: Implements the functions for managing exams.
- `PatientQueue.c`: Implements the functions for managing a queue of patients.
- `XRMachineManager.c`: Implements the functions for managing X-ray machines.
- `ExamPriorityQueue.c`: Implements the functions for managing a priority queue of exams.
- `main_imagine_dragons.c`: Main file that runs the simulation.
