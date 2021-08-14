#include <cstdio>
#include <algorithm>

int C, N;
int preorder[100], inorder[100];
int inorderPos[1001], rootPos;

void postOrder(int start, int end) {
	if (start > end) return;

	int root = preorder[rootPos++];
	int pos = inorderPos[root];

	postOrder(start, pos-1);
	postOrder(pos + 1, end);
	printf("%d ", root);
}

int main() {
	scanf("%d", &C);
	while (C--) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) scanf("%d", preorder + i);
		for (int i = 0; i < N; i++) {
			scanf("%d", inorder + i);
			inorderPos[inorder[i]] = i;
		}
		rootPos = 0;

		postOrder(0, N - 1);
		puts("");

	}
}