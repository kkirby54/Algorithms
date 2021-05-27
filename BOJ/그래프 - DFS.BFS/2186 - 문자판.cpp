#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

typedef std::pair<int, int> P;
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };


char map[105][105];
char str[85];
int N, M, K, len;

int dp[105][105][85];

// (r,c)와 지나온 횟수 count.
int dfs(int r, int c, int count) {

	// count가 len-1이면 stop.
	if (count == len - 1) {
		if (map[r][c] == str[len - 1]) {
			return 1;
		}
		return 0;
	}

	int& ret = dp[r][c][count];
	if (ret != -1) return ret;

	ret = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 1; j <= K; j++) {
			int nR = r + j * dr[i];
			int nC = c + j * dc[i];

			if (nR < 0 || nR >= N || nC < 0 || nC >= M) continue;
			
			if (map[nR][nC] == str[count+1])
				ret += dfs(nR, nC, count + 1);
		}
	}

	return ret;
}



int main() {
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < N; i++) {
		scanf("%s", map[i]);
	}
	scanf("%s", str);

	len = strlen(str);

	std::vector<P> vec;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == str[0]) {
				vec.push_back(P(i, j));
			}
		}
	}

	int cnt = 0;
	memset(dp, -1, sizeof(dp));

	for (auto p : vec) {
		cnt += dfs(p.first, p.second, 0);
	}

	printf("%d", cnt);
}