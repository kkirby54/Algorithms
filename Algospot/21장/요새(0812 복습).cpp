#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

struct Circle {
	int x, y, r;

	Circle() : x(0), y(0), r(0) {}
	Circle(int x, int y, int r) : x(x), y(y), r(r) {}
	bool operator<(const Circle& a) {
		return r < a.r;
	}
};

int C, N, farsest_node, maxD;
Circle circles[100];
vector<int> adj[100];
bool visited[100];

// a번째 원과 b번째 원 중심 사이 거리.
__inline int getDistance(int a, int b) {
	return (circles[a].x - circles[b].x) * (circles[a].x - circles[b].x) +
		(circles[a].y - circles[b].y) * (circles[a].y - circles[b].y);
}

// a번째, b번째 원의 포함관계 리턴.
// a가 항상 크다고 가정하고 input을 넣는다.
// 문제 조건 - 원들은 항상 겹치지 않기 때문에 가능함.
int CircleIn(int a, int b) {

	if (getDistance(a, b) < (circles[a].r + circles[b].r) * (circles[a].r + circles[b].r))
		return 1;
	return 0;
}

int dfs(int curr, int depth) {
	visited[curr] = true;
	if (maxD < depth) {
		maxD = depth;
		farsest_node = curr;
	}

	int ret = depth;
	for (int next : adj[curr]) {
		if (!visited[next]) {
			ret = max(ret, dfs(next, depth +1));
		}
	}
	return ret;
}


int main() {
	scanf("%d", &C);
	while (C--) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) adj[i].clear();
		fill(visited, visited + N, false);
		farsest_node = 0;
		maxD = 0;

		for (int i = 0; i < N; i++) {
			scanf("%d %d %d", &circles[i].x, &circles[i].y, &circles[i].r);
		}

		sort(circles, circles + N);
		for (int i = 0; i < N; i++) {
			for (int j = i + 1; j < N; j++) {
				// j가 i번째 원을 최소로 둘러싸는 부모
				if (CircleIn(j, i)) {
					adj[j].push_back(i);
					adj[i].push_back(j);
					break;
				}
			}
		}

		dfs(N - 1, 0);
		fill(visited, visited + N, false);
		printf("%d\n", dfs(farsest_node, 0));
	}

}