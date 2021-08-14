#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int T, N, M, u, v, edges;
vector<int> adj[500];
bool visited[500];

int main() {
	while (++T){
		scanf("%d %d", &N, &M);
		if (!N && !M) return 0;
		for (int i = 0; i < N; i++) adj[i].clear();

		for (int i = 0; i < M; i++) {
			scanf("%d %d", &u, &v);
			u--; v--;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}

		int treeNum = 0;

		fill(visited, visited + N, false);
		queue<int> Q;

		for (int i = 0; i < N; i++) {
			if (!visited[i]) {

				Q.push(i);
				visited[i] = true;
				int edges = 0;
				int vertex = 1;

				while (!Q.empty()) {
					int curr = Q.front();
					Q.pop();

					for (int next : adj[curr]) {
						// 연결된 edge들의 개수를 전부 센다.
						edges++;
						if (!visited[next]) {
							Q.push(next);
							visited[next] = true;
							vertex++;
						}
					}
				}

				// 이게 (vertex-1) * 2 == edges 면 됨.
				// 트리를 실제 이루고 있는 edges는
				// vertex - 1이다. (트리의 간선 == N-1개)
				// 한편 큐에서 모든 edges를 셌으므로 u->v, v->u가
				// 중복되어 들어갔다.
				if (2 * (vertex - 1) == edges) {
					treeNum++;
				}


			}
		}



		if (!treeNum) printf("Case %d: No trees.\n", T);
		else if (treeNum == 1) printf("Case %d: There is one tree.\n", T);
		else
			printf("Case %d: A forest of %d trees.\n", T, treeNum);

	}

}
