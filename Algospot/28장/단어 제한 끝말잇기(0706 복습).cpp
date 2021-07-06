#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

// g -> d : god
// d -> g : dog
// d -> n : dragon
// n -> d : need.

int adj[26][26];
int indegree[26];
int outdegree[26];
string tmp;
int C, N;

// wordsRelation[0][1]은 a -> b로 가는 단어가 수록되어있다.
vector<string> wordsRelation[26][26];
vector<string> ret; // 결과값을 저장할 string
vector<int> circuit; // 결과값 저장 배열. 이걸 이용해서 ret 만듦.
// ************* 
// ************* 
// FUNCTION area
// ************* 
// ************* 

bool isEulerCircuitOrTrail() {
	// Circuit은 모든 점 짝수
	// Trail은 나가는 점 + 1, 들어오는 점 - 1임.

	int plus1 = 0, minus1 = 0;
	for (int i = 0; i < 26; i++) {
		int nums = indegree[i] - outdegree[i];

		if (nums == -1) minus1++;
		else if (nums == 1) plus1++;

	}
	
	// 다 했는데 plus1과 minus1이 아예 없거나(Circuit).
	// 또는 각각 1개만 존재해야 함
	if (plus1 == 0 && minus1 == 0) return true;
	if (plus1 == 1 && minus1 == 1) return true;
	return false;
}

void getEulerCircuit(int here) {
	for (int i = 0; i < 26; i++) {
		// adj[here][i]를 본다.
		while (adj[here][i] > 0) {
			adj[here][i]--;
			getEulerCircuit(i);
		}

	}
	// 재귀 끝나고 반환하는 과정에서 push
	circuit.push_back(here);
}


// 이제 wordRelation을 돌면서,
// 어떻게 돌지 판단한다.
// 그냥 그 때 만든 함수처럼.
// 예를 들어, d g n 이렇게 되있는 오일러에 대해서
// 어떤식으로 훑을지를 저장하라~ 이말이야
void getEulerCircuitOrTrail() {
	// 일단 시작점을 찾아야해. 어떻게?
	// 트레일일 경우에는...
	// 아무 데서나 시작하면 ㅈ되고, 무조건
	// outdegree가 indegree + 1인 곳에서 시작해.

	for (int i = 0; i < 26; i++) {
		if (outdegree[i] == indegree[i] + 1) {
			// 여기서 시작하셈.
			getEulerCircuit(i);
			return;
		}
	}
	
	// 그런 곳이 없다면 그냥 아무 데서나 시작해
	for (int i = 0; i < 26; i++) {
		if (outdegree[i]) {
			getEulerCircuit(i);
			return;
		}
	}
}



int main() {
	cin >> C;

	for (int t = 0; t < C; t++) {
		cin >> N;

		// 초기화.
		memset(adj, 0, sizeof(adj));
		fill(indegree, indegree + 26, 0);
		fill(outdegree, outdegree + 26, 0);
		ret.clear();
		circuit.clear();
		for (int i = 0; i < 26; i++) {
			for (int j = 0; j < 26; j++)
				wordsRelation[i][j].clear();
		}

		for (int i = 0; i < N; i++) {
			cin >> tmp;

			int start = tmp[0] - 'a';
			int end = tmp.back() - 'a';
			adj[start][end]++;
			indegree[end]++;
			outdegree[start]++;

			// 단어 사이 저장.
			wordsRelation[start][end].push_back(tmp);
		}

		// 이제 저장됨.
		// 이제 이 간선 다 쓰면서 완료할 수 있는지?
		// EulerCircuit 판단.
		// Circuit일 수도, Trail일 수도.
		if (isEulerCircuitOrTrail()) {
			getEulerCircuitOrTrail();
			// 이제 그럼 circuit에 저장됐다.
			reverse(circuit.begin(), circuit.end());

			// 이제 거기 적힌걸 하나씩 출력하면서 제거해.
			for (int i = 0; i < circuit.size() - 1; i++) {
				// circuit[i]에서 circuit[i+1]로 가는거.
				int curr = circuit[i];
				int next = circuit[i + 1];

				// 그걸 wordsRelation에서 찾기
				
				cout << wordsRelation[curr][next].back() << " ";
				wordsRelation[curr][next].pop_back();

			}
			cout << "\n";

		}
		else {
			cout << "IMPOSSIBLE\n";
		}
	}

}