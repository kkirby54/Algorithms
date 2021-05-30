#include <cstdio>
#include <algorithm>
#include <cstring>

int C, N, map[101][101];
int dp[101][101];

int triangle(int r, int c) {
	if (r < 0 || r >= N || c < 0 || c >= N) return 0;
	if (r == N) return 0;

	int& ret = dp[r][c];
	if (ret != -1) return ret;

	// 아래 or 오른쪽 아래
	ret = map[r][c];

	ret += std::max(triangle(r + 1, c), triangle(r + 1, c + 1));

	return ret;
}

int main() {
	scanf("%d", &C);

	for (int t = 0; t < C; t++) {
		scanf("%d", &N);

		memset(dp, -1, sizeof(dp));

		for (int i = 0; i < N; i++) {
			for (int j = 0; j <= i; j++) {
				scanf("%d", &map[i][j]);
			}
		}

		printf("%d\n", triangle(0, 0));

	}

}
