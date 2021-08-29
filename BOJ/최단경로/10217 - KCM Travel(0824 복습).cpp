#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int INF = 987654321;
typedef pair<long long, long long> P;

struct Edge {
	int v, cost, dist;
	Edge(int v, int cost, int dist) : v(v), cost(cost), dist(dist) {}
	bool operator>(const Edge& a) const{
		return dist > a.dist;
	}
};

int T, N, M, K, u,v,c,d;
vector<Edge> adj[101];
int dist[101][10001];
bool visited[101][10001];

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d", &N, &M, &K);

		for (int i = 0; i <= N; i++) {
			adj[i].clear();
			fill(dist[i], dist[i] + M + 1, INF);
			fill(visited[i], visited[i] + M + 1, false);
		}

		for (int i = 0; i < K; i++) {
			scanf("%d %d %d %d", &u, &v, &c, &d);
			adj[u].push_back(Edge(v, c, d));
		}

		// M원을 갖고 시작하다가. 그게 음수가 되면 안된다.
		priority_queue<Edge, vector<Edge>, greater<Edge>> PQ;
		PQ.push(Edge(1, M, 0));
		dist[1][M] = 0;

		while (!PQ.empty()) {
			int curr, rest;
			do {
				curr = PQ.top().v;
				rest = PQ.top().cost;
				PQ.pop();
			} while (!PQ.empty() && visited[curr][rest]);
			if (visited[curr][rest]) break;

			visited[curr][rest] = true;

			for (auto& E : adj[curr]) {
				int next = E.v, cost = E.cost, distance = E.dist;

				// 지금 쓸 수 있는 비용은 rest.
				// 만약, rest < cost면 못 써.

				if (rest >= cost) {
					// 이러면 rest - cost만큼 쓰고 넘겨.
					if (dist[next][rest - cost] > dist[curr][rest] + distance) {
						dist[next][rest - cost] = dist[curr][rest] + distance;
						PQ.push(Edge(next, rest - cost, dist[next][rest - cost]));
					}
				}

			}

		}
		int ret = INF;
		for (int i = 0; i <= M; i++) {
			ret = min(ret, dist[N][i]);
		}
		if (ret == INF) puts("Poor KCM");
		else printf("%d\n", ret);
	}

}