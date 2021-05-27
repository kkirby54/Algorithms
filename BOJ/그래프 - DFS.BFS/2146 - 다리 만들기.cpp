#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>

typedef std::pair<int, int> P;

int N, map[100][100];
int cnt = 0;
bool visited[100][100];

int dr[] = { -1, 1, 0,0 };
int dc[] = { 0,0,-1,1 };

void dfs(int r, int c) {
	visited[r][c] = true;
	map[r][c] = cnt;

	for (int i = 0; i < 4; i++) {
		int nR = r + dr[i];
		int nC = c + dc[i];

		if (nR < 0 || nR >= N || nC < 0 || nC >= N) continue;
		if (visited[nR][nC]) continue;
		if (map[nR][nC] != 0) dfs(nR, nC);
	}

}

int main() {
	int ret = 987654321;

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!visited[i][j] && map[i][j]) {
				cnt++;
				dfs(i, j);
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!map[i][j]) continue;

			memset(visited, false, sizeof(visited));

			std::queue<P> Q;
			Q.push(P(i, j));
			visited[i][j] = true;

			int curr, cR, cC;
			int level = 0;
			while (!Q.empty()) {
				int qSize = Q.size();
				for (int k = 0; k < qSize; k++) {
					cR = Q.front().first;
					cC = Q.front().second;
					Q.pop();

					if (map[cR][cC] != 0 && map[cR][cC] != map[i][j])
						break;

					for (int m = 0; m < 4; m++) {
						int nR = cR + dr[m];
						int nC = cC + dc[m];

						if (nR < 0 || nR >= N || nC < 0 || nC >= N) continue;
						if (visited[nR][nC]) continue;
						if (map[nR][nC] != map[i][j]) {
							visited[nR][nC] = true;
							Q.push(P(nR, nC));
						}
					}
				}

				if (map[cR][cC] != 0 && map[cR][cC] != map[i][j]) break;
				level++;
			}

			level--;
			if (map[cR][cC] != 0 && map[cR][cC] != map[i][j]) {
				ret = std::min(ret, level);
			}

		}
	}

	printf("%d", ret);


}