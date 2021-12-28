#include <cstdio>
#include <algorithm>
#include <cstring>

int N, M, K;
int dp[11][221][221];

int countAll(int n, int m, int prev) {
	int& ret = dp[n][m][prev];
	if (ret != -1) return ret;
	if (n == 1) return ret = 1;

	ret = 0;
	for (int i = prev; n*i <= m; i++) {
		ret += countAll(n - 1, m - i, i);
	}
	return ret;
}

int ret[10];
void skip(int n, int m, int prev, int k, int p) {
	if (n == 1) {
		ret[p] = m;
		return;
	}

	int pivot = 0;
	for (int next = prev; next < m; next++) {
		// 이전에(즉, n-1), next를 쓴 경우를 pivot에 포함시켰을 때
		// k보다 크다는 의미는,
		// 지금은 next다.
		if (pivot + countAll(n - 1, m - next, next) > k) {
			ret[p] = next;
			skip(n - 1, m - next, next, k - pivot, p + 1); // 여기서
			return;
		}

		pivot += countAll(n - 1, m - next, next);
	}

}

int main() {
	scanf("%d %d %d", &N, &M, &K);
	memset(dp, -1, sizeof(dp));

	// 합이 M이 되어야 하고, 길이가 N.
	// 그런 수열들은?
	skip(N, M, 1, K-1, 0);

	for (int i = 0; i < N; i++)
		printf("%d ", ret[i]);
}