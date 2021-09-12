#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int INF = 987654321;
typedef pair<int, int> P;

int C, V, M, N, a, b, c, ret;
int dist[200][200];

int main() {
	scanf("%d", &C);
	while (C--) {
		scanf("%d %d %d", &V, &M, &N);
		for (int i = 0; i < V; i++) {
			fill(dist[i], dist[i] + V, INF);
			dist[i][i] = 0;
		}

		for (int i = 0; i < M; i++) {
			scanf("%d %d %d", &a, &b, &c);

			dist[a][b] = dist[b][a] = min(dist[a][b], min(dist[b][a], c));
		}

		// 일단 플로이드로 현재 도로로 갈 수 있는 최단 거리 갱신.
		for (int k = 0; k < V; k++) {
			for (int i = 0; i < V; i++) {
				for (int j = 0; j < V; j++) {
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
				}
			}
		}

		ret = 0;
		for (int i = 0; i < N; i++) {
			scanf("%d %d %d", &a, &b, &c);

			// a->b를 c로 잇는다고 했을 때,
			// 의미가 있으려면
			// 기존에 존재하는 dist[a][b]가 c보다 커야 한다.

			// 여기에 더해서, a-b를 c로 잇고나면,
			// a-b를 경유하는 점들도 갱신을 해줘야 함.
			if (dist[a][b] > c) {
				dist[a][b] = dist[b][a] = c;

				// S - a - b - E일 수도,
				// S - b - a - E일 수도.

				for (int j = 0; j < V; j++) {
					for (int k = 0; k < V; k++) {
						if (dist[j][k] > dist[j][a] + c + dist[b][k])
							dist[j][k] = dist[k][j] = dist[j][a] + c + dist[b][k];

						if (dist[j][k] > dist[j][b] + c + dist[a][k])
							dist[j][k] = dist[k][j] = dist[j][b] + c + dist[a][k];
					}
				}
			}
			else ret++;
		}
		printf("%d\n", ret);
	}

}