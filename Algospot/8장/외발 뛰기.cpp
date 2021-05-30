#include <cstdio>
#include <cstring>

int C, N;
int dp[101][101];
int map[101][101];

int Jumpgame(int r, int c) {
	if (r < 0 || r >= N || c < 0 || c >= N) return 0;
	if (r == N - 1 && c == N - 1) return dp[r][c] = 1;

	int& ret = dp[r][c];
	if (ret != -1) return ret;

	int off = map[r][c];

	// 아래로
	ret = Jumpgame(r, c + off) + Jumpgame(r + off, c);
	return ret;
}

int main() {
	scanf("%d", &C);

	for (int c = 0; c < C; c++) {
		scanf("%d", &N);

		memset(dp, -1, sizeof(dp));

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				scanf("%d", &map[i][j]);
		}

		Jumpgame(0, 0);
		if (dp[N - 1][N - 1] != -1) puts("YES");
		else puts("NO");


		/*
		puts("");

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				printf("%d ", dp[i][j]);
			puts("");
		}
		*/

	}


}
