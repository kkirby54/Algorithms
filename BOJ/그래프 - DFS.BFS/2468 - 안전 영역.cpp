#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };

int N, H;
int board[100][100];
bool visited[100][100];

// 안전한 곳을 센다.
void dfs(int r, int c) {
	visited[r][c] = true;

	for (int i = 0; i < 4; i++) {
		int nR = r + dr[i];
		int nC = c + dc[i];

		if (nR < 0 || nR >= N || nC < 0 || nC >= N) continue;
		if (visited[nR][nC]) continue;
		if (board[nR][nC] > H)
			dfs(nR, nC);

	}

}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &board[i][j]);
		}
	}

	int ret = 1;
	// N <= 100이라 그냥 모든 높이에 대해 시행
	for (int h = 1; h < 100; h++) {
		memset(visited, 0, sizeof(visited));
		int cnt = 0;

		H = h;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (!visited[i][j] && board[i][j] > H) {
					dfs(i, j);
					cnt++;
				}
			}
		}

		ret = max(ret, cnt);
	}
	printf("%d\n", ret);
}