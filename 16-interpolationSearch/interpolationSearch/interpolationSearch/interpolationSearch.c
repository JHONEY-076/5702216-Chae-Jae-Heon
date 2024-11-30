#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10000
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int compareCount = 0;

//랜덤 숫자를 생성해 배열에 저장
void generateRandomArray(int list[]) {
    for (int i = 0; i < SIZE; i++) {
        list[i] = rand() % 10000;
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



// 배열을 나누고, 피벗의 위치를 반환하는 함수
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

//재귀적으로 호출하여 배열을 계속 나누고 정렬하는 퀵정렬 함수
void QuickSort(int array[], int left, int right) {
    if (left < right) {
        int q = partition(array, left, right);
        QuickSort(array, left, q - 1);
        QuickSort(array, q + 1, right);
    }
}

// 이진 탐색 평균 비교 횟수를 계산하는 함수
double getAverageBinarySearchCompareCount(int array[]) {
    int totalCompare = 0;

    for (int i = 0; i < 1000; i++) {
        int key = array[rand() % SIZE];  // 배열 내 무작위 키 선택
        int low = 0;
        int high = SIZE - 1;
        int compare = 0;

        // 이진 탐색 수행
        while (low <= high) {
            
            int middle = (low + high) / 2; // 중간인덱스를 찾는 부분 

            if (array[middle] == key) {
                compare++; // 키를 찾은 경우 비교횟수 증가
                break; 
            }
            else if (key < array[middle]) {
                high = middle - 1;
                compare++; // 왼쪽으로 탐색 시에 비교횟수를 증가시켜준다.
            }
            else {
                low = middle + 1;
                compare++; // 오른쪽으로 탐색시 비교횟수를 증가시켜준다.
            }
        }
        totalCompare += compare;
    }

    return totalCompare / 1000.0;  // 평균 비교 횟수 반환
}


//보간탐색을 이용하여 정렬된 배열의 값을 무작위로 선택하여 각 탐색 시 수행된 비교횟수의 평균을 구하는 함수
double getAverageInterpolationSearchComparecount(int array[]) {
    int totalCompare = 0;

    for (int i = 0; i < 1000; i++) {
        int target = array[rand() % SIZE];
        int low = 0;
        int high = SIZE - 1;
        int compare = 0;

        while (low <= high && target >= array[low] && target <= array[high]) {
            
            // 보간 위치 계산
            int j = low + ((double)(target - array[low]) / (array[high] - array[low])) * (high - low);
            
            //각 비교 조건에서 compare를 증가시킨다.
            if (target > array[j]) {
                low = j + 1; 
                compare++;  // 비교횟수 증가
            }
            else if (target < array[j]) {
                high = j - 1;
                compare++;  // 비교횟수 증가
            }
            else {
                compare++;  // target == array[j] 경우 중가
                break;
            }
        }

        // 반복문이 종료된후 low위치에서 target을 다시 한번 확인
        if (low <= high && array[low] == target) compare++;

        totalCompare += compare;
    }

    return totalCompare / 1000.0;  // 평균 비교 횟수 반환
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