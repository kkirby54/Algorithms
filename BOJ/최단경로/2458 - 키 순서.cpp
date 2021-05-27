#include <cstdio>
#include <algorithm>

const int INF = 100000000;
int dist[501][501];

int main() {
	int N, M,a,b;
	scanf("%d %d", &N, &M);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			dist[i][j] = INF;
		}
	}

	for (int i = 0; i < M; i++) {
		scanf("%d %d", &a,&b);
		dist[a - 1][b - 1] = 1;
	}

	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
	int ret = 0;

	for (int i = 0; i < N; i++) {
		bool possible = true;
		for (int j = 0; j < N; j++) {
			if (i != j && dist[i][j] == INF && dist[j][i] == INF) {
				possible = false;
				break;
			}
		}
		if (possible) {
			ret++;
		}
	}
	printf("%d", ret);
}