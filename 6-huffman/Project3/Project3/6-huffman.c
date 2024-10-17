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

// ���� �����ϴ� �Լ�
HeapTree* create_Heap() {
    return (HeapTree*)malloc(sizeof(HeapTree));
}

// ���� �ʱ�ȭ�ϴ� �Լ�
void init_Heap(HeapTree* h) {
    h->heap_size = 0;
}

// ���� ��Ҹ� �����ϴ� �Լ�
void insert_min_Heap(HeapTree* h, element item) {
    int i = ++(h->heap_size);

    // Ʈ���� �Ž��� �ö󰡸� �θ�� ���ϴ°� 
    while (i != 1 && item.key < h->heap[i / 2].key) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item; // ���ο� ��� ����

    // ���� �� ���� ���
    for (int j = 1; j <= h->heap_size; j++) {
        printf("%d ", h->heap[j].key); // �󵵼� ���
    }
    printf("\n");
}

// ������ �ּҰ��� �����ϴ� �Լ�
element delete_min_Heap(HeapTree* h) {
    int parent, child;
    element item, temp;

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;

    while (child <= h->heap_size) {
        // �ڽ� ��� �� �� ���� ��� ã�°�
        if (child < h->heap_size && h->heap[child].key > h->heap[child + 1].key)
            child++;

        if (temp.key < h->heap[child].key) break;

        // �� ���� �Ʒ��� �̵��ϴ� ��
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

// ���� Ʈ���� �����ϴ� �Լ�
TreeNode* Create_BST(TreeNode* left, TreeNode* right) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->left = left;
    node->right = right;
    return node;
}

// ���� Ʈ���� �����ϴ� �Լ�
void destroy_tree(TreeNode* root) {
    if (root == NULL) return;
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

// ���� ������� Ȯ���ϴ� �Լ�
int is_leafNode(TreeNode* root) {
    return !(root->left) && !(root->right);
}

// ������ �ڵ带 ����ϴ� �Լ�
void display_array(int codes[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d", codes[i]);
    printf("\n");
}

void display_codes(TreeNode* root, int codes[], int top) {
    if (root->left) {
        codes[top] = 1; // ���� ��� : 1
        display_codes(root->left, codes, top + 1);
    }
    if (root->right) {
        codes[top] = 0; // ������ ���: 0
        display_codes(root->right, codes, top + 1);
    }
    if (is_leafNode(root)) {
        printf("%c: ", root->ch);
        display_array(codes, top);
    }
}

// ������ Ʈ���� �����ϴ� �Լ�
void GenerateHuffmanCodes(char ch_list[], int freq[], int n) {
    TreeNode* node, * x; // ����Ʈ���� ��带 ��Ÿ���� ������ 
    HeapTree* heap;     // ������ Ʈ���� ���� �ּ� �� 
    element e, e1, e2;  // ���� ���Ե� ��ҵ��� ��Ÿ���� ����ü
    int codes[100];     // �� ������ ������ �ڵ带 �����ϱ� ���� �迭 

    heap = create_Heap(); // �� ����
    if (heap == NULL) {
        printf("���� �Ҵ���� �ʾ���.\n");
        return;
    }

    // �� �ʱ�ȭ
    init_Heap(heap);

    // �� ������ �󵵿� ���ڸ� �����ϴ� ���ο� ����Ʈ�� ���� �����ϰ� ����Ʈ�� ��忡 ���ڿ� �󵵸� �Ҵ�
    for (int i = 0; i < n; i++) {
        node = Create_BST(NULL, NULL);
        e.ch = node->ch = ch_list[i];
        e.key = node->weight = freq[i];
        e.ptree = node;
        insert_min_Heap(heap, e); // ����Ʈ���� �ּ����� ����
    }

    // �ּ� �� ���� ��带 �����Ͽ� ���ο� ��带 �����ϰ� �ּ����� �ٽ� ����
    for (int i = 1; i < n; i++) {
        e1 = delete_min_Heap(heap); // ������ �� ���� �ּ� ���(e1, e2)�� ����
        e2 = delete_min_Heap(heap);
        x = Create_BST(e1.ptree, e2.ptree);  // ���ο� ����Ʈ�� ��带 ���� 
        e.key = x->weight = e1.key + e2.key; // ���ο� ����� �󵵴� �� ����� ���� ��
        e.ptree = x;
        printf("////%d + %d -> %d\n", e1.key, e2.key, e.key); // ���� ���� ���
        insert_min_Heap(heap, e); // ���ο� ��带 �ּ����� �ٽ� ����
    }

    // ���� Ʈ������ �ڵ� ���
    e = delete_min_Heap(heap); // ���� Ʈ��
    int top = 0; // �ڵ� �ʱ�ȭ
    display_codes(e.ptree, codes, top);
    destroy_tree(e.ptree); // Ʈ�� ����
    free(heap); // �� ����
}

int main(void) {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);
    GenerateHuffmanCodes(characters, frequencies, size);
    return 0;
}
