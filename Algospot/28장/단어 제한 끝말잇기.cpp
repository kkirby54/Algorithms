#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int C, N;
vector<string> graph[26][26];
vector<vector<int>> adj;
vector<int> indegree, outdegree;
string word;

void getEulerCircuit(int here, vector<int>& circuit) {
	for (int there = 0; there < adj[here].size(); there++) {
		while (adj[here][there]) {
			adj[here][there]--;
			getEulerCircuit(there, circuit);
		}
	}
	circuit.push_back(here);
}

// 그래프의 오일러 서킷 or 트레일을 반환해야 한다.
// 일단 있다고 가정하자.
vector<int> getEulerTrailOrCircuit() {
	// 일단 모든 점을 보면서.. indegree, outdegree를 확인해야한다.

	vector<int> circuit;

	for (int i = 0; i < 26; i++) {
		// 트레일을 찾아보기?
		
		// 나가는 점 == 들어오는 점 + 1
		// 그러면 얘가 바로 시작점
		if (outdegree[i] == indegree[i] + 1) {
			getEulerCircuit(i, circuit);
			return circuit;
		}
	}

	for (int i = 0; i < 26; i++) {
		// 서킷
		if (outdegree[i]) {
			getEulerCircuit(i, circuit);
			return circuit;
		}
	}

	// 다 실패한 경우.
	return circuit;
}

// 얘가 되는지 안되는지 여부를 확인한다.
bool checkEuler() {

	int plus1 = 0, minus1 = 0;

	for (int i = 0; i < 26; i++) {
		int tmp = outdegree[i] - indegree[i];

		// tmp는 -1, 0, 1 중에 하나다.
		if (tmp == -1) minus1++;
		else if (tmp == 0) continue;
		else if (tmp == 1) plus1++;
		else return false;
	}

	// 다 하고 나면 plus1 또는 minus1은 각각 1개 또는 아예 없어야 함/
	return (plus1 == 1 && minus1 == 1) || (plus1 == 0 && minus1 == 0);
}

int main() {
	cin >> C;

	for (int t = 0; t < C; t++) {
		cin >> N;
		
		for (int i = 0; i < 26; i++) {
			for (int j = 0; j < 26; j++)
				graph[i][j].clear();
		}
		adj = vector<vector<int>>(26, vector<int>(26, 0));
		indegree = outdegree = vector<int>(26, 0);

		for (int i = 0; i < N; i++) {
			cin >> word;

			int start = word[0] - 'a', end = word.back() -'a';

			graph[start][end].push_back(word);
			adj[start][end]++;
			indegree[end]++;
			outdegree[start]++;
		}

		// 오일러 서킷 or 트레일인지 판단해야한다.
		if (checkEuler()) {
			vector<int> ret = getEulerTrailOrCircuit();
			if (ret.size() != N + 1) {
				puts("IMPOSSIBLE");
				continue;
			}
			reverse(ret.begin(), ret.end());
			string result;

			for (int i = 1; i < ret.size(); i++) {
				int a = ret[i - 1], b = ret[i];

				// a -> b로 간다.
				if (result.size()) result += " ";
				result += graph[a][b].back();
				graph[a][b].pop_back();
			}

			cout << result << "\n";
		}
		else {
			puts("IMPOSSIBLE");
		}
		
		/*

		for (int i = 0; i < 26; i++) {
			cout << char(i + 'a') << "에 대해\n";
			for (int j = 0; j < 26; j++) {
				if (graph[i][j].empty()) continue;

				for (auto e : graph[i][j])
					cout << e << ", ";
				puts("");
			}

		}
		*/

	}

}