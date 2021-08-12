#include <cstdio>

int pXor[1000001];
int main() {
	int N, Q, s, e, num;
	scanf("%d %d", &N, &Q);
	for (int i = 0; i < N; i++) {
		scanf("%d", &num);
		pXor[i + 1] = (pXor[i] ^ num);
	}

	int ret = 0;
	for (int i = 0; i < Q; i++) {
		scanf("%d %d", &s, &e);
		ret ^= (pXor[e] ^ pXor[s - 1]);
	}
	printf("%d\n", ret);

}