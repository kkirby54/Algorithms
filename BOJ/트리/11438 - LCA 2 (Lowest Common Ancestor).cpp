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
	memset(parent, -1, sizeof(parent)); // ��Ʈ��� �θ� �����ϱ�.
	depth[0] = 0;

	for (int i = 0; i < N - 1; i++) {
		scanf("%d %d", &u, &v);
		u--; v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	makeTree(0);

	// ���� �׷��� parent �迭�� ä���� �Ѵ�.
	// parent[u][k+1] = parent[ parent[u][k] ][k];
	for (int j = 0; j < MAX_V - 1; j++) {
		for (int i = 1; i < N; i++) {
			if (parent[i][j] != -1)
				parent[i][j + 1] = parent[parent[i][j]][j];
		}
	}

	// ���� ��ó���� �Ϸ�.
	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &u, &v);
		u--; v--;

		if (depth[u] < depth[v]) swap(u, v);

		// ���� u�� �÷��� �Ѵ�.
		// �ø��µ�, �ϳ��� �ø�������, �ϴ� depth ���̸� ����
		int diff = depth[u] - depth[v];

		for (int j = 0; diff; j++) {
			// j��° ��Ʈ�� �����ִٸ�,
			// 2^j��ŭ�� �ö󰡾� �Ѵٴ� ���̴�.
			if (diff % 2)
				u = parent[u][j];

			diff /= 2;
		}

		// u�� v�� �ٸ��ٸ�.
		if (u != v) {
			// ���� �׷��� ���� ���̰� ��������.
			// ���ÿ� �����̸鼭, ���� �������Ѵ�.
			// �� ���� �ϳ��� �ø��� TLE�� ���ϱ�,
			// ������ �ߴ� ���ó�� �Ѵ�.
			// ���� parent[u][k] != parent[v][k]���,
			// �� ���� 2^k���� �� �ָ� ������ �ִٴ� ���̴�.
			// �� 2^k ��ŭ�� ���ÿ� �������� �ȴٴ� ���̴�.
			// �ٵ� parent[u][k+1] == parent[v][k+1]�̶��,
			// 2^k�� 2^(k+1) ���̿� �ִٴ� ���̴�.
			// k�� �ִ��� ũ�� ��� �����Ѵ�.
			// ������ k�� ���ǹ��ϰ� Ŀ����, u�� v�� parent�� �Ȱ���.
			// �޶����� ������ �����ؾ� �Ѵ�.

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