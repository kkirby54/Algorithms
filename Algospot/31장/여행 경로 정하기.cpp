#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cmath>

const int INF = 987654321;
using namespace std;
typedef pair<int, int> P;

struct Edge {
	int u, v, dist;
	Edge(int u=0, int v=0, int dist=0) : u(u), v(v), dist(dist) {}

	bool operator<(const Edge& x) {
		return dist < x.dist;
	}
};

struct DisjointSet {
	vector<int> parent, rank;

	DisjointSet(int N) : parent(N) {
		for (int i = 0; i < N; i++)
			parent[i] = i;
	}

	int find(int u) {
		if (parent[u] == u) return u;
		return parent[u] = find(parent[u]);
	}

	void merge(int u, int v) {
		u = find(u), v = find(v);

		if (u == v) return;
		parent[u] = v;
	}

};

int C, N, M, a, b, c;
Edge edges[4000];

// 하한을 edges[low].dist라고 했을 때,
// Start-End를 잇는 경로의 상한을 구한다.
int minUpperBound(int low) {
	// 그렇게 되려면,
	// 걍 low부터 N까지만을 이용해서 구해본다.

	DisjointSet uf(N);

	for (int i = low; i < M; i++) {
		auto curr = edges[i];

		int u = curr.u, v = curr.v;
		if (uf.find(u) == uf.find(v)) continue;

		uf.merge(u, v);

		// 시작과 끝이 연결 되어있으면 ok.
		if (uf.find(0) == uf.find(N - 1)) return curr.dist;
	}

	return INF;
}

int minWeightDifference() {
	int ret = INF;

	for (int i = 0; i < M; i++) {
		ret = min(ret, minUpperBound(i) - edges[i].dist);
	}
	return ret;
}


int main() {
	scanf("%d", &C);
	for (int t = 0; t < C; t++) {
		scanf("%d %d", &N, &M);

		for (int i = 0; i < M; i++) {
			scanf("%d %d %d", &a, &b, &c);
			edges[i] = Edge(a, b, c);
		}

		sort(edges, edges + M);

		printf("%d\n", minWeightDifference());

	}
}