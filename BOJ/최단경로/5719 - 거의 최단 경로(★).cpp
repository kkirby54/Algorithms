#include <cstdio>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;
const int INF = 987654321;
typedef pair<int,int> P;
int N, M, S, D, u, v, p;
vector<P> adj[500];
int dist[500];
bool visited[500];
vector<int> previous[500];

void backTrack(int end) {
	if (end == S) return;
	if (previous[end].size() == 0) return;
	visited[end] = true;

	int curr = end;
	for (int i = 0; i < previous[curr].size(); i++) {
		int last = previous[curr][i];
		// last->curr 사이 거리를 INF로 만들면 된다. 그리고 재귀.
		for (int j = 0; j < adj[last].size(); j++) {
			if (adj[last][j].first == curr) {
				adj[last][j].second = INF;
			}
		}
		if (!visited[last])
			backTrack(last);
	}
	return;
}

int main(){
	while (1) {
		scanf("%d %d", &N, &M);
		if (!N && !M) return 0;
		scanf("%d %d", &S, &D);
		fill(dist, dist + N, INF);
		fill(visited, visited + N, false);
		for (int i = 0; i < N; i++) adj[i].clear();
		for (int i = 0; i < N; i++) previous[i].clear();

		for (int i = 0; i < M; i++) {
			scanf("%d %d %d", &u, &v, &p);
			adj[u].push_back(P(v, p));
		}

		// Step1. 최단 경로와, 그 경로를 역추적해서 구한다.
		priority_queue<P, vector<P>, greater<P>> PQ;
		PQ.push(P(0, S));
		dist[S] = 0;

		while (!PQ.empty()) {
			int curr;
			do {
				curr = PQ.top().second;
				PQ.pop();
			} while (!PQ.empty() && visited[curr]);
			if (visited[curr]) break;

			visited[curr] = true;

			for (auto E : adj[curr]) {
				int next = E.first;
				int cost = E.second;

				if (dist[next] >= dist[curr] + cost) {
					// 더 작은 녀석이었으면, 여태까지의 previous를 비운다.
					if (dist[next] > dist[curr] + cost) {
						previous[next].clear();
						dist[next] = dist[curr] + cost;
						PQ.push(P(dist[next], next));
					}
					
					previous[next].push_back(curr);
				}
			}
		}

		if (dist[D] == INF) {
			puts("-1");
		}
		else {
			// 이제 그럼 D부터 역추적을 한다.
			fill(visited, visited + N, false);
			backTrack(D);

			// 다시 S부터 돌려본다.
			fill(dist, dist + N, INF);
			fill(visited, visited + N, false);
			PQ.push(P(0, S));
			dist[S] = 0;

			while (!PQ.empty()) {
				int curr;
				do {
					curr = PQ.top().second;
					PQ.pop();
				} while (!PQ.empty() && visited[curr]);
				if (visited[curr]) break;
				visited[curr] = true;

				for (auto E : adj[curr]) {
					int next = E.first;
					int cost = E.second;

					if (dist[next] > dist[curr] + cost) {
						dist[next] = dist[curr] + cost;
						PQ.push(P(dist[next], next));
					}
				}
			}
			int ret = dist[D];
			if (ret == INF) puts("-1");
			else printf("%d\n", ret);
		}

	}

}