#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const long long INF = 1e18;
typedef pair<long long, long long> P;

struct Vertex {
	int v;
	long long cost;
	int k;

	Vertex(int v, long long cost, int k) : v(v), cost(cost), k(k) {}
	bool operator>(const Vertex& a) const {
		return cost > a.cost;
	}
};

int N, M, K, u, v, c;
vector<P> adj[10001];
long long dist[10001][21];
bool visited[10001][21];

int main() {
	scanf("%d %d %d", &N, &M, &K);

	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &u, &v, &c);
		adj[u].push_back(P(v, c));
		adj[v].push_back(P(u, c));
	}

	for (int i = 1; i <= N; i++) {
		fill(dist[i], dist[i] + K+1, INF);
		fill(visited[i], visited[i] + K + 1, false);
	}

	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> PQ;
	PQ.push(Vertex(1, 0, K));
	dist[1][K] = 0;

	while (!PQ.empty()) {
		int curr,rest;
		do {
			curr = PQ.top().v;
			rest = PQ.top().k;
			PQ.pop();
		} while (!PQ.empty() && visited[curr][rest]);
		if (visited[curr][rest]) break;
		
		visited[curr][rest] = true;

		for (auto& E : adj[curr]) {
			int next = E.first;
			long long cost = E.second;

			// rest를 하나 쓸 수도, 안 쓸 수도 있다.
			// 안쓰고 그냥 넘기는 경우.
			if (dist[next][rest] > dist[curr][rest] + cost) {
				dist[next][rest] = dist[curr][rest] + cost;
				PQ.push(Vertex(next, dist[next][rest], rest));
			}
			// 쓰고 넘길 수도 있다. 
			if (rest > 0) {
				if (dist[next][rest - 1] > dist[curr][rest]) {
					dist[next][rest - 1] = dist[curr][rest];
					PQ.push(Vertex(next, dist[next][rest - 1], rest - 1));
				}
			}
		}

	}
	long long ret = INF;
	for (int i = 0; i <= K; i++) {
		ret = min(ret, dist[N][i]);
	}
	printf("%lld\n", ret);
}