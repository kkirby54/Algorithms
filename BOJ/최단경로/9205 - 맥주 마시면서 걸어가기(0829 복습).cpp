#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
const int INF = 987654321;
typedef pair<int, int> P;

int T, N, x[103], y[103];
int dist[103][103];

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		
		for (int i = 0; i < N+2; i++) {
			scanf("%d %d", x + i, y + i);
			fill(dist[i], dist[i] + N+2, INF);
			dist[i][i] = 0;
		}

		for (int i = 0; i < N+2; i++) {
			for (int j = i+1; j < N+2; j++) {
				// i번째 점과 j번째 점을 잇는다.
				int distance = abs(x[i] - x[j]) + abs(y[i] - y[j]);
				if (distance <= 1000) {
					dist[i][j] = dist[j][i] = distance;
				}
			}
		}

		for (int k = 0; k < N+2; k++) {
			for (int i = 0; i < N+2; i++) {
				for (int j = 0; j < N+2; j++) {
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
				}
			}
		}

		int ret = dist[0][N + 1];
		if (ret == INF)puts("sad");
		else puts("happy");

	}

}