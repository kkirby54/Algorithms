#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

const long long INF = 1e18;

int N, M, K, u, v, t;
long long dist[10000][21];
typedef std::pair<long long, long long> P;
std::vector<P> adj[10001];

int main() {
	// 도시 N개
	// 도로 M개
	// 포장할 도로 K개

	// K개 이하의 도로를 포장해서,
	// 시간을 최소로 만들어야 한다.
	// 포장하면, 시간이 0이 된다.
	scanf("%d %d %d", &N, &M, &K);

	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &u, &v, &t);
		adj[u - 1].push_back(P(v - 1, t));
		adj[v - 1].push_back(P(u - 1, t));
	}

	// 그럼 시작 점 = 0, 남은 포장 도로 K개
	// (0, K)에서.. 답은 (N-1, x) x >= 0

	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= K; j++)
			dist[i][j] = INF;
	}

	dist[0][K] = 0;
	bool visited[10000][21] = { 0, };
	std::priority_queue<P, std::vector<P>, std::greater<P>> PQ;


	PQ.push(P(0, K*10000));

	while (!PQ.empty()) {
		int curr, k;
		do {
			curr = PQ.top().second % 10000;
			k = PQ.top().second / 10000;
			PQ.pop();
		} while (!PQ.empty() && visited[curr][k]);

		visited[curr][k] = true;

		for (auto& p : adj[curr]) {
			int next = p.first;
			long long time = p.second;

			if (k > 0 && dist[next][k - 1] > dist[curr][k] + 0) {
				dist[next][k - 1] = dist[curr][k];
				PQ.push(P(dist[next][k - 1], (k - 1) * 10000 + next));
			}

			if (dist[next][k] > dist[curr][k] + time) {
				dist[next][k] = dist[curr][k] + time;
				PQ.push(P(dist[next][k], k * 10000 + next));
			}
		}

	}

	long long ret = INF;
	for (int i = 0; i <= K; i++) {
		ret = std::min(ret, dist[N - 1][i]);
	}

	printf("%lld", ret);
}