#include <cstdio>
#include <cstring>
#include <algorithm>

const int MOD = 1000000000;

int N, K;
int dp[201][201];

int part_sum(int curr, int digit) {
	if (digit == 1) return 1;

	int& ret = dp[curr][digit];
	if (ret != -1) return ret;

	// 실제 계산

	ret = 0;
	for (int i = 0; curr - i >= 0; i++) {
		ret += (part_sum(curr - i, digit - 1));
		ret %= MOD;
	}

	return ret;
}

int main() {
	scanf("%d %d", &N, &K);

	memset(dp, -1, sizeof(dp));

	printf("%d", part_sum(N, K));
}