#include <cstdio>
#include <algorithm>
typedef std::pair<int, int> P;

int T, N, ret;
int board[12][12];

// 동 서 남 북
int dr[] = { 0, 0, 1, -1 };
int dc[] = { 1, -1, 0, 0 };
P candidate[145];
int coreNums;
int maxCores;

bool isPossible(int r, int c, int dir) {

	for (int i = 1; i < N; i++) {
		int nR = r + i * dr[dir];
		int nC = c + i * dc[dir];

		if (nR < 0 || nR >= N || nC < 0 || nC >= N) return true;
		if (board[nR][nC] == 1) return false;
	}

	return true;
}

int fill(int r, int c, int dir, int val) {
	int cnt = 0;
	for (int i = 1; i < N; i++) {
		int nR = r + i * dr[dir];
		int nC = c + i * dc[dir];

		if (nR < 0 || nR >= N || nC < 0 || nC >= N) return cnt;
		board[nR][nC] = val;
		cnt++;
	}

	return cnt;
}

void dfs(int currIdx, int currCores, int totalCnt) {
	if (currIdx == coreNums) {
		if (currCores > maxCores) {
			maxCores = currCores;
			ret = totalCnt;
		}
		else if (currCores == maxCores)
			ret = std::min(ret, totalCnt);
		
		return;
	}

	int r = candidate[currIdx].first, c = candidate[currIdx].second;

	for (int dir = 0; dir < 4; dir++) {

		if (isPossible(r, c, dir)) {

			int currCnt = fill(r, c, dir, 1);

			dfs(currIdx + 1, currCores + 1, totalCnt + currCnt);

			fill(r, c, dir, 0);
		}
	}

	dfs(currIdx + 1, currCores, totalCnt);
}

int main() {
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d", &N);
		coreNums = 0;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &board[i][j]);
				if (board[i][j] == 1) {
					// 가장자리면 볼필요 x.
					if (i == 0 || i == N - 1 || j == 0 || j == N - 1) continue;
					candidate[coreNums++] = P(i, j);
				}
			}
		}
		maxCores = 0;

		ret = 1000000;

		dfs(0, 0, 0);

		printf("#%d %d\n", t, ret);
	}

}