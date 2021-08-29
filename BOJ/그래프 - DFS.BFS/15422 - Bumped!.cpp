#include <cstdio>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;
const long long INF = 1e18;
typedef pair<long long, long long> P;

int N, M, F, S, T, u, v, c;
long long dist[50000];
long long ret;
vector<P> adj[50000];

void dijkstra(int s) {
	fill(dist, dist + N, INF);
	priority_queue<P, vector<P>, greater<P>> PQ;
	PQ.push(P(0, S));
	dist[S] = 0;
	while (!PQ.empty()) {
		long long curr = PQ.top().second;
		PQ.pop();

		for (auto& E : adj[curr]) {
			long long next = E.first;
			long long cost = E.second;

			if (dist[next] > dist[curr] + cost) {
				dist[next] = dist[curr] + cost;
				PQ.push(P(dist[next], next));
			}
		}
	}

	ret = min(ret, dist[T]);
}

int main() {
	scanf("%d %d %d %d %d", &N, &M, &F, &S, &T);
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &u, &v, &c);
		adj[u].push_back(P(v, c));
		adj[v].push_back(P(u, c));
	}
	ret = INF;

	dijkstra(S);
	for (int i = 0; i < F; i++) {
		scanf("%d %d", &u, &v);
		adj[u].push_back(P(v, 0));

		dijkstra(S);

		adj[u].pop_back();
	}

	printf("%lld\n", ret);
}