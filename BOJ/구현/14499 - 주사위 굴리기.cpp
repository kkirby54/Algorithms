#include <cstdio>
#include <vector>
#include <queue>

int N, M, x, y, K;
int board[20][20];

// 초기엔 다 0
int front, rear, upper, lower, left, right;

int currR, currC;

int main() {
	scanf("%d %d %d %d %d", &N, &M, &x, &y, &K);

	currR = x;
	currC = y;

	// NxM 크기 지도
	// 주사위는 x, y에
	// 명령 개수 = K.
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &board[i][j]);
		}
	}

	for (int i = 0; i < K; i++) {
		int opr;
		scanf("%d", &opr);

		// 남쪽 이동
		if (opr == 4) {
			// 초과하면 안됨
			if (currR + 1 >= N) continue;
			currR += 1;

			// 뒤집는다.
			int prev_upper = upper;
			int prev_lower = lower;

			upper = front;
			lower = rear;

			front = prev_lower;
			rear = prev_upper;


			// 갔는데, 0이라면
			if (board[currR][currC] == 0) {
				board[currR][currC] = lower;
			}
			// 아니면 복사
			else {
				lower = board[currR][currC];
				board[currR][currC] = 0;
			}

			// 그 다음 윗면 출력
			printf("%d\n", upper);

		}
		// 북쪽
		else if (opr == 3) {
			if (currR - 1 < 0) continue;
			currR -= 1;

			// 뒤집는다.
			int prev_upper = upper;
			int prev_lower = lower;

			upper = rear;
			lower = front;

			rear = prev_lower;
			front = prev_upper;


			// 갔는데, 0이라면
			if (board[currR][currC] == 0) {
				board[currR][currC] = lower;
			}
			// 아니면 복사
			else {
				lower = board[currR][currC];
				board[currR][currC] = 0;
			}
			// 그 다음 윗면 출력
			printf("%d\n", upper);

		}
		// 동 ㄱ
		else if (opr == 1) {
			if (currC + 1 >= M) continue;
			currC += 1;

			// 뒤집기
			int prev_upper = upper;
			int prev_lower = lower;

			upper = right;
			lower = left;

			right = prev_lower;
			left = prev_upper;

			// 갔는데, 0이라면
			if (board[currR][currC] == 0) {
				board[currR][currC] = lower;

			}
			// 아니면 복사
			else {
				lower = board[currR][currC];
				board[currR][currC] = 0;
			}
			// 그 다음 윗면 출력
			printf("%d\n", upper);

		}
		else if (opr == 2) {
			if (currC - 1 < 0) continue;
			currC -= 1;

			// 뒤집기
			int prev_upper = upper;
			int prev_lower = lower;

			upper = left;
			lower = right;

			right = prev_upper;
			left = prev_lower;

			// 갔는데, 0이라면
			if (board[currR][currC] == 0) {
				board[currR][currC] = lower;
			}
			// 아니면 복사
			else {
				lower = board[currR][currC];
				board[currR][currC] = 0;
			}
			// 그 다음 윗면 출력
			printf("%d\n", upper);

		}
	}

	

}