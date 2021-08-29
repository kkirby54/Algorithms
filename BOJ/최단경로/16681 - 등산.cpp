#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const long long INF = 1e18;
typedef pair<long long, long long> P;

int N, M, D, E,a,b,n;
int H[100001];
vector<P> adj[100001];
long long dist[2][100001];
bool visited[2][100001];

int main() {
	// vertex : N
	// 1 움직일 때 체력 D 소모
	// 1 높이 당 성취감 E
	// 가치 = 성취감(hE) - 소모한 체력.

	// 높이*E - 거리*D 를 최대화해야 한다.
	scanf("%d %d %d %d", &N, &M, &D, &E);

	for (int i = 1; i <= N; i++) scanf("%d", H + i);
	for (int i = 1; i <= M; i++) {
		scanf("%d %d %d", &a, &b, &n);
		adj[a].push_back(P(b, n));
		adj[b].push_back(P(a, n));
	}

	// dist[0][]은 시작점.
	// dist[1][]은 도착점.
	for (int i = 0; i < 2; i++) {
		int start;

		fill(dist[i], dist[i] + N + 1, INF);
		fill(visited[i], visited[i] + N + 1, false);
		priority_queue<P, vector<P>, greater<P>> PQ;
		if (i == 0) start = 1;
		else start = N;

		PQ.push(P(0, start));
		dist[i][start] = 0;

		while (!PQ.empty()) {
			int curr;
			do {
				curr = PQ.top().second;
				PQ.pop();
			} while (!PQ.empty() && visited[i][curr]);
			if (visited[i][curr]) break;

			visited[i][curr] = true;

			for (auto& E : adj[curr]) {
				int next = E.first;
				int cost = E.second;

				if (H[curr] >= H[next]) continue;

				if (dist[i][next] > dist[i][curr] + cost) {
					dist[i][next] = dist[i][curr] + cost;
					PQ.push(P(dist[i][next], next));
				}
			}
		}
	}

	long long ret = -INF;
	for (int i = 1; i <= N; i++) {
		if (dist[0][i] == INF || dist[1][i] == INF) continue;
		long long totalDist = dist[0][i] + dist[1][i];

		ret = max(ret, 1LL * E * H[i] - 1LL * D * totalDist);
	}
	if (ret == -INF) puts("Impossible");
	else printf("%lld", ret);

}