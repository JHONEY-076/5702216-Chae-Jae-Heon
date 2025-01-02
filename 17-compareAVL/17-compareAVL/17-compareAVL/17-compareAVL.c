#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// AVL Tree�� BST�� ����ü ����
typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height; // AVL Ʈ�� ���� ����
} Node;

int compareCount = 0; // �� Ƚ��
int searchCount = 0;  // Ž�� Ƚ��

// �ִ��� ��ȯ�ϴ� �Լ�aaaaaaaaaa
int maxReturn(int a, int b) {
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}

// ���̸� ��ȯ�ϴ� �Լ�
int getHeight(Node* nptr) {
    if (nptr == (Node*)NULL) return 0;
    else return nptr->height;
}

// ��带 �����ϴ� �Լ�
Node* createNode(int key) {
    Node* nptr = (Node*)malloc(sizeof(Node));
    nptr->key = key;
    nptr->right = nptr->left = (Node*)NULL;
    nptr->height = 1;
    return nptr;
}

//������ ȸ���� �ϴ� �Լ�
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

//����ȸ���� �ϴ� �Լ�
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
//���ʼ� ����Ʈ���� ���̿� ������ ����Ʈ���� ���̸� �� �������� ����ϰ� ��ȯ�ϴ� �Լ�
int getBalance(Node* nptr) {
    return getHeight(nptr->left) - getHeight(nptr->right);
}

//���ο� ��带 �����ѵ� Ʈ���� ������ Ȯ���ϰ�, �ұ����� �߻��ϸ� ȸ�� ������ ��������ִ� �Լ�
Node* insertNode_AVL(Node* root, int key) {
    
    // ��� ���� �κ� 
    if (root == (Node*)NULL) return createNode(key);

    if (root->key > key)
        root->left = insertNode_AVL(root->left, key);
    else if (root->key < key)
        root->right = insertNode_AVL(root->right, key);
    else
        return root;
    
    //�� ��尡 ���ԵǸ� �ش����� ����Ʈ���� ���̰� �ٲ�� �����Ƿ� ���� ����� ���̸� ���Ž����ش�.
    root->height = 1 + ((getHeight(root->left) > getHeight(root->right))
        ? getHeight(root->left)
        : getHeight(root->right));


    int balance = getBalance(root);// ���� Ȯ��
    

    // �ұ��� ó�� �κ� 
    if (balance >= 2) {
        // LL�κ�
        if (getBalance(root->left) >= 0) 
            return rotateRight(root);
        else {
            //LR�κ� 
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }
    else if (balance <= -2) {
        //RR�κ�
        if (getBalance(root->right) < 0) 
            return rotateLeft(root);
        else {
            //RL�κ� 
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }
    else
        return root; //Ʈ���� �ұ������� ���� ���, ����� ��Ʈ�� ��ȯ�Ѵ�.
}

//Ʈ������ �ּҰ� ��带 ã�� �Լ�
Node* getMinValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// AVLƮ������ ��带 ���� �� �� Ʈ���� ������ �����ϵ��� �ϴ� �Լ�
Node* deleteNode_AVL(Node* root, int key) {
    // ���� ��� Ž��
    if (root == NULL) return root;
    if (key < root->key)
        root->left = deleteNode_AVL(root->left, key);
    else if (key > root->key)
        root->right = deleteNode_AVL(root->right, key);
    
    // ���� �۾� ���� 
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
        // �ڽ��� �Ѵ� �������� ������ ����Ʈ���� ���� ���� ���� ã�� �ش� ���� ���� ����� Ű�� ��ü�ϰ� ������ ����Ʈ������ ��ü�� Ű���� ����!!! 
        else {
            Node* temp = getMinValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode_AVL(root->right, temp->key);
        }
    }


    // ��������� ȣ��� ��, ����Ʈ���� ������ �Ϸ�Ǹ�, ���� ����� ���̸� ���Ž����ش�.
    if (root == NULL) return root;

    root->height = 1 + ((getHeight(root->left) > getHeight(root->right))
        ? getHeight(root->left) : getHeight(root->right));

    //���� Ȯ��
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root); //LL�κ� 

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root); //LR�κ�
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root); // RR�κ�

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root); // RL�κ�
    }

    return root; // ������ ������ ���·� ��ȯ�����ش�.
}

// BST�� ��� ����
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

// BST���� ��� ����
Node* deleteBST(Node* root, int key) {
    
    //���� ��� Ž��
    if (root == NULL) {
        return root;
    }

    if (key < root->key) {
        root->left = deleteBST(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteBST(root->right, key);
    }
    // ���� �۾�����
    else {
        if (root->left == NULL) {// ���� �ڽ��� ���� ��
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {// ������  �ڽ��� ������ 
            Node* temp = root->left;
            free(root);
            return temp;
        }
        // �ڽ��� �Ѵ� �������� ������ ����Ʈ���� ���� ���� ���� ã�� �ش� ���� ���� ����� Ű�� ��ü�ϰ� ������ ����Ʈ������ ��ü�� Ű���� ����!!! 
        Node* temp = getMinValueNode(root->right);
        root->key = temp->key;
        root->right = deleteBST(root->right, temp->key);
    }

    return root;
}

// Ž�� �Լ�
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

// Ʈ�� �޸� ����
void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// AVL Batch ���� �Լ� 
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

// BST Batch ���� �Լ�
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

// ���� �Լ�
int main(int argc, char* argv[]) {
    Node* root = NULL;
    srand(time(NULL));
    float allCount = 0.0;

    // �������� ���õ� AVL�� ���� 2000ȸ Batch �۾��� �����Ѵ�.
    doAVLBatch(&root);
    allCount = (float)compareCount / searchCount;
    printf("average AVL compare count: %.2f\n", allCount);

    // ������ȸ�ϸ� AVLƮ���� ��������� ��� �����͸� free
    freeTree(root);
    root = NULL;
    compareCount = searchCount = 0;
    
    
    // �������� ���õ� Binary Search Tree Batch�� �����Ѵ�.
    doBinaryBatch(&root);
    allCount = (float)compareCount / searchCount;
    printf("average Bin compare count: %.2f\n", allCount);

    freeTree(root);
    return 0;
}