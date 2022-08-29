#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
const int INF = 987654321;

struct Info {
	int restChance;
	int r;
	int c;
};

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

int N, M, K;
int board[1000][1000];
bool visited[11][1000][1000];

int main() {
	//freopen("test.txt", "r", stdin);
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%1d", &board[i][j]);
		}
	}

	// 0,0에서 시작.
	queue<Info> Q;
	Q.push({K, 0, 0 });
	visited[K][0][0] = true;
	int ans = 1;

	while (!Q.empty()) {
		int qSize = Q.size();
		while (qSize--) {
			Info curr = Q.front();
			Q.pop();

			if (curr.r == N - 1 && curr.c == M - 1) {
				printf("%d\n", ans);
				return 0;
			}

			for (int i = 0; i < 4; i++) {
				int nR = curr.r + dr[i];
				int nC = curr.c + dc[i];

				if (nR < 0 || nR >= N || nC < 0 || nC >= M) continue;
				if (board[nR][nC] == 0 && !visited[curr.restChance][nR][nC]) {
					// 쓰지 않고 지나간다.
					visited[curr.restChance][nR][nC] = true;
					Q.push({ curr.restChance, nR, nC });
				}
				else if (curr.restChance > 0 && !visited[curr.restChance - 1][nR][nC]) {

					// 낮이라면
					if (ans % 2 != 0) {
						visited[curr.restChance - 1][nR][nC] = true;
						Q.push({ curr.restChance - 1, nR, nC });
					}
					// 밤이라면
					else {
						Q.push({ curr.restChance, curr.r, curr.c});
					}

				}
			}
		}

		ans++;

	}



	printf("-1");


}