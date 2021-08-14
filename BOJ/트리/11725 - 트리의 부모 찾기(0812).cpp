#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int N, A, B;
int parent[100001];
vector<int> adj[100001];

void dfs(int curr) {
	for (int next : adj[curr]) {
		if (parent[next] == -1) {
			parent[next] = curr;
			dfs(next);
		}
	}

}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N-1; i++) {
		scanf("%d %d", &A, &B);
		adj[A].push_back(B);
		adj[B].push_back(A);
	}
	fill(parent, parent + N + 1, -1);
	dfs(1);

	for (int i = 2; i <= N; i++) {
		printf("%d\n", parent[i]);
	}


}