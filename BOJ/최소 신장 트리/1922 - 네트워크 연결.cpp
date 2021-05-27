#include <cstdio>
#include <algorithm>
#include <vector>

int N, M, cost[1001];
int a, b, c;

struct Edge {
	int c, a, b;
	Edge(int cost, int a1, int b1) : c(cost), a(a1), b(b1) {}
};

bool operator<(const Edge& a, const Edge& b) {
	return a.c < b.c;
}

std::vector<Edge> Edges;

int parent[1001];

int find(int curr) {
	if (parent[curr] == -1) return curr;
	parent[curr] = find(parent[curr]);
	return parent[curr];
}

void merge(int m, int n) {
	int m_r = find(m);
	int n_r = find(n);

	if (m_r != n_r) {
		parent[m_r] = n_r;
	}
}


int main() {
	scanf("%d %d", &N, &M);

	std::fill(parent, parent + N, -1);

	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &a, &b, &c);
		Edges.push_back(Edge(c, a, b));
	}

	// 오름차순 정렬.
	std::sort(Edges.begin(), Edges.end());

	int ret = 0;
	int cnt = 0;
	// 앞에서부터 본다.
	for (int i = 0; i < Edges.size() && cnt != N-1; i++) {
		auto curr = Edges[i];

		int u = find(curr.a);
		int v = find(curr.b);

		if (u != v) {
			merge(u, v);
			ret += curr.c;
			cnt++;
		}
	}

	printf("%d", ret);

}