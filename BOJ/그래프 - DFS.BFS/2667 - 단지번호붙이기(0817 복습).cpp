#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };

int N, M, K, r, c;
int board[25][25];
bool visited[25][25];

int dfs(int r, int c) {
	visited[r][c] = true;

	int cnt = 1;
	for (int i = 0; i < 4; i++) {
		int nR = r + dr[i];
		int nC = c + dc[i];

		if (nR < 0 || nR >= N || nC < 0 || nC >= N) continue;
		if (!visited[nR][nC] && board[nR][nC] == 1) {
			cnt += dfs(nR, nC);
		}
	}

	return cnt;
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			scanf("%1d", &board[i][j]);
	}

	vector<int> ret;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!visited[i][j] && board[i][j] == 1) {
				ret.push_back(dfs(i, j));
			}
		}
	}

	printf("%d\n", ret.size());
	sort(ret.begin(), ret.end());
	for (int e : ret) printf("%d\n", e);

}