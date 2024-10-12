#define _CRT_SECURE_NO_WARNINGS
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

// 힙 생성 함수
TreeNode* create_heap() {
    return (TreeNode*)malloc(sizeof(TreeNode));
}

// 힙 초기화 함수
void init_heap(TreeNode* h) {
    h->heap_size = 0;
}

// 현재 힙 상태의 요소를 출력해주는 함수
void display_heap(TreeNode* h) {
    for (int i = 1; i <= h->heap_size; i++) {
        printf("%02d ", h->heap[i].key); // 각 힙상태의 요소를 두 자리로 출력
    }
    printf("\n");
}



// 최대 힙에 노드를 추가하고 heapfiy 되는 과정을 보여주는 함수
void InsertMaxHeapTree(TreeNode* h, element data) {
    
    //힙이 가득찬경우에 출력
    if (h->heap_size >= MAX_SIZE - 1) {
        printf("힙이 가득 찼습니다!\n");
        return; 
    }

    int i = h->heap_size + 1; // 힙 배열의 인덱스 1 부터 지정
    int count = 0;  // 노드가 이동된 횟수를 카운트 해준다.



    // 1. 값에 상관없이 노드를 삽입하는 곳
    h->heap[i] = data;
    (h->heap_size)++;
    display_heap(h); // 힙배열에 추가된 현재 상태 출력



    // 2. 부모와 비교하며 Upheap을 진행시켜 완전 이진트리의 조건을 충족(heapfiy)시켜주는 곳

    while ((i != 1) && (h->heap[i / 2].key < data.key)) { // i가 1이 아니고 해당 인덱스의 데이터가 부모의 값보다 클때까지 반복해준다!!
        
        int parentIndex = i / 2; // 부모인덱스

        // 부모를 자식 위치로 이동(SWAP)
        element temp = h->heap[i];
        h->heap[i]= h->heap[parentIndex];
        h->heap[parentIndex]=temp;

        
        display_heap(h);// 현재 힙 상태 출력 
        count++;// 노드가 이동된 횟수를 카운트 해준다.

       
        i = parentIndex; // i를 부모 위치로 인덱스를 이동시킨다.
    }
   
    printf("노드가 이동된 횟수: %d\n", count);
}
 

// 메인함수에 배열의 값으로 최대힙을 생성하는 함수
TreeNode* generateMaxHeapTree(int inputData[], int size) {
    TreeNode* heap = create_heap();
    if (heap == NULL) {
        printf("할당된 메모리가 없습니다.\n");
        exit(1); 
    }
    init_heap(heap); // 힙 초기화 

    for (int i = 0; i < size; i++) { // 배열에 들어있는 요소를 size만큼 insert해주는곳
        InsertMaxHeapTree(heap, (element) { inputData[i] });
    }

    return heap; // 생성된 힙 리턴
}

// 최대힙을 삭제하는 함수
void delete_heap(TreeNode* h) {
    int parent, child;
    element item, temp;
    int count = 0; // 이동 횟수 카운트

    if (h->heap_size == 0) { // 힙이 비워있을 경우 
        printf("힙이 비어 있습니다!\n");
        return; 
    }

    item = h->heap[1]; // 루트 노드 저장
    temp = h->heap[h->heap_size]; // 마지막 노드 저장

    (h->heap_size)--; // 힙 크기 감소



    // 루트 노드에 마지막 노드를 저장한 후 힙 상태 출력
    h->heap[1] = temp;
    count++;
    display_heap(h); // 마지막 노드를 루트에 저장한 힙상태 출력

    
    
    // Heapify , 루트에서 시작하여 자식 노드로 내려간다(강등시켜준다)
    for (parent = 1, child = 2;
        child <= h->heap_size;
        parent = child, child = child * 2) { // child는 왼쪽 자식 노드의 인덱스

        // 현재 노드의 두 자식 중 더 큰 자식으로 child를 업데이트 해주는 곳!!!! 
        if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key)) // 만약 왼쪽 자식이 heap_size보다 작고 왼쪽 자식이 오른쪽 자식의 값보다 작으면  
            child++;                                                                 // child를 오른쪽 자식으로 업데이트 해준다.

        // temp가 자식 노드보다 크면 루프 종료
        if (temp.key >= h->heap[child].key)
            break;

        // 최종 두 자식 노드 중 큰 노드를 부모 노드로 이동키는 곳!!! (SWAP)
        element temp = h->heap[parent];
        h->heap[parent] = h->heap[child];
        h->heap[child] = temp;

        count++;

       
        display_heap(h); // 이동된 상태 힙상태 출력
    }

  
    printf("노드가 이동된 횟수: %d\n", count);
}



// 힙을 레벨별로 출력하는 함수
void level_display(TreeNode* h) {
    if (h->heap_size == 0) {
        printf("힙이 비어 있습니다.\n");
        return;
    }

    int level = 1;
    int level_node_size = 1; // 현재 레벨의 노드 수
    int index = 1;      // 힙에서 출력할 노드의 인덱스

    while (index <= h->heap_size) {  
        printf("[%d] ", level);
        for (int j = 0; j < level_node_size && index <= h->heap_size; j++) { //현재 레벨의 노드의 수와 힙사이즈 만큼 
                                                                             //저장된 힙의 인덱스를 출력 해주는 곳!!
            printf("%02d ", h->heap[index].key);
            index++;
        }
        printf("\n");
        level++;
        level_node_size *= 2; // 다음 레벨의 노드 수는 두 배로 증가 => 완전 이진트리이기 때문에 단말노드를 제외한 레벨별 노드수는 2배씩 증가한다.
    }
}


// 사용자 인터페이스 함수
void runUserInterface(TreeNode* root) {
    char c = 0;
    int a = 0;

    for (;;) {
        printf("----------------------\n");
        printf("| i  : 노드 추가    |\n");
        printf("| d  : 노드 삭제    |\n");
        printf("| p  : 레벨별 출력  |\n");
        printf("| c  : 종료         |\n");
        printf("----------------------\n");

        printf("메뉴 입력: ");
        scanf_s(" %c", &c, 1); 

        switch (c) {
        case 'i':
            printf("추가할 값 입력: ");
            scanf_s("%d", &a); 
            InsertMaxHeapTree(root, (element) { a }); // 사용자가 입력한 값을 힙에 추가
            break;
        case 'd':
            delete_heap(root);

            break;

        case 'p':
            level_display(root);
            break;

        case 'c':
            free(root); // 동적 할당된 메모리 해제
            exit(0);
            break;
        default:
            printf("다시입력해주세요.\n");
        }
    }
}

int main() {
    int inputData[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 15 };
    int size = sizeof(inputData) / sizeof(inputData[0]); // 배열 크기 계산

    TreeNode* root = generateMaxHeapTree(inputData, size);
    runUserInterface(root); 

    free(root); 

    return 0;
}
