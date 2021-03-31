#include <cstdio>
#include <algorithm>

const int INF = 1000000000;

int main() {
	int N, M, A, B;
	int dist[101][101];
	scanf("%d %d", &N, &M);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			dist[i][j] = INF;
	}

	for (int i = 0; i < M; i++) {
		scanf("%d %d", &A, &B);
		dist[A - 1][B - 1] = 1;
		dist[B - 1][A - 1] = 1;
	}

	// 이제 1차적으로 연결된 관계 완료.

	// 플로이드-와샬로 연결 가능한 모든 사람 연결.
	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}

	std::pair<int, int> P(0, INF);

	for (int i = 0; i < N; i++) {
		int ret = 0;
		for (int j = 0; j < N; j++) {
			if (i != j) ret += dist[i][j];
		}
		if (ret < P.second) {
			P.first = i + 1;
			P.second = ret;
		}
	}

	printf("%d", P.first);

}