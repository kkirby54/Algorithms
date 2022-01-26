#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

int dr[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dc[] = { -1, 0,1,-1,1,-1,0,1 };

struct Point {
	int r, c, mineCount;
	Point(int r = 0, int c = 0, int mineCount = 0) : r(r), c(c), mineCount(mineCount) {}

	bool operator<(const Point& a) const {
		return mineCount < a.mineCount;
	}
};

int T, N, ret;
char board[301][301];
bool visited[301][301];
std::priority_queue <Point, std::vector<Point>> PQ;

int getBlankCount(int r, int c) {
	if (board[r][c] == '*') return -1;
	int blank = 0;
	for (int i = 0; i < 8; i++) {
		int nR = r + dr[i];
		int nC = c + dc[i];

		if (nR < 0 || nR >= N || nC < 0 || nC >= N) continue;
		if (board[nR][nC] == '*') return -1;
		if (board[nR][nC] == '.')
			blank++;
	}

	return blank;
}

void dfs(int r, int c) {
	visited[r][c] = true;
	//printf("%d %d 방문\n", r, c);

	if (getBlankCount(r, c) == -1) return;

	for (int i = 0; i < 8; i++) {
		int nR = r + dr[i];
		int nC = c + dc[i];

		if (nR < 0 || nR >= N || nC < 0 || nC >= N) continue;
		if (visited[nR][nC]) continue;
		if (board[nR][nC] == '*') continue;
		dfs(nR, nC);
	}
}

int main() {
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%s", board[i]);
		}
		memset(visited, 0, sizeof(visited));
		ret = 0;

		// 주위에 지뢰가 몇개 있는지 세줘야한다 일단은
		// 그래서 작은 지뢰들부터 빼줘야한다고.
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (board[i][j] == '*') continue;
				int ret = getBlankCount(i, j);
				if (ret == -1) continue;

				PQ.push(Point(i, j, ret));
			}
		}

		while (!PQ.empty()) {
			int currR = PQ.top().r;
			int currC = PQ.top().c;
			int mineCount = PQ.top().mineCount;
			PQ.pop();

			if (visited[currR][currC]) continue;
			// 이전에 실행한걸로 인해 바뀌었을 수도 있어서,
			// 다시 한번 구해준다.
			if (mineCount !=
				getBlankCount(currR, currC)) {
				PQ.push(Point(currR, currC, getBlankCount(currR, currC)));
			}
			else {
				// 여기서 dfs를 돌린다.
				ret++;
				dfs(currR, currC);
			}
		}

		// 짜바리들 처리
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (visited[i][j] || board[i][j] == '*')  continue;
				ret++;
			}
		}

		printf("#%d %d\n", t, ret);
	}
}