#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define NODE_MAX 2001
#define EDGE_MAX 600001 // ����� �����̹Ƿ� 600,000��

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

	// �� ���Ҹ� ������ ��������� �� ����
	// cost�� ���� edge�� ���� �ü� �ֵ���
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

	// ��������� �� ����
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
	// ����, ���� ������ ���� ����
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);

	// ��������Ʈ �ʱ�ȭ, ���� �迭 �ʱ�ȭ
	adj = (Node**)malloc(sizeof(Node*) * (n + 1));
	for (int i = 1; i <= n; i++) {
		adj[i] = NULL;
		ans[i] = INT_MAX;
	}

	// �켱����ť ���� �� �ʱ�ȭ
	PriorityQueue *pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
	pq->count = 0;

	// ��������Ʈ �Է�
	for (int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);

		addNode(adj, a, makeEdge(b, c));
	}

	// ���ͽ�Ʈ�� ����
	ans[k] = 0;
	push(pq, makeEdge(k, 0));

	while (1) {
		Edge* now = pop(pq);

		if (now == NULL) break;

		int curNode = now->node; // ���� ���
		int curCost = now->cost; // ���
		free(now);

		// ���� ������ ���� ����� ���ŵ� ��뺸�� ũ�ٸ� �Ѿ
		if (curCost > ans[curNode]) continue;

		// ���� ������ ���� ����� �� �۰ų� ���ٸ� 
		// ���� ���� ������ ������ �����鵵 ��� ��ȸ�ϸ� �������ֱ�
		Node* cur = adj[curNode];

		while (cur != NULL) {
			Edge* tmp = cur->data;
			int nextNode = tmp->node;
			int nextCost = curCost + tmp->cost;

			// ���� ��带 ���ļ� ���� ����� ���ŵ� ��뺸�� �۴ٸ� ���� ����
			if (nextCost < ans[nextNode]) {
				ans[nextNode] = nextCost; // ����
				push(pq, makeEdge(nextNode, nextCost)); // �켱����ť�� ���
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