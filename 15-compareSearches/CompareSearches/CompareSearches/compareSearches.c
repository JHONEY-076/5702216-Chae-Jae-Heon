#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int compareCount = 0;

//���� ���ڸ� ������ �迭�� ����
void generateRandomArray(int list[]) {
    for (int i = 0; i < SIZE; i++) {
        list[i] = rand() % 1000;
    }
}

// �迭�� ó�� 20���� ������ 20���� ���Ҹ� ������ִ� �Լ�
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++)
        printf("%3d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%3d ", array[i]);
    printf("\n");
}

// ���� Ž������ 
double getAverageLinearSearchCompareCount(int array[]) {
    int totalCompare = 0;
    for (int i = 0; i < 100; i++) { // ����Ž���� 100�� ����

        int key = array[rand() % SIZE]; // �迭 ���� ������ �ε����� �����ϰ�, �ش��ϴ� ���� key������ �������ش�.
        int compareCount = 0;
        //����Ž�� �˰��� �κ�
        for (int j = 0; j < SIZE; j++) {
            compareCount++; //��Ƚ�� ī��Ʈ
            if (array[j] == key) break; //Ű ���� ã���� break
        }
        totalCompare += compareCount; //100���� Ž���� ���� ��Ƚ���� ���������ش�.
    }
    return totalCompare / 100.0;
}

// �迭�� ������, �ǹ��� ��ġ�� ��ȯ�ϴ� �Լ�
int partition(int array[], int left, int right) {
    int pivot, temp;
    int low = left;
    int high = right + 1;
    pivot = array[left];

    do {
        do {
            low++;
            compareCount++;
        } while (low <= right && array[low] < pivot);

        do {
            high--;
            compareCount++;
        } while (high >= left && array[high] > pivot);

        if (low < high) {
            SWAP(array[low], array[high], temp);
        }
    } while (low < high);

    SWAP(array[left], array[high], temp);
    return high;
}

//��������� ȣ���Ͽ� �迭�� ��� ������ �����ϴ� ������ �Լ�
void quickSort(int array[], int left, int right) {
    if (left < right) {
        int q = partition(array, left, right);
        quickSort(array, left, q - 1);
        quickSort(array, q + 1, right);
    }
}

//��Ƚ���� �ʱ�ȭ �����ְ� �迭 ��ü�� ���� �������� ��������ִ� �Լ�
void getQuickSortCompareCount(int array[]) {
    compareCount = 0; // ��Ƚ�� �ʱ�ȭ
    quickSort(array, 0, SIZE - 1); // �迭 ��ü�� ���� �� ���� ����
}



double getAverageBinarySearchCompareCount(int array[]) {
    int totalCompare = 0;

    for (int i = 0; i < 100; i++) {  // ���� Ž���� 100�� ����
        int key = array[rand() % SIZE];  // �迭 ������ ������ Ű ����
        int low = 0;
        int high = SIZE - 1;
        int compare = 0;

        while (low <= high) {
            int middle = (low + high) / 2;  // �߰� �ε��� ���
            

            if (array[middle] == key) {
                compare++;  // �߰��� �� �� ī��Ʈ
                break;  // Ű�� ã���� ����
            }
            else if (key < array[middle]) {
                compare++;  // �߰��� �� �� ī��Ʈ
                high = middle - 1;
            }
            else {
                compare++;  // �߰��� �� �� ī��Ʈ
                low = middle + 1;
            }
        }
        totalCompare += compare;  // Ž�� ���� �� �� Ƚ�� ����
    }
    return totalCompare / 100.0;  // ��� �� Ƚ�� ��ȯ
}


int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];
    generateRandomArray(array);
    //��հ��� ��ȯ�ޱ� ���� ��ġ
    printf("Average Linear Search Compare Count: %.2f\n",
        getAverageLinearSearchCompareCount(array));
    //compareCount�� global variable�̹Ƿ�, ������ ���� ����
    //array�� ���ؼ� ���� �����ϸ� �ȴ�.
    getQuickSortCompareCount(array);
    printf("Quick Sort Compare Count: %d\n", compareCount);
    //���ĵ� Array�� ���ؼ� Binary Search 100ȸ ���� �� ��� ��Ƚ�� ���
    printf("Average Binary Search Compare Count: %.2f\n\n",
        getAverageBinarySearchCompareCount(array));
    printArray(array);
    return 0;
}