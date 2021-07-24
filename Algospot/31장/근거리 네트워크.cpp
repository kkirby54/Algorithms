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

int C, N, M, x[500], y[500], a, b;

// a건물, b건물 사이의 거리의 제곱을 구하는 함수
int sqrDist(int a, int b) {
	return (x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b]);
}

Edge Edges[250000];

int main() {
	scanf("%d", &C);
	for (int t = 0; t < C; t++) {
		scanf("%d %d", &N, &M);
		DisjointSet UF(N);
		memset(Edges, 0, sizeof(Edges));

		for (int i = 0; i < N; i++) scanf("%d", x + i);
		for (int i = 0; i < N; i++) scanf("%d", y + i);

		for (int i = 0; i < M; i++) {
			// 이건 그냥 연결되어 있음.
			// 그럼 UF로 둘을 그냥 묶어줘.
			scanf("%d %d", &a, &b);
			UF.merge(a,b);
		}

		int edgesNum = 0;

		// 이제 간선들을 모아야한다.
		for (int i = 0; i < N; i++) {
			// 모든 edges를 만들어 본다.
			for (int j = i+1; j < N; j++) {
				if (UF.find(i) == UF.find(j)) continue;
				Edges[edgesNum++] = Edge(i, j, sqrDist(i, j));
			}
		}

		sort(Edges, Edges + edgesNum);

		double ret = 0;
		for (int i = 0; i < edgesNum; i++) {
			Edge curr = Edges[i];

			int rootU = UF.find(curr.u);
			int rootV = UF.find(curr.v);

			if (rootU == rootV) continue;

			UF.merge(rootU, rootV);
			ret += sqrt(curr.dist);
		}

		printf("%.10lf\n", ret);

	}

}