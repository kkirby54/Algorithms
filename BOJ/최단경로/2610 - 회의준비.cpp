#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int INF = 987654321;
typedef pair<int, int> P;

int N, M,a,b, ret, minVal;
int dist[100][100];
vector<int> adj[100];
bool visited[100];

void dfs(int curr) {
	visited[curr] = true;

	int val = 0;
	for (int i = 0; i < N; i++) {
		if (dist[curr][i] != INF)
			val = max(val, dist[curr][i]);
	}
	if (minVal > val) {
		minVal = val;
		ret = curr;
	}

	for (int next : adj[curr]) {
		if (!visited[next]) {
			dfs(next);
		}
	}
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		fill(dist[i], dist[i] + N, INF);
		dist[i][i] = 0;
	}
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &a, &b);
		a--; b--;
		dist[a][b] = dist[b][a] = 1;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
	int cnt = 0;
	vector<int> ans;
	for (int i = 0; i < N; i++) {
		if (!visited[i]) {
			cnt++;
			ret = i;
			minVal = INF;
			dfs(i);
			ans.push_back(ret + 1);
		}
	}
	sort(ans.begin(), ans.end());
	printf("%d\n", cnt);
	for (int e : ans)printf("%d\n", e);

}