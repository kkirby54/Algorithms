#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

typedef pair<int, int> P;
int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };

int T, w, h;
char board[1001][1001];
bool visited[1001][1001];

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &w, &h);
		memset(visited, false, sizeof(visited));
		bool isPossible = false;
		queue<P> fire, human;

		for (int i = 0; i < h; i++) {
			scanf("%s", board[i]);
			for (int j = 0; j < w; j++) {
				if (board[i][j] == '@' || board[i][j] == '*')
				{
					if (board[i][j] == '@') human.push(P(i, j));
					else fire.push(P(i, j));
					visited[i][j] = true;
				}
			}
		}

		int level = 0;
		while (!human.empty()) {
			int qSize = fire.size();
			for (int i = 0; i < qSize; i++) {
				int r = fire.front().first;
				int c = fire.front().second;
				fire.pop();

				for (int j = 0; j < 4; j++) {
					int nR = r + dr[j];
					int nC = c + dc[j];

					if (nR < 0 || nR >= h || nC < 0 || nC >= w) continue;
					if (visited[nR][nC]) continue;
					if (board[nR][nC] == '.') {
						board[nR][nC] = '*';
						visited[nR][nC] = true;
						fire.push(P(nR, nC));
					}
				}

			}
			// 이번엔 human
			qSize = human.size();
			for (int i = 0; i < qSize; i++) {
				int r = human.front().first;
				int c = human.front().second;
				human.pop();

				if (r == 0 || r == h - 1 || c == 0 || c == w - 1) {
					//printf("찾았어\n");
					isPossible = true;
					break;
				}
				
				for (int j = 0; j < 4; j++) {
					int nR = r + dr[j];
					int nC = c + dc[j];

					if (nR < 0 || nR >= h || nC < 0 || nC >= w) continue;
					if (visited[nR][nC]) continue;
					if (board[nR][nC] == '.') {
						board[nR][nC] = '@';
						visited[nR][nC] = true;
						human.push(P(nR, nC));
					}
				}
			}
			if (isPossible) break;
			level++;
		}
		if (isPossible) {
			printf("%d\n", level + 1);
		}
		else puts("IMPOSSIBLE");


	}

}