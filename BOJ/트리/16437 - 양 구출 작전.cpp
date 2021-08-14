#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int N, u;
int isSheep[123456], a[123456];
char ch;
vector<int> adj[123456];

// 모든 정점을 돌면서,
// 재귀적으로 더해준다.

// 여기서 현재 있는 곳이 늑대라면, -1을 곱해준다.
// 그리고 재귀 값이 음수라면, 늑대가 양보다 많은 곳으로 더하지 않는다.
long long dfs(int curr) {
	long long ret = a[curr];
	if (!isSheep[curr]) ret *= -1;

	for (int next : adj[curr]) {
		long long tmp = dfs(next);
		if (tmp > 0) ret += tmp;
	}
	return ret;
}


int main() {
	scanf("%d", &N);
	// 1번 섬 ~ N-1번 섬까지 입력
	for (int i = 1; i < N; i++) {
		getchar();
		scanf("%c %d %d", &ch, a + i, &u);
		u--;

		if (ch == 'S') isSheep[i] = true;

		adj[u].push_back(i);
	}

	printf("%lld\n", dfs(0));

}