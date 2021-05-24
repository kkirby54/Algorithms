#include <cstdio>
#include <vector>
#include <algorithm>

typedef std::pair<int, int> P;

int map[9][9];
int cnt;
bool isEnd = false;
std::vector<P> vec;

// (r,c)에 놓을 수 있냐?
bool isPossible(int r, int c) {
	int standard = map[r][c];

	for (int i = 0; i < 9; i++) {
		if (i == r) continue;
		if (map[i][c] == standard) return false;
	}

	for (int i = 0; i < 9; i++) {
		if (i == c) continue;
		if (map[r][i] == standard) return false;
	}

	// 3 * 3.
	int s_r = (r / 3) * 3;
	int s_c = (c / 3) * 3;

	for (int i = s_r; i < s_r + 3; i++) {
		for (int j = s_c; j < s_c + 3; j++) {
			if (i == r && j == c) continue;
			if (map[i][j] == standard) return false;
		}
	}

	return true;
}

void sudoku(int curr) {
	if (isEnd) {
		return;
	}

	if (curr == cnt) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				printf("%d ", map[i][j]);
			}
			puts("");
		}
		isEnd = true;
		return;
	}

	for (int i = 1; i <= 9; i++) {
		int cR = vec[curr].first;
		int cC = vec[curr].second;

		//printf("%d %d 도착\n", cR, cC);
		map[cR][cC] = i;

		if (isPossible(cR, cC)) {
			sudoku(curr + 1);
		}

		map[cR][cC] = 0;
	}

}

int main() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 0) {
				vec.push_back(P(i, j));
			}
		}
	}
	
	cnt = vec.size();
	sudoku(0);

}