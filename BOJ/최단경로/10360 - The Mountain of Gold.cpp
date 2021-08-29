#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
const long long INF = 1e18;
typedef pair<int , int> P;

int T, N, M, A, B, C;

int main() {
	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		scanf("%d %d", &N, &M);
		vector<P> adj[1000];
		long long dist[1000];
		bool visited[1000] = { 0 };
		fill(dist, dist + N, INF);

		for (int i = 0; i < M; i++) {
			scanf("%d %d %d", &A, &B, &C);
			adj[A].push_back(P(B, C));
		}

		dist[0] = 0;
		queue<int> Q;
		for (int k = 0; k < N; k++) {
			for (int curr = 0; curr < N; curr++) {
				if (dist[curr] == INF) continue;

				for (auto& E : adj[curr]) {
					int next = E.first;
					int cost = E.second;

					if (dist[next] > dist[curr] + cost) {
						dist[next] = dist[curr] + cost;
						if (k == N - 1) {
							Q.push(curr);
							visited[curr] = true;
						}
					}
				}
			}
		}

		// 음의 사이클이 존재한다고 하더라도,
		// 그게 바로 음수가 될 수는 없다.
		// 무한으로 돌기 때문에, 그 사이클로부터 갈 수 있는 정점들을 구하면,
		// 그 정점들은 전부 다 음의 무한대를 갖는다고 볼 수 있다.

		bool isPossible = (dist[0] < 0);
		while (!Q.empty()) {
			int curr = Q.front();
			Q.pop();

			if (curr == 0) {
				isPossible = true;
				break;
			}

			for (auto& E : adj[curr]) {
				int next = E.first;

				if (!visited[next]) {
					Q.push(next);
					visited[next] = true;
				}
			}
		}
		
		printf("Case #%d: ", t+1);
		if (isPossible) puts("possible");
		else puts("not possible");
	}

}