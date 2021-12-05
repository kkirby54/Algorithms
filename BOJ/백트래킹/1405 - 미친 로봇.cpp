#include <cstdio>
#include <algorithm>

int dr[] = { 0, 0, 1, -1 };
int dc[] = { -1, 1, 0,0 };

int N;
bool board[35][35];
double percentage[4];
double ret;

void backtrack(int cnt, int r, int c, double curr_perctent) {
	// Base case
	if (cnt == N) {
		ret += curr_perctent;
		return;
	}

	for (int i = 0; i < 4; i++) {
		int nR = r + dr[i];
		int nC = c + dc[i];

		// 만약 다음 꺼가 이미 방문한 상태면 안됨.
		if (board[nR][nC]) continue;

		board[nR][nC] = true;
		backtrack(cnt + 1, nR, nC, curr_perctent * percentage[i]);
		board[nR][nC] = false;
	}

}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < 4; i++) {
		scanf("%lf", percentage + i);
		percentage[i] /= 100;
	}
	board[15][15] = true;
	backtrack(0, 15, 15, 1);

	printf("%.13lf\n", ret);
}