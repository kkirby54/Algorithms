#include <cstdio>
#include <algorithm>

const int INF = 1000000000;

int main() {
	int N, K, s, a, b;
	int dist[401][401];
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			dist[i][j] = INF;
	}

	for (int i = 0; i < K; i++) {
		scanf("%d %d", &a, &b);
		dist[a - 1][b - 1] = 1; // dist[a][b]는.. a가 b 앞에 왔으니까 1
	}

	// 플로이드 와샬
	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
		}
	}

	scanf("%d", &s);
	for (int i = 0; i < s; i++) {
		scanf("%d %d", &a, &b);
		// dist[a-1][b-1]를 보고 판단한다.
		if (dist[a - 1][b - 1] != INF) printf("-1\n");
		else {
			if (dist[b - 1][a - 1] == INF) printf("0\n");
			else {
				printf("1\n");
			}
		}

	}


}