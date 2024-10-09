#include"kmeans.h"

// K-means Ŭ�����͸�
void kmeans(double** data, int n, int dim, int k) {
    double** centers = (double**)malloc(k * sizeof(double*));
    for (int i = 0; i < k; i++) {
        centers[i] = (double*)malloc(dim * sizeof(double));
    }

    int* labels = (int*)malloc(n * sizeof(int));

    auto normalizeStart = std::chrono::high_resolution_clock::now();
    //0~1���̷� ����ȭ
    normalize(data, n, dim);
    auto normalizeEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> normalizeElapsed = normalizeEnd - normalizeStart;

   
    auto firstCenterStart = std::chrono::high_resolution_clock::now();
    // �ʱ� �߽��� ����
    findFirstCenter(data, centers, n, dim, k);
    auto firstCenterEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> firstCenterElapsed = firstCenterEnd - firstCenterStart;
   

    std::chrono::duration<double, std::milli> assignElapsed(0);
    std::chrono::duration<double, std::milli> newCenterElapsed(0);

    auto clusterStart = std::chrono::high_resolution_clock::now();
    // �ݺ� ����
    int iter = 0;
    int centerChanged;
    do {
        // ���� �߽����� ����
        double** oldCenters = (double**)malloc(k * sizeof(double*));
        for (int i = 0; i < k; i++) {
            oldCenters[i] = (double*)malloc(dim * sizeof(double));
            for (int j = 0; j < dim; j++) {
                oldCenters[i][j] = centers[i][j];
            }
        }

        auto assignStart = std::chrono::high_resolution_clock::now();
        // ������ Ŭ������ ����
        assignCluster(data, centers, labels, n, dim, k);
        auto assignEnd = std::chrono::high_resolution_clock::now();
        assignElapsed += assignEnd - assignStart;

        auto newCenterStart = std::chrono::high_resolution_clock::now();
        // ���ο� �߽��� ã��
        findNewCenter(data, centers, labels, n, dim, k);
        auto newCenterEnd = std::chrono::high_resolution_clock::now();
        newCenterElapsed += newCenterEnd - newCenterStart;

        // �߽����� �ٲ������ Ȯ��
        centerChanged = isCenterChanged(oldCenters, centers, dim, k);

        // �޸� ����
        for (int i = 0; i < k; i++) {
            free(oldCenters[i]);
        }
        free(oldCenters);

        iter++;
    } while (centerChanged && iter < MAX_ITER);
    auto clusterEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> clusterElapsed = clusterEnd - clusterStart;
   
    std::cout << "����ȭ �ð�: " << normalizeElapsed.count() << " ms" << std::endl;
    std::cout << "kmeans++ �ð�: " << firstCenterElapsed.count() << " ms" << std::endl;
    std::cout << "�Ҵ� ��ü �ð�: " << assignElapsed.count() << " ms" << std::endl;
    std::cout << "�Ҵ� ��� �ð�: " << assignElapsed.count()/(double)iter << " ms" << std::endl;
    std::cout << "�߽��� ���� ��ü �ð�: " << newCenterElapsed.count() << " ms" << std::endl;
    std::cout << "�߽��� ���� ��� �ð�: " << newCenterElapsed.count()/(double)iter << " ms" << std::endl;
    std::cout << "��ü kmeans �ð�: " << clusterElapsed.count() << " ms" << std::endl;



    // �Ƿ翧 ��� ���
    //double* silhouetteScores = silhouetteCoefficient(data, labels, centers, n, k, dim);

    //// ���� �߽��� ���
    //printf("���� �߽���:\n");
    //for (int i = 0; i < k; i++) {
    //    printf("Cluster %d Center: ", i);
    //    for (int j = 0; j < dim; j++) {
    //        printf("%lf ", centers[i][j]);
    //    }
    //    printf("\n");
    //}

    // �� �߽����� �Ҵ�� ������ ���
    //printf("\n�� �߽����� �Ҵ�� ������:\n");
    //printClusterData(data, labels, n, dim, k, silhouetteScores);

    //// �� Ŭ�������� ��� �Ƿ翧 ����� ���� ���
    //evaluateSilhouette(silhouetteScores, labels, n, k);

    //printf("�ݺ� Ƚ��: %d", iter);

    //// �޸� ����
    //free(silhouetteScores);

    // �޸� ����
    for (int i = 0; i < k; i++) {
        free(centers[i]);
    }
    free(centers);
    free(labels);
}