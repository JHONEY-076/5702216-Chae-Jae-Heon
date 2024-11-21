#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int sorted[SIZE];
int comparisonCount = 0; // �� Ƚ��
int moveCount = 0; // �̵� Ƚ��
int totalComparisons = 0; // �� �� Ƚ��
int totalMoves = 0; // �� �̵� Ƚ��
int isFirst = 0; // ù ���� üũ
int rounds = 0; // rounds ī����

// ���� ������ ���� �Լ�
void generateRandomArray(int array[SIZE]) {

    srand(time(0));
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

// �迭 ��� �Լ�
void printArray(int array[SIZE], int size) {
    for (int i = 0; i < size; i++) {
        printf("%3d ", array[i]);
    }
    printf("\n");
}

// Merge Sort ���� �Լ�
void merge(int list[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = left; // ����,������ �κ��� �����ϴ� �ε����� ���յ� ��� �迭�� ���� ä�� �ִ� �ε����� �ʱ�ȭ �����ش�.

    while (i <= mid && j <= right) { //���ʰ� �������� ���� ���� ������ ���� �ݺ�
        comparisonCount++;  // ��Ƚ�� ����
        // �� ���� ���Ͽ� ���� ���� ��������ش�.
        if (list[i] <= list[j]) {
            sorted[k++] = list[i++];
        }
        else {
            sorted[k++] = list[j++];
        }
        moveCount++; // �̵� Ƚ�� ����
    }

    // ���� �� ó�� �κ�
   // �̶� �̵�Ƚ���� ���� �����ش�.


   // ���� �κп� ���� �����ִٸ� �迭�� �־��ش�
    while (i <= mid) {
        sorted[k++] = list[i++];
        moveCount++;
    }
    // ������ �κп� ���� ���Ҵٸ� �迭�� �־��ش�.
    while (j <= right) {
        sorted[k++] = list[j++];
        moveCount++;
    }


    // ���� �迭�� ����� ���� �����ִ� �κ�
    for (i = left; i <= right; i++) {
        list[i] = sorted[i];
        moveCount++; // �̵�Ƚ�� ����
    }
}


// �պ����� �Լ�
void doMergeSort(int array[SIZE], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        // �������ִ� ��
        doMergeSort(array, left, mid);
        doMergeSort(array, mid + 1, right);

        // �������ִ� ��
        merge(array, left, mid, right);

        // 10������ ��½����ش�!!
        rounds++;
        if (rounds % 10 == 0 && isFirst == 0) {
            for (int i = 0; i < 10; i++) {
                printf("%3d ", array[i]);
            }
            printf("| ");
            for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++) {
                printf("%3d ", array[i]);
            }
            printf("\n\n");
        }
    }
}




int main() {


    int array[SIZE];

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;


        if (i == 0) {
            printf("Merge Sort Run\n");
            doMergeSort(array, 0, SIZE - 1);
            printf("Result\n");
            printArray(array, SIZE);
            isFirst++;
        }
        else {
           doMergeSort(array, 0, SIZE - 1);
        }

        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }

    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}


////���ʽ� �κ�= > ���� ���ذ�
// 
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//
//#define SIZE 100
//#define PRINT_INTERVAL 10  
//
//int sorted[SIZE];
//int comparisonCount = 0; 
//int moveCount = 0; 
//int totalComparisons = 0; 
//int totalMoves = 0; 
//int isFirst = 0; 
//int rounds = 0; 
//
//
//void generateRandomArray(int array[SIZE]) {
//    srand(time(0));
//    for (int i = 0; i < SIZE; i++) {
//        array[i] = rand() % 1000;
//    }
//}
//
//// �迭 ��� �Լ�
//void printArray(int array[SIZE], int size) {
//    for (int i = 0; i < size; i++) {
//        printf("%3d ", array[i]);
//    }
//    printf("\n");
//}
//
//// Merge Sort ���� �Լ�
//void merge(int list[], int left, int mid, int right) {
//    int i = left, j = mid + 1, k = left; 
//    while (i <= mid && j <= right) {
//        comparisonCount++; 
//       
//        if (list[i] <= list[j]) {
//            sorted[k++] = list[i++];
//        }
//        else {
//            sorted[k++] = list[j++];
//        }
//        moveCount++; 
//    }
//
//   
//
//  
//    while (i <= mid) {
//        sorted[k++] = list[i++];
//        moveCount++;
//    }
//    
//    while (j <= right) {
//        sorted[k++] = list[j++];
//        moveCount++;
//    }
//
//    
//    for (i = left; i <= right; i++) {
//        list[i] = sorted[i];
//        moveCount++; 
//    }
//}
//
//// �պ����� �ݺ��� ��� (bottom-up ���)
//void doMergeSortIterative(int array[SIZE]) {
//    // �ݺ����� ����Ͽ� 1���� SIZE������ ũ�� ������ ������ ����
//    for (int size = 1; size < SIZE; size = 2 * size) {
//        for (int left = 0; left < SIZE - 1; left += 2 * size) {
//            int mid = (left + size - 1 < SIZE - 1) ? left + size - 1 : SIZE - 1;
//            int right = (left + 2 * size - 1 < SIZE - 1) ? left + 2 * size - 1 : SIZE - 1;
//
//            merge(array, left, mid, right);
//        }
//
//       
//        rounds++;
//
//        // 10������ ���
//        if (rounds % PRINT_INTERVAL == 0) {  // ��� ���Ǹ� üũ, isFirst�� �� �̻� �ʿ� ���� �� ����
//            // �迭�� ó�� 10�� ���� �߾ӿ��� 10�� �� ���
//            for (int i = 0; i < PRINT_INTERVAL; i++) {
//                printf("%3d ", array[i]);
//            }
//            printf("| ");
//            for (int i = SIZE / 2 - 1; i < SIZE / 2 + PRINT_INTERVAL; i++) {
//                printf("%3d ", array[i]);
//            }
//            printf("\n\n");
//        }
//    }
//}
//
//int main() {
//    srand(time(0)); 
//
//    int array[SIZE];
//
//    for (int i = 0; i < 20; i++) {
//        generateRandomArray(array);
//        comparisonCount = 0;
//        moveCount = 0;
//
//        
//        if (i == 0) {
//            printf("Merge Sort Run\n");
//            doMergeSortIterative(array); 
//            printf("Result\n");
//            printArray(array, SIZE); 
//        }
//        else {
//            doMergeSortIterative(array);  
//        }
//
//        totalComparisons += comparisonCount;
//        totalMoves += moveCount;
//    }
//
//    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
//    printf("Average Moves: %.2f\n", totalMoves / 20.0);
//
//    return 0;
//}
