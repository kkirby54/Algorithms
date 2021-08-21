#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };

int N, M, K, r, c;
int board[100][100];
bool visited[100][100];

int dfs(int r, int c) {
	visited[r][c] = true;
	//printf("%d %d방문\n", r, c);
	int ret = 1;
	for (int i = 0; i < 4; i++) {
		int nR = r + dr[i];
		int nC = c + dc[i];

		if (nR < 0 || nR >= N || nC < 0 || nC >= M) continue;
		if (!visited[nR][nC] && board[nR][nC] == 1)
			ret += dfs(nR, nC);
	}
	return ret;
}

int main() {
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < K; i++) {
		scanf("%d %d", &r, &c);
		board[r-1][c-1] = 1;
	}

	int ans = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (!visited[i][j] && board[i][j] == 1) {
				ans = max(ans, dfs(i, j));
			}
		}
	}
	printf("%d", ans);
}