#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int C, H, W, ret;
char board[21][21];

int dr[4][2] = { {1,0}, {0,1}, {1,1}, {1,1} };
int dc[4][2] = { {0,1}, {1,1}, {0,1}, {0,-1} };

void cover() {
	int r = -1, c = -1;
	// 가장 왼쪽 위에 있는 좌표 고른다.
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (board[i][j] == '.') {
				r = i, c = j;
				break;
			}
		}
		if (r != -1) break;
	}
	// r이 -1이라면 다 채워진 경우임.
	if (r == -1) {
		ret++; return;
	}

	//printf("r = %d, c = %d에서 작업 중\n", r, c);
	// 4가지 케이스를 다 본다.
	for (int i = 0; i < 4; i++) {
		int nR1 = r + dr[i][0];
		int nR2 = r + dr[i][1];
		int nC1 = c + dc[i][0];
		int nC2 = c + dc[i][1];

		// 이제 (n,r), (nR1, nC1), (nR2, nC2)
		// 얘네가 다 .이어야지 할 수가 있음.
		if (nR1 < 0 || nR1 >= H || nR2 < 0 || nR2 >= H) continue;
		if (nC1 < 0 || nC1 >= W || nC2 < 0 || nC2 >= W) continue;

		if (board[nR1][nC1] == '.' &&
			board[nR2][nC2] == '.') {
			board[r][c] = board[nR1][nC1] = board[nR2][nC2] = '#';
			//printf("(%d,%d)에서 일단 처리: type=%d\n", r, c, i);
			cover();
			board[r][c] = board[nR1][nC1] = board[nR2][nC2] = '.';
		}

	}

}


int main() {
	scanf("%d", &C);
	for (int t = 0; t < C; t++) {
		scanf("%d %d", &H, &W);
		ret = 0;

		for (int i = 0; i < H; i++)
			scanf("%s", board[i]);

		cover();
		printf("%d\n", ret);

	}

}