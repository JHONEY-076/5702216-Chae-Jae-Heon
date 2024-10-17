#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

typedef struct TreeNode {
    int weight;
    char ch;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct {
    TreeNode* ptree;
    char ch;
    int key;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapTree;

// 힙을 생성하는 함수
HeapTree* create_Heap() {
    return (HeapTree*)malloc(sizeof(HeapTree));
}

// 힙을 초기화하는 함수
void init_Heap(HeapTree* h) {
    h->heap_size = 0;
}

// 힙에 요소를 삽입하는 함수
void insert_min_Heap(HeapTree* h, element item) {
    int i = ++(h->heap_size);

    // 트리를 거슬러 올라가며 부모와 비교하는곳 
    while (i != 1 && item.key < h->heap[i / 2].key) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item; // 새로운 노드 삽입

    // 현재 힙 상태 출력
    for (int j = 1; j <= h->heap_size; j++) {
        printf("%d ", h->heap[j].key); // 빈도수 출력
    }
    printf("\n");
}

// 힙에서 최소값을 삭제하는 함수
element delete_min_Heap(HeapTree* h) {
    int parent, child;
    element item, temp;

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;

    while (child <= h->heap_size) {
        // 자식 노드 중 더 작은 노드 찾는곳
        if (child < h->heap_size && h->heap[child].key > h->heap[child + 1].key)
            child++;

        if (temp.key < h->heap[child].key) break;

        // 한 레벨 아래로 이동하는 곳
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

// 이진 트리를 생성하는 함수
TreeNode* Create_BST(TreeNode* left, TreeNode* right) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->left = left;
    node->right = right;
    return node;
}

// 이진 트리를 해제하는 함수
void destroy_tree(TreeNode* root) {
    if (root == NULL) return;
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

// 리프 노드인지 확인하는 함수
int is_leafNode(TreeNode* root) {
    return !(root->left) && !(root->right);
}

// 허프만 코드를 출력하는 함수
void display_array(int codes[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d", codes[i]);
    printf("\n");
}

void display_codes(TreeNode* root, int codes[], int top) {
    if (root->left) {
        codes[top] = 1; // 왼쪽 노드 : 1
        display_codes(root->left, codes, top + 1);
    }
    if (root->right) {
        codes[top] = 0; // 오른쪽 노드: 0
        display_codes(root->right, codes, top + 1);
    }
    if (is_leafNode(root)) {
        printf("%c: ", root->ch);
        display_array(codes, top);
    }
}

// 허프만 트리를 생성하는 함수
void GenerateHuffmanCodes(char ch_list[], int freq[], int n) {
    TreeNode* node, * x; // 이진트리의 노드를 나타내는 포인터 
    HeapTree* heap;     // 허프만 트리를 위한 최소 힙 
    element e, e1, e2;  // 힙에 삽입될 요소들을 나타내는 구조체
    int codes[100];     // 각 문자의 허프만 코드를 저장하기 위한 배열 

    heap = create_Heap(); // 힙 생성
    if (heap == NULL) {
        printf("힙이 할당되지 않았음.\n");
        return;
    }

    // 힙 초기화
    init_Heap(heap);

    // 각 문자의 빈도와 문자를 포함하는 새로운 이진트리 노드들 생성하고 이진트리 노드에 문자와 빈도를 할당
    for (int i = 0; i < n; i++) {
        node = Create_BST(NULL, NULL);
        e.ch = node->ch = ch_list[i];
        e.key = node->weight = freq[i];
        e.ptree = node;
        insert_min_Heap(heap, e); // 이진트리를 최소힙에 삽입
    }

    // 최소 두 개의 노드를 병합하여 새로운 노드를 생성하고 최소힙에 다시 삽입
    for (int i = 1; i < n; i++) {
        e1 = delete_min_Heap(heap); // 힙에서 두 개의 최소 요소(e1, e2)를 삭제
        e2 = delete_min_Heap(heap);
        x = Create_BST(e1.ptree, e2.ptree);  // 새로운 이진트리 노드를 생성 
        e.key = x->weight = e1.key + e2.key; // 새로운 노드의 빈도는 두 노드의 빈도의 합
        e.ptree = x;
        printf("////%d + %d -> %d\n", e1.key, e2.key, e.key); // 병합 과정 출력
        insert_min_Heap(heap, e); // 새로운 노드를 최소힙에 다시 삽입
    }

    // 최종 트리에서 코드 출력
    e = delete_min_Heap(heap); // 최종 트리
    int top = 0; // 코드 초기화
    display_codes(e.ptree, codes, top);
    destroy_tree(e.ptree); // 트리 해제
    free(heap); // 힙 해제
}

int main(void) {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);
    GenerateHuffmanCodes(characters, frequencies, size);
    return 0;
}
