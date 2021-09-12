#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;
const long long INF = 1e18;
typedef pair<int, double> IDP;
typedef pair<double, int> DIP;


int C, N, M,a,b;
double c;
vector<IDP> adj[10000];
double dist[10000];

int main() {
	scanf("%d", &C);
	while (C--) {
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; i++) adj[i].clear();
		fill(dist, dist + N, INF);

		for (int i = 0; i < M; i++) {
			scanf("%d %d %lf", &a, &b, &c);

			adj[a].push_back(IDP(b, log10(c)));
			adj[b].push_back(IDP(a, log10(c)));
		}

		// 0부터 N-1까지.
		dist[0] = 0;
		priority_queue<DIP, vector<DIP>, greater<DIP>> PQ;
		PQ.push(DIP(0, 0));

		while (!PQ.empty()) {
			int curr = PQ.top().second;
			PQ.pop();

			for (auto& E : adj[curr]) {
				int next = E.first;
				double cost = E.second;

				if (dist[next] > dist[curr] + cost) {
					dist[next] = dist[curr] + cost;
					PQ.push(DIP(dist[next], next));
				}
			}
		}

		double ret = pow(10, dist[N - 1]);
		printf("%.10lf\n", ret);

	}


}