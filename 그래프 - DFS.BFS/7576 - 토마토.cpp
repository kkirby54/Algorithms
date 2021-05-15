#include <cstdio>
#include <queue>
#include <algorithm>
#include <vector>

typedef std::pair<int, int> P;

int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0,0,-1,1 };

int M, N;
int map[1000][1000];
std::queue<P> toma;

int main() {
	scanf("%d %d", &M, &N);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 1) toma.push(P(i, j));
		}
	}

	int level = 0;
	// toma에서 뺀다.
	while (!toma.empty()) {
		int qSize = toma.size();
		for (int i = 0; i < qSize; i++) {
			int curr_r = toma.front().first;
			int curr_c = toma.front().second;

			toma.pop();

			for (int j = 0; j < 4; j++) {
				int n_r = curr_r + dr[j];
				int n_c = curr_c + dc[j];

				if (n_r < 0 || n_r >= N || n_c < 0 || n_c >= M) continue;
				if (map[n_r][n_c] == 0) {
					map[n_r][n_c] = 1;
					toma.push(P(n_r, n_c));
				}
			}
		}
		level++;
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			if (map[i][j] == 0) {
				printf("-1");
				return 0;
			}
	}

	printf("%d", level - 1);

}