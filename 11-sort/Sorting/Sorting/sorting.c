#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))


// �ش� ����Ʈ�� ������ִ� �Լ�
void print_list(int list[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}



// ���� ���Ŀ��� ���� ������ 10���� 20 ������ ������ְ� ������ ��°�� ������ִ� �Լ�
void doSelectionSort(int list[]) {
    int i, j, least, temp;
    int n = SIZE;

    printf("Selection Sort:\n");

    // ���� ���� ����
    for (i = 0; i < n - 1; i++) {
        least = i;
        for (j = i + 1; j < n; j++) {
            if (list[least] > list[j])
                least = j;
        }

        SWAP(list[i], list[least], temp);

        //���� ������ 10���� 20 ������ ������ִ� �κ�
        if ((i + 1) % 20 == 10 ) {
            printf("step %d: ", i + 1);
            print_list(list, n);
            printf("\n");
        }
    }
    // ������ ��°�� ������ִ� �κ�
    printf("step 99:\n");
    print_list(list, n);
}



// ���� �����͸� ������ִ� �Լ�
void generateRandomData(int list[]) {
    srand(time(0));
    for (int i = 0; i < SIZE; i++) {
        list[i] = rand() % 1000;
    }
}

//���� ���� 20ȸ�� �õ��ϰ� ��� ��Ƚ���� ���İ���� ������ִ� �Լ�
void doInsertionSort(int list[]) {
    int i, j, key, compare;
    int n = SIZE;
    long totalCompare = 0;

    printf("\n\nInsertion Sort Compare ");

    // 20���� ���� ������ �õ�
    int LastList[SIZE];  // ���� ���ĵ� �迭 ����

    

    for (int attempt = 0; attempt < 20; attempt++) {
       

        compare = 0;


        //��ȸ���� ������ ������ ���� �Լ��� ȣ���� �Ź� �ٸ� ���� ������ �����Ų��
        int CopyList[SIZE];
        generateRandomData(CopyList);

        // ���� ���� ����
        for (i = 1; i < n; i++) {
            key = CopyList[i];
            j = i - 1;

            while (j >= 0 && CopyList[j] > key) {
                CopyList[j + 1] = CopyList[j];
                j--;
                compare++; //��Ƚ���� ���������ش�.
            }

            CopyList[j + 1] = key;
        }

        totalCompare += compare; // �� �õ��� �� Ƚ���� ���Ѵ�.


        // 20��° �õ� �� ���� �迭�� ��������ִ°�
        if (attempt == 19) {
            for (int i = 0; i < SIZE; i++) {
                LastList[i] = CopyList[i];
            }
        }
    }

    int averageCompare = (double)totalCompare / 20.0;
    printf("Average: %d\n", averageCompare);
    printf("Insertion Sort Result:\n");
    print_list(LastList, SIZE);  // ������ ���ĵ� �迭 ���
}


// ���� ������ 20ȸ �õ��ϰ� ��� �̵�ȸ���� ���� ����� ������ִ� �Լ�
void doBubbleSort(int list[]) {
    int i, j, temp, flag, moves;
    int n = SIZE;
    long totalMove = 0;  // �̵� Ƚ���� ����
    int LastList[SIZE];  // ���� ���ĵ� �迭 ����

    // 20���� ���� ������ �����ش�.
    for (int attempt = 0; attempt < 20; attempt++) {
        
        moves = 0;

        //��ȸ���� ������ ������ ���� �Լ��� ȣ���� �Ź� �ٸ� ���� ������ �����Ų��
        int Copylist[SIZE];
        generateRandomData(Copylist);  // ������ ������ ���� �Լ� ȣ��

        // ���� ���� �����ϴ� ��!! 
        for (i = n - 1; i > 0; i--) {
            flag = 0;
            for (j = 0; j < i; j++) {
               
                if (Copylist[j] > Copylist[j + 1]) {
                    
                    
                    // swap�� �߻��ϸ� �̵� Ƚ�� 3ȸ ����
                    SWAP(Copylist[j], Copylist[j + 1], temp);
                    flag = 1;
                    moves += 3;
                }
            }
            if (flag == 0) break;  // �̹� ���ĵǾ����� ����
        }

        totalMove += moves; // �̵� Ƚ�� ����




        // 20��° �õ� �� ���� �迭�� ��������ִ°�
        if (attempt == 19) {
            for (int i = 0; i < SIZE; i++) {
                LastList[i] = Copylist[i];
            }
        }
    }

    // ��� �̵� Ƚ���� ������ִ°�!!
    int averageMoves = totalMove / 20;
    printf("\n\nBubble Sort Move Average: %d\n", averageMoves);
    printf("Bubble Sort Result:\n");
    print_list(LastList, SIZE);
}



int main(void) {
    int randomData[SIZE];
    generateRandomData(randomData);
    doSelectionSort(randomData);
    doInsertionSort(randomData);
    doBubbleSort(randomData);
    return 0;
}

