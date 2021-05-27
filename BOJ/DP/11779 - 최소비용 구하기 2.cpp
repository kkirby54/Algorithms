#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>

const int INF = 1000000000;

typedef std::pair<int, int> P;

std::vector<P> adj[1000];
std::stack<int> S;
int dist[1000];
int prev[1000];
bool visited[1000] = { 0 };

int main() {
	int N, M, A, B, c;
	int goal_A, goal_B;

	scanf("%d %d", &N, &M);

	std::fill(dist, dist + N, INF);

	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &A, &B, &c);

		adj[A - 1].push_back(P(B - 1, c));
	}

	// 다익스트라로 풀어버리기.
	scanf("%d %d", &goal_A, &goal_B);
	goal_A--; goal_B--;

	dist[goal_A] = 0;
	std::priority_queue<P, std::vector<P>, std::greater<P>> PQ;
	// (거리, 출발)
	PQ.push(P(0, goal_A));

	int curr;
	while (!PQ.empty()) {
		do {
			curr = PQ.top().second;
			PQ.pop();
		} while (!PQ.empty() && visited[curr]);
		if (visited[curr]) break;

		visited[curr] = true;

		for (auto& p : adj[curr]) {
			int next = p.first, d = p.second;

			if (dist[next] > dist[curr] + d) {
				dist[next] = dist[curr] + d;
				prev[next] = curr;
				PQ.push(P(dist[next], next));
			}
		}
	}

	printf("%d\n", dist[goal_B]);

	for (curr = goal_B; curr != goal_A; curr = prev[curr]) {
		S.push(curr + 1);
	}
	S.push(goal_A + 1);


	printf("%d\n", S.size());

	while (!S.empty()) {
		printf("%d ", S.top());
		S.pop();
	}

	/*
	printf("================\n");
	for (int i = 0; i < N; i++) {
		printf("거리 : %d\n", dist[i]);
	}
	*/
}