#include <cstdio>
#include <algorithm>
#include <cmath>

const int INF = 1000000000;

int main() {
	int T, N, r, c;
	int dist[102][102];
	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		scanf("%d", &N);
		int x[102], y[102];

		for (int i = 0; i < N + 2; i++) {
			scanf("%d %d", &x[i], &y[i]);
		}

		for (int i = 0; i < N + 2; i++) {
			for (int j = 0; j < N + 2; j++) {
				int x_dis = (int) abs(x[i] - x[j]);
				int y_dis = (int) abs(y[i] - y[j]);

				if (x_dis + y_dis > 1000) dist[i][j] = INF;
				else dist[i][j] = 1;
			}
		}

		// 플로이드 와샬
		for (int k = 0; k < N+2; k++) {
			for (int i = 0; i < N + 2; i++) {
				for (int j = 0; j < N + 2; j++)
					if (dist[i][k] != INF && dist[k][j] != INF) dist[i][j] = 1;
			}
		}

		if (dist[0][N + 1] == INF && dist[N + 1][0] == INF) {
			printf("sad\n");
		}
		else printf("happy\n");

		// x[0] y[0]이 출발.
		// x[N+1], y[N+1]이 도착지점.

		// 그걸 N개의 편의점을 이용해서 갈 수 있냐?



	}

}