#include <cstdio>
#include <algorithm>

int C, H, W;
char tmp[21];
int board[21][21];

const int coverType[4][3][2] = {
	{ {0,0}, {1,0}, {0, 1} },
	{ {0,0}, {0, 1}, {1,1} },
	{ {0,0 }, {1,0}, {1,1} },
	{ {0,0 }, {1,0}, {1, -1}}
};

bool set(int r, int c, int index, int delta) {
	// 덮을 수 있는지 없는지.
	int R, C;
	bool isPossible = true;

	for (int i = 0; i < 3; i++) {
		R = r + coverType[index][i][0];
		C = c + coverType[index][i][1];

		if (R < 0 || R >= H || C < 0 || C >= W) {
			isPossible = false;
		}
		else if ((board[R][C] += delta) > 1)
			isPossible = false;

	}

	return isPossible;
}

// 제일 위에서부터 덮는다고 가정하자.
// 남은 블록
int cover(int rest) {
	if (rest == 0) return 1;

	int cur_r = -1, cur_c = -1;

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (board[i][j] == 0) {
				cur_r = i, cur_c = j;
				break;
			}
		}
		if (cur_r != -1) break;
	}

	int ret = 0;

	// 현재 처리해야 할 블록의 좌표를 알았다.
	// 그러면 덮어봐. 어떻게? 4가지 방법으로.
	for (int i = 0; i < 4; i ++) {
		// 덮을 수 있다면
		if (set(cur_r, cur_c, i, 1)) {
			ret += cover(rest - 1);
		}

		// 돌려놔
		set(cur_r, cur_c, i, -1);
	}
	
	return ret;
}

int main() {
	scanf("%d", &C);
	for (int t = 0; t < C; t++) {
		scanf("%d %d", &H, &W);
		int cnt = 0;
		int N;

		for (int i = 0; i < H; i++) {
			scanf("%s", tmp);
			for (int j = 0; j < W; j++) {
				if (tmp[j] == '.') {
					board[i][j] = 0;
					cnt++;
				}
				else board[i][j] = 1;
			}
		}

		if (cnt % 3 != 0) {
			printf("0\n");
			continue;
		} 
		else N = cnt / 3;

		//printf("총 : %d개\n", N);

		// N개의 블록을 이용해 덮어야한다.
		printf("%d\n", cover(N));


	}

}