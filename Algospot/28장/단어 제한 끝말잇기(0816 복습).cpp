#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
typedef pair<int, int> P;

int C, N;
vector<vector<int>> adj;
vector<P> wordRelation[26]; // wordRelaton[i].push_back(P(j, word));
char words[100][11];
int indegree[26];
int outdegree[26];
int total_edges;
vector<int> ret;

int isCircuitOrTrail() {
	int plus = 0, minus = 0, zero = 0;
	for (int i = 0; i < 26; i++) {
		int delta = outdegree[i] - indegree[i];
		if (delta == 0) zero++;
		else if (delta == 1) plus++;
		else minus++;
	}

	// 전부 다 zero라면 회로
	if (!plus && !minus) return 2;
	else if (plus == 1 && minus == 1) return 1;
	else return 0;
}

void getEuler(int curr) {
	for (int next = 0; next < 26; next++) {
		while (adj[curr][next]) {
			adj[curr][next]--;
			total_edges++;
			getEuler(next);
		}
	}

	ret.push_back(curr);
}


int main() {
	scanf("%d", &C);
	while (C--) {
		scanf("%d", &N);
		fill(indegree, indegree + 26, 0);
		fill(outdegree, outdegree + 26, 0);
		adj = vector<vector<int>>(26, vector<int>(26, 0));
		ret.clear();
		for (int i = 0; i < 26; i++) wordRelation[i].clear();

		for (int i = 0; i < N; i++) {
			scanf("%s", words[i]);

			int len = strlen(words[i]);
			int a = words[i][0] - 'a';
			int b = words[i][len-1] - 'a';

			wordRelation[a].push_back(P(b, i)); // a->b로 가는 데 word[i]를 이용한다.
			indegree[b]++;
			outdegree[a]++;
			adj[a][b]++;
		}

		int isPossible = isCircuitOrTrail();
		if (isPossible) {
			total_edges = 0;
			if (isPossible == 2) {
				// 아무 점에서 오일러 회로.
				for (int i = 0; i < 26; i++) {
					if (outdegree[i]) {
						getEuler(i);
						break;
					}
				}
			}
			// 나가는 점이 더 많은 곳에서 trail
			else {
				for (int i = 0; i < 26; i++) {
					if ((outdegree[i] - indegree[i]) % 2 == 1) {
						getEuler(i);
						break;
					}
				}
			}
			
			if (total_edges != N) {
				puts("IMPOSSIBLE");
				break;
			}

			// 뒤집는다.
			reverse(ret.begin(), ret.end());

			for (int i = 1; i < ret.size(); i++) {
				// ret[i-1]과 ret[i]를 이어줘야 한다.
				int a = ret[i - 1];
				int b = ret[i];

				for (int i = 0; i < wordRelation[a].size(); i++) {
					auto e = wordRelation[a][i];
					if (e.first == b) {
						printf("%s ", words[e.second]);
						wordRelation[a].erase(wordRelation[a].begin() + i);
						break;
					}
				}
			}
			puts("");
		}
		else {
			puts("IMPOSSIBLE");
		}

	}
}