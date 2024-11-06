#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define INF 100

// 그래프 간선을 나타내는 구조체
typedef struct EdgeNode {
    int vertex;
    int weight;
    struct EdgeNode* next;
} EdgeNode;

// 각 정점의 인접리스트를 관리하는 구조체
typedef struct VertexNode {
    EdgeNode* head; 
} VertexNode;

// 그래프 전체 관리 구조체
typedef struct GraphType {
    int nvertex; // 총 정점의 수
    VertexNode adjList[MAX_VERTICES]; //  각 정점의 인접 리스트를 저장하는 배열
} GraphType;


// 최소 힙의 요소를 나타내는 구조체
typedef struct {
    int vertex;
    int key;
} Element;

//최소힙을 구현하기 위한 구조체
typedef struct {
    Element heap[MAX_VERTICES];
    int size;
} MinHeap;

int distance[MAX_VERTICES];
int found[MAX_VERTICES];
int foundOrder[MAX_VERTICES];
int orderIndex = 0;


// 힙을 초기화하는 함수
void init_heap(MinHeap* h) {
    h->size = 0;
}


// 최소힙에 새 요소를 삽입하는 함수 
void insert_heap(MinHeap* h, int v, int key) {
    int i = ++(h->size);
    while ((i != 1) && (key < h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i].vertex = v;
    h->heap[i].key = key;
}

//힙의 루트 노드를 제거하는 함수(최소힙 삭제)
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


// 그래프를 초기화 시켜주는 함수
void graph_init(GraphType* g, int totalVertex) {
    g->nvertex = totalVertex;
    for (int i = 0; i < totalVertex; i++) {
        g->adjList[i].head = NULL;
    }
}

// 그래프의 간선을 추가해주는 함수
void insert_edge(GraphType* g, int start, int end, int weight) {
    EdgeNode* new_Node = (EdgeNode*)malloc(sizeof(EdgeNode));
    new_Node->vertex = end;
    new_Node->weight = weight;
    new_Node->next = g->adjList[start].head;
    g->adjList[start].head = new_Node;
}

// 현재 distance 배열의 상태를 출력해주는 함수
void print_Distance(int n) {
    printf("Distance: ");
    for (int i = 1; i < n; i++) {
        if (distance[i] == INF) printf("* ");
        else printf("%d ", distance[i]);
    }
}

// 현재 Found 배열의 상태를 출력해주는 함수 
void print_Found(int n) {
    printf("\nFound:    ");
    for (int i = 1; i < n; i++) {
        printf("%d ", found[i]);
    }
    printf("\n\n");


}

//다익스트라 알고리즘을 사용해 주어진 시작 정점에서 다른 정점까지의 최단거리를 찾는 함수
void dijkstra(GraphType* g, int start) {

    //최소힙 초기화하는 부분
    MinHeap heap;
    init_heap(&heap);

    // distance를 무한대로 초기화하고 found 배열을 false로 나타내 방문하지 않았음을 나타냄
    for (int i = 0; i < g->nvertex; i++) {
        distance[i] = INF;
        found[i] = 0;
    }
    // 시작 정점의 거리를 0으로 설정
    distance[start] = 0;
    // 최소힙에 삽입하여 최단 경로 탐색의 시작점으로 사용한다.
    insert_heap(&heap, start, 0);

    
    // 힙이 빌때까지 루프를 반복한다.
    while (heap.size > 0) {
        Element u = delete_heap(&heap); // 최소힙에서 루트노드 추출(삭제)
       
        // 이미 방문한 노드는 건너뛰고 방문하지 않은 정점을 표시해준다.
        if (found[u.vertex]==1) continue;
        found[u.vertex] = 1;
        
        //현재 distance와 found배열의 상태를 출력해주는곳
        foundOrder[orderIndex++] = u.vertex;
        print_Distance(g->nvertex);
        print_Found(g->nvertex);


        // 인접 정점의 거리를 갱신시켜주는 곳!! 
        EdgeNode* currNode = g->adjList[u.vertex].head;
        while (currNode != NULL) {
            int v = currNode->vertex;
            int weight = currNode->weight;

            // 만약 새 경로가 기존 distance[v]보다 짧으면 distance[v]를 갱신하고 v를 힙에 삽입해준다.
            if (!found[v] && distance[u.vertex] + weight < distance[v]) {
                distance[v] = distance[u.vertex] + weight;
                insert_heap(&heap, v, distance[v]);
            }
            currNode = currNode->next;
        }
    }

    // 방문 순서 출력
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
