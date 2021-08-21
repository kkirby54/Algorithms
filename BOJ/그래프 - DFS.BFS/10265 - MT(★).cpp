#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

typedef pair<int, int> P;

int N, K, X;
int adj[1000];
vector<int> undirected[1000];
bool visited[1000], finished[1000];

vector<P> ret;
vector<P> candidate;

// 사이클을 판단하고, 사이클이 있는 경우에
// 몇 개의 정점이 속해있는지 알아낸다.
void dfs(int curr) {
	visited[curr] = true;

	int next = adj[curr];
	if (!visited[next]) {
		dfs(next);
	}
	else {
		if (!finished[next]) {
			int cnt = 0;
			int temp = curr;
			do {
				cnt++;
				temp = adj[temp];
			} while (temp != curr);
			ret.push_back(P(cnt, curr)); // cnt개의 정점을 꼭 써야한다. curr이 속한 컴포넌트에.
		}

	}
	finished[curr] = true;
}

// 무방향 그래프에서 정점 개수를 센다.
int dfs2(int curr) {
	visited[curr] = true;

	int cnt = 1;
	for (int next : undirected[curr]) {
		if (!visited[next]) {
			cnt += dfs2(next);
		}
	}

	return cnt;
}

int dp[1000][1000];

int MT(int curr, int remain) {
	if (curr == candidate.size()) return 0;

	int& ret = dp[curr][remain];
	if (ret != -1)return ret;

	// curr에 있는 걸 쓰는데,
	// 얼마나 쓸지는 모른다.
	// minVal ~ maxVal까지 쓸 수 있다.
	int minVal = candidate[curr].first;
	int maxVal = candidate[curr].second;

	ret = MT(curr + 1, remain);

	// 쓰는 경우에는, 쓰고 넘김.
	for (int x = minVal; x <= maxVal; x++) {
		// x만큼 쓴다.
		if (remain - x >= 0)
			ret = max(ret, MT(curr + 1, remain - x) + x);
	}

	return ret;
}

int main() {
	scanf("%d %d", &N, &K);
	//fill(adj, adj + N, -1);
	memset(dp, -1, sizeof(dp));

	for (int i = 0; i < N; i++) {
		scanf("%d", &X);
		adj[i] = X - 1;

		undirected[i].push_back(X - 1);
		undirected[X - 1].push_back(i);
	}

	// 사이클에 포함된 정점을 찾아본다.
	for (int i = 0; i < N; i++) {
		if (!visited[i]) {
			dfs(i);
		}
	}

	// 이제 무방향 그래프에서 해결한다.
	fill(visited, visited + N, false);
	for (auto& E : ret){
		int curr = E.second;
		if (!visited[curr]) {
			int maxCnt = dfs2(curr);

			candidate.push_back(P(E.first, maxCnt));
		}
	}

	// 그럼 candidate에 있는 것들을
	// 적절히 사용해서.. K 이하를 맞춰야 한다.
	int ans = MT(0, K);
	printf("%d\n", ans);
}

