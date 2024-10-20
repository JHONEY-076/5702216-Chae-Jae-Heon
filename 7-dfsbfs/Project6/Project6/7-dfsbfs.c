#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
typedef struct {
    int n; // ������ ����
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphMatType;

// ���� ����ü
typedef struct {
    int items[MAX_VERTICES];
    int top;
} Stack;

// ť ����ü
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
        insert_vertex_mat_graph(g, i); // ���� �����ϴ°�
    }

    // ���� ���� �ϴ°�
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


    runUserInterface(g);// ����� �������̽��� �����ϴ� ��
    free(g);
    return 0;
}


// ������� �׷����� �����ϴ� �Լ� 
GraphMatType* create_matrix_graph() {
    return (GraphMatType*)malloc(sizeof(GraphMatType));
}


// ������� �׷����� �ʱ�ȭ �����ִ� �Լ�
void init_mat_graph(GraphMatType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
        for (int j = 0; j < MAX_VERTICES; j++)
            g->adj_mat[i][j] = 0;
}


// ������� �׷������� ������ �����ϴ� �Լ�
void insert_vertex_mat_graph(GraphMatType* g, int v) {
    if ((g->n) >= (MAX_VERTICES - 1)) {
        fprintf(stderr, "������ ������ �ʰ� �Ǿ����ϴ�\n");
        return;
    }
    (g->n)++;// ������ ������ 1���� ��Ų��.
}

