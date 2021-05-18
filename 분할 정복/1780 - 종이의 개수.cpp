#include <cstdio>
#include <algorithm>

int N;
int ret[3];
int map[2187][2187];

void paper(int r, int c, int size) {
	if (size == 1) {
		ret[map[r][c] + 1]++;
		return;
	}

	int standard = map[r][c];
	bool isPossible = true;

	// 다 본다.
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (map[r + i][c + j] != standard) {
				isPossible = false;
				break;
			}
		}
		if (!isPossible) break;
	}

	// 가능하면 통으로 1
	if (isPossible) {
		ret[standard + 1]++;
	}
	// 불가능하면 분할
	else {
		int nSize = size / 3;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				paper(r + i * nSize, c + j * nSize, nSize);
			}
		}
	}
}

int main() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	paper(0, 0, N);

	for (int i = 0; i < 3; i++) {
		printf("%d\n", ret[i]);
	}

}