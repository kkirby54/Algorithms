#include <cstdio>
#include <vector>
#include <queue>

int N, M;

int board[505][505];
int maxVal = -1;

int tetro[4][3][3] = {
	{
	{1, 1, 0},
	{1, 1, 0},
	{0, 0, 0}
	},
	{
		{1, 0, 0},
		{1, 0, 0},
		{1, 1, 0}
	},
	{
		{1, 0, 0},
		{1, 1, 0},
		{0, 1, 0}
	},
	{
		{1, 1, 1},
		{0, 1, 0},
		{0, 0, 0}
	}

};

// y축 대칭
void yTrans(int type) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 1; j++) {
			int tmp = tetro[type][i][j];
			tetro[type][i][j] = tetro[type][i][2 - j];
			tetro[type][i][2 - j] = tmp;
			
		}
	}
}

void xTrans(int type) {
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 3; j++) {
			int tmp = tetro[type][i][j];
			tetro[type][i][j] = tetro[type][2 -i][j];
			tetro[type][2 - i][j] = tmp;
		}
	}
}

void rRotate(int type) {
	int tmpArr[10][10] = { 0 };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			//printf("(%d,%d) -> (%d,%d)\n", i, j, 2 - j, i);
			tmpArr[i][j] = tetro[type][2 - j][i];
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			tetro[type][i][j] = tmpArr[i][j];
		}
	}
}


int checkFunc(int type, int r, int c) {
	// (r,c)를 기준으로 tetro 놓아본다.

	int sum = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			// 이럼 아예 못 놓는 경우
			if (r + i < 0 || r + i > N + 2 || c + j < 0 || c + j > M + 2) return -1;
			
			// tetro를 봤는데 1이라면 점수 획득
			if (tetro[type][i][j] == 1) {
				sum += board[r + i][c + j];
			}
		}
	}

	return sum;
}

void getMax(int type) {
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= M; j++) {
			// (i,j)가 기준이다.
			// 여기서부터 tetro 기준.
			// checkfunc을 만든다.

			int ret = checkFunc(type, i, j);
			if (ret > maxVal) {
				maxVal = ret;
			}
		}
	}


}

int main() {
	scanf("%d %d", &N, &M);

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			scanf("%d", &board[i][j]);
		}
	}

	// 그냥 수평은 따로 처리.
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= M; j++) {
			int sum = 0;
			// i,j 기준
			for (int k = j; k < j + 4; k++) {
				if (k > M + 2) break;

				sum += board[i][k];
			}
			if (sum > maxVal) {
				maxVal = sum;
				//printf("%d,%d에서 최대%d\n", i, j, maxVal);
			}
		}
	}
	// 그냥 수평은 따로 처리.
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= M; j++) {
			int sum = 0;
			// i,j 기준
			for (int k = i; k < i + 4; k++) {
				if (k > N + 2) break;

				sum += board[k][j];
			}
			if (sum > maxVal) {
				maxVal = sum;
				//printf("%d,%d에서 최대%d\n", i, j, maxVal);
			}
		}
	}


	getMax(0);

	// 100
	// 100
	// 110
	getMax(1);
	xTrans(1);
	getMax(1);
	yTrans(1);
	getMax(1);
	xTrans(1);
	getMax(1);
	yTrans(1);
	rRotate(1);
	getMax(1);
	xTrans(1);
	getMax(1);
	yTrans(1);
	getMax(1);
	xTrans(1);
	getMax(1);


	getMax(2);
	xTrans(2);
	getMax(2);
	rRotate(2);
	getMax(2);
	yTrans(2);
	getMax(2);

	
	getMax(3);
	xTrans(3);
	getMax(3);
	rRotate(3);
	getMax(3);
	yTrans(3);
	getMax(3);

	printf("%d\n", maxVal);
	



}