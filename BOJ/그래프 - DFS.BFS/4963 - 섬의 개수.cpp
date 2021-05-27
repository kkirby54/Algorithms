#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

int w, h, map[50][50];
bool visited[50][50];

int dr[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dc[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

void dfs(int r, int c) {
	visited[r][c] = true;

	for (int i = 0; i < 8; i++) {
		int n_r = r + dr[i];
		int n_c = c + dc[i];

		if (n_r < 0 || n_r >= h || n_c < 0 || n_c >= w) continue;
		if (visited[n_r][n_c]) continue;
		if (map[n_r][n_c]) {
			dfs(n_r, n_c);
		}
	}
}

int main() {
	while (1) {
		scanf("%d %d", &w, &h);
		if (!w && !h) return 0;

		int cnt = 0;
		memset(visited, false, sizeof(visited));

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++)
				scanf("%d", &map[i][j]);
		}

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if (!visited[i][j] && map[i][j]) {
					dfs(i, j);
					cnt++;
				}
			}
		}

		printf("%d\n", cnt);
	}

}