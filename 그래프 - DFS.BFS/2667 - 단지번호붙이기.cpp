#include <cstdio>
#include <vector>
#include <algorithm>

int map[25][25], N;
bool visited[25][25];
std::vector<int> ret;

int dr[] = { -1,1, 0,0 };
int dc[] = { 0,0, -1, 1 };

int dfs(int r, int c) {
	visited[r][c] = true;
	
	int ret = 1;
	for (int i = 0; i < 4; i++) {
		int n_r = r + dr[i];
		int n_c = c + dc[i];

		if (n_r < 0 || n_r >= N || n_c < 0 || n_c >= N) continue;
		if (visited[n_r][n_c]) continue;
		if (map[n_r][n_c]) {
			ret += dfs(n_r, n_c);
		}
	}

	return ret;
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			scanf("%1d", &map[i][j]);
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			if (!visited[i][j] && map[i][j]) {
				ret.push_back(dfs(i, j));
			}
	}
	std::sort(ret.begin(), ret.end());
	printf("%d\n", ret.size());
	for (int e : ret)
		printf("%d\n", e);

}