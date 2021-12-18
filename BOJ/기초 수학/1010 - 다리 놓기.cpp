#include <cstdio>
#include <cstring>
#include <algorithm>

int N, M, T;
int dp[31][31];

int bridge(int n, int k) {
	if (n == k || k == 0) return 1;
	if (n < k) return 0;
	int& ret = dp[n][k];
	if (ret != -1) return ret;

	return ret = bridge(n - 1, k - 1) + bridge(n - 1, k);
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &N, &M);
		memset(dp, -1, sizeof(dp));

		printf("%d\n", bridge(M, N));
	}

}

