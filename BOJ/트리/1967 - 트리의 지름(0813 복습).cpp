#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int, int> P;

int N, u, v, w;
vector<P> adj[10000];
bool visited[10000];

int longest;

int getHeight(int curr) {
	visited[curr] = true;
	if (adj[curr].empty()) return 0;

	int fVal = 0, sVal = 0;
	for (auto& p : adj[curr]) {
		int next = p.first, distance = p.second;
		if (!visited[next]) {
			int val = distance + getHeight(next);
			if (val > fVal) {
				sVal = fVal;
				fVal = val;
			}
			else if (val > sVal) {
				sVal = val;
			}
		}
	}
	longest = max(longest, fVal + sVal);
	return fVal;
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N-1; i++) {
		scanf("%d %d %d", &u, &v, &w);
		adj[u - 1].push_back(P(v - 1, w));
		adj[v - 1].push_back(P(u - 1, w));
	}

	getHeight(0);
	printf("%d\n", longest);

}