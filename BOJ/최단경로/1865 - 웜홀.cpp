#include <cstdio>
#include <vector>
#include <algorithm>

typedef std::pair<int, int> P;
const long long INF = 10000000000;

int main() {
	int TC, N, M, W, S, E, T;

	scanf("%d", &TC);

	for (int t = 0; t < TC; t++) {
		scanf("%d %d %d", &N, &M, &W);

		std::vector<P> adj[501];
		long long dist[501];
		std::fill(dist, dist + 501, INF);

		bool visited[501] = { 0, };
		bool infinite = false;

		// 실제 도로
		for (int i = 0; i < M; i++) {
			scanf("%d %d %d", &S, &E, &T);
			adj[S - 1].push_back(P(E - 1, T));
			adj[E - 1].push_back(P(S - 1, T));
		}

		// 웜홀
		for (int i = 0; i < W; i++) {
			scanf("%d %d %d", &S, &E, &T);
			adj[S - 1].push_back(P(E - 1, -T));
		}

		// 컴포넌트 별로 벨만포드 적용.

		for (int index = 0; index < N; index++) {
			// 방문했다면 이미 완성된 컴포넌트.
			if (visited[index]) continue;

			dist[index] = 0;

			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					if (dist[j] == INF) continue;

					visited[j] = true;
					for (auto& p : adj[j]) {
						int next = p.first, d = p.second;

						if (dist[next] > dist[j] + d) {
							dist[next] = dist[j] + d;

							if (i == N - 1) {
								infinite = true;
								break;
							}
						}
					}

				}
			}
			if (infinite) break;
		}

		if (infinite) printf("YES\n");
		else {
			printf("NO\n");
		}

	}
}
