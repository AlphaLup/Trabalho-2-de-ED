#include <stdio.h>

float average_time_to_examined (int count) {
    FILE *file = fopen("db_report.txt", "r");
    if (file == NULL) {
        perror("Falha ao abrir o arquivo");
        exit(1);
    }

    float time = 0;

    while (!feof(file)) {
        int id, patient_id, rx_id, register_time, priority;
        char condition_IA[20];

        fscanf(file, "%d\n", &id);
        fscanf(file, "%d\n", &patient_id);
        fscanf(file, "%d\n", &rx_id);
        fscanf(file, "%d\n", &register_time);
        fscanf(file, "%s\n", condition_IA);
        fscanf(file, "%d\n", &priority);

        time += register_time;
    }

    fclose(file);

    return time / count;
}