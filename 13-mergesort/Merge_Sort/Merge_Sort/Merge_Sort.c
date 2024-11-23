#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int sorted[SIZE];
int comparisonCount = 0; // 비교 횟수
int moveCount = 0; // 이동 횟수
int totalComparisons = 0; // 총 비교 횟수
int totalMoves = 0; // 총 이동 횟수
int isFirst = 0; // 첫 실행 체크
int rounds = 0; // rounds 카운터

// 랜덤 데이터 생성 함수
void generateRandomArray(int array[SIZE]) {

    srand(time(0));
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

// 배열 출력 함수
void printArray(int array[SIZE], int size) {
    for (int i = 0; i < size; i++) {
        printf("%3d ", array[i]);
    }
    printf("\n");
}

// Merge Sort 병합 함수
void merge(int list[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = left; // 왼쪽,오른쪽 부분을 추적하는 인덱스와 병합된 결과 배열에 값을 채워 넣는 인덱스를 초기화 시켜준다.

    while (i <= mid && j <= right) { //왼쪽과 오른쪽이 값이 남아 있을때 까지 반복
        comparisonCount++;  // 비교횟수 증가
        // 두 값을 비교하여 작은 값을 저장시켜준다.
        if (list[i] <= list[j]) {
            sorted[k++] = list[i++];
        }
        else {
            sorted[k++] = list[j++];
        }
        moveCount++; // 이동 횟수 증가
    }

    // 남은 값 처리 부분
   // 이때 이동횟수도 증가 시켜준다.


   // 왼쪽 부분에 값이 남아있다면 배열에 넣어준다
    while (i <= mid) {
        sorted[k++] = list[i++];
        moveCount++;
    }
    // 오른쪽 부분에 값이 남았다면 배열에 넣어준다.
    while (j <= right) {
        sorted[k++] = list[j++];
        moveCount++;
    }


    // 원본 배열에 결과를 복사 시켜주는 부분
    for (i = left; i <= right; i++) {
        list[i] = sorted[i];
        moveCount++; // 이동횟수 증가
    }
}


// 합병정렬 함수
void doMergeSort(int array[SIZE], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        // 분할해주는 곳
        doMergeSort(array, left, mid);
        doMergeSort(array, mid + 1, right);

        // 결합해주는 곳
        merge(array, left, mid, right);

        // 10번마다 출력시켜준다!!
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


////보너스 부분= > 아직 미해결
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
//// 배열 출력 함수
//void printArray(int array[SIZE], int size) {
//    for (int i = 0; i < size; i++) {
//        printf("%3d ", array[i]);
//    }
//    printf("\n");
//}
//
//// Merge Sort 병합 함수
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
//// 합병정렬 반복적 방법 (bottom-up 방식)
//void doMergeSortIterative(int array[SIZE]) {
//    // 반복문을 사용하여 1부터 SIZE까지의 크기 단위로 병합을 수행
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
//        // 10번마다 출력
//        if (rounds % PRINT_INTERVAL == 0) {  // 출력 조건만 체크, isFirst는 더 이상 필요 없을 수 있음
//            // 배열의 처음 10개 값과 중앙에서 10개 값 출력
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
