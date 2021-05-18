#include <cstdio>
#include <cstring>

int N;
char map[3000][3000];

void stars(int r, int c, int size) {
	if (size == 1) {
		map[r][c] = '*';
		return;
	}

	// r, r+1, ... => size만큼
	int nSize = size / 3;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == 1 && j == 1) continue;
			stars(r + i * nSize, c + j * nSize, nSize);

		}
	}



}

int main() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			map[i][j] = ' ';
	}

	stars(0, 0, N);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			printf("%c", map[i][j]);
		puts("");
	}


}