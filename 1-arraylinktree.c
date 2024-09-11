#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 15

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
}TreeNode;


void GenerateArrayTree(int* tree) {

    int list[15] = { 1, 2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15 };

    for (int i = 0; i < 15; i++) {
        tree[i] = list[i];
    }

    for (int i = 0; i < 15; i++) {
        printf(" %2d", tree[i]);
    }
    printf("\n\n");
}


void ArrayPreOrder(int* tree, int index) {
    if (index < MAX_SIZE && tree[index] != -1) {
        printf(" %2d", tree[index]);
        ArrayPreOrder(tree, 2 * index + 1);
        ArrayPreOrder(tree, 2 * index + 2);
    }
}

void ArrayInorder(int* tree, int index) {
    if (index < MAX_SIZE && tree[index] != -1) {
        ArrayInorder(tree, 2 * index + 1);
        printf(" %2d", tree[index]);
        ArrayInorder(tree, 2 * index + 2);
    }
}

void ArrayPostOrder(int* tree, int index) {
    if (index < MAX_SIZE && tree[index] != -1) {
        ArrayPostOrder(tree, 2 * index + 1);
        ArrayPostOrder(tree, 2 * index + 2);
        printf(" %2d", tree[index]);
    }
}

void ArrayOrders(int* tree) {
   
    ArrayPreOrder(tree, 0);
    printf("\n");

   
    ArrayInorder(tree, 0);
    printf("\n");

   
    ArrayPostOrder(tree, 0);
    printf("\n");
    printf("\n");
}

void PlaceNode(TreeNode* root, int direction, int data)
{
    if (direction == 0) {
        root->left = malloc(sizeof(TreeNode));
        root->left->data = data;
        root->left->left = NULL;
        root->left->right = NULL;
    }
    else if(direction==1){
        root->right = malloc(sizeof(TreeNode));
        root->right->data = data;
        root->right->right = NULL;
        root->right->left = NULL;
    }

}

void GenerateLinkTree(TreeNode* root) {
    PlaceNode(root, 0, 2);
    PlaceNode(root, 1, 9);
    PlaceNode(root->left, 0, 3);
    PlaceNode(root->left, 1, 5);
    PlaceNode(root->right,0, 10);
    PlaceNode(root->right,1, 13);
    PlaceNode(root->left->left, 0, 4);
    PlaceNode(root->left->left, 1, 6);
    PlaceNode(root->left->right,0 ,7);
    PlaceNode(root->left->right,1,8);
    PlaceNode(root->right->left,0,11);
    PlaceNode(root->right->left, 1, 12);
    PlaceNode(root->right->right,0, 14);
    PlaceNode(root->right->right, 1, 15);
}

void LinkePreOrder(TreeNode* tree) {
    if (tree != NULL) {
        printf(" %2d", tree->data);
        LinkePreOrder(tree->left);
        LinkePreOrder(tree->right);
    }
}

void LinkInOrder(TreeNode* tree) {
    if (tree != NULL) {

        LinkInOrder(tree->left);
        printf(" %2d", tree->data);
        LinkInOrder(tree->right);
    }
}


void LinkPostOrder(TreeNode* tree) {
    if (tree != NULL) {

        LinkPostOrder(tree->left);

        LinkPostOrder(tree->right);
       
        printf(" %2d", tree->data);
        

    }

}

void LinkOrders(TreeNode* root) {
    LinkePreOrder(root);
    printf("\n");
    LinkInOrder(root);
    printf("\n");
    LinkPostOrder(root);
    printf("\n");

}



int main() {
    int arr[MAX_SIZE];
    TreeNode* root = malloc(sizeof(TreeNode));
    root->data = 1;

    GenerateArrayTree(arr);
    GenerateLinkTree(root);



    ArrayOrders(arr);
    LinkOrders(root);


    
    return 0;
}
