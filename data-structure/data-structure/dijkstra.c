#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define NODE_MAX 2001
#define EDGE_MAX 600001 // 양방향 간선이므로 600,000개

typedef struct {
	int cost;
	int node;
} Edge;

void swap(Edge* a, Edge* b) {
	Edge tmp;
	tmp.cost = a->cost;
	tmp.node = a->node;
	a->cost = b->cost;
	a->node = b->node;
	b->cost = tmp.cost;
	b->node = tmp.node;
}

typedef struct {
	Edge* heap[EDGE_MAX];
	int count;
} PriorityQueue;

void push(PriorityQueue* pq, Edge* edge) {
	if (pq->count >= EDGE_MAX) return;

	pq->heap[pq->count] = edge;
	int now = pq->count;
	int parent = (now - 1) / 2;

	// 새 원소를 삽입후 상향식으로 힙 구성
	// cost가 낮은 edge가 위로 올수 있도록
	while (now > 0 && pq->heap[now]->cost < pq->heap[parent]->cost) {
		swap(pq->heap[now], pq->heap[parent]);
		now = parent;
		parent = (now - 1) / 2;
	}

	pq->count++;
}

Edge* pop(PriorityQueue* pq) {
	if (pq->count <= 0) return NULL;

	Edge* res = pq->heap[0];
	pq->count--;
	pq->heap[0] = pq->heap[pq->count];
	
	int now = 0;
	int leftChild = 1;
	int rightChild = 2;
	int target = now;

	// 하향식으로 힙 구성
	while (leftChild < pq->count) {
		if (pq->heap[target]->cost > pq->heap[leftChild]->cost) target = leftChild;

		if (rightChild < pq->count && pq->heap[target]->cost > pq->heap[rightChild]->cost) target = rightChild;

		if (target == now) break;

		swap(pq->heap[now], pq->heap[target]);
		now = target;
		leftChild = now * 2 + 1;
		rightChild = now * 2 + 2;
	}

	return res;
}

typedef struct Node {
	Edge* data;
	struct Node* next;
} Node;

Node** adj;
int ans[NODE_MAX];

void addNode(Node** target, int index, Edge* edge) {
	if (target[index] == NULL) {
		target[index] = (Node*)malloc(sizeof(Node));
		target[index]->data = edge;
		target[index]->next = NULL;
	}
	else {
		Node* node = (Node*)malloc(sizeof(Node));
		node->data = edge;
		node->next = target[index];
		target[index] = node;
	}
}

Edge* makeEdge(int node, int cost) {
	Edge *edge = (Edge*)malloc(sizeof(Edge));
	edge->node = node;
	edge->cost = cost;

	return edge;
}

int main(void) {
	// 정점, 간선 개수와 시작 정점
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);

	// 인접리스트 초기화, 정답 배열 초기화
	adj = (Node**)malloc(sizeof(Node*) * (n + 1));
	for (int i = 1; i <= n; i++) {
		adj[i] = NULL;
		ans[i] = INT_MAX;
	}

	// 우선순위큐 선언 및 초기화
	PriorityQueue *pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
	pq->count = 0;

	// 인접리스트 입력
	for (int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);

		addNode(adj, a, makeEdge(b, c));
	}

	// 다익스트라 시작
	ans[k] = 0;
	push(pq, makeEdge(k, 0));

	while (1) {
		Edge* now = pop(pq);

		if (now == NULL) break;

		int curNode = now->node; // 현재 노드
		int curCost = now->cost; // 비용
		free(now);

		// 현재 노드까지 가는 비용이 갱신된 비용보다 크다면 넘어감
		if (curCost > ans[curNode]) continue;

		// 현재 노드까지 가는 비용이 더 작거나 같다면 
		// 현재 노드랑 인접한 노드들의 엣지들도 모두 순회하며 갱신해주기
		Node* cur = adj[curNode];

		while (cur != NULL) {
			Edge* tmp = cur->data;
			int nextNode = tmp->node;
			int nextCost = curCost + tmp->cost;

			// 현재 노드를 거쳐서 가는 비용이 갱신된 비용보다 작다면 새로 갱신
			if (nextCost < ans[nextNode]) {
				ans[nextNode] = nextCost; // 갱신
				push(pq, makeEdge(nextNode, nextCost)); // 우선순위큐에 담기
			}

			cur = cur->next;
		}
	}

	for (int i = 1; i <= n; i++) {
		if (ans[i] == INT_MAX) printf("INF\n");
		else printf("%d\n", ans[i]);
	}

	system("pause");
	return 0;
}