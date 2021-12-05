#include <cstdio>
#include <algorithm>
#include <vector>
const int INF = 987654321;

int board[10][10];
int ret = INF;
int remain[6];
bool isFin = false;

// (r,c)부터 num개 만큼을 사각형으로 칠한다.
void fill(int r, int c, int num, int val) {
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			board[r + i][c + j] = val;
		}
	}
}

// (r,c)부터 시작해서 넣을 수 있는지를 확인한다.
bool checkBoard(int r, int c, int num) {

	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (r + i >= 10 || c + j >= 10) return false;
			if (board[r + i][c + j] != 1) return false;
		}
	}
	return true;
}

// 덮어야 할 거를 찾아서 거기서부터 시작.
void backtrack() {
	int r, c;
	bool isFound = false;
	// 제일 먼저를 찾는다.
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (board[i][j] == 1) {
				r = i; c = j;
				isFound = true;
				break;
			}


		}
		if (isFound) break;
	}

	// 발견이 안됐다면 다 덮은 상황. 또는 덮을 수 없는 상황
	if (!isFound) {
		int sum = 0;
		for (int i = 1; i <= 5; i++) {
			sum += 5 - remain[i];
			if (remain[i] < 0) return;
		}

		if (ret > sum) {
			ret = sum;
		}

		return;
	}

	// 이제 되는 곳인 (r,c)부터 체크를 한다.
	for (int i = 5; i >= 1; i--) {
		// i개를 칠할 수 있으면 칠한다.
		// 그리고 넘기고, 되돌린다.
		if (checkBoard(r, c, i) && remain[i] > 0) {
			fill(r, c, i, 2);
			remain[i]--;

			backtrack();

			// 다시 되돌리기
			fill(r, c, i, 1);
			remain[i]++;
		}

	}


}

int main() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			scanf("%d", &board[i][j]);
		}
	}
	for (int i = 1; i <= 5; i++) remain[i] = 5;

	backtrack();
	printf("%d", ret == INF ? -1 : ret);
}