#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// AVL Tree와 BST의 구조체 정의
typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height; // AVL 트리 높이 정보
} Node;

int compareCount = 0; // 비교 횟수
int searchCount = 0;  // 탐색 횟수

// 최댓값을 반환하는 함수aaaaaaaaaa
int maxReturn(int a, int b) {
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}

// 높이를 반환하는 함수
int getHeight(Node* nptr) {
    if (nptr == (Node*)NULL) return 0;
    else return nptr->height;
}

// 노드를 생성하는 함수
Node* createNode(int key) {
    Node* nptr = (Node*)malloc(sizeof(Node));
    nptr->key = key;
    nptr->right = nptr->left = (Node*)NULL;
    nptr->height = 1;
    return nptr;
}

//오른쪽 회전을 하는 함수
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

//왼쪽회전을 하는 함수
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
//왼쪽서 서브트리의 높이와 오른쪽 서브트리의 높이를 뺀 균형값을 계산하고 반환하는 함수
int getBalance(Node* nptr) {
    return getHeight(nptr->left) - getHeight(nptr->right);
}

//새로운 노드를 삽입한뒤 트리의 균형을 확인하고, 불균형이 발생하면 회전 연산을 수행시켜주는 함수
Node* insertNode_AVL(Node* root, int key) {
    
    // 노드 삽입 부분 
    if (root == (Node*)NULL) return createNode(key);

    if (root->key > key)
        root->left = insertNode_AVL(root->left, key);
    else if (root->key < key)
        root->right = insertNode_AVL(root->right, key);
    else
        return root;
    
    //새 노드가 삽입되면 해당노드의 서브트리의 높이가 바뀔수 있으므로 현재 노드의 높이를 갱신시켜준다.
    root->height = 1 + ((getHeight(root->left) > getHeight(root->right))
        ? getHeight(root->left)
        : getHeight(root->right));


    int balance = getBalance(root);// 균형 확인
    

    // 불균형 처리 부분 
    if (balance >= 2) {
        // LL부분
        if (getBalance(root->left) >= 0) 
            return rotateRight(root);
        else {
            //LR부분 
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }
    else if (balance <= -2) {
        //RR부분
        if (getBalance(root->right) < 0) 
            return rotateLeft(root);
        else {
            //RL부분 
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }
    else
        return root; //트리가 불균형하지 않은 경우, 변경된 루트를 반환한다.
}

//트리에서 최소값 노드를 찾는 함수
Node* getMinValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// AVL트리에서 노드를 삭제 한 후 트리의 균형을 유지하도록 하는 함수
Node* deleteNode_AVL(Node* root, int key) {
    // 삭제 대상 탐색
    if (root == NULL) return root;
    if (key < root->key)
        root->left = deleteNode_AVL(root->left, key);
    else if (key > root->key)
        root->right = deleteNode_AVL(root->right, key);
    
    // 삭제 작업 수행 
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
        // 자식이 둘다 없을때는 오른쪽 서브트리의 가장 작은 값을 찾아 해당 값을 현재 노드의 키로 대체하고 오른쪽 서브트리에서 대체된 키값을 삭제!!! 
        else {
            Node* temp = getMinValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode_AVL(root->right, temp->key);
        }
    }


    // 재귀적으로 호출된 후, 서브트리의 삭제가 완료되면, 현재 노드의 높이를 갱신시켜준다.
    if (root == NULL) return root;

    root->height = 1 + ((getHeight(root->left) > getHeight(root->right))
        ? getHeight(root->left) : getHeight(root->right));

    //균형 확인
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root); //LL부분 

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root); //LR부분
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root); // RR부분

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root); // RL부분
    }

    return root; // 균형을 유지한 상태로 반환시켜준다.
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
    
    //삭제 대상 탐색
    if (root == NULL) {
        return root;
    }

    if (key < root->key) {
        root->left = deleteBST(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteBST(root->right, key);
    }
    // 삭제 작업수행
    else {
        if (root->left == NULL) {// 왼쪽 자식이 없을 때
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {// 오른쪽  자식이 없을때 
            Node* temp = root->left;
            free(root);
            return temp;
        }
        // 자식이 둘다 없을때는 오른쪽 서브트리의 가장 작은 값을 찾아 해당 값을 현재 노드의 키로 대체하고 오른쪽 서브트리에서 대체된 키값을 삭제!!! 
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

// AVL Batch 실행 함수 
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

// BST Batch 실행 함수
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