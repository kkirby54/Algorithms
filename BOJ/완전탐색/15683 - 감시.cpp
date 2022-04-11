#include <cstdio>
#include <algorithm>
#include <cstring>

int N, M, board[8][8];
int numOfCctvs;
int cctvDirections[6];
bool visited[8][8];

int ret = 987654321;
int currCctvs = 0;

int dr[] = { 0, -1, 0, 1 };
int dc[] = { 1, 0, -1, 0 };

void fill(int r, int c, int type, int val) {

	int cctv = board[r][c];
	
	// 끝에 도달하거나, 6을 만나면 종료.
	// 1,2,3,4,5(즉 cctv)를 만나면 그냥 continue.

	int orders[] = { 0, 2, 1, 3 };

	for (int k = 0; k < 4; k++) {
		if (cctv == 1 && k == 1) return;
		if (cctv == 3 && k == 1) continue;
		if (cctv == 2 && k == 2) return;

		if (cctv != 5 && k == 3) return;

		int i = 1;
		while (1) {
			int nR = r + dr[(type + orders[k]) % 4] * i;
			int nC = c + dc[(type + orders[k]) % 4] * i;

			if (nR < 0 || nR >= N || nC < 0 || nC >= M) break;
			if (board[nR][nC] == 6) break;
			if (1 <= board[nR][nC] && board[nR][nC] <= 5) {
				i++;
				continue;
			}

			if (val == -1)
				board[nR][nC]--;
			else board[nR][nC]++;

			i++;
		}


	}
	
}

void dfs(int r, int c) {
	// 종료 조건
	if (currCctvs == numOfCctvs) {
		int cnt = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (board[i][j] == 0) cnt++;
			}
		}
		ret = std::min(ret, cnt);

		return;
	}

	for (int i = r; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j] <= 0 || board[i][j] == 6) continue;

			if (visited[i][j]) continue;

			int cctv = board[i][j];


			for (int k = 0; k < 4; k++) {
				if (cctv == 5 && k == 1) break;
				if (cctv == 2 && k == 2) break;

				cctvDirections[cctv] = k;
				fill(i, j, k, -1);

				visited[i][j] = true;
				currCctvs++;
				dfs(i, j);
				currCctvs--;
				visited[i][j] = false;

				fill(i, j, k, 0);

			}
		}
	}



}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &board[i][j]);
			if (board[i][j] != 0 && board[i][j] != 6)
				numOfCctvs++;
		}
	}

	// 지나간 건 -1로 한다.
	// 벽은 6.
	// 1,2,3,4,5가 CCTV.

	dfs(0, 0);
	printf("%d", ret);

}