// ���� ��� �׷������� ������ �����ϴ� �Լ�
void insert_edge_mat_graph(GraphMatType* g, int start, int end) {
    
    // �Է��� ������ ���� ��ȣ�� ����ȣ�� �߸� �Է��Ѱ�� �׷��� ���� ��ȣ ������ ǥ�����ش�.
    if (g->n <= start || g->n <= end) {
        fprintf(stderr, "�׷��� ������ȣ ����.\n");
        return;
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1; 
}

// ���� ��� �׷����� ���¸� ����ؼ� Ȯ�ν����ִ� �Լ�(���� �����Լ������� ȣ������ ����)
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
// ���� ��ķ� ������ �׷������� DFS�� Ž���ϴ� �Լ� 
void DFS_matrix(GraphMatType* g, int start, int target) {
    int visited[MAX_VERTICES] = { 0 }; // �湮 ���� ����
    Stack s;
    s.top = -1;
    push(&s, start);
    int count = 0; // �湮�� ��� �� ī��Ʈ

    while (!is_empty_stack(&s)) {
        int vertex = pop(&s);

        // �湮���� ���� �����
        if (!visited[vertex]) {
            visited[vertex] = 1; // �湮 ó��
            count++;
            printf("%d ", vertex); // �湮�� ��� ���

            if (vertex == target) {
                printf("\nŽ�� ����: %d\n", target);
                printf("�湮�� ��� ��: %d\n", count);
                return;
            }

            // ���� ��忡�� ������ ��带 ���ÿ� Ǫ��
            for (int i = 0; i < g->n; i++) {
                if (g->adj_mat[vertex][i] == 1 && !visited[i]) {
                    push(&s, i);
                }
            }
        }
        else {
            printf("%d ", vertex); // �̹� �湮�� ��忡�� ��Ʈ�� �� ���
        }
    }
    printf("\nŸ�� %d �߰����� ����.\n", target);
    printf("�湮�� ��� ��: %d\n", count);
}



// ������ķ� ������ �׷����� BFS�� Ž���ϴ� �Լ�
void BFS_matrix(GraphMatType* g, int start, int target) {
    // �迭�� �ʱ�ȭ ���� �湮���θ� �����ϴ� ��
    int visited[MAX_VERTICES] = { 0 };

    // ť�� �ʱ�ȭ ���ְ�, Ž���� ù��° ��带 ť�� �����Ѵ�.
    Queue q;
    q.front = 0;
    q.rear = -1;
    enqueue(&q, start);
    int count = 0; // �湮�� ��� �� ī��Ʈ

    // ť�� ��� ���� ������ ���� ���� 
    while (!is_empty_queue(&q)) {
        int vertex = dequeue(&q); // ť�� ����ִ� ��带 ������.

        // ���� �湮���� ���� ��带 �湮 ó�����ְ� �湮�� ��� ���� ī��Ʈ ���ش�. 
        if (visited[vertex] == 0) {
            visited[vertex] = 1; // �湮 ó��
            count++; // �湮�� ��� �� ����

            printf("%d ", vertex); // �湮�� ��� ���

            // ���� �湮�� ��尡 Ÿ�� ���� ������ Ž�� ����  
            if (vertex == target) {
                printf("\nŽ�� ����: %d\n", target);
                printf("�湮�� ��� ��: %d\n", count);
                return;
            }

            // ���� ���� ���� ��尡 ����Ǿ�����, �湮 ������� Ȯ�����ָ� ť�� ���� Ž�� ������� �����Ѵ�.
            for (int i = 0; i < g->n; i++) {
                if (g->adj_mat[vertex][i] == 1 && !visited[i]) {
                    enqueue(&q, i);
                }
            }
        }
        else {
            // �̹� �湮�� ��忡�� ��Ʈ�� �� ���
            printf("%d ", vertex);
        }
    }
    printf("\nŸ�� %d �߰����� ����.\n", target);
    printf("�湮�� ��� ��: %d\n", count); // �湮�� ��� �� ���
}


//����� �������̽� �޴� �Լ�
void runUserInterface(GraphMatType* root) {
    int c = 0;
    int start_node = 0;
    int target_node = 0;

    for (;;) {
        printf("------------------------------\n");
        printf("1     : ���� �켱 Ž��        |\n");
        printf("2     : �ʺ� �켱 Ž��        |\n");
        printf("3     : ����                  |\n");
        printf("------------------------------\n");

        printf("�޴� �Է�: ");
        scanf_s("%d", &c);

        switch (c) {
        case 1:
            printf("���� ��ȣ�� Ž���� �� �Է�: ");
            scanf_s("%d", &start_node); // ���� ���
            scanf_s("%d", &target_node);// Ž���ҳ�� 
            DFS_matrix(root, start_node, target_node); //���۳���� ���� Ž���� ����� ���� �޾� DFS�� Ž���Ѵ�.
            break;
        case 2:
            printf("���� ��ȣ�� Ž���� �� �Է�: ");
            scanf_s("%d", &start_node); // ���� ���
            scanf_s("%d", &target_node);// Ž���� ��� 
            BFS_matrix(root, start_node, target_node); // ���۳���� ���� Ž���� ����� ���� �޾� BFS�� Ž���Ѵ�.
            break;
        case 3:
            exit(0);
        default:
            printf("�ٽ��Է����ּ���.\n");
        }
    }
}

// ���� Ǫ�� �Լ� 
void push(Stack* s, int value) {
    if (s->top < MAX_VERTICES - 1) {
        s->items[++(s->top)] = value;
    }
}


//���� �� �Լ�
int pop(Stack* s) {
    if (s->top >= 0) {
        return s->items[(s->top)--];
    }
    return -1; 
}
//������ ����ִ��� Ȯ���ϴ� �Լ�
int is_empty_stack(Stack* s) {
    return s->top == -1;
}


// ť�� Ǫ���ϴ� �Լ�
void enqueue(Queue* q, int value) {
    if (q->rear < MAX_VERTICES - 1) {
        q->items[++(q->rear)] = value;
    }
}

// ť�� ���ϴ� �Լ� 
int dequeue(Queue* q) {
    if (q->front <= q->rear) {
        return q->items[(q->front)++];
    }
    return -1; 
}

// ť�� ����ִ��� Ȯ���ϴ� �Լ�
int is_empty_queue(Queue* q) {
    return q->front > q->rear;
}
