#include <cstdio>
#include <algorithm>

int N, M, maxVal;
int budget[10000];

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", budget + i);
		maxVal = std::max(maxVal, budget[i]);
	}
	scanf("%d", &M);


	int lo = 0, hi = maxVal + 1;

	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;

		// mid를 상한액으로 잡는다.
		int ret = 0;
		for (int i = 0; i < N; i++) {
			if (mid < budget[i]) ret += mid;
			else ret += budget[i];
		}

		// 예산 총액을 초과하면 줄여야 함.
		if (ret > M)
			hi = mid;
		else lo = mid;

	}
	printf("%d\n", lo);

}