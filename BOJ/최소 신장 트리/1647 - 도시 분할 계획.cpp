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

int parent[100005];
Edge Edges[1000005];

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
	int N, M, A,B,C;
	scanf("%d %d", &N, &M);

	std::fill(parent, parent + N, -1);

	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &A, &B, &C);
		A--; B--;
		Edges[i] = Edge(A,B,C);
	}

	// 간선을 오름차순으로 정렬
	std::sort(Edges, Edges + M);

	// 두 개의 분리된 마을.
	// 그럼 간선이 V-2개면 끝.

	int cnt = 0;
	int ret = 0;

	for (int i = 0; i < M && cnt != N - 2; i++) {
		int ARoot = find(Edges[i].u);
		int BRoot = find(Edges[i].v);

		if (ARoot != BRoot) {
			merge(ARoot, BRoot);
			ret += Edges[i].cost;
			cnt++;
		}
	}

	printf("%d\n", ret);


}