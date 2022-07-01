#include <cstdio>
#include <queue>
#include <vector>
typedef std::pair<int, int> P;

int N, M;
char board[11][11];
bool visited[11][11][11][11] = { 0 };

struct Pos {
	int redR, redC, blueR, blueC;
};

int redR, redC, blueR, blueC;
std::queue <Pos> Q;

// �������� ����̱�.
int horizon(int redR, int redC, int blueR, int blueC, int type) {

	int ret = 0;	

	// type�� 1�̸� ������.
	// type�� -1�̸� ���� ����̱�.
	bool redFirst = true;
	if (redR == blueR) {
		// �̷��� blue ���� �����δ�.
		if (type == 1) {
			if (redC < blueC)
				redFirst = false;
		}
		// ���� ����� ����
		else {
			if (redC > blueC) {
				redFirst = false;
			}
		}
	}

	// red ���� �����̱�.
	if (redFirst) {
		// #�� ���� ������ �����δ�.
		while (board[redR][redC + type] != '#') {
			redC += type;

			// �������µ� O��� ������.
			if (board[redR][redC] == 'O') {
				ret = 1;
				break;
			}
		}

		// ���Ŀ� blue �����̱�
		while (board[blueR][blueC + type] != '#'){
			// ���� ���ο� �����鼭 �����̸� red�� �Ǹ� �ȵ�.
			if (redR == blueR && (redC == blueC + type)) {
				// �����̾��ٸ�, blue�� ������ �ȵ�.
				if (board[redR][redC] == 'O') {
					ret = -1;
				}

				break;
			}

			blueC += type;

			// �ȵǴ� ��� ó��
			if (board[blueR][blueC] == 'O') {
				ret = -1;
				break;
			}
		}
	}
	else {
		// blue ���� �̵�
		while (board[blueR][blueC + type] != '#') {
			blueC += type;

			if (board[blueR][blueC] == 'O') {
				ret = -1;
				break;
			}
		}

		// red �̵�
		while (board[redR][redC + type] != '#') {
			if (redR == blueR && (blueC == redC + type)) {
				if (board[blueR][blueC] == 'O')
					ret = -1;

				break;
			}

			redC += type;

			// O�鼭, blue�� ���� �ʾҴٸ� ����.
			if (board[redR][redC] == 'O' && ret != -1) {
				ret = 1;
				break;
			}
		}
	}

	// ret�� 0�̸�, ť���ٰ� �־��ش�.
	if (ret == 0) {
		if (!visited[redR][redC][blueR][blueC]) {
			Q.push({ redR, redC, blueR, blueC });
			//printB(redR, redC, blueR, blueC);
		}
	}

	// 1�̸� red��.
	// -1�̸� blue ��.
	return ret;
}

int vertical(int redR, int redC, int blueR, int blueC, int type) {

	int ret = 0;

	// type�� 1�̸� �Ʒ�.
	// type�� -1�̸� ���� ����̱�.
	bool redFirst = true;
	if (redC == blueC) {
		// �̷��� blue ���� �����δ�.
		if (type == 1) {
			if (redR < blueR)
				redFirst = false;
		}
		// ���� ����� ��
		else {
			if (redR > blueR) {
				redFirst = false;
			}
		}
	}

	// red ���� �����̱�.
	if (redFirst) {
		// #�� ���� ������ �����δ�.
		while (board[redR + type][redC] != '#') {
			redR += type;

			// �׷��ٰ� ���� ������ ������.
			if (board[redR][redC] == 'O') {
				ret = 1;
				break;
			}
		}
		//printf("�̵� �� red = %d %d\n", redR, redC);

		// ���Ŀ� blue �����̱�
		while (board[blueR + type][blueC] != '#') {
			// ���� ���ο� �����鼭 �����̸� red�� �Ǹ� �ȵ�
			if (redC == blueC && (redR == blueR + type)) {
				// �����̾��ٸ�, blue�� ������ ����
				if (board[redR][redC] == 'O') {
					ret = -1;
				}

				break;
			}
			blueR += type;

			// �ȵǴ� ���
			if (board[blueR][blueC] == 'O') {
				ret = -1;
				break;
			}
		}
	}
	else {
		// blue ���� �̵�
		while (board[blueR + type][blueC] != '#') {
			blueR += type;

			if (board[blueR][blueC] == 'O') {
				ret = -1;
				break;
			}
		}

		// red �̵�
		while (board[redR + type][redC] != '#') {
			if (redC == blueC && (blueR == redR + type)) {
				if (board[blueR][blueC] == 'O')
					ret = -1;

				break;
			}

			redR += type;

			// O�鼭, blue�� ���� �ʾҴٸ�
			if (board[redR][redC] == 'O' && ret != -1) {
				ret = 1;
				break;
			}
		}
	}

	// ret�� 0�̸�, ť���ٰ� �־������.
	if (ret == 0) {
		if (!visited[redR][redC][blueR][blueC]) {
			Q.push({ redR, redC, blueR, blueC });
		}
	}

	// 1�̸� red��.
	// -1�̸� blue ��.
	return ret;
}

int main() {
	scanf("%d %d", &N, &M);

	for (int i = 0; i < N; i++) {
		scanf("%s", board[i]);

		for (int j = 0; j < M; j++) {
			if (board[i][j] == 'B') {
				blueR = i;
				blueC = j;
				board[i][j] = '.';
			}
			else if (board[i][j] == 'R') {
				redR = i;
				redC = j;
				board[i][j] = '.';
			}
		}

	}

	// ���⼭���� ��￩�� �Ѵ�.
	// ť�� �ְ�, �ִ� 10�� �ݺ�.

	Q.push({ redR, redC, blueR, blueC });

	for (int cnt = 0; cnt < 10; cnt++) {
		int qSize = Q.size();
		for (int i = 0; i < qSize; i++) {
			int redR = Q.front().redR;
			int redC = Q.front().redC;
			int blueR = Q.front().blueR;
			int blueC = Q.front().blueC;
			Q.pop();

			visited[redR][redC][blueR][blueC] = true;

			// ���� 4�������� ��￩����.

			// ������ ����̱�.
			int ret = horizon(redR, redC, blueR, blueC, 1);
			if (ret == 1) {
				printf("%d\n", cnt + 1);
				return 0;
			}

			// ���� ����̱�
			ret = horizon(redR, redC, blueR, blueC, -1);
			if (ret == 1) {
				printf("%d\n", cnt + 1);
				return 0;
			}

			// �Ʒ���
			ret = vertical(redR, redC, blueR, blueC, 1);
			if (ret == 1) {
				printf("%d\n", cnt + 1);
				return 0;
			}

			ret = vertical(redR, redC, blueR, blueC, -1);
			if (ret == 1) {
				printf("%d\n", cnt + 1);
				return 0;
			}
		}
	}

	printf("-1");

}