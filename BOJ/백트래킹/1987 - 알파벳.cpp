#include <cstdio>
#include <algorithm>

int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };

int R, C;
char board[21][21];
bool visited[26];

int ret;
int tmp;

void backtrack(int r, int c) {
	ret = std::max(ret, tmp);

	for (int i = 0; i < 4; i++) {
		int nR = r + dr[i];
		int nC = c + dc[i];

		if (nR < 0 || nR >= R || nC < 0 || nC >= C) continue;
		if (visited[board[nR][nC] - 'A']) continue;

		visited[board[nR][nC] - 'A'] = true;
		tmp++;
		backtrack(nR, nC);
		tmp--;
		visited[board[nR][nC] - 'A'] = false;
	}



}

int main() {
	scanf("%d %d", &R, &C);
	for (int i = 0; i < R; i++) {
		scanf("%s", board[i]);
	}

	// (0,0)에서 시작한다.
	visited[board[0][0] - 'A'] = true;

	backtrack(0, 0);
	printf("%d", ret + 1);

}