#include <stdio.h>
#include <stdlib.h>

// 이진트리구조체
typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

// 스레드 이진트리 구조체
typedef struct ThreadTree {
	int data;
	struct ThreadTree* left, * right;
	int is_thread; // 스레드 여부를 나타내는 변수
} ThreadTree;


// 새로운 노드 생성
TreeNode* new_node(int key) {
	TreeNode* temp = NULL;
	temp = malloc(sizeof(TreeNode));
	temp->data = key;
	temp->left = temp->right = NULL;

	return temp;
}

TreeNode* insert_node(TreeNode* root, int key) {
	
	//노드가 없으면 새로운 노드 생성
	if (root == NULL) {
		return new_node(key);
	}
	// 노드의 데이터가 삽입하려는 노드의 데이터와 같으면 리턴
	if (root->data == key) {
		return root;
	}
	// 노드의 데이터가 삽입하려는 노드의 데이터보다 작다면 노드의 왼쪽에 새로운 노드를 삽입한다.
	else if (root->data > key) {
		root->left = insert_node(root->left, key);
	}
	//노드의 데이터가 삽입하려는 노드의 데이터보다 크다면 노드의 오른족에 새로운 노드를 삽입한다.
	else if (root->data < key) {
		root->right = insert_node(root->right, key);
	}
	return root;

}


TreeNode* GenerateBinaryTree(int inputData[]) {
	TreeNode* root = NULL;

	for (int i = 0; i < 15; i++) {
		root = insert_node(root, inputData[i]);
	}
	return root;

}

// 이진트리 중위순회 
void BinaryTreeInOrder(TreeNode* root) {


	if (root != NULL) {

		BinaryTreeInOrder(root->left);
		printf("%d ", root->data);
		BinaryTreeInOrder(root->right);
	}
}


//새로운 노드 생성
ThreadTree* new_thread_node(int key) {
	ThreadTree* temp = malloc(sizeof(ThreadTree));
	if (!temp) {
		fprintf(stderr, "메모리 할당 실패\n");
		exit(EXIT_FAILURE);
	}
	temp->data = key;
	temp->left = temp->right = NULL;
	temp->is_thread = 0; // 스레드의 초기값을 모두 0으로 초기화 해준다.
	return temp;
}





ThreadTree* insert_Thread_node(ThreadTree* root, int key) {
	
	//노드가 없으면 새 노드 생성
	if (root == NULL) {
		return new_thread_node(key);
	}

	//해당 노드의 데이터와 삽입할 노드의 데이터가 같다면 리턴
	if (root->data == key) {
		return root;
	}
	//해당 노드의 데이터보다 삽입할 노드의 데이터가 작다면 해당 노드의 왼쪽으로 삽입
	else if (root->data > key) {
		root->left = insert_Thread_node(root->left, key);
	}
	//해당 노드의 데이터보다 삽입할 노드의 데이터가 크다면 해당 노드의 오른쪽으로 삽입
	else {
		root->right = insert_Thread_node(root->right, key);
	}
		
	return root;
}


ThreadTree* GenerateThreadTree(int inputData[]) {
	ThreadTree* root = NULL;

	for (int i = 0; i < 15; i++) {
		root = insert_Thread_node(root, inputData[i]); // 할당된 배열의 원소를 트리에 삽입해준다.
	}
	return root;

}

// 스레드 중위순회 설정
void setInorderThreads(ThreadTree* root) {
	if (root == NULL) return;

	root->left->right->left->is_thread = 1;	//2는 스레드로 표시 
	root->left->right->left->right = root->left->right; //2의 오른쪽은 3을 가리킴 


	root->left->right->is_thread = 1;	//3을 스레드로 표시
	root->left->right->right = root;	//3의 오른쪽은 4를 가리킴 

	root->right->left->left->is_thread = 1;		// 5를 스레드로 표시
	root->right->left->left->right = root->right->left;	// 5의 오른쪽운 6을 가리킴 

	root->right->left->right->right->is_thread = 1; //8을 스레드로 표시
	root->right->left->right->right->right = root->right;	// 8의 오른쪽은 9를 가리킴

	root->right->right->left->right->left->is_thread = 1; // 11을 스레드로 표시
	root->right->right->left->right->left->right = root->right->right->left->right;	 // 11의 오른쪽은 12로 가리킴

	root->right->right->left->right->is_thread = 1; // 12를 스레드로 표시 
	root->right->right->left->right->right = root->right->right; // 12의 오른쪽은 13을 가리킴

	root->right->right->right->left->is_thread = 1; // 14를 스레드로 표시 
	root->right->right->right->left->right = root->right->right->right;	// 14의 오른쪽은 15로 가리킴
}




//스레드 중위순회
void ThreadTreeInOrder(ThreadTree* root) {
	setInorderThreads(root);
	ThreadTree* currentNode = root;

	//cuurentNode가 NULL일때까지 왼쪽 자식으로 이동
	while (currentNode && currentNode->left) {
		currentNode = currentNode->left;
	}

	printf("\nThread tree inorder:  ");
	while (currentNode != NULL) {
		printf("%d ", currentNode->data);
		if (currentNode->is_thread) {
			currentNode = currentNode->right; // 스레드를 따라 이동
		}
		else {
			currentNode = currentNode->right; // 일반 링크를 따라 이동
			while (currentNode && currentNode->left) {
				currentNode = currentNode->left; // 왼쪽자식의 끝으로 이동
			}
		}
	}
}



int main() {
	int inputData[] = { 4,1,9,13,15,3,6,14,7,10,12,2,5,8,11 };

	//트리생성, *root에 트리를 생성해 반환
	TreeNode* root = GenerateBinaryTree(inputData);
	printf("Binary tree inorder: ");
	BinaryTreeInOrder(root);

	ThreadTree* troot = GenerateThreadTree(inputData);
	ThreadTreeInOrder(troot);

	free(root);
	free(troot);

	return 0;
}



