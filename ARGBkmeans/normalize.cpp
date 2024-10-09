#include "normalize.h"
#define COLS 4
void normalize(double **data, int rows, int cols) {
    double min_val[COLS], max_val[COLS];

    // �ʱ�ȭ
    for (int j = 0; j < cols; j++) {
        min_val[j] = DBL_MAX;
        max_val[j] = -DBL_MAX;
    }

    // �� ���� �ּҰ��� �ִ밪 ���
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (data[i][j] < min_val[j]) {
                min_val[j] = data[i][j];
            }
            if (data[i][j] > max_val[j]) {
                max_val[j] = data[i][j];
            }
        }
    }

    // ����ȭ ����
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (max_val[j] != min_val[j]) {
                data[i][j] = (data[i][j] - min_val[j]) / (max_val[j] - min_val[j]);
            }
            else {
                data[i][j] = 0.0; // �ִ밪�� �ּҰ��� ������ 0���� ����
            }
        }
    }
}