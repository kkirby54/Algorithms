#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>

const int INF = 1000000000;
struct Edge {
	int next, cost, time;
	Edge(int n, int c, int t) : next(n), cost(c), time(t) {}
};

int T, N, M, K, u, v, c, d;

std::vector<Edge> adj[100];

// M이하의 비용을 가지고, N-1에 도달한다.
int dp[100][10001];

int KCM(int curr, int money) {
	int& ret = dp[curr][money];
	if (ret != -1) return ret;
	if (curr == N - 1) return ret = 0;

	// money가 0 미만이 되면 안돼.
	ret = INF;
	for (auto& e : adj[curr]) {
		if (money - e.cost >= 0) {
			ret = std::min(ret, e.time + KCM(e.next, money - e.cost));
		}
	}
	return ret;

}

int main() {
	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		scanf("%d %d %d", &N, &M, &K);

		for (int i = 0; i < N; i++) {
			adj[i].clear();
		}

		for (int i = 0; i < K; i++) {
			scanf("%d %d %d %d", &u, &v, &c, &d);
			adj[u - 1].push_back(Edge(v-1, c, d));
		}

		memset(dp, -1, sizeof(dp));
		int ret = KCM(0, M);

		if (ret == INF) puts("Poor KCM");
		else printf("%d\n", ret);

	}

}