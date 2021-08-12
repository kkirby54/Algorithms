#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int pSum[100001];
int main() {
	int N, M, num, s, e;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &num);
		pSum[i + 1] = pSum[i] + num;
	}

	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &s, &e);
		printf("%d\n", pSum[e] - pSum[s - 1]);
	}

}