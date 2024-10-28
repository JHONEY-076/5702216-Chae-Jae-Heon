#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 1000
#define INF 10000

// ������ ���Ǵ� ���� ��ȣ�� �ش� ���������� ����ġ�� ��Ÿ���� ����ü
typedef struct {
    int vertex;
    int key;
} Element;

// �ּ� ���� �����ϱ� ���� ����ü�� �ִ� ������ �� ũ��� ���� ���� ũ�⸦ ���� 
typedef struct {
    Element heap[MAX_VERTICES];
    int size;
} MinHeap;


// �׷����� ���� ������ �����ϴ� ����ü
struct Edge {
    int start, end, weight;
};


// �׷����� ǥ���ϴ� ����ü�� ������, ������, �������, ��������� �����Ѵ�.
typedef struct GraphType {
    int n;
    int nvertex;
    struct Edge edges[2 * MAX_VERTICES];
    int adj[MAX_VERTICES][MAX_VERTICES]; 
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];
int parent[MAX_VERTICES];

// ���� �ʱ�ȭ �����ִ� �Լ�
void init_heap(MinHeap* h) {
    h->size = 0;
}

// �ּ����� �����ϴ� �Լ�
void insert_heap(MinHeap* h, int vertex, int key) {
    int i = ++(h->size);
    while ((i != 1) && (key < h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i].vertex = vertex;
    h->heap[i].key = key;
}

// �ּ����� �����ϴ� �Լ�
Element delete_heap(MinHeap* h) {
    int parent = 1, child = 2;
    Element item, temp;
    item = h->heap[1];
    temp = h->heap[(h->size)--];

    while (child <= h->size) {
        if ((child < h->size) && (h->heap[child].key > h->heap[child + 1].key)) {
            child++;
        }
        if (temp.key <= h->heap[child].key) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

// �׷����� �ʱ�ȭ �ϴ� �Լ�
void graph_init(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->adj[i][j] = INF; //�������
        }
    }
}

// �� ������ ����ġ�� �����Ͽ� ������ �����ϴ� �Լ�
void insert_edge(GraphType* g, int start, int end, int weight) {
    g->adj[start][end] = weight;
    g->adj[end][start] = weight; 
}


// ������ �˰��� �Լ� 
void prim_heap(GraphType* g, int s) {

    printf("Prim MST Algorithm :\n");
    MinHeap h;
    init_heap(&h); // �ּ����� �ʱ�ȭ�����ش�.

    for (int i = 0; i < g->nvertex; i++) {
        distance[i] = INF; // �� ������ ���� �ʱ� ����ġ�� ���Ѵ�� �迭���ٰ� ����
        selected[i] = FALSE; // ������ MST�� ���ԵǾ����� ���θ� ��Ÿ���� �迭 
        parent[i] = -1; // �� ������ �θ� ��Ÿ���� �迭, (�ʱ���¿����� �θ� ������ -1�� �������ش�.)
    }
    distance[s] = 0; // ���������� 0���� �������ش�.
    insert_heap(&h, s, 0); // ���������� ����ġ 0���� �ּ������밡 �������ش�.

    while (h.size > 0) { // ���� ��Ұ� ���� �ִµ��� �ݺ� 
        Element min_vertex = delete_heap(&h); // �ּ����� ��Ʈ�� �����ϸ鼭 �ּ� ����ġ�� ���� �������� ǥ�����ش�.
        int u = min_vertex.vertex; // ������ ������ ��ȣ�� u�� �����Ѵ�.
       
        if (selected[u] == TRUE) {
            continue; // ������ ������ ��ȣ�� MST�� ���Ե� �����̸� �ǳʶڴ�.
        }
        else {
            selected[u] = TRUE; // MST�� ������ �� �� �����̸� ���Խ�Ų��.
        }

        printf("���� %d �߰�\n", u);  // MST�� �߰��� ������ ����Ѵ�.


        // ���� ������ ������Ʈ ���ִ� ��
        for (int v = 0; v < g->nvertex; v++) {// ��� ���� ������ ���Ͽ� �ݺ����ش�.
            
            // *����*
            // 1.������ ������ ����Ǿ� �ִ��� Ȯ���ϰ� 
            // 2.selected�� ���� MST�� ���Ե��� �ʰ�, 
            // 3.���� ������ ����ġ�� ���� v���� ���� ����ġ���� �۴ٸ�  
            if (g->adj[u][v] != INF && selected[v]==FALSE && g->adj[u][v] < distance[v]) {  
                
                distance[v] = g->adj[u][v]; // ���� v�� ����ġ�� ������Ʈ ���ش�.
                parent[v] = u; // v�� �θ� u�� �����Ͽ� MST ������踦 ������ش�.
                insert_heap(&h, v, distance[v]); // ������Ʈ�� ����ġ�� ���� �����Ͽ� �ּ� ����ġ ���� Ž���� �غ��Ѵ�.
            }
        }
    }
}


void FindPrimMST(GraphType* g) {
    prim_heap(g, 1);  //prim �˰����� ȣ���Ͽ� MST�� ã�´�.
}

//�������� ������ �̾� ����ġ�� ��Ÿ���� �׷����� ����� �Լ�
void GenerateGraph(GraphType* g) {
    insert_edge(g, 1, 2, 3);
    insert_edge(g, 1, 7, 12);
    insert_edge(g, 1, 6, 11);
    insert_edge(g, 2, 3, 5);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 2, 7, 8);
    insert_edge(g, 2, 6, 7);
    insert_edge(g, 3, 4, 2);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 3, 8, 5);
    insert_edge(g, 4, 5, 13);
    insert_edge(g, 4, 10, 16);
    insert_edge(g, 4, 8, 14);
    insert_edge(g, 5, 6, 9);
    insert_edge(g, 5, 10, 17);
    insert_edge(g, 5, 9, 18);
    insert_edge(g, 7, 8, 13);
    insert_edge(g, 8, 10, 15);
    insert_edge(g, 9, 10, 10);
    g->nvertex = 11;  
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    GenerateGraph(g);

    FindPrimMST(g);

    free(g);
    return 0;
}
