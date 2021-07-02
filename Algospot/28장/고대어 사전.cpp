#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int C, N;
string word[1000];
vector<int> adj[26];
bool visited[26];
vector<int> ret;

void dfs(int curr) {
	visited[curr] = true;

	for (int i = 0; i < 26; i++) {
		if (adj[curr][i] && !visited[i]) {
			dfs(i);
		}
	}

	ret.push_back(curr);
}

int main() {
	cin >> C;

	for (int t = 0; t < C; t++) {
		cin >> N;

		// adj를 다 0으로
		for (int i = 0; i < 26; i++) {
			adj[i] = vector<int>(26, 0);
		}

		fill(visited, visited + 26, false);
		ret.clear();
		bool isPossible = true;

		// 단어를 받는다.
		for (int i = 0; i < N; i++) {
			cin >> word[i];
		}

		for (int i = 0; i < N - 1; i++) {
			
			// word[i+1]과 비교한다.
			int len = min(word[i].size(), word[i + 1].size());

			for (int k = 0; k < len; k++) {
				// 다르다면 
				if (word[i][k] != word[i + 1][k]) {
					int u = word[i][k] - 'a';
					int v = word[i + 1][k] - 'a';
					// u -> v로 이어준다는 의미
					adj[u][v] = 1;
					break;
				}
			}
		}

		for (int i = 25; i >= 0; i--) {
			if (!visited[i]) {
				dfs(i);
			}
		}

		reverse(ret.begin(), ret.end());

		// 뒤집은 걸 갖다가 확인
		for (int i = 0; i < 26; i++) {
			for (int j = i + 1; j < 26; j++) {
				// ret[j]에서 ret[i]로 가는게 있으면 안된다고.
				if (adj[ret[j]][ret[i]]) {
					isPossible = false;
					break;
				}
			}
			if (!isPossible) break;
		}

		if (isPossible) {
			for (int e : ret)
				cout << char(e + 'a');
			puts("");
		}
		else puts("INVALID HYPOTHESIS");
	}

}