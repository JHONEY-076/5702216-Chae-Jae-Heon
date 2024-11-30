#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10000
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int compareCount = 0;

//���� ���ڸ� ������ �迭�� ����
void generateRandomArray(int list[]) {
    for (int i = 0; i < SIZE; i++) {
        list[i] = rand() % 10000;
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



// �迭�� ������, �ǹ��� ��ġ�� ��ȯ�ϴ� �Լ�
int partition(int array[], int left, int right) {
    int pivot, temp;
    int low = left;
    int high = right + 1;
    pivot = array[left];

    do {
        do {
            low++;
            ;
        } while (low <= right && array[low] < pivot);

        do {
            high--;
           
        } while (high >= left && array[high] > pivot);

        if (low < high) {
            SWAP(array[low], array[high], temp);
        }
    } while (low < high);

    SWAP(array[left], array[high], temp);
    return high;
}

//��������� ȣ���Ͽ� �迭�� ��� ������ �����ϴ� ������ �Լ�
void QuickSort(int array[], int left, int right) {
    if (left < right) {
        int q = partition(array, left, right);
        QuickSort(array, left, q - 1);
        QuickSort(array, q + 1, right);
    }
}

// ���� Ž�� ��� �� Ƚ���� ����ϴ� �Լ�
double getAverageBinarySearchCompareCount(int array[]) {
    int totalCompare = 0;

    for (int i = 0; i < 1000; i++) {
        int key = array[rand() % SIZE];  // �迭 �� ������ Ű ����
        int low = 0;
        int high = SIZE - 1;
        int compare = 0;

        // ���� Ž�� ����
        while (low <= high) {
            
            int middle = (low + high) / 2; // �߰��ε����� ã�� �κ� 

            if (array[middle] == key) {
                compare++; // Ű�� ã�� ��� ��Ƚ�� ����
                break; 
            }
            else if (key < array[middle]) {
                high = middle - 1;
                compare++; // �������� Ž�� �ÿ� ��Ƚ���� ���������ش�.
            }
            else {
                low = middle + 1;
                compare++; // ���������� Ž���� ��Ƚ���� ���������ش�.
            }
        }
        totalCompare += compare;
    }

    return totalCompare / 1000.0;  // ��� �� Ƚ�� ��ȯ
}


//����Ž���� �̿��Ͽ� ���ĵ� �迭�� ���� �������� �����Ͽ� �� Ž�� �� ����� ��Ƚ���� ����� ���ϴ� �Լ�
double getAverageInterpolationSearchComparecount(int array[]) {
    int totalCompare = 0;

    for (int i = 0; i < 1000; i++) {
        int target = array[rand() % SIZE];
        int low = 0;
        int high = SIZE - 1;
        int compare = 0;

        while (low <= high && target >= array[low] && target <= array[high]) {
            
            // ���� ��ġ ���
            int j = low + ((double)(target - array[low]) / (array[high] - array[low])) * (high - low);
            
            //�� �� ���ǿ��� compare�� ������Ų��.
            if (target > array[j]) {
                low = j + 1; 
                compare++;  // ��Ƚ�� ����
            }
            else if (target < array[j]) {
                high = j - 1;
                compare++;  // ��Ƚ�� ����
            }
            else {
                compare++;  // target == array[j] ��� �߰�
                break;
            }
        }

        // �ݺ����� ������� low��ġ���� target�� �ٽ� �ѹ� Ȯ��
        if (low <= high && array[low] == target) compare++;

        totalCompare += compare;
    }

    return totalCompare / 1000.0;  // ��� �� Ƚ�� ��ȯ
}





int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];
    generateRandomArray(array);
    QuickSort(array, 0, SIZE - 1);
    printArray(array);
    printf("Average Compare Count of Binary Search: %.2f\n",
        getAverageBinarySearchCompareCount(array));
    printf("Average Compare Count of Interpolation Search: %.2f\n",
        getAverageInterpolationSearchComparecount(array));
    return 0;
}