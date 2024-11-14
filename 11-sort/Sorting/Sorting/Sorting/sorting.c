#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))


// 해당 리스트를 출력해주는 함수
void print_list(int list[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}



// 선택 정렬에서 정렬 과정을 10부터 20 단위로 출력해주고 마지막 번째를 출력해주는 함수
void doSelectionSort(int list[]) {
    int i, j, least, temp;
    int n = SIZE;

    printf("Selection Sort:\n");

    // 선택 정렬 수행
    for (i = 0; i < n - 1; i++) {
        least = i;
        for (j = i + 1; j < n; j++) {
            if (list[least] > list[j])
                least = j;
        }

        SWAP(list[i], list[least], temp);

        //정렬 과정을 10부터 20 단위로 출력해주는 부분
        if ((i + 1) % 20 == 10 ) {
            printf("step %d: ", i + 1);
            print_list(list, n);
            printf("\n");
        }
    }
    // 마지막 번째를 출력해주는 부분
    printf("step 99:\n");
    print_list(list, n);
}



// 랜덤 데이터를 만들어주는 함수
void generateRandomData(int list[]) {
    srand(time(0));
    for (int i = 0; i < SIZE; i++) {
        list[i] = rand() % 1000;
    }
}

//삽입 정렬 20회를 시도하고 평균 비교횟수와 정렬결과를 출력해주는 함수
void doInsertionSort(int list[]) {
    int i, j, key, compare;
    int n = SIZE;
    long totalCompare = 0;

    printf("\n\nInsertion Sort Compare ");

    // 20번의 삽입 정렬을 시도
    int LastList[SIZE];  // 최종 정렬된 배열 저장

    

    for (int attempt = 0; attempt < 20; attempt++) {
       

        compare = 0;


        //매회마다 무작위 데이터 생성 함수를 호출해 매번 다른 랜덤 값으로 수행시킨다
        int CopyList[SIZE];
        generateRandomData(CopyList);

        // 삽입 정렬 수행
        for (i = 1; i < n; i++) {
            key = CopyList[i];
            j = i - 1;

            while (j >= 0 && CopyList[j] > key) {
                CopyList[j + 1] = CopyList[j];
                j--;
                compare++; //비교횟수를 증가시켜준다.
            }

            CopyList[j + 1] = key;
        }

        totalCompare += compare; // 각 시도의 비교 횟수를 합한다.


        // 20번째 시도 후 최종 배열을 저장시켜주는곳
        if (attempt == 19) {
            for (int i = 0; i < SIZE; i++) {
                LastList[i] = CopyList[i];
            }
        }
    }

    int averageCompare = (double)totalCompare / 20.0;
    printf("Average: %d\n", averageCompare);
    printf("Insertion Sort Result:\n");
    print_list(LastList, SIZE);  // 마지막 정렬된 배열 출력
}


// 버블 정렬을 20회 시도하고 평균 이동회수와 정렬 결과를 출력해주는 함수
void doBubbleSort(int list[]) {
    int i, j, temp, flag, moves;
    int n = SIZE;
    long totalMove = 0;  // 이동 횟수의 총합
    int LastList[SIZE];  // 최종 정렬된 배열 저장

    // 20번의 버블 정렬을 시켜준다.
    for (int attempt = 0; attempt < 20; attempt++) {
        
        moves = 0;

        //매회마다 무작위 데이터 생성 함수를 호출해 매번 다른 랜덤 값으로 수행시킨다
        int Copylist[SIZE];
        generateRandomData(Copylist);  // 무작위 데이터 생성 함수 호출

        // 버블 정렬 수행하는 곳!! 
        for (i = n - 1; i > 0; i--) {
            flag = 0;
            for (j = 0; j < i; j++) {
               
                if (Copylist[j] > Copylist[j + 1]) {
                    
                    
                    // swap이 발생하면 이동 횟수 3회 증가
                    SWAP(Copylist[j], Copylist[j + 1], temp);
                    flag = 1;
                    moves += 3;
                }
            }
            if (flag == 0) break;  // 이미 정렬되었으면 종료
        }

        totalMove += moves; // 이동 횟수 누적




        // 20번째 시도 후 최종 배열을 저장시켜주는곳
        if (attempt == 19) {
            for (int i = 0; i < SIZE; i++) {
                LastList[i] = Copylist[i];
            }
        }
    }

    // 평균 이동 횟수를 출력해주는곳!!
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

