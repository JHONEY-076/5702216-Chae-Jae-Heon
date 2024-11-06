#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define INF 100

// �׷��� ������ ��Ÿ���� ����ü
typedef struct EdgeNode {
    int vertex;
    int weight;
    struct EdgeNode* next;
} EdgeNode;

// �� ������ ��������Ʈ�� �����ϴ� ����ü
typedef struct VertexNode {
    EdgeNode* head; 
} VertexNode;

// �׷��� ��ü ���� ����ü
typedef struct GraphType {
    int nvertex; // �� ������ ��
    VertexNode adjList[MAX_VERTICES]; //  �� ������ ���� ����Ʈ�� �����ϴ� �迭
} GraphType;


// �ּ� ���� ��Ҹ� ��Ÿ���� ����ü
typedef struct {
    int vertex;
    int key;
} Element;

//�ּ����� �����ϱ� ���� ����ü
typedef struct {
    Element heap[MAX_VERTICES];
    int size;
} MinHeap;

int distance[MAX_VERTICES];
int found[MAX_VERTICES];
int foundOrder[MAX_VERTICES];
int orderIndex = 0;


// ���� �ʱ�ȭ�ϴ� �Լ�
void init_heap(MinHeap* h) {
    h->size = 0;
}


// �ּ����� �� ��Ҹ� �����ϴ� �Լ� 
void insert_heap(MinHeap* h, int v, int key) {
    int i = ++(h->size);
    while ((i != 1) && (key < h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i].vertex = v;
    h->heap[i].key = key;
}

//���� ��Ʈ ��带 �����ϴ� �Լ�(�ּ��� ����)
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


// �׷����� �ʱ�ȭ �����ִ� �Լ�
void graph_init(GraphType* g, int totalVertex) {
    g->nvertex = totalVertex;
    for (int i = 0; i < totalVertex; i++) {
        g->adjList[i].head = NULL;
    }
}

// �׷����� ������ �߰����ִ� �Լ�
void insert_edge(GraphType* g, int start, int end, int weight) {
    EdgeNode* new_Node = (EdgeNode*)malloc(sizeof(EdgeNode));
    new_Node->vertex = end;
    new_Node->weight = weight;
    new_Node->next = g->adjList[start].head;
    g->adjList[start].head = new_Node;
}

// ���� distance �迭�� ���¸� ������ִ� �Լ�
void print_Distance(int n) {
    printf("Distance: ");
    for (int i = 1; i < n; i++) {
        if (distance[i] == INF) printf("* ");
        else printf("%d ", distance[i]);
    }
}

// ���� Found �迭�� ���¸� ������ִ� �Լ� 
void print_Found(int n) {
    printf("\nFound:    ");
    for (int i = 1; i < n; i++) {
        printf("%d ", found[i]);
    }
    printf("\n\n");


}

//���ͽ�Ʈ�� �˰����� ����� �־��� ���� �������� �ٸ� ���������� �ִܰŸ��� ã�� �Լ�
void dijkstra(GraphType* g, int start) {

    //�ּ��� �ʱ�ȭ�ϴ� �κ�
    MinHeap heap;
    init_heap(&heap);

    // distance�� ���Ѵ�� �ʱ�ȭ�ϰ� found �迭�� false�� ��Ÿ�� �湮���� �ʾ����� ��Ÿ��
    for (int i = 0; i < g->nvertex; i++) {
        distance[i] = INF;
        found[i] = 0;
    }
    // ���� ������ �Ÿ��� 0���� ����
    distance[start] = 0;
    // �ּ����� �����Ͽ� �ִ� ��� Ž���� ���������� ����Ѵ�.
    insert_heap(&heap, start, 0);

    
    // ���� �������� ������ �ݺ��Ѵ�.
    while (heap.size > 0) {
        Element u = delete_heap(&heap); // �ּ������� ��Ʈ��� ����(����)
       
        // �̹� �湮�� ���� �ǳʶٰ� �湮���� ���� ������ ǥ�����ش�.
        if (found[u.vertex]==1) continue;
        found[u.vertex] = 1;
        
        //���� distance�� found�迭�� ���¸� ������ִ°�
        foundOrder[orderIndex++] = u.vertex;
        print_Distance(g->nvertex);
        print_Found(g->nvertex);


        // ���� ������ �Ÿ��� ���Ž����ִ� ��!! 
        EdgeNode* currNode = g->adjList[u.vertex].head;
        while (currNode != NULL) {
            int v = currNode->vertex;
            int weight = currNode->weight;

            // ���� �� ��ΰ� ���� distance[v]���� ª���� distance[v]�� �����ϰ� v�� ���� �������ش�.
            if (!found[v] && distance[u.vertex] + weight < distance[v]) {
                distance[v] = distance[u.vertex] + weight;
                insert_heap(&heap, v, distance[v]);
            }
            currNode = currNode->next;
        }
    }

    // �湮 ���� ���
    printf("Found Order: ");
    for (int i = 0; i < orderIndex; i++) {
        printf("%d ", foundOrder[i]);
    }
    printf("\n");
}




// 
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
}

int main(void) {
    GraphType g;
    graph_init(&g, 11);

    GenerateGraph(&g);

   
    dijkstra(&g, 1);

    return 0;
}
