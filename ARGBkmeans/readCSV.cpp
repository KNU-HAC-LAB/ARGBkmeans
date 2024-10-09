#include"inoutputCluster.h"

void read_csv(double data[ROWS][COLS], const char* filename) {
    FILE* file;
    errno_t err = fopen_s(&file, filename, "r");
    if (err!=0) {
        perror("Error opening file");
        return;
    }

    char line[256];
    int row = 0;

    // ù ��° ���� ����̹Ƿ� ����
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        sscanf_s(line, "%lf,%lf,%lf,%lf", &data[row][0], &data[row][1], &data[row][2], &data[row][3]);
        row++;
    }

    fclose(file);
}