#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// AVL Tree와 BST를 위한 구조체 및 함수 정의
typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height; // AVL 트리를 위한 높이 정보
} Node;

int compareCount = 0; // 비교 횟수
int searchCount = 0;  // 탐색 횟수

// 유틸리티 함수: 최대값 반환
int maxReturn(int a, int b) {
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}

int getHeight(Node* nptr) {
    if (nptr == (Node*)NULL) return 0;
    else return nptr->height;
}

Node* createNode(int key) {
    Node* nptr = (Node*)malloc(sizeof(Node));
    nptr->key = key;
    nptr->right = nptr->left = (Node*)NULL;
    nptr->height = 1;
    return nptr;
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T3 = x->right;

    x->right = y;
    y->left = T3;

    y->height = 1 + ((getHeight(y->left) > getHeight(y->right))
        ? getHeight(y->left)
        : getHeight(y->right));

    x->height = 1 + ((getHeight(x->left) > getHeight(x->right))
        ? getHeight(x->left)
        : getHeight(x->right));

    return x;
}

Node* rotateLeft(Node* y) {
    Node* x = y->right;
    Node* T2 = x->left;

    x->left = y;
    y->right = T2;

    y->height = 1 + ((getHeight(y->left) > getHeight(y->right))
        ? getHeight(y->left)
        : getHeight(y->right));

    x->height = 1 + ((getHeight(x->left) > getHeight(x->right))
        ? getHeight(x->left)
        : getHeight(x->right));

    return x;
}

int getBalance(Node* nptr) {
    return getHeight(nptr->left) - getHeight(nptr->right);
}

Node* insertNode_AVL(Node* root, int key) {
    if (root == (Node*)NULL) return createNode(key);

    if (root->key > key)
        root->left = insertNode_AVL(root->left, key);
    else if (root->key < key)
        root->right = insertNode_AVL(root->right, key);
    else
        return root;

    root->height = 1 + ((getHeight(root->left) > getHeight(root->right))
        ? getHeight(root->left)
        : getHeight(root->right));

    int balance = getBalance(root);

    if (balance >= 2) {
        if (getBalance(root->left) >= 0) return rotateRight(root);
        else {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }
    else if (balance <= -2) {
        if (getBalance(root->right) < 0) return rotateLeft(root);
        else {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }
    else
        return root;
}

//트리에서 최소값 노드 찾기
Node* getMinValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

Node* deleteNode_AVL(Node* root, int key) {
    if (root == NULL) return root;
    if (key < root->key)
        root->left = deleteNode_AVL(root->left, key);
    else if (key > root->key)
        root->right = deleteNode_AVL(root->right, key);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else {
                *root = *temp;
            }
            free(temp);
        }
        else {
            Node* temp = getMinValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode_AVL(root->right, temp->key);
        }
    }

    if (root == NULL) return root;

    root->height = 1 + ((getHeight(root->left) > getHeight(root->right))
        ? getHeight(root->left) : getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// BST에 노드 삽입
Node* insertBST(Node* node, int key) {
    if (node == NULL) {
        return createNode(key);
    }

    if (key < node->key) {
        node->left = insertBST(node->left, key);
    }
    else if (key > node->key) {
        node->right = insertBST(node->right, key);
    }

    return node;
}

// BST에서 노드 삭제
Node* deleteBST(Node* root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->key) {
        root->left = deleteBST(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteBST(root->right, key);
    }
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = getMinValueNode(root->right);
        root->key = temp->key;
        root->right = deleteBST(root->right, temp->key);
    }

    return root;
}

// 탐색 함수
int searchTree(Node* root, int key) {
    if (root == NULL) {
        return 0;
    }
    compareCount++;
    if (key == root->key) {
        return 1;
    }
    else if (key < root->key) {
        return searchTree(root->left, key);
    }
    else {
        return searchTree(root->right, key);
    }
}

// 트리 메모리 해제
void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// AVL Batch 실행
void doAVLBatch(Node** root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;
        int B = rand() % 1000;
        if (A == 0) {
            *root = insertNode_AVL(*root, B);
        }
        else if (A == 1) {
            *root = deleteNode_AVL(*root, B);
        }
        else if (A == 2) {
            searchCount++;
            searchTree(*root, B);
        }
    }
}

// BST Batch 실행
void doBinaryBatch(Node** root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;
        int B = rand() % 1000;
        if (A == 0) {
            *root = insertBST(*root, B);
        }
        else if (A == 1) {
            *root = deleteBST(*root, B);
        }
        else if (A == 2) {
            searchCount++;
            searchTree(*root, B);
        }
    }
}

// 메인 함수
int main(int argc, char* argv[]) {
    Node* root = NULL;
    srand(time(NULL));
    float allCount = 0.0;

    // 과제에서 제시된 AVL에 대한 2000회 Batch 작업을 수행한다.
    doAVLBatch(&root);
    allCount = (float)compareCount / searchCount;
    printf("average AVL compare count: %.2f\n", allCount);

    // 후위순회하며 AVL트리로 만들어졌던 모든 데이터를 free
    freeTree(root);
    root = NULL;
    compareCount = searchCount = 0;
    
    
    // 과제에서 제시된 Binary Search Tree Batch를 수행한다.
    doBinaryBatch(&root);
    allCount = (float)compareCount / searchCount;
    printf("average Bin compare count: %.2f\n", allCount);

    freeTree(root);
    return 0;
}