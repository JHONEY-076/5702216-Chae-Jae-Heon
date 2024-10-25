#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 1000


int parent[MAX_VERTICES];



// 모든 정점의 부모를 -1로 초기화 해주는 함수
void set_init(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = -1;
    }
}



int set_find(int curr) {
   
    //만약 parent[curr]가 -1이라면 해당 정점 curr는 루트노드이다.
    if (parent[curr] == -1)
        //정점을 반환한다.
        return curr;

    while (parent[curr] != -1)
        curr = parent[curr];
    
    //parent 배열의 인덱스(정점)을 반환한다.
    return curr;
}




void set_union(int a, int b) {
    
 
    int root1 = set_find(a); 
    int root2 = set_find(b);

    //집합의 정점이 다른 집합에 속한다면 두 집합을 합친다. 
    if (root1 != root2) // 
        parent[root1] = root2; //parent배열의 root1의 정점에 root2를 넣는다.
}


//Edge 구조체는 그래프의 간선을 나타냄
struct Edge {
    int start, end, weight;
};



typedef struct GraphType {
    int n; // 현재 그래프에 저장된 간선의 수 
    int nvertex; // 그래프의 정점 수 
    struct Edge edges[2 * MAX_VERTICES]; 
} GraphType;


// 모든 간선의 시작정점, 끝정점, 가중치를 초기화한다.
void graph_init(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < 2 * MAX_VERTICES; i++) {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = 1000;
    }
}


// 간선 추가 함수
void insert_edge(GraphType* g, int start, int end, int w) {
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = w;
    g->n++;
}

//간선 비교함수
int compare(const void* a, const void* b) {

    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;
    return (x->weight - y->weight);
}



// 최소힙의 노드를 이동시키기 위해 만들어진 스왑 함수
void swap(struct Edge* a, struct Edge* b) {
    struct Edge temp = *a;
    *a = *b;
    *b = temp;
}



// 최소 힙의 heapify 함수
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

// 주저진 배열을 최소 힙으로 변환하여 heapify를 호출하여 최소 힙을 만든다.
void min_heap(struct Edge heap[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(heap, n, i);
    }
}

// 최소힙의 루트노드를 삭제(반환하는)함수
struct Edge extract_min(struct Edge heap[], int* n) {
    struct Edge min = heap[0];
    heap[0] = heap[*n - 1];
    (*n)--;
    heapify(heap, *n, 0);
    return min;
}

// 최소힙을 이용한 Kruskal 함수
void MinHeapKruskal(GraphType* g) {
    int edge_accepted = 0;
    int uset, vset;
    struct Edge e;

    set_init(g->nvertex); // 집합 초기화
    min_heap(g->edges, g->n); // 간선을 최소 힙으로 정렬

    printf("\nMinheap Based Kruskal\n");
    int heap_size = g->n;
    while (edge_accepted < (g->nvertex - 1) && heap_size > 0) { // 현재 선택된 간선의 수가 간선 수보다 적고,
                                                                // 최소 힙에 남아 있는 간선이 있을 경우에만 루프를 진행함.
        e = extract_min(g->edges, &heap_size); // 최소힙의 루트에 있는 가장 작은 가중치의 간선을 삭제하고, Heapfiy 시키는 함수
                                               
        //* e는 간선의 시작 정점, 끝정점, 가중치를 포함하고 있는 구조체이다.*
        
        // 선택된 간선의 시작 정점과 끝정점의 집합을 찾는다.
        uset = set_find(e.start);
        vset = set_find(e.end); 
        if (uset != vset) {// 정점의 대표노드들이 다르면 갼션을 MST에 포함시킨다.(사이클이 생기지 않을 조건)
            printf("Edge (%d,%d) %d select\n", e.start, e.end, e.weight);
            edge_accepted++;// 선택된 간선의 수
            set_union(uset, vset); //두개의 집합을 합치는 함수
        }
    }
}


// quick 기반 Kruskal 함수
void QuickKruskal(GraphType* g) {
    int edge_accepted = 0; // 선택된 간선의 수
    int uset, vset;
    struct Edge e;

    set_init(g->nvertex); // 집합 초기화
    qsort(g->edges, g->n, sizeof(struct Edge), compare); // 간선 정렬

    printf("Quick Based Kruskal\n");
    int i = 0;
    while (edge_accepted < (g->nvertex - 1)) { // 현재 선택된 간선의 수가 총 간선의 수보다 적을 때 까지 진행   
        e = g->edges[i]; // 현재 인덱스에 해당하는 간선을 선택하여 e에 저장
        
        // 선택된 간선의 시작 정점과 끝정점의 집합을 찾는다.
        uset = set_find(e.start); 
        vset = set_find(e.end);

        // 서로 다른 집합이라면 
        if (uset != vset) {
            printf("Edge (%d,%d) %d select\n", e.start, e.end, e.weight); // 선택된 간선의 정보가 출력
            edge_accepted++; // 선택된 간선의 수 증가
            set_union(uset, vset); // 집합을 합친다.
        }
        i++;// 다음 간선으로 이동
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

    g->nvertex = 10; // 정점의 수 설정
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);
   
    // 그래프를 생성하는 함수
    GenerateGraph(g);

    QuickKruskal(g); // quick 기반 Kruskal
    MinHeapKruskal(g); // minheap 기반 Kruskal
    free(g);
    return 0;
}
