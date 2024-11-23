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


// �迭 ��� �Լ�
void printArray(int list[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

// ���� ������ ���� �Լ�
void generateRandomArray(int list[]) {

    for (int i = 0; i < SIZE; i++) {
        list[i] = rand() % 1000;
    }
}


// �迭�� ������, �ǹ��� ��ġ�� ��ȯ�ϴ� �Լ�
int partition(int array[], int left, int right) {
    int pivot, temp;
    int low, high;


    low = left; // ���ʿ��� Ž���� �����ϴ� �ε��� 
    high = right + 1; // �����ʿ��� Ž���� �����ϴ� �ε���
    pivot = array[left]; // ������ �Ǵ� �� ����(�迭�� ù��° ��Ҹ� �ǹ����� ����)

    do {

        do {
            low++;
            comparisonCount++; // ��Ƚ�� ����
        } while (array[low] < pivot && low <= right); // �ǹ����� ū ���� ã�� ������ low�� ���� ��Ų��.


        do {
            high--;
            comparisonCount++; // ��Ƚ�� ����
        } while (array[high] > pivot && high >= left); // �ǹ����� ���� ���� ã�������� high�� ���� ��Ų��.


        //low�� high�� ����Ű�� ���� ��ȯ���ִ� �κ�!!
        if (low < high) { 
            SWAP(array[low], array[high], temp); 
            moveCount += 3;  // �̵�Ƚ�� ����
        }
    } while (low < high);

    // Ž���� ������ �ǹ��� array[high]�� ��ȯ�ؼ� �ǹ��� �ùٸ� ��ġ�� ������ ���ش�.
    SWAP(array[left], array[high], temp);
    moveCount += 3; // �̵�Ƚ�� ����

    return high;
}

//
////��������� ȣ���Ͽ� �迭�� ��� ������ �����ϸ�, ���� ������ ����ϴ� �Լ�
//void doQuickSort(int array[], int left, int right) {
//    if (left < right) {
//        int q = partition(array, left, right); // �Լ��� ȣ���Ͽ� �迭�� ������, �ǹ��� ��ġ�� ��ȯ�ϴ� �κ�
//        doQuickSort(array, left, q - 1); // �ǹ��� �������κ��� ���� �κ� �迭�� ���ȣ��
//        doQuickSort(array, q + 1, right); // �ǹ��� �������κ��� ������ �κ� �迭�� ���ȣ��
//
//    }
//
//    // ��°��� �κ�
//    if (rounds % 10 == 0 && isFirst == 0) {
//        for (int i = 40; i < 60; i++)
//            printf("%d ", array[i]);
//        printf("\n\n");
//    }
//    rounds++;
//
//}


//----------------------------------------------------------------

// ���ʽ� �κ� �Դϴ� !!!! 

void doQuickSort(int array[], int left, int right) {


    // ���� �ʱ�ȭ �κ� 
    int stack[SIZE];
    int top = -1;
    
    // ù��° ���� ������ ���ÿ� �߰� �����ش�.
    stack[++top] = left;
    stack[++top] = right;



    while (top >= 0) { // ������ ��� ���� ���������� ��� ����

        // ���ÿ��� ������ ������ ó�� �����ش�        
        right = stack[top--];
        left = stack[top--];

        // ���� ������ ��Ƽ�� �� �ǹ��� �ε����� ��ȯ�����ش�.
        int pivotIndex = partition(array, left, right);

        // �ǹ� �ε����� ���� �κ��� �����ؾ� �� �������� ���ÿ� �߰����ش�.
        if (pivotIndex - 1 > left) {
            stack[++top] = left;
            stack[++top] = pivotIndex - 1;
        }


        // �ǹ� �ε����� ������ �κ��� �����ؾ� �� �������� ���ÿ� �߰����ش�.
        if (pivotIndex + 1 < right) {
            stack[++top] = pivotIndex + 1;
            stack[++top] = right;
        }

        // ��� �κ�
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

