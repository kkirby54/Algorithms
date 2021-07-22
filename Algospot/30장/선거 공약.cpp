#include <cstdio>
#include <vector>
#include <algorithm>

const int INF = 987654321;
using namespace std;
typedef pair<int, int> P;

int C, V, M, N, a, b, c;
int dist[200][200];


int main() {
	scanf("%d", &C);
	for (int t = 0; t < C; t++) {
		// 정점 수 V, 이미 있는 도로 M, 새로 깔릴 N.
		scanf("%d %d %d", &V, &M, &N);
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++)
				if (i == j) dist[i][j] = 0;
				else dist[i][j] = INF;
		}

		for (int i = 0; i < M; i++) {
			scanf("%d %d %d", &a, &b, &c);
			if (dist[a][b] > c ||
				dist[b][a] > c) {
				dist[a][b] = c;
				dist[b][a] = c;
			}
		}

		// 일단 플로이드를 돌려
		for (int k = 0; k < V; k++) {
			for (int i = 0; i < V; i++) {
				for (int j = 0; j < V; j++) {
					dist[i][j] = dist[j][i] = min(dist[i][j],
						dist[i][k] + dist[k][j]);
				}
			}
		}

		// N개의 고속도로를 건설한다고 하자.
		// 그럼 건설할 의미가 있는 경우는?
		int ret = 0;

		for (int itr = 0; itr < N; itr++) {
			scanf("%d %d %d", &a, &b, &c);

			bool hasMeaning = false;
			for (int i = 0; i < V; i++) {
				for (int j = 0; j < V; j++) {
					if (dist[i][j] > dist[i][a] +
						c + dist[b][j]) {
						// 이러면 갱신이 된거임
						//printf("%d %d 갱신됨\n", i, j);

						dist[i][j] = dist[j][i] = dist[i][a] + c + dist[b][j];
						hasMeaning = true;
					}
				}
			}

			if (!hasMeaning) ret++;
		}

		printf("%d\n", ret);
	}

}