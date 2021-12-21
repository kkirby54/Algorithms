#include <cstdio>
#include <algorithm>
#include <cstring>
#include <climits>
using namespace std;

int N, r, c;
int R[500], C[500];
int dp[501][501];

// Top-down
int matrixMul(int s, int e) {
	int& ret = dp[s][e];
	if (ret != -1) return ret;
	if (s >= e) return 0;
	if (s + 1 == e) return R[s] * C[s] * C[e];

	ret = INT_MAX;
	for (int i = s; i < N; i++) {
		ret = min(ret, matrixMul(s, i) + matrixMul(i + 1, e) + R[s]*C[i]*C[e] );
	}

	return ret;
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", R + i, C + i);
	}

	//memset(dp, -1, sizeof(dp));
	//printf("%d\n", matrixMul(0, N - 1));

	// Bottom-up
	for (int len = 1; len < N; len++) {
		for (int i = 0; i + len < N; i++) {
			int j = i + len;
			dp[i][j] = INT_MAX;

			for (int k = i; k < j; k++) {
				dp[i][j] =
					min(dp[i][j], dp[i][k] + dp[k + 1][j] + R[i] * C[k] * C[j]);
			}
		}
	}
	printf("%d", dp[0][N - 1]);

}