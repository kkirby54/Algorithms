#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

typedef pair<int, int> P;
int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };

struct Point {
	int r, c;
	bool hasGun;
	Point(int r, int c, bool hasGun = true) : r(r), c(c), hasGun(hasGun) {}
};

int N, M;
int board[1005][1005];
bool visited[1005][1005][2];

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%1d", &board[i][j]);
		}
	}
	// 0은 이동 가능. 1은 이동 불가. 하나는 부술 수 있음.
	queue<Point> Q;
	Q.push(Point(0, 0));
	visited[0][0][1] = true;
	int cnt = 1;
	bool isPossible = false;

	while (!Q.empty()) {
		int qSize = Q.size();
		for (int i = 0; i < qSize; i++) {
			int r = Q.front().r;
			int c = Q.front().c;
			bool hasGun = Q.front().hasGun;
			Q.pop();

			if (r == N - 1 && c == M - 1) {
				isPossible = true;
				break;
			}

			for (int j = 0; j < 4; j++) {
				int nR = r + dr[j];
				int nC = c + dc[j];

				if (nR < 0 || nR >= N || nC < 0 || nC >= M) continue;
				if (visited[nR][nC][hasGun]) continue;
				// 장애물 없다면
				if (board[nR][nC] == 0) {
					Q.push(Point(nR, nC, hasGun));
					visited[nR][nC][hasGun] = true;
				}
				else {
					if (hasGun) {
						Q.push(Point(nR, nC, false));
						visited[nR][nC][false] = true;
					}

				}
			}
		}
		cnt++;
		if (isPossible) break;
	}
	if (isPossible) printf("%d", cnt - 1);
	else printf("-1");

}