#include <cstdio>
#include <algorithm>

int C, N, arr[501];

int main() {
	scanf("%d", &C);
	for (int t = 0; t < C; t++) {
		scanf("%d", &N);

		int ans = -1;
		int dp[501] = { 0 };

		for (int i = 0; i < N; i++) {
			scanf("%d", arr + i);

			// dp[i]는 i번째 수를 마지막으로 하는 LIS

			dp[i] = 1;
			for (int j = 0; j < i; j++) {
				if (arr[j] < arr[i]) {
					dp[i] = std::max(dp[i], dp[j] + 1);
					ans = std::max(ans, dp[i]);
				}
			}
		}

		printf("%d\n", ans);
	}

}
