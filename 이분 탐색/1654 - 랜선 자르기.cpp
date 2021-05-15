#include <cstdio>
#include <algorithm>

int N, K, arr[10005];
long long s, e;

int main() {
	scanf("%d %d", &K, &N);

	for (int i = 0; i < K; i++) {
		scanf("%d", arr + i);
	}

	// 이미 K개 갖고 있음
	// 여기서 잘라서 N개를 갖고 싶음.

	e = 3000000000;
	while (s +1 < e) {
		long long mid = (s + e) / 2;

		long long ret = 0;
		// K개의 랜선 잘라봐
		for (int i = 0; i < K; i++) {
			ret += (arr[i] / mid);
		}

		if (ret >= N) s = mid;
		else e = mid;
	}
	printf("%lld", s);

}