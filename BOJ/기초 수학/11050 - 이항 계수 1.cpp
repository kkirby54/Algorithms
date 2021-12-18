#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

int N, K;
int dp[11][11];

int binomial(int n, int k) {
	if (n == k || k == 0) return 1;

	int& ret = dp[n][k];
	if (ret != -1) return ret;

	return ret = binomial(n - 1, k - 1) + binomial(n - 1, k);
}

int main() {
	scanf("%d %d", &N, &K);
	memset(dp, -1, sizeof(dp));
	printf("%d", binomial(N, K));
}