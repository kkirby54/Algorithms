#include <cstdio>
#include <algorithm>
#include <cstring>

int N, M, continent_cnt = 1;
int map[11][11];
bool visited[11][11] = { 0 };

int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };

void dfs(int r, int c) {
	visited[r][c] = true;
	map[r][c] = continent_cnt;

	int nR, nC;

	for (int i = 0; i < 4; i++) {
		nR = r + dr[i];
		nC = c + dc[i];

		if (nR < 0 || nR >= N || nC < 0 || nC >= M) continue;
		if (visited[nR][nC]) continue;
		if (map[nR][nC] != 0) {
			dfs(nR, nC);
		}
	}
}

struct Edge {
	int u, v, dist;
	Edge() : u(0), v(0), dist(0) {}
	Edge(int u1, int v1, int dist1) : u(u1), v(v1), dist(dist1) {}
};
bool operator<(const Edge& a, const Edge& b) {
	return a.dist < b.dist;
}

Edge e[1000];
int parent[1000], EdgeNums = 0;

int find(int curr) {
	if (parent[curr] == -1) return curr;
	return parent[curr] = find(parent[curr]);
}

void merge(int x, int y) {
	int xRoot = find(x);
	int yRoot = find(y);

	if (xRoot != yRoot) {
		parent[xRoot] = yRoot;
	}
}

int main() {
	scanf("%d %d", &N, &M);
	std::fill(parent, parent + 1000, -1);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	// DFS로 섬을 구분짓는다.
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] && !visited[i][j]) {
				dfs(i, j);
				continent_cnt++;
			}
		}
	}
	continent_cnt--;

	// (섬 개수 - 1)개의 간선으로 연결하면 된다.
	// 각각을 돌면서, 간선들을 만든다.

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (!map[i][j]) continue;

			// 모든 좌표를 훑기 때문에 위, 오른쪽만 본다.
			bool is_possible = false;
			int k, min_k, min_d;

			// 상
			for (k = i - 1; k >= 0; k--) {
				// 위에가 같다면(즉, 같은 섬의 일부라면)
				// 차라리 그 위쪽에서 훑는 게 최소 거리로 뽑힌다.
				// 즉 이 좌표에서 해봤자 이미 더 최소 거리를 뽑은 상태다.
				if (map[k][j] == map[i][j]) break;

				if (map[k][j] &&
					map[k][j] != map[i][j] &&
					(i - k) >= 2) {

					// 1 차이면 다리 없음.(여기선 2로 표현)
					if (i - k == 2) {
						break;
					}
					else {
						is_possible = true;

						// min_k는 위에서 올라가다가 만난 다른 섬의 실제 r 좌표.
						// min_d는 그 거리
						min_k = k;
						min_d = i - k;

						break;
					}
				}
			}

			if (is_possible) {
				e[EdgeNums++] = Edge(map[i][j], map[min_k][j], min_d - 1);
			}

			// 우
			is_possible = false;

			for (k = j + 1; k < M; k++) {
				if (map[i][k] == map[i][j]) {
					break;
				}
				if (map[i][k] &&
					map[i][k] != map[i][j] &&
					(k - j) >= 2) {

					if (k - j == 2) {
						break;
					}
					else {
						is_possible = true;

						min_k = k;
						min_d = k - j;
						break;
					}
				}
			}

			if (is_possible) {
				e[EdgeNums++] = Edge(map[i][j], map[i][min_k], min_d - 1);
			}
		}
	}

	std::sort(e, e + EdgeNums);

	// UF 적용.
	int cnt = 0;
	int ret = 0;

	for (int i = 0; i < EdgeNums; i++) {
		int uRoot = find(e[i].u);
		int vRoot = find(e[i].v);

		if (uRoot != vRoot) {
			merge(uRoot, vRoot);
			cnt++;
			ret += e[i].dist;
		}

		if (cnt == continent_cnt - 1) {
			break;
		}

	}
	// (섬 개수 - 1)개 간선이 안되면, 불가능
	if (cnt != continent_cnt - 1) {
		puts("-1");
	}
	else printf("%d\n", ret);

}
