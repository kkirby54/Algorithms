#include <cstdio>
#include <algorithm>
const int INF = 987654321;

int N, M;
char board[21][21];
int c_x[2], c_y[2], cnt;

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

int ret = INF;


bool process(int r1, int c1, int r2, int c2) {
	if (0 <= r1 && r1 < N && 0 <= c1 && c1 < M) {
		if (0 <= r2 && r2 < N && 0 <= c2 && c2 < M)
			return true;
	}
	return false;
}

bool canGo(int r, int c) {
	if (r < 0 || r >= N || c < 0 || c >= M) return true;
	return board[r][c] != '#';
}

void backtrack(int cnt) {
	// 10 초과시 X
	if (cnt >= 10) {
		return;
	}

	for (int i = 0; i < 4; i++) {

		int origin_r1 = c_x[0];
		int origin_r2 = c_x[1];
		int origin_c1 = c_y[0];
		int origin_c2 = c_y[1];

		if (canGo(c_x[0] + dr[i], c_y[0] + dc[i])) {
			c_x[0] += dr[i];
			c_y[0] += dc[i];
		}
		if (canGo(c_x[1] + dr[i], c_y[1] + dc[i])) {
			c_x[1] += dr[i];
			c_y[1] += dc[i];
		}
		
		// 이렇게 움직여서,
		// 진행 중인지 판단해야 한다.
		if (process(c_x[0], c_y[0], c_x[1], c_y[1])) {
			backtrack(cnt + 1);
		}
		else {
			// 둘 다 빠졌으면 실패
			bool isFail = false;
			if (c_x[0] < 0 || c_x[0] >= N || c_y[0] < 0 || c_y[0] >= M) {
				if (c_x[1] < 0 || c_x[1] >= N || c_y[1] < 0 || c_y[1] >= M) {
					isFail = true;
				}
			}

			if (!isFail) {
				ret = std::min(ret, cnt + 1);
			}
		}

		c_x[0] = origin_r1;
		c_y[0] = origin_c1;
		
		
		c_x[1] = origin_r2;
		c_y[1] = origin_c2;

	}

}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		scanf("%s", board[i]);
		for (int j = 0; j < M; j++) {
			if (board[i][j] == 'o') {
				c_x[cnt] = i;
				c_y[cnt] = j;
				cnt++;
			}
		}
	}

	backtrack(0);
	printf("%d\n", ret == INF ? -1 : ret);

}