#include <stdio.h>
#include <stdlib.h>
#define INF 999999

typedef struct {
	int data;
	struct Node *next;
} Node;

typedef struct {
	Node* top;
} Stack;

void push(Stack* stack, int data) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->next = stack->top;
	stack->top = node;
}

void pop(Stack* stack) {
	if (stack->top == NULL) {
		return INF;
	}

	Node* node = stack->top;
	int data = node->data;
	stack->top = node->next;
	free(node);
	return data;
}

void show(Stack* stack) {
	Node* cur = stack->top;
	while (cur != NULL) {
		printf("%d ", cur->data);
		cur = cur->next;
	}
}

int main(void) {
	Stack stack;
	stack.top = NULL;
	
	push(&stack, 7);
	push(&stack, 5);
	push(&stack, 4);
	pop(&stack);
	show(&stack);
	system("pause");
	return 0;
}