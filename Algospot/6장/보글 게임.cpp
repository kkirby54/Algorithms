#include <cstdio>
#include <cstring>
#include <algorithm>

int dr[] = { -1,-1,-1, 0, 0, 1, 1, 1 };
int dc[] = { -1,0,1, -1, 1, -1, 0, 1 };
int dp[6][6][11];

int C, N, len;
char board[6][6], word[11];

int boggle(int r, int c, int cnt) {
	if (cnt == len - 1 &&
		board[r][c] == word[cnt]) return 1;

	int& ret = dp[r][c][cnt];
	if (ret != -1) return ret;

	ret = 0;
	for (int i = 0; i < 8; i++) {
		int nR = r + dr[i];
		int nC = c + dc[i];

		if (r < 0 || r >= 5 || c < 0 || c >= 5) continue;

		// 만약 board[nR][nC]가 cnt+1이면 그럼
		if (board[nR][nC] == word[cnt + 1])
			if (boggle(nR, nC, cnt + 1))
				return ret = 1;

	}

	return ret;
}

int main() {
	scanf("%d", &C);
	
	for (int t = 0; t < C; t++) {
		for (int i = 0; i < 5; i++) {
			scanf("%s", board[i]);
		}

		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%s", word);
			len = strlen(word);

			memset(dp, -1, sizeof(dp));

			bool isPossible = false;
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					if (board[i][j] == word[0]) {
						if (boggle(i, j, 0))
							isPossible = true;
					}
				}
			}
			printf("%s ", word);

			if (isPossible) puts("YES");
			else puts("NO");

		}

	}

}