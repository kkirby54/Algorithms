#include <cstdio>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;
const int INF = 987654321;
typedef pair<int, int> P;

int N, M, a, b, c;
vector<P> adj[1000];

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &a, &b, &c);
		a--; b--;
		adj[a].push_back(P(b, c));
		adj[b].push_back(P(a, c));
	}
	int dist[1000];
	int prev[1000];
	fill(dist, dist + N, INF);
	fill(prev, prev + N, -1);

	priority_queue<P, vector<P>, greater<P>> PQ;
	PQ.push(P(0,0));
	dist[0] = 0;
	prev[0] = 0;

	while (!PQ.empty()) {
		int curr = PQ.top().second;
		PQ.pop();

		for (auto& E : adj[curr]) {
			int next = E.first;
			int cost = E.second;

			if (dist[next] > dist[curr] + cost) {
				dist[next] = dist[curr] + cost;
				prev[next] = curr;
				PQ.push(P(dist[next], next));
			}
		}
	}
	// 각 정점에 대해,
	// curr = prev[curr]로 찾아가기.
	set<P> S;
	for (int i = 0; i < N; i++) {
		int curr = i;
		while (curr != prev[curr]) {
			// curr -> prev[curr]을 복구한다.
			if (S.find(P(curr, prev[curr])) == S.end() &&
				S.find(P(prev[curr], curr)) == S.end()) {
				S.insert(P(curr, prev[curr]));
			}
			curr = prev[curr];
		}
	}
	printf("%d\n", S.size());
	for (auto E : S) {
		printf("%d %d\n", E.first+1, E.second+1);
	}

}
