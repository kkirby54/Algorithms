#include <cstdio>
#include <vector>
#include <algorithm>

const int INF = 1000000000;
int dist[101][101];
int track[101][101];

int main() {
	int N, M, a, b, c;

	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		std::fill(dist[i], dist[i] + N+1, INF);
		std::fill(track[i], track[i] + N+1, INF);
	}

	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &a, &b, &c);
		if (dist[a][b] > c) {
			dist[a][b] = c;
			track[a][b] = b; // 한 번에 갈 수 있다.
		}
	}

	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				// 갱신이 된다면..
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];

					track[i][j] = track[i][k];
				}
			}
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (i == j) printf("0 ");
			else printf("%d ", dist[i][j] == INF ? 0 : dist[i][j]);
		}

		printf("\n");
	}
	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (i == j || dist[i][j] == INF) printf("0\n");
			else {
				// track 배열을 이용한다.
				// i에서 j까지 간다고 쳐봐.
				std::vector<int> ret;

				int k = i;
				ret.push_back(k);

				while (k != j && k != INF) {
					k = track[k][j];
					ret.push_back(k);
				}
				
				printf("%d ", ret.size());
				for (auto e: ret) {
					printf("%d ", e);
				}
				puts("");

			}
		}
	}


}

