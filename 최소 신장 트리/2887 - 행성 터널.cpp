#include <cstdio>
#include <algorithm>
#include <cmath>

struct Edge {
	int u, v;
	int cost;
	Edge() : u(0), v(0), cost(0) {}
	Edge(int u1, int v1, int cost1) : u(u1), v(v1), cost(cost1) {}
};
bool operator<(const Edge& a, const Edge& b) {
	return a.cost < b.cost;
}

int parent[100005];

int find(int curr) {
	if (parent[curr] == -1) return curr;
	return parent[curr] = find(parent[curr]);
}

void merge(int x, int y) {
	int XRoot = find(x);
	int YRoot = find(y);

	if (XRoot != YRoot) {
		parent[XRoot] = YRoot;
	}
}


// (값, 몇 번째)를 담는다.
typedef std::pair<int, int> P;

P X[100005], Y[100005], Z[100005];
Edge e[300005];

int main() {
	int N, M = 0, a, b, c;

	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d %d %d", &a, &b, &c);
		// (값, 몇 번째)
		X[i] = P(a, i);
		Y[i] = P(b, i);
		Z[i] = P(c, i);
	}
	
	std::sort(X, X + N);
	std::sort(Y, Y + N);
	std::sort(Z, Z + N);

	for (int i = 0; i < N - 1; i++) {
		e[M++] = Edge(X[i + 1].second, X[i].second, (X[i + 1].first - X[i].first));
		e[M++] = Edge(Y[i + 1].second, Y[i].second, (Y[i + 1].first - Y[i].first));
		e[M++] = Edge(Z[i + 1].second, Z[i].second, (Z[i + 1].first - Z[i].first));
	}

	std::sort(e, e + M);
	std::fill(parent, parent + N, -1);

	// 이제 준비 끝. UF로 간선을 뽑는다.

	int uRoot, vRoot;
	int ret = 0, cnt = 0;

	for (int i = 0; i < M; i++) {
		uRoot = find(e[i].u);
		vRoot = find(e[i].v);
		
		if (uRoot != vRoot) {
			merge(uRoot, vRoot);
			cnt++;
			ret += e[i].cost;
		}
		if (cnt == N - 1) break;
	}

	printf("%d", ret);
}