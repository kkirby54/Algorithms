#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
const int INF = 987654321;
typedef pair<int, int> P;

vector<P> adj[101];
bool reachable[101][101];
int dist[101][101];

int C, V, W, a, b, d;

int bellmanFord(int src, int dest) {
	vector<int> upper(V, INF);
	upper[src] = 0;

	// V-1번 반복
	for (int itr = 0; itr < V - 1; itr++) {
		for (int curr = 0; curr < V; curr++) {
			for (auto E : adj[curr]) {
				int next = E.first, cost = E.second;

				upper[next] = min(upper[next], upper[curr] + cost);
			}
		}
	}

	// V번째 반복
	for (int curr = 0; curr < V; curr++) {
		for (auto E : adj[curr]) {
			int next = E.first, cost = E.second;

			// 갱신이 된다면, curr -> next를 잇는 사이클.
			if (upper[next] > upper[curr] + cost) {
				if (reachable[src][curr] && reachable[curr][dest])
					return -INF;
			}
		}
	}

	return upper[dest];
}

int main() {
	scanf("%d", &C);
	for (int t = 0; t < C; t++) {
		scanf("%d %d", &V, &W);

		memset(reachable, false, sizeof(reachable));
		for (int i = 0; i < V; i++) adj[i].clear();
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {
				if (i == j) dist[i][j] = 0;
				else dist[i][j] = INF;
			}
		}

		for (int i = 0; i < W; i++) {
			scanf("%d %d %d", &a, &b, &d);
			adj[a].push_back(P(b, d));
			reachable[a][b] = true;
			dist[a][b] = d;
		}

		// 플로이드
		for (int k = 0; k < V; k++) {
			for (int i = 0; i < V; i++) {
				for (int j = 0; j < V; j++) {
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
				}
			}
		}

		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {
				if (dist[i][j] < INF - 123456789) reachable[i][j] = true;
			}
		}

		if (!reachable[0][1]) {
			puts("UNREACHABLE");
		}
		else {
			int shortest = bellmanFord(0, 1);
			if (shortest == -INF) printf("INFINITY ");
			else printf("%d ", shortest);

			for (int i = 0; i < V; i++) {
				for (auto& E : adj[i]) {
					E.second *= -1;
				}
			}

			int longest = bellmanFord(0, 1);
			if (longest == -INF) printf("INFINITY\n");
			else printf("%d\n", -longest);

		}



	}
	
}