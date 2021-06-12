#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

int C, N;
int farest_node;
int curr_max;

vector<int> adj[101];
bool visited[101];

struct Circle {
	int x, y, r;

	Circle() : x(0), y(0), r(0) {}
	Circle(int x, int y, int r) : x(x), y(y), r(r) {}
	bool operator<(const Circle& a) {
		return r < a.r;
	}
};

// a번째 원과 b번째 원의 포함관계를 알아내야 한다.
// a가 b를 포함하면 1을 리턴한다.
int CircleRelation(Circle a, Circle b) {
	int distance = (int)sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));

	if (distance < (a.r + b.r)) {
		if (a.r > b.r) return 1;
	}
	return 0;
}


void dfs(int curr, int distance) {
	visited[curr] = true;

	if (distance > curr_max) {
		farest_node = curr;
		curr_max = distance;
	}

	int ret = 0;

	for (int next : adj[curr]) {
		if (visited[next]) continue;

		dfs(next, distance + 1);
	}
}

int main() {
	scanf("%d", &C);
	
	for (int t = 0; t < C; t++) {
		scanf("%d", &N);

		Circle circles[100];
		for (int i = 0; i < N; i++)
			adj[i].clear();

		std::fill(visited, visited + N, false);
		curr_max = -987654321;
		farest_node = 0;
		
		// i번째 원에 대한 정보.
		for (int i = 0; i < N; i++) {
			scanf("%d %d %d", &circles[i].x, &circles[i].y, &circles[i].r);
		}

		// 반지름 기준으로 sort한다.
		// 그러면 작은 원부터 주르륵 나올텐데,
		// for문을 돌리면서, 자기를 포함하고 있는 가장 작은 원을 만나면 처리 하고 break 한다.
		std::sort(circles, circles + N);
		
		for (int i = 0; i < N; i++) {
			for (int j = i + 1; j < N; j++) {
				if (CircleRelation(circles[j], circles[i])) {
					adj[i].push_back(j);
					adj[j].push_back(i);
					break;
				}
			}
		}
		
		// 루트부터. 즉 N-1에서 dfs 돌린다.
		// 그러면 제일 먼 노드를 리턴한다.

		dfs(N - 1, 0);

		// 거기서 다시 dfs 돌려서 젤 먼 노드까지의 길이를 구한다.
		std::fill(visited, visited + N, false);
		
		dfs(farest_node, 0);
		printf("%d\n", curr_max);
	}

}