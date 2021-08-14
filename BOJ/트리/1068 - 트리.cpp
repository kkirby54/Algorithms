#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int N, removed, parent[50], root;
vector<int> adj[50];

int leafCnt(int curr) {
	if (adj[curr].empty()) return 1;

	int ret = 0;
	for (int next : adj[curr]) {
		ret += leafCnt(next);
	}
	return ret;
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", parent + i);
		if (parent[i] == -1) root = i;
		else adj[parent[i]].push_back(i);
	}

	scanf("%d", &removed);
	if (removed == root) puts("0");
	else {
		int currNode = parent[removed];
		for (int i = 0; i < adj[currNode].size(); i++) {
			if (adj[currNode][i] == removed) {
				adj[currNode].erase(adj[currNode].begin() + i);
			}
		}
		printf("%d\n", leafCnt(root));
	}
	
}