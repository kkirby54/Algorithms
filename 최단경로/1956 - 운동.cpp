#include <cstdio>
#include <algorithm>

const int INF = 1000000000;

int main() {
	int V, E, a, b, c;
	int dist[401][401];
	scanf("%d %d", &V, &E);
	
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++)
			dist[i][j] = INF;
	}

	for (int i = 0; i < E; i++) {
		scanf("%d %d %d", &a, &b, &c);
		dist[a - 1][b - 1] = c;
	}

	for (int k = 0; k < V; k++) {
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {
				dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}

	// i,j 를 오가는 사이클.
	// 그냥 dist[i][j] + dist[j][i] 확인하기.
	/*
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (i != j) {
				if (dist[i][j] + dist[j][i] < ret)
					ret = dist[i][j] + dist[j][i];
			}
		}
	}
	*/

	// 굳이 그렇게 안 해도,
	// dist[i][i]라는게, i에서 출발해서 i에서 돌아오는 최단경로.
	// 따라서 for문 한 번만 돌려서 가능.
	int ret = INF;

	for (int i = 0; i < V; i++) {
		ret = std::min(ret, dist[i][i]);
	}

	printf("%d", ret == INF ? -1 : ret);
}