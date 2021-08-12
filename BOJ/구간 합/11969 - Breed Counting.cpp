#include <cstdio>
#include <algorithm>


int pSum[3][100001];
int main() {
	int N, Q, num, s, e;
	scanf("%d %d", &N, &Q);
	for (int i = 0; i < N; i++) {
		scanf("%d", &num);
		pSum[0][i + 1] = pSum[0][i];
		pSum[1][i + 1] = pSum[1][i];
		pSum[2][i + 1] = pSum[2][i];
		pSum[num - 1][i + 1] += 1;
	}

	for (int i = 0; i < Q; i++) {
		scanf("%d %d", &s, &e);
		for (int j = 0; j < 3; j++) {
			printf("%d ", pSum[j][e] - pSum[j][s - 1]);
		}
		puts("");
	}

}