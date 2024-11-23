#include <stdio.h>
#include <stdlib.h>
#define SIZE 100
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))


int comparisonCount = 0;
int moveCount = 0;
int isFirst = 0;
int totalComparisons = 0;
int totalMoveCount = 0;
int rounds = 0;


// 배열 출력 함수
void printArray(int list[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

// 랜덤 데이터 생성 함수
void generateRandomArray(int list[]) {

    for (int i = 0; i < SIZE; i++) {
        list[i] = rand() % 1000;
    }
}


// 배열을 나누고, 피벗의 위치를 반환하는 함수
int partition(int array[], int left, int right) {
    int pivot, temp;
    int low, high;


    low = left; // 왼쪽에서 탐색을 시작하는 인덱스 
    high = right + 1; // 오른쪽에서 탐색을 시작하는 인덱스
    pivot = array[left]; // 기준이 되는 값 설정(배열의 첫번째 요소를 피벗으로 설정)

    do {

        do {
            low++;
            comparisonCount++; // 비교횟수 증가
        } while (array[low] < pivot && low <= right); // 피벗보다 큰 값을 찾을 때까지 low를 증가 시킨다.


        do {
            high--;
            comparisonCount++; // 비교횟수 증가
        } while (array[high] > pivot && high >= left); // 피벗보다 작은 값을 찾을때까지 high를 감소 시킨다.


        //low와 high가 가리키는 값을 교환해주는 부분!!
        if (low < high) { 
            SWAP(array[low], array[high], temp); 
            moveCount += 3;  // 이동횟수 증가
        }
    } while (low < high);

    // 탐색이 끝나면 피벗과 array[high]를 교환해서 피벗을 올바른 위치에 놓도록 해준다.
    SWAP(array[left], array[high], temp);
    moveCount += 3; // 이동횟수 증가

    return high;
}

//
////재귀적으로 호출하여 배열을 계속 나누고 정렬하며, 정렬 과정을 출력하는 함수
//void doQuickSort(int array[], int left, int right) {
//    if (left < right) {
//        int q = partition(array, left, right); // 함수르 호출하여 배열을 나누고, 피벗의 위치를 반환하는 부분
//        doQuickSort(array, left, q - 1); // 피벗을 기준으로부터 왼쪽 부분 배열을 재귀호출
//        doQuickSort(array, q + 1, right); // 피벗을 기준으로부터 오른쪽 부분 배열을 재귀호출
//
//    }
//
//    // 출력과정 부분
//    if (rounds % 10 == 0 && isFirst == 0) {
//        for (int i = 40; i < 60; i++)
//            printf("%d ", array[i]);
//        printf("\n\n");
//    }
//    rounds++;
//
//}


//----------------------------------------------------------------

// 보너스 부분 입니다 !!!! 

void doQuickSort(int array[], int left, int right) {


    // 스택 초기화 부분 
    int stack[SIZE];
    int top = -1;
    
    // 첫번째 정렬 구간을 스택에 추가 시켜준다.
    stack[++top] = left;
    stack[++top] = right;



    while (top >= 0) { // 스택이 비어 있지 않을때까지 계속 수행

        // 스택에서 구간을 꺼내어 처리 시켜준다        
        right = stack[top--];
        left = stack[top--];

        // 현재 구간을 파티션 후 피벗의 인덱스를 반환시켜준다.
        int pivotIndex = partition(array, left, right);

        // 피벗 인덱스의 왼쪽 부분을 정렬해야 할 구간으로 스택에 추가해준다.
        if (pivotIndex - 1 > left) {
            stack[++top] = left;
            stack[++top] = pivotIndex - 1;
        }


        // 피벗 인덱스의 오른쪽 부분을 정렬해야 할 구간으로 스택에 추가해준다.
        if (pivotIndex + 1 < right) {
            stack[++top] = pivotIndex + 1;
            stack[++top] = right;
        }

        // 출력 부분
        if (rounds % 10 == 0 && isFirst == 0) {
            for (int i = 40; i < 60; i++)
                printf("%d ", array[i]);
            printf("\n\n");
        }
        rounds++;
    }
}


//--------------------------------------------------------------------




int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];
    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;
        if (i == 0) {
            printf("Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1);
            printf("Result\n");
            printArray(array, SIZE);
            isFirst++;
        }
        else {
            doQuickSort(array, 0, SIZE - 1);
        }
        totalComparisons += comparisonCount;
        totalMoveCount += moveCount;
    }
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);
    return 0;

}

