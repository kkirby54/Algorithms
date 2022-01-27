#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
const int MAX_V = 17; // 10000 = 2^16.xx

int N, M, u, v;
vector<int> adj[100000];
int depth[100000];
int parent[100000][MAX_V];

void makeTree(int curr) {
	for (int next : adj[curr]) {
		if (depth[next] == -1) {
			parent[next][0] = curr;
			depth[next] = depth[curr] + 1;
			makeTree(next);
		}
	}

}

int main() {
	scanf("%d", &N);
	memset(depth, -1, sizeof(depth));
	memset(parent, -1, sizeof(parent)); // 루트라면 부모 없으니까.
	depth[0] = 0;

	for (int i = 0; i < N - 1; i++) {
		scanf("%d %d", &u, &v);
		u--; v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	makeTree(0);

	// 이제 그러면 parent 배열을 채워야 한다.
	// parent[u][k+1] = parent[ parent[u][k] ][k];
	for (int j = 0; j < MAX_V - 1; j++) {
		for (int i = 1; i < N; i++) {
			if (parent[i][j] != -1)
				parent[i][j + 1] = parent[parent[i][j]][j];
		}
	}

	// 이제 전처리가 완료.
	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &u, &v);
		u--; v--;

		if (depth[u] < depth[v]) swap(u, v);

		// 이제 u를 올려야 한다.
		// 올리는데, 하나씩 올리지말고, 일단 depth 차이를 구해
		int diff = depth[u] - depth[v];

		for (int j = 0; diff; j++) {
			// j번째 비트가 켜져있다면,
			// 2^j만큼을 올라가야 한다는 말이다.
			if (diff % 2)
				u = parent[u][j];

			diff /= 2;
		}

		// u와 v가 다르다면.
		if (u != v) {
			// 이제 그러면 둘의 깊이가 같아졌음.
			// 동시에 움직이면서, 맞춰 나가야한다.
			// 이 역시 하나씩 올리면 TLE가 나니까,
			// 위에서 했던 방식처럼 한다.
			// 만약 parent[u][k] != parent[v][k]라면,
			// 이 말은 2^k보다 더 멀리 떨어져 있다는 말이다.
			// 즉 2^k 만큼은 동시에 움직여도 된다는 말이다.
			// 근데 parent[u][k+1] == parent[v][k+1]이라면,
			// 2^k와 2^(k+1) 사이에 있다는 말이다.
			// k를 최대한 크게 잡고 시작한다.
			// 어차피 k가 무의미하게 커지면, u와 v의 parent는 똑같다.
			// 달라지는 순간을 관찰해야 한다.

			for (int k = MAX_V - 1; k >= 0; k--) {
				if (parent[u][k] != -1 && parent[u][k] != parent[v][k]) {
					u = parent[u][k];
					v = parent[v][k];
				}
			}

			u = parent[u][0];
		}

		printf("%d\n", u + 1);
	}

}