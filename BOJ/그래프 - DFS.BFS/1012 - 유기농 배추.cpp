#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

int T, M, N, K, X, Y, ret;
int board[50][50];
bool visited[50][50];

void dfs(int r, int c) {
	visited[r][c] = true;

	for (int i = 0; i < 4; i++) {
		int nR = r + dr[i];
		int nC = c + dc[i];

		if (nR < 0 || nR >= N || nC < 0 || nC >= M) continue;
		if (!visited[nR][nC] && board[nR][nC] == 1) {
			dfs(nR, nC);
		}
	}

}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d", &M, &N, &K);
		memset(visited, false, sizeof(visited));
		memset(board, 0, sizeof(board));
		ret = 0;

		// N * M
		for (int i = 0; i < K; i++) {
			scanf("%d %d", &X, &Y);
			board[Y][X] = 1;
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (!visited[i][j] && board[i][j] == 1) {
					dfs(i, j);
					ret++;
				}
			}
		}

		printf("%d\n", ret);
	}

}