#include <cstdio>
#include <algorithm>

int N, K;
// N제곱은 100억까지 가능.

int main() {
	scanf("%d %d", &N, &K);

	// 어떤 수 X에 대해,
	// X보다 작거나 같은 수를 센다.
	// 이 세는 방법은 -> N개 행을 돌면서 세봄.
	// 다 돌았는데 K보다 같거나 많다면?..
	// B[K]와 같거나 초과하는 수, 따라서 hi = mid.

	long long lo = 0, hi = (long long)1e10;

	while (lo + 1 < hi) {
		long long mid = (lo + hi) / 2;

		long long sum = 0;
		// mid와 같거나 작은 수를 세본다.
		for (int i = 1; i <= N; i++) {
			if (mid >= (long long)i * N) {
				sum += N;
			}
			else sum += (mid / i);
		}

		if (sum >= K) {
			hi = mid;
		}
		else lo = mid;

	}

	printf("%lld\n", hi);

}