#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 1000


int parent[MAX_VERTICES];



// ��� ������ �θ� -1�� �ʱ�ȭ ���ִ� �Լ�
void set_init(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = -1;
    }
}



int set_find(int curr) {
   
    //���� parent[curr]�� -1�̶�� �ش� ���� curr�� ��Ʈ����̴�.
    if (parent[curr] == -1)
        //������ ��ȯ�Ѵ�.
        return curr;

    while (parent[curr] != -1)
        curr = parent[curr];
    
    //parent �迭�� �ε���(����)�� ��ȯ�Ѵ�.
    return curr;
}




void set_union(int a, int b) {
    
 
    int root1 = set_find(a); 
    int root2 = set_find(b);

    //������ ������ �ٸ� ���տ� ���Ѵٸ� �� ������ ��ģ��. 
    if (root1 != root2) // 
        parent[root1] = root2; //parent�迭�� root1�� ������ root2�� �ִ´�.
}


//Edge ����ü�� �׷����� ������ ��Ÿ��
struct Edge {
    int start, end, weight;
};



typedef struct GraphType {
    int n; // ���� �׷����� ����� ������ �� 
    int nvertex; // �׷����� ���� �� 
    struct Edge edges[2 * MAX_VERTICES]; 
} GraphType;


// ��� ������ ��������, ������, ����ġ�� �ʱ�ȭ�Ѵ�.
void graph_init(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < 2 * MAX_VERTICES; i++) {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = 1000;
    }
}


// ���� �߰� �Լ�
void insert_edge(GraphType* g, int start, int end, int w) {
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = w;
    g->n++;
}

//���� ���Լ�
int compare(const void* a, const void* b) {

    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;
    return (x->weight - y->weight);
}



// �ּ����� ��带 �̵���Ű�� ���� ������� ���� �Լ�
void swap(struct Edge* a, struct Edge* b) {
    struct Edge temp = *a;
    *a = *b;
    *b = temp;
}



// �ּ� ���� heapify �Լ�
void heapify(struct Edge heap[], int n, int i) {
    int min = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left].weight < heap[min].weight)
        min = left;
    if (right < n && heap[right].weight < heap[min].weight)
        min = right;

    if (min != i) {
        swap(&heap[i], &heap[min]);
        heapify(heap, n, min);
    }
}

// ������ �迭�� �ּ� ������ ��ȯ�Ͽ� heapify�� ȣ���Ͽ� �ּ� ���� �����.
void min_heap(struct Edge heap[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(heap, n, i);
    }
}

// �ּ����� ��Ʈ��带 ����(��ȯ�ϴ�)�Լ�
struct Edge extract_min(struct Edge heap[], int* n) {
    struct Edge min = heap[0];
    heap[0] = heap[*n - 1];
    (*n)--;
    heapify(heap, *n, 0);
    return min;
}

// �ּ����� �̿��� Kruskal �Լ�
void MinHeapKruskal(GraphType* g) {
    int edge_accepted = 0;
    int uset, vset;
    struct Edge e;

    set_init(g->nvertex); // ���� �ʱ�ȭ
    min_heap(g->edges, g->n); // ������ �ּ� ������ ����

    printf("\nMinheap Based Kruskal\n");
    int heap_size = g->n;
    while (edge_accepted < (g->nvertex - 1) && heap_size > 0) { // ���� ���õ� ������ ���� ���� ������ ����,
                                                                // �ּ� ���� ���� �ִ� ������ ���� ��쿡�� ������ ������.
        e = extract_min(g->edges, &heap_size); // �ּ����� ��Ʈ�� �ִ� ���� ���� ����ġ�� ������ �����ϰ�, Heapfiy ��Ű�� �Լ�
                                               
        //* e�� ������ ���� ����, ������, ����ġ�� �����ϰ� �ִ� ����ü�̴�.*
        
        // ���õ� ������ ���� ������ �������� ������ ã�´�.
        uset = set_find(e.start);
        vset = set_find(e.end); 
        if (uset != vset) {// ������ ��ǥ������ �ٸ��� ������ MST�� ���Խ�Ų��.(����Ŭ�� ������ ���� ����)
            printf("Edge (%d,%d) %d select\n", e.start, e.end, e.weight);
            edge_accepted++;// ���õ� ������ ��
            set_union(uset, vset); //�ΰ��� ������ ��ġ�� �Լ�
        }
    }
}


// quick ��� Kruskal �Լ�
void QuickKruskal(GraphType* g) {
    int edge_accepted = 0; // ���õ� ������ ��
    int uset, vset;
    struct Edge e;

    set_init(g->nvertex); // ���� �ʱ�ȭ
    qsort(g->edges, g->n, sizeof(struct Edge), compare); // ���� ����

    printf("Quick Based Kruskal\n");
    int i = 0;
    while (edge_accepted < (g->nvertex - 1)) { // ���� ���õ� ������ ���� �� ������ ������ ���� �� ���� ����   
        e = g->edges[i]; // ���� �ε����� �ش��ϴ� ������ �����Ͽ� e�� ����
        
        // ���õ� ������ ���� ������ �������� ������ ã�´�.
        uset = set_find(e.start); 
        vset = set_find(e.end);

        // ���� �ٸ� �����̶�� 
        if (uset != vset) {
            printf("Edge (%d,%d) %d select\n", e.start, e.end, e.weight); // ���õ� ������ ������ ���
            edge_accepted++; // ���õ� ������ �� ����
            set_union(uset, vset); // ������ ��ģ��.
        }
        i++;// ���� �������� �̵�
    }
}




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

    g->nvertex = 10; // ������ �� ����
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);
   
    // �׷����� �����ϴ� �Լ�
    GenerateGraph(g);

    QuickKruskal(g); // quick ��� Kruskal
    MinHeapKruskal(g); // minheap ��� Kruskal
    free(g);
    return 0;
}
