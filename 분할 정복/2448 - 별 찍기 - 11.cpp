#include <cstdio>

int N;
char map[3200][6500];

void stars(int r, int c, int size) {
	if (size == 3) {
		//  *
		// * *
		//*****
		// 모양으로 별을 찍는다.

		map[r][c] = '*';
		map[r + 1][c - 1] = '*';
		map[r + 1][c + 1] = '*';
		for (int i = 0; i < 5; i++)
			map[r + 2][c - 2 + i] = '*';
		
		return;
	}

	int nSize = size / 2;

	stars(r, c, nSize);
	stars(r + nSize, c-nSize, nSize);
	stars(r + nSize, c + nSize, nSize);

}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 2*N-1; j++)
			map[i][j] = ' ';
	}

	stars(0, N-1, N);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 2*N - 1; j++)
			printf("%c", map[i][j]);
		puts("");
	}
}