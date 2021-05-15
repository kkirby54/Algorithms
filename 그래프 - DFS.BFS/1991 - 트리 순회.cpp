#include <cstdio>
#include <algorithm>
#include <vector>

int N;
char u, v, w;
int left_child[26];
int right_child[26];

void preorder(int curr) {

	printf("%c", curr + 'A');
	if (left_child[curr])
		preorder(left_child[curr]);
	if (right_child[curr])
		preorder(right_child[curr]);

}


void inorder(int curr) {


	if (left_child[curr])
		inorder(left_child[curr]);
	printf("%c", curr + 'A');
	if (right_child[curr])
		inorder(right_child[curr]);

}

void postorder(int curr) {

	if (left_child[curr])
		postorder(left_child[curr]);
	if (right_child[curr])
		postorder(right_child[curr]);
	printf("%c", curr + 'A');

}


int main() {
	scanf("%d", &N);
	getchar();

	for (int i = 0; i < N; i++) {
		scanf("%c %c %c", &u, &v, &w);
		getchar();

		if (v != '.')
			left_child[u - 'A'] = v - 'A';
		if (w != '.')
			right_child[u - 'A'] = w - 'A';
	}

	preorder(0); puts("");
	inorder(0); puts("");
	postorder(0);

}