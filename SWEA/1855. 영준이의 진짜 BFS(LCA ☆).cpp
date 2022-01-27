#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
const int MAX_V = 17;

int T, N, p, ch;
int parent[100000][MAX_V];
int depth[100000];
vector<int> adj[100000];

int findLCA(int u, int v) {
	if (depth[u] < depth[v]) swap(u, v);

	// u�� v
	int diff = depth[u] - depth[v];

	// ���̸� ���� �����ش�.
	for (int j = 0; diff; j++) {
		if (diff % 2)
			u = parent[u][j];
		diff /= 2;
	}

	// ���� ���̰� ����.
	// ���ÿ� �ø��鼭 ����.
	if (u != v) {
		for (int k = MAX_V - 1; k >= 0; k--) {
			if (parent[u][k] != -1 &&
				parent[u][k] != parent[v][k]) {
				u = parent[u][k];
				v = parent[v][k];
			}
		}
		
		u = parent[u][0];
	}
	return u;
}

int main() {
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d", &N);
		memset(parent, -1, sizeof(parent));
		memset(depth, -1, sizeof(depth));
		for (int i = 0; i < N; i++) adj[i].clear();

		for (int i = 1; i < N; i++) {
			scanf("%d", &p);
			p--;
			parent[i][0] = p;
			adj[p].push_back(i);
		}

		queue<int> Q;
		depth[0] = 0;
		Q.push(0);
		int level = 0;

		while (!Q.empty()) {
			int qSize = Q.size();
			for (int s = 0; s < qSize; s++) {
				int curr = Q.front();
				Q.pop();

				for (int next : adj[curr]) {
					if (depth[next] == -1) {
						depth[next] = depth[curr] + 1;
						Q.push(next);
					}
				}
			}
			level++;
		}

		// parent �迭 ä���
		for (int j = 0; j < MAX_V - 1; j++) {
			for (int i = 0; i < N; i++) {
				if (parent[i][j] != -1)
					parent[i][j + 1] = parent[parent[i][j]][j];
			}
		}

		Q.push(0);
		int cursor = 0; // 0���� �����ؼ� �̰� ��� �����δ�.
		long long ret = 0;
		while (!Q.empty()) {
			int qSize = Q.size();
			for (int s = 0; s < qSize; s++) {
				int curr = Q.front();
				Q.pop();

				for (int next : adj[curr]) {
					// cursor -> next�� ���� �Ѵ�.
					// �׷�����, cursor�� next�� LCA�� ���Ѵ�.
					int lcaBetweenCursorNext = findLCA(cursor, next);

					// cursor -> lcaBetweenCursorNext -> next�� ����.
					ret += (long long)
						(depth[cursor] - depth[lcaBetweenCursorNext]) +
						(depth[next] - depth[lcaBetweenCursorNext]);

					cursor = next;
					
					Q.push(next);
				}
			}
		}


		printf("#%d %lld\n", t, ret);
	}
}