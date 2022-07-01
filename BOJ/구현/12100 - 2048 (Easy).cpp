#include <cstdio>
#include <vector>
#include <queue>

int N;
int board[20][20];
void printB();

int maxVal = -1;

// 역시 위 아래 왼 오.

void up() {
	// board를 차례로 훑는다
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] != 0) {
				// 같은 열을 훑어야한다.
				// 그러면서 같은 게 있다면?

				bool isFound = false;
				for (int k = i + 1; k < N; k++) {
					// 같다면, 얘네 둘을 합쳐야 한다.
					if (board[k][j] == board[i][j]) {

						// i - 1부터 0이 아닌 거 나올 때까지 쭉 올려
						int maxUp = i - 1;
						for (maxUp = i - 1; maxUp >= 0; maxUp--) {
							if (board[maxUp][j] != 0)
								break;
						}
						maxUp += 1;

						int val = board[i][j];

						board[i][j] = 0;
						board[k][j] = 0;

						// 두 배로 만들고
						board[maxUp][j] = val * 2;
						maxVal = std::max(maxVal, val * 2);

						// 원래 있던 board[i][j], board[i][k]는 0으로 만들기.

						isFound = true;
						break;
					}
					// 0이 아닌 다른 녀석이 중간에 있다면 이건 안되는 경우
					else if (board[k][j] != 0)
						break;

				}

				// 아무 것도 없다면, 쭉 올린다.
				if (!isFound) {
					// i - 1부터 0이 아닌 거 나올 때까지 쭉 올려
					int maxUp = i - 1;
					for (maxUp = i - 1; maxUp >= 0; maxUp--) {
						if (board[maxUp][j] != 0)
							break;
					}
					maxUp += 1;

					// 쭉 올려
					board[maxUp][j] = board[i][j];

					// 원래 있던 board[i][j]는 0으로 만들기.
					if (maxUp != i)
						board[i][j] = 0;
				}
			}
		}
	}
}

void down() {
	// board를 차례로 훑는다
	for (int i = N-1; i >= 0; i--) {
		for (int j = N - 1; j >= 0; j--) {
			if (board[i][j] != 0) {
				// 같은 열을 훑어야한다.
				// 그러면서 같은 게 있다면?
				bool isFound = false;
				for (int k = i - 1; k >= 0; k--) {
					// 같다면, 얘네 둘을 합쳐야 한다.
					if (board[k][j] == board[i][j]) {

						// i + 1부터 0이 아닌 거 나올 때까지 쭉 내려
						int maxUp = i + 1;
						for (maxUp = i + 1; maxUp < N; maxUp++) {
							if (board[maxUp][j] != 0)
								break;
						}
						maxUp -= 1;

						int val = board[i][j];

						board[i][j] = 0;
						board[k][j] = 0;

						// 두 배로 만들고
						board[maxUp][j] = val * 2;
						maxVal = std::max(maxVal, val * 2);

						// 원래 있던 board[i][j], board[i][k]는 0으로 만들기.

						isFound = true;
						break;
					}
					// 0이 아닌 다른 녀석이 중간에 있다면 이건 안되는 경우
					else if (board[k][j] != 0)
						break;

				}

				// 아무 것도 없다면, 쭉 올린다.
				if (!isFound) {
					// i + 1부터 0이 아닌 거 나올 때까지 쭉 내려
					int maxUp = i + 1;
					for (maxUp = i + 1; maxUp < N; maxUp++) {
						if (board[maxUp][j] != 0)
							break;
					}
					maxUp -= 1;

					// 쭉 올려
					board[maxUp][j] = board[i][j];

					// 원래 있던 board[i][j]는 0으로 만들기.
					if (maxUp != i)
						board[i][j] = 0;
				}
			}
		}
	}
}

