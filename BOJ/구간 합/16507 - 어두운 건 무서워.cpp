#include <cstdio>

int R, C, Q, num, r1, r2, c1, c2;
int board[1001][1001];

int main() {
	scanf("%d %d %d", &R, &C, &Q);
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			scanf("%d", &num);
			board[i + 1][j + 1] = board[i][j + 1] + board[i + 1][j] - board[i][j] + num;
		}
	}

	for (int i = 0; i < Q; i++) {
		scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
		printf("%d\n", (board[r2][c2] - board[r1-1][c2] - board[r2][c1-1] + board[r1-1][c1-1]) / ((r2 - r1 + 1) * (c2 - c1 + 1)) );

	}

}