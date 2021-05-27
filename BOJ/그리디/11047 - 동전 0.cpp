#include <cstdio>

int main() {
	int N, K;
	int cost[10];
	int cnt = 0;

	scanf("%d %d", &N, &K);

	for (int i = 0; i < N; i++) {
		scanf("%d", cost + i);
	}

	// 무조건 제일 큰 거부터 쓴다.
	for (int i = N - 1; i >= 0; i--) {
		while (cost[i] <= K && K != 0) {
			cnt += K / cost[i];
			K = K % cost[i];
		}
	}

	printf("%d", cnt);

}