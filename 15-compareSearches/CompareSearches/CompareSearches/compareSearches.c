#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int compareCount = 0;

//랜덤 숫자를 생성해 배열에 저장
void generateRandomArray(int list[]) {
    for (int i = 0; i < SIZE; i++) {
        list[i] = rand() % 1000;
    }
}

// 배열의 처음 20개와 마지막 20개의 원소를 출력해주는 함수
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++)
        printf("%3d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%3d ", array[i]);
    printf("\n");
}

// 순차 탐색으로 
double getAverageLinearSearchCompareCount(int array[]) {
    int totalCompare = 0;
    for (int i = 0; i < 100; i++) { // 순차탐색을 100번 수행

        int key = array[rand() % SIZE]; // 배열 내의 무작위 인덱스를 선택하고, 해당하는 값을 key값으로 지정해준다.
        int compareCount = 0;
        //순차탐색 알고리즘 부분
        for (int j = 0; j < SIZE; j++) {
            compareCount++; //비교횟수 카운트
            if (array[j] == key) break; //키 값을 찾으면 break
        }
        totalCompare += compareCount; //100번의 탐색에 대한 비교횟수를 누적시켜준다.
    }
    return totalCompare / 100.0;
}

// 배열을 나누고, 피벗의 위치를 반환하는 함수
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

//재귀적으로 호출하여 배열을 계속 나누고 정렬하는 퀵정렬 함수
void quickSort(int array[], int left, int right) {
    if (left < right) {
        int q = partition(array, left, right);
        quickSort(array, left, q - 1);
        quickSort(array, q + 1, right);
    }
}

//비교횟수를 초기화 시켜주고 배열 전체에 대해 퀵정렬을 수행시켜주는 함수
void getQuickSortCompareCount(int array[]) {
    compareCount = 0; // 비교횟수 초기화
    quickSort(array, 0, SIZE - 1); // 배열 전체에 대해 퀵 정렬 수행
}



double getAverageBinarySearchCompareCount(int array[]) {
    int totalCompare = 0;

    for (int i = 0; i < 100; i++) {  // 이진 탐색을 100번 수행
        int key = array[rand() % SIZE];  // 배열 내에서 무작위 키 선택
        int low = 0;
        int high = SIZE - 1;
        int compare = 0;

        while (low <= high) {
            int middle = (low + high) / 2;  // 중간 인덱스 계산
            

            if (array[middle] == key) {
                compare++;  // 중간값 비교 시 카운트
                break;  // 키를 찾으면 종료
            }
            else if (key < array[middle]) {
                compare++;  // 중간값 비교 시 카운트
                high = middle - 1;
            }
            else {
                compare++;  // 중간값 비교 시 카운트
                low = middle + 1;
            }
        }
        totalCompare += compare;  // 탐색 종료 후 비교 횟수 누적
    }
    return totalCompare / 100.0;  // 평균 비교 횟수 반환
}


int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];
    generateRandomArray(array);
    //평균값을 반환받기 위한 조치
    printf("Average Linear Search Compare Count: %.2f\n",
        getAverageLinearSearchCompareCount(array));
    //compareCount가 global variable이므로, 다음과 같이 구현
    //array에 대해서 직접 정렬하면 된다.
    getQuickSortCompareCount(array);
    printf("Quick Sort Compare Count: %d\n", compareCount);
    //정렬된 Array에 대해서 Binary Search 100회 수행 및 평균 비교횟수 출력
    printf("Average Binary Search Compare Count: %.2f\n\n",
        getAverageBinarySearchCompareCount(array));
    printArray(array);
    return 0;
}