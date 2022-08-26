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
	// 벽 3개를 세웠을 시
	if (cnt == 3) {

		// BFS 위한 visited와,
		// 임시로 활용한 board
		memset(visited, 0, sizeof(visited));
		int tmpBoard[8][8];

		// 여기서 bfs 돌려서 구한다.
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
		
		// 0의 개수 = 안전지대의 개수
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

	// 범위 초과 시 종료
	if (r < 0 || r >= N || c < 0 || c >= M) return;


	// 벽을 놓기 위해서는 지금이 0이어야 함.
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

	// 이번 꺼 안 쓰고 넘기는 케이스
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

	// 0이 된 곳에 3가지를 골라서 벽을 세워야 한다.
	// 최대 8*8 보드에, 최대 64 - 2(바이러스의 최소 개수) = 62개의 공백.
	// 62C3이므로 넉넉하게 들어오기 가능.
	backtrack(0, 0, 0);

	printf("%d\n", maxVal);
}