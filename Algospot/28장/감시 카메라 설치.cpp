#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int C, G, H, a, b;
vector<int> adj[1000];
bool visited[1000];

const int UNWATCHED = 0;
const int WATCHED = 1;
const int INSTALLED = 2;

// 총 설치된 카메라 수
int installed;

// dfs가 반환하는 값은..
// 지금 값의 정보
int dfs(int curr) {
	visited[curr] = true;

	int children[3] = { 0, };
	for (int next : adj[curr]) {
		if (!visited[next]) {
			++children[dfs(next)];
		}
	}

	// 그럼 children에는 unwatched, watched, installed.

	// 감시되지 않은 애가 있다면
	if (children[UNWATCHED]) {
		++installed;
		return INSTALLED;
	}

	// 자식 중에 installed된 애가 있으면
	if (children[INSTALLED]) {
		return WATCHED;
	}

	return UNWATCHED;
}


int main() {
	scanf("%d", &C);

	for (int t = 0; t < C; t++) {
		scanf("%d %d", &G, &H);

		installed = 0;
		for (int i = 0; i < G; i++) adj[i].clear();
		fill(visited, visited + G, false);
		for (int i = 0; i < H; i++) {
			scanf("%d %d", &a, &b);

			adj[a].push_back(b);
			adj[b].push_back(a);
		}

		for (int i = 0; i < G; i++) {
			if (!visited[i] && dfs(i) == UNWATCHED) {
				installed++;
			}
		}
		printf("%d\n", installed);
	}

}