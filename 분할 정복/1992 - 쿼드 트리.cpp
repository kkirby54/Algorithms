#include <cstdio>

int N;
char map[65][65];

void quad(int r, int c, int size) {
	if (size == 1) {
		printf("%c", map[r][c]);
		return;
	}

	char standard = map[r][c];
	bool isPossible = true;

	for (int i = r; i < r + size; i++) {
		for (int j = c; j < c + size; j++) {
			if (map[i][j] != standard) {
				isPossible = false;
				break;
			}
		}
		if (!isPossible) break;
	}


	if (isPossible) printf("%c", standard);
	else {
		printf("(");
		quad(r, c, size / 2);
		quad(r, c + size / 2, size / 2);
		quad(r + size / 2, c, size / 2);
		quad(r + size / 2, c + size / 2, size / 2);
		printf(")");
	}
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%s", map[i]);
	}

	quad(0, 0, N);

}