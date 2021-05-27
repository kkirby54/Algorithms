#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
const int INF = 1000000000;
typedef std::pair<int, int> P;

// 그래프 담을 벡터
// 최단거리 담을 배열1 - 돌아오는 길
// 최단거리 담을 배열2 - 가는 길
std::vector<P> adj[10001];
int comeback_dist[10001];
int go_dist[10001];

// 전역변수로 설정
int N, M, X, u, v, w;

// curr을 시작으로 하는 다익스트라.
int get_dist(int curr) {
	std::fill(go_dist, go_dist + 10001, INF);
	go_dist[curr] = 0;
	
	std::priority_queue<P, std::vector<P>, std::greater<P>> PQ;
	PQ.push(P(0, curr));

	int c = curr;
	// c가 X, 즉 도착점이면 다른 마을은 굳이 확인 안 해도 됨.
	while (!PQ.empty() && c != X) {
		c = PQ.top().second;
		PQ.pop();

		for (auto& p : adj[c]) {
			int next = p.first, d = p.second;

			if (go_dist[next] > go_dist[c] + d) {
				go_dist[next] = go_dist[c] + d;
				PQ.push(P(go_dist[next], next));
			}
		}
	}

	return go_dist[X] + comeback_dist[curr];
}

int main() {
	// N명의 학생
	// M개의 단방향 도로
	// X번 마을에 모인다.
	scanf("%d %d %d", &N, &M, &X);
	X--;

	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &u, &v, &w);
		u--; v--;
		adj[u].push_back(P(v, w));
	}

	// 시작점을 X로 하고 다익스트라
	std::fill(comeback_dist, comeback_dist + 10001, INF);
	comeback_dist[X] = 0;

	// 우선순위 큐
	std::priority_queue<P, std::vector<P>, std::greater<P>> PQ;
	PQ.push(P(0, X));

	while (!PQ.empty()) {
		int curr = PQ.top().second;
		PQ.pop();

		for (auto& p : adj[curr]) {
			int next = p.first, d = p.second;

			if (comeback_dist[next] > comeback_dist[curr] + d) {
				comeback_dist[next] = comeback_dist[curr] + d;
				PQ.push(P(comeback_dist[next], next));
			}
		}
	}

	int ret = 0;
	for (int i = 0; i < N; i++) {
		if (i != X) {
			ret = std::max(ret, get_dist(i));
		}
	}
	printf("%d", ret);
}