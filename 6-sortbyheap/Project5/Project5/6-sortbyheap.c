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

// �Լ� ������Ÿ�� ����
void swap(int arr[], int i, int j);
void resortHeap(int arr[], int n, int i);
void insertToHeap(int arr[], int* n, int value);

// �� ���� �Լ�
TreeNode* create_heap() {
    return (TreeNode*)malloc(sizeof(TreeNode));
}

// �� �ʱ�ȭ �Լ�
void init_heap(TreeNode* h) {
    h->heap_size = 0;
}

// �迭�� ��Ҹ� ��ȯ(SWAP)�ϴ� �Լ�
void swap(int arr[], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// �־��� �ε��� i�� �������� �ִ����� �籸���ϴ� �Լ�
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

// ���� ���� �����ϰ� �ִ� ������ �����ϴ� �Լ�
void insertToHeap(int arr[], int* n, int value) {
    arr[*n] = value; // �迭�� �������� �� �� ����
    int i = *n;
    (*n)++;

    // Upheap: �θ�� ���ϸ� �ִ� �� Ư���� ����
    while (i != 0 && arr[(i - 1) / 2] < arr[i]) {
        swap(arr, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }

    // ���� �� ���� ���
    for (int j = 0; j < *n; j++) {
        printf("%d ", arr[j]);
    }
    printf("\n");
}

// ���� �����ϰ� �����ϴ� �Լ�
void BuildMaxHeapAndSort(int inputData[], int n) {
    int heapSize = 0;
    int heap[MAX_SIZE];

    // �迭�� ���� �ִ� ���� ����
    for (int i = 0; i < n; i++) {
        insertToHeap(heap, &heapSize, inputData[i]);
    }

    // �� ����
    for (int i = heapSize - 1; i > 0; i--) {
        swap(heap, 0, i); // ù��° �ε����� i��°(������)�ε����� ��ȯ���ش�.
        ResortHeap(heap, i, 0);

        // �� ���� �� ���� ���
        for (int j = 0; j < i; j++) {
            printf("%d ", heap[j]);
        }
        printf("\n");
    }

    // ���ĵ� ����� ���� �迭�� ����
    for (int i = 0; i < n; i++) {
        inputData[i] = heap[i];
    }
}

int main() {
    int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // �� ���� ����
    BuildMaxHeapAndSort(inputData, size);

    // ���ĵ� ��� ���
    printf("\nSorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    return 0;
}
