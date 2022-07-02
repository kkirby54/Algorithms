#include <cstdio>
#include <vector>
#include <queue>

int N, M, x, y, K;
int board[20][20];

// �ʱ⿣ �� 0
int front, rear, upper, lower, left, right;

int currR, currC;

int main() {
	scanf("%d %d %d %d %d", &N, &M, &x, &y, &K);

	currR = x;
	currC = y;

	// NxM ũ�� ����
	// �ֻ����� x, y��
	// ��� ���� = K.
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &board[i][j]);
		}
	}

	for (int i = 0; i < K; i++) {
		int opr;
		scanf("%d", &opr);

		// ���� �̵�
		if (opr == 4) {
			// �ʰ��ϸ� �ȵ�
			if (currR + 1 >= N) continue;
			currR += 1;

			// �����´�.
			int prev_upper = upper;
			int prev_lower = lower;

			upper = front;
			lower = rear;

			front = prev_lower;
			rear = prev_upper;


			// ���µ�, 0�̶��
			if (board[currR][currC] == 0) {
				board[currR][currC] = lower;
			}
			// �ƴϸ� ����
			else {
				lower = board[currR][currC];
				board[currR][currC] = 0;
			}

			// �� ���� ���� ���
			printf("%d\n", upper);

		}
		// ����
		else if (opr == 3) {
			if (currR - 1 < 0) continue;
			currR -= 1;

			// �����´�.
			int prev_upper = upper;
			int prev_lower = lower;

			upper = rear;
			lower = front;

			rear = prev_lower;
			front = prev_upper;


			// ���µ�, 0�̶��
			if (board[currR][currC] == 0) {
				board[currR][currC] = lower;
			}
			// �ƴϸ� ����
			else {
				lower = board[currR][currC];
				board[currR][currC] = 0;
			}
			// �� ���� ���� ���
			printf("%d\n", upper);

		}
		// �� ��
		else if (opr == 1) {
			if (currC + 1 >= M) continue;
			currC += 1;

			// ������
			int prev_upper = upper;
			int prev_lower = lower;

			upper = right;
			lower = left;

			right = prev_lower;
			left = prev_upper;

			// ���µ�, 0�̶��
			if (board[currR][currC] == 0) {
				board[currR][currC] = lower;

			}
			// �ƴϸ� ����
			else {
				lower = board[currR][currC];
				board[currR][currC] = 0;
			}
			// �� ���� ���� ���
			printf("%d\n", upper);

		}
		else if (opr == 2) {
			if (currC - 1 < 0) continue;
			currC -= 1;

			// ������
			int prev_upper = upper;
			int prev_lower = lower;

			upper = left;
			lower = right;

			right = prev_upper;
			left = prev_lower;

			// ���µ�, 0�̶��
			if (board[currR][currC] == 0) {
				board[currR][currC] = lower;
			}
			// �ƴϸ� ����
			else {
				lower = board[currR][currC];
				board[currR][currC] = 0;
			}
			// �� ���� ���� ���
			printf("%d\n", upper);

		}
	}

	

}