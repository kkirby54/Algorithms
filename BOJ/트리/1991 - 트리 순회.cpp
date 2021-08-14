#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int N;
char ch, c1,c2;
char lc[26], rc[26];

void preorder(int root) {
	printf("%c", root + 'A');
	if (lc[root])
		preorder(lc[root] - 'A');
	if (rc[root])
		preorder(rc[root] - 'A');
}

void inorder(int root) {
	if (lc[root])
		inorder(lc[root] - 'A');
	printf("%c", root + 'A');
	if (rc[root])
		inorder(rc[root] - 'A');
}

void postorder(int root) {
	if (lc[root])
		postorder(lc[root] - 'A');
	if (rc[root])
		postorder(rc[root] - 'A');
	printf("%c", root + 'A');
}


int main() {
	scanf("%d", &N);
	getchar();
	for (int i = 0; i < N; i++) {
		scanf("%c %c %c", &ch, &c1, &c2);
		getchar();
		if (c1 != '.')
			lc[ch - 'A'] = c1;
		if (c2 != '.')
			rc[ch - 'A'] = c2;
	}
	preorder(0); puts("");
	inorder(0); puts("");
	postorder(0);
}