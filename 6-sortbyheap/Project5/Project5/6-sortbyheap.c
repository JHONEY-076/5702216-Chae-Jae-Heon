#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct {
    int key;
} element;

typedef struct {
    element heap[MAX_SIZE];
    int heap_size;
} TreeNode;

// 함수 프로토타입 선언
void swap(int arr[], int i, int j);
void resortHeap(int arr[], int n, int i);
void insertToHeap(int arr[], int* n, int value);

// 힙 생성 함수
TreeNode* create_heap() {
    return (TreeNode*)malloc(sizeof(TreeNode));
}

// 힙 초기화 함수
void init_heap(TreeNode* h) {
    h->heap_size = 0;
}

// 배열의 요소를 교환(SWAP)하는 함수
void swap(int arr[], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// 주어진 인덱스 i를 기준으로 최대힙을 재구성하는 함수
void ResortHeap(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(arr, i, largest);
        ResortHeap(arr, n, largest);
    }
}

// 힙에 값을 삽입하고 최대 힙으로 유지하는 함수
void insertToHeap(int arr[], int* n, int value) {
    arr[*n] = value; // 배열의 마지막에 새 값 삽입
    int i = *n;
    (*n)++;

    // Upheap: 부모와 비교하며 최대 힙 특성을 유지
    while (i != 0 && arr[(i - 1) / 2] < arr[i]) {
        swap(arr, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }

    // 현재 힙 상태 출력
    for (int j = 0; j < *n; j++) {
        printf("%d ", arr[j]);
    }
    printf("\n");
}

// 힙을 생성하고 정렬하는 함수
void BuildMaxHeapAndSort(int inputData[], int n) {
    int heapSize = 0;
    int heap[MAX_SIZE];

    // 배열의 값을 최대 힙에 삽입
    for (int i = 0; i < n; i++) {
        insertToHeap(heap, &heapSize, inputData[i]);
    }

    // 힙 정렬
    for (int i = heapSize - 1; i > 0; i--) {
        swap(heap, 0, i); // 첫번째 인덱스와 i번째(마지막)인덱스를 교환해준다.
        ResortHeap(heap, i, 0);

        // 힙 정렬 후 상태 출력
        for (int j = 0; j < i; j++) {
            printf("%d ", heap[j]);
        }
        printf("\n");
    }

    // 정렬된 결과를 원래 배열에 복사
    for (int i = 0; i < n; i++) {
        inputData[i] = heap[i];
    }
}

int main() {
    int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // 힙 정렬 실행
    BuildMaxHeapAndSort(inputData, size);

    // 정렬된 결과 출력
    printf("\nSorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    return 0;
}
