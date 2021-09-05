#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define NODE_MAX 1001
#define EDGE_MAX 200001 // ����� �����̹Ƿ� 200,000��

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
int d[NODE_MAX];

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

int main(void) {
	// ������ ������ ����
	int n, m;
	scanf("%d %d", &n, &m);

	// ��������Ʈ ���� �� �ʱ�ȭ
	adj = (Node**)malloc(sizeof(Node*) * (n + 1));
	for (int i = 1; i <= n; i++) adj[i] = NULL;

	// �켱����ť ���� �� �ʱ�ȭ
	PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
	pq->count = 0;

	// ���Ḯ��Ʈ �ʱ�ȭ
	for (int i = 0; i < m; i++) {
		// a �������� b ���� ���� ����� c
		// b �������� a ���� ���� ����� c
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);

		Edge* edge1 = (Edge*)malloc(sizeof(Edge));
		edge1->node = b;
		edge1->cost = c;
		addNode(adj, a, edge1);

		Edge* edge2 = (Edge*)malloc(sizeof(Edge));
		edge2->node = a;
		edge2->cost = c;
		addNode(adj, b, edge2);
	}

	// ���� �˰��� ����
	long long res = 0;
	Edge* start = (Edge*)malloc(sizeof(Edge));
	start->cost = 0;
	start->node = 1;
	push(pq, start);
	
	for (int i = 1; i <= n; i++) {
		int nextNode = -1;
		int nextCost = INT_MAX;

		while (1) {
			Edge* now = pop(pq);

			if (now == NULL) break;

			nextNode = now->node;

			// �ش� ������ ������� �ʾ��� �� break
			if (!d[nextNode]) {
				nextCost = now->cost;
				break;
			}
		}

		// ���� ������ ã�� ���ߴٸ� ���� �׷����� �ƴ�.
		if (nextCost == INT_MAX) printf("���� �׷����� �ƴ�. \n");

		// �ش� ���� ��� ����
		res += nextCost;
		// �ش� ���� ���� ǥ��
		d[nextNode] = 1;

		// ���� ������ ����� ������ ��� �켱����ť�� ����
		Node* cur = adj[nextNode];
		while (cur != NULL) {
			push(pq, cur->data);
			cur = cur->next;
		}
	}

	printf("%lld\n", res);
	system("pause");
	return 0;
}