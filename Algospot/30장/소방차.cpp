#include <cstdio>
#include <algorithm>
#include <queue>
#include <cmath>
#include <vector>

using namespace std;
const int INF = 987654321;

int C, V, E, n, m, a, b, t;
typedef pair<int, int> P;

vector<P> adj[1001];
int locateState[1001]; // 0이면 머글, 1이면 화재, 2면 소방서
int dist[1001];
int ret[1001];

int main() {
	scanf("%d", &C);

	for (int tc = 0; tc < C; tc++) {
		scanf("%d %d %d %d", &V, &E, &n, &m);

		for (int i = 1; i <= V; i++)
			adj[i].clear();

		fill(ret, ret + V + 1, INF);
		fill(locateState, locateState + V + 1, 0);
		fill(dist, dist + V + 1, INF);
		// 도로를 잇기
		for (int i = 0; i < E; i++) {
			scanf("%d %d %d", &a, &b, &t);

			adj[a].push_back(P(b, t));
			adj[b].push_back(P(a, t));
		}


		// 화재
		for (int i = 0; i < n; i++) {
			scanf("%d", &a);
			locateState[a] = 1;
		}
		// 소방서 위치
		// Try 2. 애초에 다 넣고 시작한다.

		priority_queue<P, vector<P>, greater<P>> Q;

		for (int i = 0; i < m; i++) {
			scanf("%d", &a);
			locateState[a] = 2;
			Q.push(P(0, a));
			dist[a] = 0;
		}
		while (!Q.empty()) {
			int curr = Q.top().second;
			Q.pop();

			for (auto E : adj[curr]) {
				int next = E.first;
				int d = E.second;

				if (dist[next] > dist[curr] + d) {
					dist[next] = dist[curr] + d;
					Q.push(P(dist[next], next));

					// 여기서 처리해
					if (locateState[next] == 1)
						ret[next] = min(ret[next], dist[next]);

				}
			}
		}
		int ans = 0;
		for (int i = 1; i <= V; i++) {
			if (locateState[i] == 1) {
				ans += ret[i];
			}

		}
		printf("%d\n", ans);

	}

}