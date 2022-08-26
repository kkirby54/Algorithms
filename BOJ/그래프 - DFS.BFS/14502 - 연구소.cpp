#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int, int> P;

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0,0,-1,1 };

int N, M;
int board[8][8];
bool visited[8][8];

int maxVal;

void backtrack(int r, int c, int cnt) {
	// �� 3���� ������ ��
	if (cnt == 3) {

		// BFS ���� visited��,
		// �ӽ÷� Ȱ���� board
		memset(visited, 0, sizeof(visited));
		int tmpBoard[8][8];

		// ���⼭ bfs ������ ���Ѵ�.
		queue<P> Q;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				tmpBoard[i][j] = board[i][j];
				if (board[i][j] == 2) {
					Q.push(P(i, j));
					visited[i][j] = true;
				}
			}
		}

		while (!Q.empty()) {
			int cR = Q.front().first;
			int cC = Q.front().second;
			Q.pop();

			for (int i = 0; i < 4; i++) {
				int nR = cR + dr[i];
				int nC = cC + dc[i];

				if (nR < 0 || nR >= N || nC < 0 || nC >= M) continue;
				if (visited[nR][nC]) continue;
				if (tmpBoard[nR][nC] == 0) {
					tmpBoard[nR][nC] = 2;
					visited[nR][nC] = true;
					Q.push(P(nR, nC));
				}
			}
		}
		
		// 0�� ���� = ���������� ����
		int tmpCnt = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (tmpBoard[i][j] == 0) {
					tmpCnt++;
				}
			}
		}

		maxVal = std::max(maxVal, tmpCnt);

		return;
	}

	// ���� �ʰ� �� ����
	if (r < 0 || r >= N || c < 0 || c >= M) return;


	// ���� ���� ���ؼ��� ������ 0�̾�� ��.
	if (board[r][c] == 0) {
		board[r][c] = 1;
		if (c != M - 1) {
			backtrack(r, c + 1, cnt + 1);
		}
		else {
			backtrack(r + 1, 0, cnt + 1);
		}
		board[r][c] = 0;
	}

	// �̹� �� �� ���� �ѱ�� ���̽�
	if (c != M - 1) {
		backtrack(r, c + 1, cnt);
	}
	else {
		backtrack(r + 1, 0, cnt);
	}

}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &board[i][j]);
		}
	}

	// 0�� �� ���� 3������ ��� ���� ������ �Ѵ�.
	// �ִ� 8*8 ���忡, �ִ� 64 - 2(���̷����� �ּ� ����) = 62���� ����.
	// 62C3�̹Ƿ� �˳��ϰ� ������ ����.
	backtrack(0, 0, 0);

	printf("%d\n", maxVal);
}