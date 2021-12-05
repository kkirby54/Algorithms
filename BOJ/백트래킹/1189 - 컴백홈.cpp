#include <cstdio>
#include <algorithm>

int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };

int R, C, K;
char map[6][6];
bool visited[6][6];
int ret = 0;

void backtrack(int r, int c, int dist) {
	// 집에 도착한 경우
	if (r == 0 && c == C - 1) {
		if (dist == K)
			ret++;
		return;
	}

	for (int i = 0; i < 4; i++) {
		int nR = r + dr[i];
		int nC = c + dc[i];

		if (nR < 0 || nR >= R || nC < 0 || nC >= C) continue;
		if (map[nR][nC] == 'T' || visited[nR][nC]) {
			continue;
		}

		visited[r][c] = true;

		backtrack(nR, nC, dist + 1);

		visited[r][c] = false;
	}

}

int main() {
	scanf("%d %d %d", &R, &C, &K);

	for (int i = 0; i < R; i++) {
		scanf("%s", map[i]);
	}

	// map[r-1][0] 부터 시작한다.
	backtrack(R - 1, 0, 1);

	printf("%d", ret);
}