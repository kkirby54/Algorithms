#include <cstdio>
#include <cstring>
#include <algorithm>

// N개의 물건, W무게, V가치
// 최대 K만큼의 무게만을 넣을 수 있다.
int N, K, W[100], V[100];
int dp[101][100001];

int solve(int curr, int rest) {
	if (curr == N) return 0;

	int& ret = dp[curr][rest];
	if (ret != -1) return ret;

	// curr번째를 안쓰고 넘길 수도 있음
	ret = solve(curr + 1, rest);

	// 또는 쓰고 넘긴다.
	if (W[curr] <= rest) {
		ret = std::max(ret, solve(curr + 1, rest - W[curr]) + V[curr]);
	}

	return ret;
}

int main() {
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", W + i, V + i);
	}

	memset(dp, -1, sizeof(dp));

	printf("%d\n", solve(0, K));
}