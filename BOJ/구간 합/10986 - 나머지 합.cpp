#include <cstdio>
#include <algorithm>

int N, M, num;
int sum;
int memo[1001] = { 1, };

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		scanf("%d", &num);
		sum = (sum +  num) % M;
		memo[sum]++;
	}

	long long ret = 0;
	for (int i = 0; i < M; i++) {
		ret += (1LL * memo[i] * (memo[i] - 1)) / 2;
	}

	printf("%lld\n", ret);
}