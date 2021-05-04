#include <cstdio>
#include <algorithm>
#include <cstring>

int M, N;
int dp[505][505];
int map[505][505];



int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

int cnt;

int road(int r, int c) {
	if (r < 0 || r >= M || c < 0 || c >= N) return 0;

	int& ret = dp[r][c];
	if (r == M - 1 && c == N - 1) {
		return 1;
	}

	if (ret != -1) return ret;


	ret = 0;
	for (int i = 0; i < 4; i++) {
		int n_r = r + dr[i];
		int n_c = c + dc[i];

		// 다음 좌표가 이번 좌표보다 더 작다면
		if (n_r < 0 || n_r >= M || n_c < 0 || n_c >= N) continue;

		if (map[r][c] > map[n_r][n_c]) {
			ret += road(n_r, n_c);
		}
	}

	return ret;

}

int main() {
	scanf("%d %d", &M, &N);

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
		}
	}
	
	memset(dp, -1, sizeof(dp));
	
	printf("%d", road(0, 0));

}