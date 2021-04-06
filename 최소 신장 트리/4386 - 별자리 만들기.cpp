#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>

struct Edge {
	int u, v;
	double cost;
	Edge() : u(0), v(0), cost(0) {}
	Edge(int u1, int v1, double cost1) : u(u1), v(v1), cost(cost1) {}
};
bool operator<(const Edge& a, const Edge& b) {
	return a.cost < b.cost;
}

int parent[105];
Edge Edges[10005];
double X[101], Y[101];

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
	int N;
	int M = 0;
	scanf("%d", &N);

	std::fill(parent, parent + N, -1);

	// N이 100이하기 때문에 O(N^2)으로 간선 구한다.
	for (int i = 0; i < N; i++) {
		scanf("%lf %lf", &X[i], &Y[i]);

		for (int j = 0; j < i; j++) {
			Edges[M++] = Edge(i, j, sqrt((X[i] - X[j]) * (X[i] - X[j]) + (Y[i] - Y[j]) * (Y[i] - Y[j])));
		}
	}

	// 간선을 오름차순으로 정렬
	std::sort(Edges, Edges + M);

	int cnt = 0;
	double ret = 0;

	for (int i = 0; i < M && cnt != N - 1; i++) {
		int ARoot = find(Edges[i].u);
		int BRoot = find(Edges[i].v);

		if (ARoot != BRoot) {
			merge(ARoot, BRoot);
			ret += Edges[i].cost;
			cnt++;
		}
	}

	printf("%.2lf\n", ret);


}