#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

int C, N;
char words[1000][21];
vector<vector<int>> adj; // 인접 행렬. 알파벳들 간의 선후관계.
bool visited[26], finished[26];
bool isPossible;
char ret[26];
int retNums;

// curr이랑 연결된 애들.
void dfs(int curr) {
	visited[curr] = true;

	for (int i = 0; i < 26; i++) {
		if (!visited[i] && adj[curr][i]) {
			dfs(i);
		}
		if (visited[i] && adj[curr][i]) {
			if (finished[i]) continue;
			else {
				// 끝나있지 않다면, dfs(i)가 실행 중이다. 즉 사이클이다.
				isPossible = false;
				break;
			}
		}
	}
	ret[retNums++] = curr + 'a';
	finished[curr] = true;
}

int main() {
	scanf("%d", &C);
	while (C--) {
		scanf("%d", &N);
		adj = vector<vector<int>>(26, vector<int>(26));
		fill(visited, visited + 26, false);
		fill(finished, finished + 26, false);
		isPossible = true;

		retNums = 0;
		for (int i = 0; i < N; i++) {
			scanf("%s", words[i]);
		}

		// 이제 words들을 돌면서, 선후관계를 확인.
		for (int i = 0; i < N-1; i++) {
			// i번째와 i+1번째를 비교한다.
			// 달라지는 부분을 캐치한다.
			int idx1 = 0, idx2 = 0;
			int len1 = strlen(words[i]);
			int len2 = strlen(words[i + 1]);

			while (idx1 < len1 &&
				idx2 < len2 &&
				words[i][idx1] == words[i + 1][idx2]) {
				idx1++;
				idx2++;
			}

			if (idx1 < len1 &&
				idx2 < len2) {
				char a = words[i][idx1];
				char b = words[i + 1][idx2];

				// a -> b순이다.
				adj[a - 'a'][b - 'a'] = 1;
			}
		}

		for (int i = 25; i >= 0; i--) {
			if (!visited[i]) {
				dfs(i);
			}
		}

		if (!isPossible) puts("INVALID HYPOTHESIS");
		else {
			for (int i = 25; i >= 0; i--) {
				printf("%c", ret[i]);
			}
			puts("");
		}

	}

}
