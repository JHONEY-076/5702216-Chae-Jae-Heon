#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARRAY_SIZE 100

// 전체 리스트 출력 함수
void print_list(int list[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

// 인덱스 19까지만 출력해주는 리스트 출력 함수 
void print_list_gap(int list[], int n) {
    for (int i = 0; i < 20; i++) {
        printf("%d ", list[i]);
    }
    printf("...\n"); 
}


// 랜덤 데이터를 생성하는 함수
void generateRandomNumbers(int list[]) {
    srand((unsigned int)time(0));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        list[i] = rand() % 1000;
    }
}

// gap 값을 기준으로 간격 삽입 정렬을 수행하는 함수
int gap_insertion_sort(int list[], int first, int last, int gap, int* moveCount) {
    int i, j, key, count = 0;
    


    // 삽입 정렬 알고리즘 부분
    for (i = first + gap; i <= last; i += gap) {
        key = list[i];
        (*moveCount)++; // key 값을 복사한 횟수를 이동횟수로 카운트 시켜준다.
        
        ///key를 삽입할 위치를 찾기 위해 비교와 이동을 수행시켜주는 부분
        for (j = i - gap; j >= first; j -= gap) {
            count++; // 비교횟수 증가 
            if (list[j] > key) {
                list[j + gap] = list[j];
                (*moveCount)++; // 값이 이동한 횟수를 카운트 시켜준다.
            }
            else {
                break; // 정렬 조건을 만족하면 종료
            }
        }
        list[j + gap] = key; // key값을 최종 위치로 이동시켜준다.
        (*moveCount)++; // 이동횟수 카운트
    }
    return count;
}

// 쉘 정렬 알고리즘으로 gap을 줄이면서 반복적으로 정렬하는 함수
void doShellSort(int list[], int gap_num, int* comparisonCount, int* moveCount) {
    int i, n = ARRAY_SIZE, totalCompare = 0, totalMove = 0;

    for (int attempt = 0; attempt < 1; attempt++) {
        int tempArray[ARRAY_SIZE];
        for (i = 0; i < ARRAY_SIZE; i++) {
            tempArray[i] = list[i];  // 원본 배열을 복사해준다.
        }


        // 쉘 정렬 알고리즘 부분
        int gap, count = 0, moveCount = 0;
        for (gap = n / gap_num; gap > 0; gap /= gap_num) {
            if (gap < 1) gap = 1; // gap이 1 이하로 내려가는것을 방지해준다.

            for (i = 0; i < gap; i++) { 
                count += gap_insertion_sort(tempArray, i, n - 1, gap, &moveCount); // 간격 gap에 따라 부분 배열을 정렬하고 비교횟수와 이동 횟수를 누적시킨다.
            }


            // 매 gap 단계마다 정렬된 배열 상태를 출력시켜준다.
            printf("\nSorting with gap = %d:\n", gap);
            print_list_gap(tempArray, n); 
        }

        // 최종 정렬 결과 출력
        if (attempt == 0) {
            printf("\nSorted shellArray (gap = %d):\n", gap_num);
            print_list(tempArray, n);
        }


        // 비교횟수와 이동횟수를 누적 시켜주는곳
        totalCompare += count;
        totalMove += moveCount; 
    }


    // 최종 비교횟수와 이동횟수를 반환하는 곳
    *comparisonCount = totalCompare;
    *moveCount = totalMove;
}

// 삽입 정렬 함수
void doInsertionSort(int list[], int* averageComparison, int* averageMove) {
    int compareCount = 0, moveCount = 0;


    // 삽입정렬 알고리즘 부분
    for (int i = 1; i < ARRAY_SIZE; i++) {
        int key = list[i]; // 현재 삽입할 값을 key에 저장한다.
        int j = i - 1; // 정렬 부분을 탐색하기 위해 j를 설정시켜준다.



        while (j >= 0 && list[j] > key) {
            list[j + 1] = list[j]; //list[j]>key 조건을 만족한다면 원소를 오른쪽으로 이동시켜준다.
            j--; // 왼쪽으로 한칸 이동하여 계속 탐색 
            compareCount++; // 비교 횟수 카운트
            moveCount++;       // 이동 횟수 카운트
        }
        list[j + 1] = key;
        moveCount++; // 이동횟수 카운트
    }

    print_list(list, ARRAY_SIZE); // 정렬된 리스트 출력
    *averageComparison = compareCount;
    *averageMove = moveCount;
}


int main() {
    int array[ARRAY_SIZE];
    int comparisonCount, moveCount;

    generateRandomNumbers(array);

   
    printf("Shell Sort (n/2):\n");
    doShellSort(array, 2, &comparisonCount, &moveCount);
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    
    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, &comparisonCount, &moveCount);
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

   
    printf("Insertion Sort:\n");
    doInsertionSort(array, &comparisonCount, &moveCount);
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

    return 0;
}