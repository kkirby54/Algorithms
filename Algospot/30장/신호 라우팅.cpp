#include <cstdio>
#include <algorithm>
#include <queue>
#include <cmath>
#include <vector>

using namespace std;
typedef pair<int, double> IDP;
typedef pair<double, int> DIP;
const double INF = 1e20;

int C, N, M, a, b;
double c;
vector<IDP> adj[10005];
double dist[10005];

int main() {
	scanf("%d", &C);

	for (int t = 0; t < C; t++) {
		scanf("%d %d", &N, &M);

		for (int i = 0; i < N; i++)
			adj[i].clear();
		fill(dist, dist + N, INF);

		// 0 ~ N-1까지의 Node
		for (int i = 0; i < M; i++) {
			scanf("%d %d %lf", &a, &b, &c);
			adj[a].push_back(IDP(b, log10(c)));
			adj[b].push_back(IDP(a, log10(c)));
		}

		// 이제 Edge 완료.
		// Dijstra 알고리즘 적용
		priority_queue<DIP, vector<DIP>, greater<DIP>> Q;
		Q.push(DIP(0, 0));
		dist[0] = 0;

		while (!Q.empty()) {
			int curr = Q.top().second;
			double cost = Q.top().first;
			Q.pop();

			for (int i = 0; i < adj[curr].size(); i++) {
				int next = adj[curr][i].first;
				double d = adj[curr][i].second;

				if (dist[next] > dist[curr] + d) {
					dist[next] = dist[curr] + d;
					Q.push(DIP(dist[next], next));
				}
			}
		}

		printf("%.10lf\n", pow(10, dist[N - 1]));


		/*
		for (int i = 0; i < N; i++) {
			printf("%d에 대해서 : ", i);
			for (auto E : adj[i]) {
				printf("(%d, %lf), ", E.first, E.second);
			}
			puts("");
		}
		*/
	}
}