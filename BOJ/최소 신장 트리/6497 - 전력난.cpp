#include <cstdio>
#include <algorithm>
#include <vector>

struct Edge {
	int u, v, cost;
	Edge() : u(0), v(0), cost(0) {}
	Edge(int u1, int v1, int cost1) : u(u1), v(v1), cost(cost1) {}
};
bool operator<(const Edge& a, const Edge& b) {
	return a.cost < b.cost;
}

int parent[200000];
Edge Edges[200000];

int find(int curr) {
	if (parent[curr] == -1) return curr;
	parent[curr] = find(parent[curr]);
	return parent[curr];
}

void merge(int x, int y) {
	int xRoot = find(x);
	int yRoot = find(y);

	if (xRoot != yRoot) {
		parent[xRoot] = yRoot;
	}
}

int main() {
	int M, N, x, y, z;

	while (1) {
		scanf("%d %d", &M, &N);
		if (!M && !N) break;

		std::fill(parent, parent + M, -1);
		int total_cost = 0;

		for (int i = 0; i < N; i++) {
			scanf("%d %d %d", &x, &y, &z);

			Edges[i] = Edge(x, y, z);
			total_cost += z;
		}

		// 간선을 오름차순으로 정렬
		std::sort(Edges, Edges + N);

		// 간선 개수가 V-1이 되면 종료
		int cnt = 0;
		int ret = 0;

		for (int i = 0; i < N && cnt != M - 1; i++) {
			int ARoot = find(Edges[i].u);
			int BRoot = find(Edges[i].v);

			if (ARoot != BRoot) {
				merge(ARoot, BRoot);
				ret += Edges[i].cost;
				cnt++;
			}
		}

		printf("%d\n", total_cost - ret);
	}


}