﻿#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

const int INF = 1000000000;

int T, N, M, K, u, v, c, d;

struct Edge {
	int next, cost, time;
	Edge(int n, int c, int t) : next(n), cost(c), time(t) {}
};

// 소요시간을 기준으로 정렬하는 Operator
bool operator>(const Edge& a, const Edge& b) {
	if (a.time == b.time) return a.cost > b.cost;
	return a.time > b.time;
}

// 1부터 N까지.
// M 이하의 비용을 이용한다.
// 그래서.. 2차원 dist배열이 되는데,
// dist[0][0]에서 시작한다.
// 그래서 dist[N-1][]까지 도착한다.
// dist[N-1][x]에서 x가 M을 넘으면 실패.

int dist[101][10001];


int main() {
	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		scanf("%d %d %d", &N, &M, &K);

		std::vector<Edge> adj[100];

		for (int i = 0; i < K; i++) {
			scanf("%d %d %d %d", &u, &v, &c, &d);
			adj[u - 1].push_back(Edge(v - 1, c, d));
		}

		// dist 배열 초기화
		for (int i = 0; i < N; i++) {
			for (int j = 0; j <= M; j++)
				dist[i][j] = INF;
		}

		// 시작점은 dist[0][0]
		// 이제 여기서 dist[next][비용]으로 가야 한다.
		dist[0][0] = 0;

		// PQ 준비.
		std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> PQ;
		PQ.push(Edge(0, 0, 0));

		// 될 수 있는 후보들 저장할 벡터
		std::vector<int> Vec;

		while (!PQ.empty()) {
			int curr = PQ.top().next;
			int time = PQ.top().time;
			int cost = PQ.top().cost;
			PQ.pop();

			for (auto& e : adj[curr]) {
				int next = e.next;
				int n_time = e.time;
				int n_cost = e.cost;

				// 다음으로 가는 비용에 대한 시간
				// vs
				// 현재를 거쳐서 
				if (cost + n_cost <= M &&
					dist[next][cost + n_cost] >
					dist[curr][cost] + n_time)
				{
					dist[next][cost + n_cost] =
						dist[curr][cost] + n_time;

					if (next == N - 1 && dist[next][cost + n_cost] != INF)
						Vec.push_back(dist[next][cost + n_cost]);

					PQ.push(Edge(next, cost + n_cost, time + n_time));
				}
			}

		}

		// 이걸 다 하고 나면, dist[0][0]부터 시작해서 N-1번 공항까지 가는 최단소요시간이 저장되어있음.

		/*
		int ret = INF;
		for (int i = 0; i <= M; i++) {
			ret = std::min(ret, dist[N - 1][i]);
		}

		if (ret == INF) printf("Poor KCM\n");
		else printf("%d\n", ret);
		*/

		if (Vec.empty()) printf("Poor KCM\n");
		else {
			std::sort(Vec.begin(), Vec.end());
			printf("%d\n", Vec[0]);
		}

	}

}