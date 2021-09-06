#include <stdio.h>
#define NUMBER 8

int tree[NUMBER];

void update(int i, int diff) {
	while (i <= NUMBER) {
		tree[i] += diff;
		i += (i & -i);
	}
}

int psum(int i) {
	int ans = 0;

	while (i > 0) {
		ans += tree[i];
		i -= (i & -i);
	}

	return ans;
}

int getSection(int start, int end) {
	return psum(end) - psum(start - 1);
}

int main(void) {
	update(1, 7);
	update(2, 1);
	update(3, 9);
	update(4, 5);
	update(5, 6);
	update(6, 4);
	update(7, 1);

	for (int i = 1; i <= NUMBER; i++) {
		printf("%d\n", tree[i]);
	}

	printf("\n");

	printf("1���� 7������ ���� ��: %d\n", getSection(1, 7));

	printf("�ε��� 6�� ���Ҹ� +3��ŭ ����\n");
	update(6, 3);

	printf("4���� 7������ ���� ��: %d\n", getSection(4, 7));
	system("pause");
	return 0;
}