#include <cstdio>
#include <algorithm>

int arr[1000000];

int main() {
	int N, M;
	scanf("%d %d", &N, &M);

	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}

	long long s = 0, e = 2000000000, mid, ret;

	while (s + 1 < e) {
		mid = (s + e) / 2;

		ret = 0;

		// 높이 - mid
		for (int i = 0; i < N; i++) {
			if (mid < arr[i]) {
				ret += arr[i] - mid;
			}
		}

		if (ret >= M) s = mid;
		else e = mid;
	}

	printf("%lld", s);

}