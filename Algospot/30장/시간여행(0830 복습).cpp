#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int INF = 987654321;
typedef pair<int, int> P;

int C, V, W,a,b,d;
vector<P> adj[100];
int shortest[100];
int longest[100];

int main() {
	scanf("%d", &C);
	while (C--) {
		scanf("%d %d", &V, &W);
		for (int i = 0; i < V; i++) adj[i].clear();
		fill(shortest, shortest + V, INF);
		fill(longest, longest + V, -INF);

		for (int i = 0; i < W; i++) {
			scanf("%d %d %d", &a, &b, &d);

			adj[a].push_back(P(b, d));
		}

		// 0 출발, 1로 도착.
		longest[0] = 0;
		shortest[0] = 0;

		queue<int> Q[2];
		bool visited[2][100] = { 0 };

		// V번 완화.
		for (int k = 0; k < V; k++) {
			// curr -> next로 가는 경로에서 완화 시도.
			for (int curr = 0; curr < V; curr++) {
				for (auto& E : adj[curr]) {
					int next = E.first;
					int cost = E.second;

					if (shortest[curr] != INF && shortest[next] > shortest[curr] + cost) {
						shortest[next] = shortest[curr] + cost;

						// V번째에 완화되면, 음의 사이클이 존재한다.
						// Q[0]에 넣어놓는다.
						if (k == V - 1) {
							Q[0].push(curr);
							visited[0][curr] = true;
						}
					}

					if (longest[curr] != -INF && longest[next] < longest[curr] + cost) {
						longest[next] = longest[curr] + cost;

						// V번째에 완화되면, 양의 사이클이 존재한다.
						// Q[1]에 넣어놓는다.
						if (k == V - 1) {
							Q[1].push(curr);
							visited[1][curr] = true;
						}
					}
				}
			}
		}
		
		bool minusCycle = false, plusCycle = false;
		// Q[i] 처리
		// Q에 있는 걸 빼서 처리하다가,
		// 1로 도착한다면, 음/양의 사이클이 된다는 의미.
		for (int i = 0; i < 2; i++) {
			while (!Q[i].empty()) {
				int curr = Q[i].front();
				Q[i].pop();

				if (curr == 1) {
					if (i == 0) minusCycle = true;
					else plusCycle = true;
					break;
				}

				for (auto& E : adj[curr]) {
					int next = E.first;
					if (!visited[i][next]) {
						Q[i].push(next);
						visited[i][next] = true;
					}
				}
			}
		}


		// 최단거리가 INF면 애초에 도달 X.
		if (shortest[1] == INF) {
			puts("UNREACHABLE");
		}
		else {
			if (minusCycle) printf("INFINITY ");
			else printf("%d ", shortest[1]);

			if (plusCycle) printf("INFINITY\n");
			else printf("%d\n", longest[1]);

		}


	}


}