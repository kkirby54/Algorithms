#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
const int INF = 987654321;
typedef pair<int, int> P;

int N, M, u, v, b, k, s,e, ret;
vector<int> adj[300];
int dist[300][300];

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		fill(dist[i], dist[i] + N, INF);
		dist[i][i] = 0;
	}

	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &u, &v, &b);
		u--; v--;
		// a->b
		dist[u][v] = 0;
		if (b == 1) dist[v][u] = 0;
		else dist[v][u] = 1;
	}

	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}

	scanf("%d", &k);
	for (int i = 0; i < k; i++) {
		scanf("%d %d", &s, &e);
		s--; e--;

		printf("%d\n", dist[s][e]);
	}
	
}