#include <cstdio>
#include <vector>
#include <queue>

int N;
int board[20][20];
void printB();

int maxVal = -1;

// ���� �� �Ʒ� �� ��.

void up() {
	// board�� ���ʷ� �ȴ´�
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] != 0) {
				// ���� ���� �Ⱦ���Ѵ�.
				// �׷��鼭 ���� �� �ִٸ�?

				bool isFound = false;
				for (int k = i + 1; k < N; k++) {
					// ���ٸ�, ��� ���� ���ľ� �Ѵ�.
					if (board[k][j] == board[i][j]) {

						// i - 1���� 0�� �ƴ� �� ���� ������ �� �÷�
						int maxUp = i - 1;
						for (maxUp = i - 1; maxUp >= 0; maxUp--) {
							if (board[maxUp][j] != 0)
								break;
						}
						maxUp += 1;

						int val = board[i][j];

						board[i][j] = 0;
						board[k][j] = 0;

						// �� ��� �����
						board[maxUp][j] = val * 2;
						maxVal = std::max(maxVal, val * 2);

						// ���� �ִ� board[i][j], board[i][k]�� 0���� �����.

						isFound = true;
						break;
					}
					// 0�� �ƴ� �ٸ� �༮�� �߰��� �ִٸ� �̰� �ȵǴ� ���
					else if (board[k][j] != 0)
						break;

				}

				// �ƹ� �͵� ���ٸ�, �� �ø���.
				if (!isFound) {
					// i - 1���� 0�� �ƴ� �� ���� ������ �� �÷�
					int maxUp = i - 1;
					for (maxUp = i - 1; maxUp >= 0; maxUp--) {
						if (board[maxUp][j] != 0)
							break;
					}
					maxUp += 1;

					// �� �÷�
					board[maxUp][j] = board[i][j];

					// ���� �ִ� board[i][j]�� 0���� �����.
					if (maxUp != i)
						board[i][j] = 0;
				}
			}
		}
	}
}

void down() {
	// board�� ���ʷ� �ȴ´�
	for (int i = N-1; i >= 0; i--) {
		for (int j = N - 1; j >= 0; j--) {
			if (board[i][j] != 0) {
				// ���� ���� �Ⱦ���Ѵ�.
				// �׷��鼭 ���� �� �ִٸ�?
				bool isFound = false;
				for (int k = i - 1; k >= 0; k--) {
					// ���ٸ�, ��� ���� ���ľ� �Ѵ�.
					if (board[k][j] == board[i][j]) {

						// i + 1���� 0�� �ƴ� �� ���� ������ �� ����
						int maxUp = i + 1;
						for (maxUp = i + 1; maxUp < N; maxUp++) {
							if (board[maxUp][j] != 0)
								break;
						}
						maxUp -= 1;

						int val = board[i][j];

						board[i][j] = 0;
						board[k][j] = 0;

						// �� ��� �����
						board[maxUp][j] = val * 2;
						maxVal = std::max(maxVal, val * 2);

						// ���� �ִ� board[i][j], board[i][k]�� 0���� �����.

						isFound = true;
						break;
					}
					// 0�� �ƴ� �ٸ� �༮�� �߰��� �ִٸ� �̰� �ȵǴ� ���
					else if (board[k][j] != 0)
						break;

				}

				// �ƹ� �͵� ���ٸ�, �� �ø���.
				if (!isFound) {
					// i + 1���� 0�� �ƴ� �� ���� ������ �� ����
					int maxUp = i + 1;
					for (maxUp = i + 1; maxUp < N; maxUp++) {
						if (board[maxUp][j] != 0)
							break;
					}
					maxUp -= 1;

					// �� �÷�
					board[maxUp][j] = board[i][j];

					// ���� �ִ� board[i][j]�� 0���� �����.
					if (maxUp != i)
						board[i][j] = 0;
				}
			}
		}
	}
}