void left() {
	// board를 차례로 훑는다
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] != 0) {
				// 같은 row을 훑어야한다.
				// 그러면서 같은 게 있다면?

				bool isFound = false;
				for (int k = j + 1; k < N; k++) {
					// 같다면, 얘네 둘을 합쳐야 한다.
					if (board[i][k] == board[i][j]) {

						// j - 1부터 0이 아닌 거 나올 때까지 쭉 왼쪽으로
						int maxUp = j - 1;
						for (maxUp = j - 1; maxUp >= 0; maxUp--) {
							if (board[i][maxUp] != 0)
								break;
						}
						maxUp += 1;

						int val = board[i][j];

						board[i][j] = 0;
						board[i][k] = 0;

						// 두 배로 만들고
						board[i][maxUp] = val * 2;
						maxVal = std::max(maxVal, val * 2);

						// 원래 있던 board[i][j], board[i][k]는 0으로 만들기.

						isFound = true;
						break;
					}
					// 0이 아닌 다른 녀석이 중간에 있다면 이건 안되는 경우
					else if (board[i][k] != 0)
						break;

				}

				// 아무 것도 없다면, 쭉 올린다.
				if (!isFound) {
					// j - 1부터 0이 아닌 거 나올 때까지 쭉 왼쪽으로
					int maxUp = j - 1;
					for (maxUp = j - 1; maxUp >= 0; maxUp--) {
						if (board[i][maxUp] != 0)
							break;
					}
					maxUp += 1;

					// 쭉 올려
					board[i][maxUp] = board[i][j];

					// 원래 있던 board[i][j]는 0으로 만들기.
					if (maxUp != j)
						board[i][j] = 0;
				}
			}
		}
	}
}

void right() {
	// board를 차례로 훑는다
	for (int i = 0; i < N; i++) {
		for (int j = N-1; j >=0; j--) {
			if (board[i][j] != 0) {
				// 같은 row을 훑어야한다.
				// 그러면서 같은 게 있다면?

				bool isFound = false;
				for (int k = j - 1; k >= 0; k--) {
					// 같다면, 얘네 둘을 합쳐야 한다.
					if (board[i][k] == board[i][j]) {

						// j + 1부터 0이 아닌 거 나올 때까지 쭉 오른쪽으로
						int maxUp = j + 1;
						for (maxUp = j + 1; maxUp < N; maxUp++) {
							if (board[i][maxUp] != 0)
								break;
						}
						maxUp -= 1;

						int val = board[i][j];

						board[i][j] = 0;
						board[i][k] = 0;

						// 두 배로 만들고
						board[i][maxUp] = val * 2;
						maxVal = std::max(maxVal, val * 2);

						// 원래 있던 board[i][j], board[i][k]는 0으로 만들기.

						isFound = true;
						break;
					}
					// 0이 아닌 다른 녀석이 중간에 있다면 이건 안되는 경우
					else if (board[i][k] != 0)
						break;

				}

				// 아무 것도 없다면, 쭉 올린다.
				if (!isFound) {
					// j + 1부터 0이 아닌 거 나올 때까지 쭉 오른쪽으로
					int maxUp = j + 1;
					for (maxUp = j + 1; maxUp < N; maxUp++) {
						if (board[i][maxUp] != 0)
							break;
					}
					maxUp -= 1;

					// 쭉 올려
					board[i][maxUp] = board[i][j];

					// 원래 있던 board[i][j]는 0으로 만들기.
					if (maxUp != j)
						board[i][j] = 0;
				}
			}
		}
	}
}


void backtrack(int k) {
	if (k == 5) {
		return;
	}

	// 우선 되돌릴 이전 board 저장하고 있는다.
	int prevBoard[20][20] = { 0 };
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			prevBoard[i][j] = board[i][j];
		}
	}

	// 1. 위로 움직인다. board 전체를 움직인다.
	// 2. backtrack(k+1)
	// 3. 되돌린다.

	up();
	backtrack(k + 1);
	
	// 되돌리기
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = prevBoard[i][j];
		}
	}

	// 이번엔 아래로
	down();
	backtrack(k + 1);

	// 되돌리기
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = prevBoard[i][j];
		}
	}
	
	// 이번엔 오른쪽
	right();
	backtrack(k + 1);

	// 되돌리기
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = prevBoard[i][j];
		}
	}

	// 이번엔 왼쪽.
	left();
	backtrack(k + 1);

	// 되돌리기
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = prevBoard[i][j];
		}
	}

}

void printB() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", board[i][j]);
		}
		puts("");
	}
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &board[i][j]);
			maxVal = std::max(maxVal, board[i][j]);
		}
	}


	backtrack(0);

	printf("%d", maxVal);

}