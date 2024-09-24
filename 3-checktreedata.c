#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

typedef struct {
    TreeNode* node;
    int level;
} QueueElement;

typedef struct {
    QueueElement data[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

void init_queue(QueueType* q) {
    q->front = q->rear = 0;
}

int is_empty(QueueType* q) {
    return (q->front == q->rear);
}

int is_full(QueueType* q) {
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType* q, QueueElement item) {
    if (is_full(q)) {
        printf("큐가 포화 상태입니다.\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

QueueElement dequeue(QueueType* q) {
    if (is_empty(q)) {
        printf("큐가 공백상태입니다.\n");
        exit(1);
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

void PlaceNode(TreeNode* root, int direction, int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    if (direction == 0) {
        root->left = newNode;
    }
    else if (direction == 1) {
        root->right = newNode;
    }
}

void GenerateLinktree(TreeNode* root) {
    PlaceNode(root, 0, 2);
    PlaceNode(root, 1, 9);
    PlaceNode(root->left, 0, 3);
    PlaceNode(root->left, 1, 5);
    PlaceNode(root->right, 0, 10);
    PlaceNode(root->right, 1, 13);
    PlaceNode(root->left->left, 0, 4);
    PlaceNode(root->left->left, 1, 6);
    PlaceNode(root->left->right, 0, 7);
    PlaceNode(root->left->right, 1, 8);
    PlaceNode(root->right->left, 0, 11);
    PlaceNode(root->right->left, 1, 12);
    PlaceNode(root->right->right, 0, 14);
    PlaceNode(root->right->right, 1, 15);
}

int GetSumOfNodes(TreeNode* root) {
    int sum = 0;
    QueueType q;
    init_queue(&q);
    if (root == NULL) return 0;
    enqueue(&q, (QueueElement) { root, 0 });

    while (!is_empty(&q)) {
        TreeNode* ptr = dequeue(&q).node;
        sum += ptr->data;
        if (ptr->left)
            enqueue(&q, (QueueElement) { ptr->left, 0 });
        if (ptr->right)
            enqueue(&q, (QueueElement) { ptr->right, 0 });
    }
    return sum;
}

int GetNumberOfNodes(TreeNode* root) {
    int count = 0;
    QueueType q;
    init_queue(&q);
    if (root == NULL) return 0;
    enqueue(&q, (QueueElement) { root, 0 });

    while (!is_empty(&q)) {
        TreeNode* current = dequeue(&q).node;
        count++;
        if (current->left)
            enqueue(&q, (QueueElement) { current->left, 0 });
        if (current->right)
            enqueue(&q, (QueueElement) { current->right, 0 });
    }
    return count;
}

int GetHeightOfTree(TreeNode* root) {
    if (root == NULL) return 0;

    QueueType q;
    init_queue(&q);
    enqueue(&q, (QueueElement) { root, 1 });

    int height = 0;

    while (!is_empty(&q)) {
        QueueElement ptr = dequeue(&q);
        height = ptr.level; 

        if (ptr.node->left) {
            enqueue(&q, (QueueElement) { ptr.node->left, ptr.level + 1 });
        }
        if (ptr.node->right) {
            enqueue(&q, (QueueElement) { ptr.node->right, ptr.level + 1 });
        }
    }

    return height;
}

int GetNumberOfLeafNodes(TreeNode* root) {
    int leafNode = 0;
    QueueType q;
    init_queue(&q);
    if (root == NULL) return 0;
    enqueue(&q, (QueueElement) { root, 0 });

    while (!is_empty(&q)) {
        TreeNode* ptr = dequeue(&q).node;
        if (ptr->left == NULL && ptr->right == NULL) {
            leafNode++;
        }
        else {
            if (ptr->left) {
                enqueue(&q, (QueueElement) { ptr->left, 0 });
            }
            if (ptr->right) {
                enqueue(&q, (QueueElement) { ptr->right, 0 });
            }
        }
    }
    return leafNode;
}

void free_tree(TreeNode* root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main() {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    if (root == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        return 1;
    }
    root->data = 1;

    GenerateLinktree(root);
    printf("Sum of nodes : %d\n", GetSumOfNodes(root));
    printf("Number of nodes: %d\n", GetNumberOfNodes(root));
    printf("Height of Tree: %d\n", GetHeightOfTree(root));
    printf("Number of leaf nodes: %d\n", GetNumberOfLeafNodes(root));

    free_tree(root);  
    return 0;
}