void left() {
	// board�� ���ʷ� �ȴ´�
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] != 0) {
				// ���� row�� �Ⱦ���Ѵ�.
				// �׷��鼭 ���� �� �ִٸ�?

				bool isFound = false;
				for (int k = j + 1; k < N; k++) {
					// ���ٸ�, ��� ���� ���ľ� �Ѵ�.
					if (board[i][k] == board[i][j]) {

						// j - 1���� 0�� �ƴ� �� ���� ������ �� ��������
						int maxUp = j - 1;
						for (maxUp = j - 1; maxUp >= 0; maxUp--) {
							if (board[i][maxUp] != 0)
								break;
						}
						maxUp += 1;

						int val = board[i][j];

						board[i][j] = 0;
						board[i][k] = 0;

						// �� ��� �����
						board[i][maxUp] = val * 2;
						maxVal = std::max(maxVal, val * 2);

						// ���� �ִ� board[i][j], board[i][k]�� 0���� �����.

						isFound = true;
						break;
					}
					// 0�� �ƴ� �ٸ� �༮�� �߰��� �ִٸ� �̰� �ȵǴ� ���
					else if (board[i][k] != 0)
						break;

				}

				// �ƹ� �͵� ���ٸ�, �� �ø���.
				if (!isFound) {
					// j - 1���� 0�� �ƴ� �� ���� ������ �� ��������
					int maxUp = j - 1;
					for (maxUp = j - 1; maxUp >= 0; maxUp--) {
						if (board[i][maxUp] != 0)
							break;
					}
					maxUp += 1;

					// �� �÷�
					board[i][maxUp] = board[i][j];

					// ���� �ִ� board[i][j]�� 0���� �����.
					if (maxUp != j)
						board[i][j] = 0;
				}
			}
		}
	}
}

void right() {
	// board�� ���ʷ� �ȴ´�
	for (int i = 0; i < N; i++) {
		for (int j = N-1; j >=0; j--) {
			if (board[i][j] != 0) {
				// ���� row�� �Ⱦ���Ѵ�.
				// �׷��鼭 ���� �� �ִٸ�?

				bool isFound = false;
				for (int k = j - 1; k >= 0; k--) {
					// ���ٸ�, ��� ���� ���ľ� �Ѵ�.
					if (board[i][k] == board[i][j]) {

						// j + 1���� 0�� �ƴ� �� ���� ������ �� ����������
						int maxUp = j + 1;
						for (maxUp = j + 1; maxUp < N; maxUp++) {
							if (board[i][maxUp] != 0)
								break;
						}
						maxUp -= 1;

						int val = board[i][j];

						board[i][j] = 0;
						board[i][k] = 0;

						// �� ��� �����
						board[i][maxUp] = val * 2;
						maxVal = std::max(maxVal, val * 2);

						// ���� �ִ� board[i][j], board[i][k]�� 0���� �����.

						isFound = true;
						break;
					}
					// 0�� �ƴ� �ٸ� �༮�� �߰��� �ִٸ� �̰� �ȵǴ� ���
					else if (board[i][k] != 0)
						break;

				}

				// �ƹ� �͵� ���ٸ�, �� �ø���.
				if (!isFound) {
					// j + 1���� 0�� �ƴ� �� ���� ������ �� ����������
					int maxUp = j + 1;
					for (maxUp = j + 1; maxUp < N; maxUp++) {
						if (board[i][maxUp] != 0)
							break;
					}
					maxUp -= 1;

					// �� �÷�
					board[i][maxUp] = board[i][j];

					// ���� �ִ� board[i][j]�� 0���� �����.
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

	// �켱 �ǵ��� ���� board �����ϰ� �ִ´�.
	int prevBoard[20][20] = { 0 };
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			prevBoard[i][j] = board[i][j];
		}
	}

	// 1. ���� �����δ�. board ��ü�� �����δ�.
	// 2. backtrack(k+1)
	// 3. �ǵ�����.

	up();
	backtrack(k + 1);
	
	// �ǵ�����
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = prevBoard[i][j];
		}
	}

	// �̹��� �Ʒ���
	down();
	backtrack(k + 1);

	// �ǵ�����
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = prevBoard[i][j];
		}
	}
	
	// �̹��� ������
	right();
	backtrack(k + 1);

	// �ǵ�����
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = prevBoard[i][j];
		}
	}

	// �̹��� ����.
	left();
	backtrack(k + 1);

	// �ǵ�����
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