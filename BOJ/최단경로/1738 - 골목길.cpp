#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
const long long INF = 1e18;
typedef pair<int, int> P;

int N, M, A, B, C;
long long dist[100];
int previous[100];
vector<P> adj[100];
bool reachable[100][100];

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &A, &B, &C);
		A--; B--;
		adj[A].push_back(P(B, C));
		reachable[A][B] = 1;
	}
	fill(dist, dist + N, -INF);
	fill(previous, previous + N, -1);
	dist[0] = 0;
	previous[0] = 0;

	// 일단 플로이드로 reachable을 판단해.
	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (!reachable[i][j]) {
					reachable[i][j] = (reachable[i][k] && reachable[k][j]);
				}
			}
		}
	}

	bool infinite = false;
	for (int k = 0; k < N; k++) {

		for (int curr = 0; curr < N; curr++) {
			for (auto& E : adj[curr]) {
				int next = E.first, cost = E.second;
				
				if (dist[curr] != -INF && dist[next] < dist[curr] + cost) {
					dist[next] = dist[curr] + cost;
					previous[next] = curr;

					if (k == N - 1) {
						// 그리고 이 curr -> next가 연결되었다면..
						// 그게 만약 0 -> curr -> next 연결되어있냐?
						if (reachable[0][curr] && reachable[next][N-1])
							infinite = true;
					}
				}
			}
		}
	}

	if (infinite || !reachable[0][N-1]) {
		puts("-1");
	}
	else {
		stack<int> S;

		int curr = N - 1;
		while (curr != previous[curr]) {
			S.push(curr + 1);
			curr = previous[curr];
		}
		S.push(curr + 1);
		while (!S.empty()) {
			printf("%d ", S.top());
			S.pop();
		} puts("");
	}

}