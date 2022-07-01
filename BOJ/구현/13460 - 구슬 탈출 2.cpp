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

// 수평으로 기울이기.
int horizon(int redR, int redC, int blueR, int blueC, int type) {

	int ret = 0;	

	// type이 1이면 오른쪽.
	// type이 -1이면 왼쪽 기울이기.
	bool redFirst = true;
	if (redR == blueR) {
		// 이러면 blue 먼저 움직인다.
		if (type == 1) {
			if (redC < blueC)
				redFirst = false;
		}
		// 왼쪽 기울일 때는
		else {
			if (redC > blueC) {
				redFirst = false;
			}
		}
	}

	// red 먼저 움직이기.
	if (redFirst) {
		// #을 만날 때까지 움직인다.
		while (board[redR][redC + type] != '#') {
			redC += type;

			// 움직였는데 O라면 빼내짐.
			if (board[redR][redC] == 'O') {
				ret = 1;
				break;
			}
		}

		// 이후에 blue 움직이기
		while (board[blueR][blueC + type] != '#'){
			// 같은 라인에 있으면서 움직이면 red가 되면 안됨.
			if (redR == blueR && (redC == blueC + type)) {
				// 구멍이었다면, blue가 빠져서 안됨.
				if (board[redR][redC] == 'O') {
					ret = -1;
				}

				break;
			}

			blueC += type;

			// 안되는 경우 처리
			if (board[blueR][blueC] == 'O') {
				ret = -1;
				break;
			}
		}
	}
	else {
		// blue 먼저 이동
		while (board[blueR][blueC + type] != '#') {
			blueC += type;

			if (board[blueR][blueC] == 'O') {
				ret = -1;
				break;
			}
		}

		// red 이동
		while (board[redR][redC + type] != '#') {
			if (redR == blueR && (blueC == redC + type)) {
				if (board[blueR][blueC] == 'O')
					ret = -1;

				break;
			}

			redC += type;

			// O면서, blue가 들어가지 않았다면 가능.
			if (board[redR][redC] == 'O' && ret != -1) {
				ret = 1;
				break;
			}
		}
	}

	// ret가 0이면, 큐에다가 넣어준다.
	if (ret == 0) {
		if (!visited[redR][redC][blueR][blueC]) {
			Q.push({ redR, redC, blueR, blueC });
			//printB(redR, redC, blueR, blueC);
		}
	}

	// 1이면 red만.
	// -1이면 blue 들어감.
	return ret;
}

int vertical(int redR, int redC, int blueR, int blueC, int type) {

	int ret = 0;

	// type이 1이면 아래.
	// type이 -1이면 위로 기울이기.
	bool redFirst = true;
	if (redC == blueC) {
		// 이러면 blue 먼저 움직인다.
		if (type == 1) {
			if (redR < blueR)
				redFirst = false;
		}
		// 위로 기울일 때
		else {
			if (redR > blueR) {
				redFirst = false;
			}
		}
	}

	// red 먼저 움직이기.
	if (redFirst) {
		// #을 만날 때까지 움직인다.
		while (board[redR + type][redC] != '#') {
			redR += type;

			// 그러다가 구멍 만나면 빼내짐.
			if (board[redR][redC] == 'O') {
				ret = 1;
				break;
			}
		}
		//printf("이동 후 red = %d %d\n", redR, redC);

		// 이후에 blue 움직이기
		while (board[blueR + type][blueC] != '#') {
			// 같은 라인에 있으면서 움직이면 red가 되면 안됨
			if (redC == blueC && (redR == blueR + type)) {
				// 구멍이었다면, blue가 빠져서 실패
				if (board[redR][redC] == 'O') {
					ret = -1;
				}

				break;
			}
			blueR += type;

			// 안되는 경우
			if (board[blueR][blueC] == 'O') {
				ret = -1;
				break;
			}
		}
	}
	else {
		// blue 먼저 이동
		while (board[blueR + type][blueC] != '#') {
			blueR += type;

			if (board[blueR][blueC] == 'O') {
				ret = -1;
				break;
			}
		}

		// red 이동
		while (board[redR + type][redC] != '#') {
			if (redC == blueC && (blueR == redR + type)) {
				if (board[blueR][blueC] == 'O')
					ret = -1;

				break;
			}

			redR += type;

			// O면서, blue가 들어가지 않았다면
			if (board[redR][redC] == 'O' && ret != -1) {
				ret = 1;
				break;
			}
		}
	}

	// ret가 0이면, 큐에다가 넣어줘야함.
	if (ret == 0) {
		if (!visited[redR][redC][blueR][blueC]) {
			Q.push({ redR, redC, blueR, blueC });
		}
	}

	// 1이면 red만.
	// -1이면 blue 들어감.
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

	// 여기서부터 기울여야 한다.
	// 큐에 넣고, 최대 10번 반복.

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

			// 이제 4방향으로 기울여본다.

			// 오른쪽 기울이기.
			int ret = horizon(redR, redC, blueR, blueC, 1);
			if (ret == 1) {
				printf("%d\n", cnt + 1);
				return 0;
			}

			// 왼쪽 기울이기
			ret = horizon(redR, redC, blueR, blueC, -1);
			if (ret == 1) {
				printf("%d\n", cnt + 1);
				return 0;
			}

			// 아래로
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