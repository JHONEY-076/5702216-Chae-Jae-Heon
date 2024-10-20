#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
typedef struct {
    int n; // 정점의 개수
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphMatType;

// 스택 구조체
typedef struct {
    int items[MAX_VERTICES];
    int top;
} Stack;

// 큐 구조체
typedef struct {
    int items[MAX_VERTICES];
    int front;
    int rear;
} Queue;

GraphMatType* create_matrix_graph();
void destroy_mat_graph(GraphMatType* g);
void init_mat_graph(GraphMatType* g);
void insert_vertex_mat_graph(GraphMatType* g, int v);
void insert_edge_mat_graph(GraphMatType* g, int s, int e);
void print_adj_mat(GraphMatType* g);
void DFS_matrix(GraphMatType* g, int start, int target);
void BFS_matrix(GraphMatType* g, int start, int target);
void runUserInterface(GraphMatType* root);
void push(Stack* s, int value);
int pop(Stack* s);
int is_empty_stack(Stack* s);
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
int is_empty_queue(Queue* q);

int main() {
    GraphMatType* g = create_matrix_graph();
    init_mat_graph(g);

    for (int i = 0; i < 11; i++) {
        insert_vertex_mat_graph(g, i); // 정점 삽입하는곳
    }

    // 간선 삽입 하는곳
    insert_edge_mat_graph(g, 0, 5);
    insert_edge_mat_graph(g, 0, 2);
    insert_edge_mat_graph(g, 0, 6);
    insert_edge_mat_graph(g, 0, 9);

    insert_edge_mat_graph(g, 1, 5);
    insert_edge_mat_graph(g, 1, 4);
    insert_edge_mat_graph(g, 1, 7);
    insert_edge_mat_graph(g, 1, 10);

    insert_edge_mat_graph(g, 2, 3);
    insert_edge_mat_graph(g, 2, 0);
    insert_edge_mat_graph(g, 2, 4);

    insert_edge_mat_graph(g, 3, 2);
    insert_edge_mat_graph(g, 3, 5);
    insert_edge_mat_graph(g, 3, 4);

    insert_edge_mat_graph(g, 4, 2);
    insert_edge_mat_graph(g, 4, 3);
    insert_edge_mat_graph(g, 4, 6);
    insert_edge_mat_graph(g, 4, 7);
    insert_edge_mat_graph(g, 4, 1);

    insert_edge_mat_graph(g, 5, 0);
    insert_edge_mat_graph(g, 5, 3);
    insert_edge_mat_graph(g, 5, 1);

    insert_edge_mat_graph(g, 6, 0);
    insert_edge_mat_graph(g, 6, 4);
    insert_edge_mat_graph(g, 6, 7);
    insert_edge_mat_graph(g, 6, 8);

    insert_edge_mat_graph(g, 7, 1);
    insert_edge_mat_graph(g, 7, 4);
    insert_edge_mat_graph(g, 7, 6);
    insert_edge_mat_graph(g, 7, 10);

    insert_edge_mat_graph(g, 8, 6);
    insert_edge_mat_graph(g, 8, 9);
    insert_edge_mat_graph(g, 8, 10);

    insert_edge_mat_graph(g, 9, 0);
    insert_edge_mat_graph(g, 9, 8);

    insert_edge_mat_graph(g, 10, 1);
    insert_edge_mat_graph(g, 10, 7);
    insert_edge_mat_graph(g, 10, 8);


    runUserInterface(g);// 사용자 인터페이스를 실행하는 곳
    free(g);
    return 0;
}


// 인접행렬 그래프를 생성하는 함수 
GraphMatType* create_matrix_graph() {
    return (GraphMatType*)malloc(sizeof(GraphMatType));
}


// 인접행렬 그래프를 초기화 시켜주는 함수
void init_mat_graph(GraphMatType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
        for (int j = 0; j < MAX_VERTICES; j++)
            g->adj_mat[i][j] = 0;
}


// 인접행렬 그래프에서 정점을 삽입하는 함수
void insert_vertex_mat_graph(GraphMatType* g, int v) {
    if ((g->n) >= (MAX_VERTICES - 1)) {
        fprintf(stderr, "정점의 개수가 초과 되었습니다\n");
        return;
    }
    (g->n)++;// 정점의 개수를 1증가 시킨다.
}

// 인접 행렬 그래프에서 간선을 삽입하는 함수
void insert_edge_mat_graph(GraphMatType* g, int start, int end) {
    
    // 입력한 정점의 시작 번호와 끝번호를 잘못 입력한경우 그래프 정점 번호 오류를 표시해준다.
    if (g->n <= start || g->n <= end) {
        fprintf(stderr, "그래프 정점번호 오류.\n");
        return;
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1; 
}

// 인접 행렬 그래프의 형태를 출력해서 확인시켜주는 함수(실제 메인함수에서는 호출하지 않음)
void print_adj_mat(GraphMatType* g) {
    printf("     ");
    for (int i = 0; i < g->n; i++) {
        printf(" %02d ", i);
    }
    printf("\n_____");
    for (int i = 0; i < g->n; i++) {
        printf("_______");
    }
    printf("\n");
    for (int i = 0; i < g->n; i++) {
        printf(" %02d: ", i);
        for (int j = 0; j < g->n; j++)
            printf(" %02d ", g->adj_mat[i][j]);
        printf("\n");
    }
}
// 인접 행렬로 구성된 그래프에서 DFS로 탐색하는 함수 
void DFS_matrix(GraphMatType* g, int start, int target) {
    int visited[MAX_VERTICES] = { 0 }; // 방문 여부 추적
    Stack s;
    s.top = -1;
    push(&s, start);
    int count = 0; // 방문한 노드 수 카운트

    while (!is_empty_stack(&s)) {
        int vertex = pop(&s);

        // 방문하지 않은 노드라면
        if (!visited[vertex]) {
            visited[vertex] = 1; // 방문 처리
            count++;
            printf("%d ", vertex); // 방문한 노드 출력

            if (vertex == target) {
                printf("\n탐색 성공: %d\n", target);
                printf("방문한 노드 수: %d\n", count);
                return;
            }

            // 현재 노드에서 인접한 노드를 스택에 푸시
            for (int i = 0; i < g->n; i++) {
                if (g->adj_mat[vertex][i] == 1 && !visited[i]) {
                    push(&s, i);
                }
            }
        }
        else {
            printf("%d ", vertex); // 이미 방문한 노드에서 백트랙 시 출력
        }
    }
    printf("\n타겟 %d 발견하지 못함.\n", target);
    printf("방문한 노드 수: %d\n", count);
}



// 인접행렬로 구성된 그래프를 BFS로 탐색하는 함수
void BFS_matrix(GraphMatType* g, int start, int target) {
    // 배열을 초기화 시켜 방문여부를 추적하는 곳
    int visited[MAX_VERTICES] = { 0 };

    // 큐를 초기화 해주고, 탐색할 첫번째 노드를 큐에 삽입한다.
    Queue q;
    q.front = 0;
    q.rear = -1;
    enqueue(&q, start);
    int count = 0; // 방문한 노드 수 카운트

    // 큐가 비어 있지 않을때 까지 실행 
    while (!is_empty_queue(&q)) {
        int vertex = dequeue(&q); // 큐에 들어있는 노드를 꺼낸다.

        // 현재 방문하지 않은 노드를 방문 처리해주고 방문한 노드 수를 카운트 해준다. 
        if (visited[vertex] == 0) {
            visited[vertex] = 1; // 방문 처리
            count++; // 방문한 노드 수 증가

            printf("%d ", vertex); // 방문한 노드 출력

            // 현재 방문한 노드가 타겟 노드와 같으면 탐색 종료  
            if (vertex == target) {
                printf("\n탐색 성공: %d\n", target);
                printf("방문한 노드 수: %d\n", count);
                return;
            }

            // 인접 노드와 현재 노드가 연결되었는지, 방문 노드인지 확인해주면 큐에 다음 탐색 대상으로 설정한다.
            for (int i = 0; i < g->n; i++) {
                if (g->adj_mat[vertex][i] == 1 && !visited[i]) {
                    enqueue(&q, i);
                }
            }
        }
        else {
            // 이미 방문한 노드에서 백트랙 시 출력
            printf("%d ", vertex);
        }
    }
    printf("\n타겟 %d 발견하지 못함.\n", target);
    printf("방문한 노드 수: %d\n", count); // 방문한 노드 수 출력
}


//사용자 인터페이스 메뉴 함수
void runUserInterface(GraphMatType* root) {
    int c = 0;
    int start_node = 0;
    int target_node = 0;

    for (;;) {
        printf("------------------------------\n");
        printf("1     : 깊이 우선 탐색        |\n");
        printf("2     : 너비 우선 탐색        |\n");
        printf("3     : 종료                  |\n");
        printf("------------------------------\n");

        printf("메뉴 입력: ");
        scanf_s("%d", &c);

        switch (c) {
        case 1:
            printf("시작 번호와 탐색할 값 입력: ");
            scanf_s("%d", &start_node); // 시작 노드
            scanf_s("%d", &target_node);// 탐색할노드 
            DFS_matrix(root, start_node, target_node); //시작노드의 값과 탐색할 노드의 값을 받아 DFS로 탐색한다.
            break;
        case 2:
            printf("시작 번호와 탐색할 값 입력: ");
            scanf_s("%d", &start_node); // 시작 노드
            scanf_s("%d", &target_node);// 탐색할 노드 
            BFS_matrix(root, start_node, target_node); // 시작노드의 값과 탐색할 노드의 값을 받아 BFS로 탐색한다.
            break;
        case 3:
            exit(0);
        default:
            printf("다시입력해주세요.\n");
        }
    }
}

// 스택 푸쉬 함수 
void push(Stack* s, int value) {
    if (s->top < MAX_VERTICES - 1) {
        s->items[++(s->top)] = value;
    }
}


//스택 팝 함수
int pop(Stack* s) {
    if (s->top >= 0) {
        return s->items[(s->top)--];
    }
    return -1; 
}
//스택이 비어있는지 확인하는 함수
int is_empty_stack(Stack* s) {
    return s->top == -1;
}


// 큐를 푸쉬하는 함수
void enqueue(Queue* q, int value) {
    if (q->rear < MAX_VERTICES - 1) {
        q->items[++(q->rear)] = value;
    }
}

// 큐를 팝하는 함수 
int dequeue(Queue* q) {
    if (q->front <= q->rear) {
        return q->items[(q->front)++];
    }
    return -1; 
}

// 큐가 비어있는지 확인하는 함수
int is_empty_queue(Queue* q) {
    return q->front > q->rear;
}
