#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_SIZE 10000

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

typedef struct {
	int heap[MAX_SIZE];
	int count;
} PriorityQueue;

void push(PriorityQueue* pq, int data) {
	if (pq->count >= MAX_SIZE) return;

	// 새원소 삽입
	pq->heap[pq->count] = data;

	int now = pq->count;
	int parent = (now - 1) / 2;

	// 새원소 삽입후 상향식으로 힙 구성
	while (now > 0 && pq->heap[now] > pq->heap[parent]) {
		swap(&pq->heap[now], &pq->heap[parent]);
		now = parent;
		parent = (now - 1) / 2;
	}
	pq->count++;
}

int pop(PriorityQueue* pq) {
	if (pq->count <= 0) return -9999;

	int res = pq->heap[0];
	pq->count--;
	pq->heap[0] = pq->heap[pq->count];

	int now = 0;
	int leftChild = 1;
	int rightChild = 2;
	int target = now;

	// 새원소 추출후 하향식으로 힙 구성
	while (leftChild < pq->count) {
		// 왼쪽 자식이 클 때
		if (pq->heap[target] < pq->heap[leftChild]) target = leftChild;

		// 오른쪽 자식이 클 때
		if (rightChild < pq->count && pq->heap[target] < pq->heap[rightChild]) target = rightChild;

		// 더 이상 내려가지 않아도 될 때 종료
		if (target == now) break;

		swap(&pq->heap[now], &pq->heap[target]);
		now = target;
		leftChild = now * 2 + 1;
		rightChild = now * 2 + 2;
	}

	return res;
}

int main(void) {
	int n, data;
	scanf("%d", &n);

	PriorityQueue pq;
	pq.count = 0;

	for (int i = 0; i < n; i++) {
		scanf("%d", &data);
		push(&pq, data);
	}

	for (int i = 0; i < n; i++) {
		data = pop(&pq);
		printf("%d ", data);
	}

	system("pause");
	return 0;
}