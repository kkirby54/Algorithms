#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int INF = 987654321;
typedef pair<int, int> P;

int N, K, S, a,b;
vector<int> adj[400];
int dist[400][400];

int main() {
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++)
		fill(dist[i], dist[i] + N, INF);

	for (int i = 0; i < K; i++) {
		scanf("%d %d", &a, &b);
		a--; b--;
		adj[a].push_back(b);
		dist[a][b] = 1;
	}

	// 플로이드
	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				dist[i][j] = min(dist[i][j],
					dist[i][k] + dist[k][j]);
			}
		}
	}

	scanf("%d", &S);
	for (int i = 0; i < S; i++) {
		scanf("%d %d", &a, &b);
		a--; b--;
		// a->b또는 b->a 확인.
		if (dist[a][b] != INF) {
			puts("-1");
		}
		else if (dist[b][a] != INF) puts("1");
		else puts("0");

	}
	

}