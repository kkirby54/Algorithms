#include <cstdio>
#include <queue>
#include <algorithm>

typedef std::pair<int, int> P;
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0,0,-1,1 };

int M, N;
int map[100][100];
bool visited[100][100];

int main() {
	scanf("%d %d", &N, &M);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%1d", &map[i][j]);
		}
	}

	std::queue<P> Q;
	Q.push(P(0, 0));
	visited[0][0] = true;

	int level = 0;
	int curr_r, curr_c;
	while (!Q.empty()) {
		int qSize = Q.size();
		for (int i = 0; i < qSize; i++) {
			curr_r = Q.front().first;
			curr_c = Q.front().second;
			if (curr_r == N-1 && curr_c == M-1)
				break;

			Q.pop();

			for (int j = 0; j < 4; j++) {
				int n_r = curr_r + dr[j];
				int n_c = curr_c + dc[j];

				if (n_r < 0 || n_r >= N || n_c < 0 || n_c >= M) continue;
				if (map[n_r][n_c] == 1 && !visited[n_r][n_c]) {
					visited[n_r][n_c] = true;
					Q.push(P(n_r, n_c));
				}
			}
		}
		level++;
		if (curr_r == N - 1 && curr_c == M - 1) break;
	}

	printf("%d", level);

}