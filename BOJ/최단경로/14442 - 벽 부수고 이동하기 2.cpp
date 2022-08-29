#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
const int INF = 987654321;

struct Info {
	int distance;
	int restChance;
	int r;
	int c;

	bool operator>(const Info& a) const {
		if (distance == a.distance) {
			if (restChance == a.restChance) {
				if (r == a.r) return c > a.c;
				return r > a.r;
			}
			return restChance > a.restChance;
		}
		return distance > a.distance;
	}
};

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1};

int N, M, K;
int board[1000][1000];
int dist[11][1000][1000];

int main() {
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%1d", &board[i][j]);
		}
	}
	for (int i = 0; i <= K; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < M; k++) {
				dist[i][j][k] = INF;
			}
		}
	}

	
	// 0,0에서 시작.
	priority_queue<Info, vector<Info>, greater<Info>> PQ;
	PQ.push({1, K, 0, 0 });
	dist[K][0][0] = 1;

	while (!PQ.empty()) {
		Info curr = PQ.top();
		PQ.pop();


		if (curr.r == N - 1 && curr.c == M - 1) {
			printf("%d\n", curr.distance);
			return 0;
		}

		for (int i = 0; i < 4; i++) {
			int nR = curr.r + dr[i];
			int nC = curr.c + dc[i];

			if (nR < 0 || nR >= N || nC < 0 || nC >= M) continue;
			if (board[nR][nC] == 0) {
				// 쓰지 않고 지나간다.
				if (dist[curr.restChance][nR][nC] > dist[curr.restChance][curr.r][curr.c] + 1) {
					dist[curr.restChance][nR][nC] = dist[curr.restChance][curr.r][curr.c] + 1;
					PQ.push({ dist[curr.restChance][nR][nC], curr.restChance, nR, nC });
				}
			}
			else if (curr.restChance > 0) {
				// 하나 쓰고 넘긴다.
				if (dist[curr.restChance-1][nR][nC] > dist[curr.restChance][curr.r][curr.c] + 1) {
					dist[curr.restChance-1][nR][nC] = dist[curr.restChance][curr.r][curr.c] + 1;
					PQ.push({ dist[curr.restChance-1][nR][nC], curr.restChance-1, nR, nC });
				}
			}
		}


	}



	printf("-1");


}