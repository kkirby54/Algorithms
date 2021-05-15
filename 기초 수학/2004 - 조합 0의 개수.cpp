#include <cstdio>
#include <algorithm>

int main() {
	int N, M;
	long long k;
	long long cnt[3] = { 0 };
	long long cnt_t[3] = { 0 };
	scanf("%d %d", &N, &M);

	int standard[3] = { N, M, N - M };

	// N, M, N-M 이하의 5의 개수

	for (int i = 0; i < 3; i++) {
		k = 5;
		while (standard[i] >= k) {
			cnt[i] += standard[i] / k;
			k *= 5;
		}

		k = 2;
		while (standard[i] >= k) {
			cnt_t[i] += standard[i] / k;
			k *= 2;
		}

	}

	long long ret = cnt[0] - (cnt[2] + cnt[1]);
	long long ret2 = cnt_t[0] - (cnt_t[2] + cnt_t[1]);

	printf("%lld", std::min(ret, ret2));


}