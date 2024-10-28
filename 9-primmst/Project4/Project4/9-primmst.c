#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 1000
#define INF 10000

// 힙에서 사용되는 정점 번호와 해당 정점으로의 가중치를 나타내는 구조체
typedef struct {
    int vertex;
    int key;
} Element;

// 최소 힙을 구현하기 위한 구조체로 최대 정점의 수 크기와 힙의 현재 크기를 저장 
typedef struct {
    Element heap[MAX_VERTICES];
    int size;
} MinHeap;


// 그래프의 간선 정보를 저장하는 구조체
struct Edge {
    int start, end, weight;
};


// 그래프를 표현하는 구조체로 정점수, 간선수, 간선목록, 인접행렬을 포함한다.
typedef struct GraphType {
    int n;
    int nvertex;
    struct Edge edges[2 * MAX_VERTICES];
    int adj[MAX_VERTICES][MAX_VERTICES]; 
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];
int parent[MAX_VERTICES];

// 힙을 초기화 시켜주는 함수
void init_heap(MinHeap* h) {
    h->size = 0;
}

// 최소힙을 삽입하는 함수
void insert_heap(MinHeap* h, int vertex, int key) {
    int i = ++(h->size);
    while ((i != 1) && (key < h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i].vertex = vertex;
    h->heap[i].key = key;
}

// 최소힙을 삭제하는 함수
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

// 그래프를 초기화 하는 함수
void graph_init(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->adj[i][j] = INF; //인접행렬
        }
    }
}

// 두 정점의 가중치를 설정하여 간선을 삽입하는 함수
void insert_edge(GraphType* g, int start, int end, int weight) {
    g->adj[start][end] = weight;
    g->adj[end][start] = weight; 
}


// 프라임 알고리즘 함수 
void prim_heap(GraphType* g, int s) {

    printf("Prim MST Algorithm :\n");
    MinHeap h;
    init_heap(&h); // 최소힙을 초기화시켜준다.

    for (int i = 0; i < g->nvertex; i++) {
        distance[i] = INF; // 각 정점에 대한 초기 가중치를 무한대로 배열에다가 설정
        selected[i] = FALSE; // 정점이 MST에 포함되었는지 여부를 나타내는 배열 
        parent[i] = -1; // 각 정점의 부모를 나타내는 배열, (초기상태에서는 부모가 없도록 -1을 설정해준다.)
    }
    distance[s] = 0; // 시작정점을 0으로 설정해준다.
    insert_heap(&h, s, 0); // 시작정점을 가중치 0으로 최소힙에대가 삽입해준다.

    while (h.size > 0) { // 힙에 요소가 남아 있는동안 반복 
        Element min_vertex = delete_heap(&h); // 최소힙의 루트를 삭제하면서 최소 가중치를 가진 정점으로 표시해준다.
        int u = min_vertex.vertex; // 삭제된 정점의 번호를 u에 저장한다.
       
        if (selected[u] == TRUE) {
            continue; // 삭제된 정점의 번호가 MST에 포함된 정점이면 건너뛴다.
        }
        else {
            selected[u] = TRUE; // MST에 포함이 안 된 정점이면 포함시킨다.
        }

        printf("정점 %d 추가\n", u);  // MST에 추가된 정점을 출력한다.


        // 인접 정점을 업데이트 해주는 곳
        for (int v = 0; v < g->nvertex; v++) {// 모든 인접 정점에 대하여 반복해준다.
            
            // *조건*
            // 1.정점과 간선이 연결되어 있는지 확인하고 
            // 2.selected가 아직 MST에 포함되지 않고, 
            // 3.현재 간선의 가중치가 정점 v로의 기존 가중치보다 작다면  
            if (g->adj[u][v] != INF && selected[v]==FALSE && g->adj[u][v] < distance[v]) {  
                
                distance[v] = g->adj[u][v]; // 정점 v의 가중치를 업데이트 해준다.
                parent[v] = u; // v의 부모를 u로 설정하여 MST 연결관계를 기록해준다.
                insert_heap(&h, v, distance[v]); // 업데이트된 가중치를 힙에 삽입하여 최소 가중치 정점 탐색을 준비한다.
            }
        }
    }
}


void FindPrimMST(GraphType* g) {
    prim_heap(g, 1);  //prim 알고리즘을 호출하여 MST를 찾는다.
}

//두정점의 간선을 이어 가중치를 나타내는 그래프를 만드는 함수
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
