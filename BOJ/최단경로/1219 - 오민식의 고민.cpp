#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
const long long INF = 1e18;
typedef pair<int , int> P;

int N, M, A, B, u, v, c;
int profit[100];
bool visited[100];
long long dist[100];
vector<P> adj[100];

int main() {
	scanf("%d %d %d %d", &N, &A, &B, &M);

	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &u, &v, &c);
		adj[u].push_back(P(v, c));
	}

	for (int i = 0; i < N; i++) scanf("%d", profit + i);
	fill(dist, dist + N, INF);
	queue<int> Q;

	dist[A] = -profit[A];

	for (int k = 0; k < N; k++) {

		for (int i = 0; i < N; i++) {
			if (dist[i] == INF) continue;

			for (auto& E : adj[i]) {
				int next = E.first;
				int cost = E.second;

				if (dist[next] > dist[i] + cost - profit[next]) {
					dist[next] = dist[i] + cost - profit[next];
					if (k == N - 1) {
						visited[i] = true;
						Q.push(i);
					}
				}
			}
		}
	}

	if (dist[B] == INF) {
		puts("gg");
	}
	else {
		// 큐를 돌면서
		bool isInfinite = false;
		while (!Q.empty()) {
			int curr = Q.front();
			Q.pop();

			if (curr == B) {
				isInfinite = true;
				break;
			}

			for (auto& E : adj[curr]) {
				int next = E.first;
				if (!visited[next]) {
					visited[next] = true;
					Q.push(next);
				}
			}
		}

		// 음의 사이클이 있으면서, B 까지 도달 했다면,
		if (isInfinite) puts("Gee");
		else printf("%lld", -dist[B]);

	}


}