#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

int C,N;
string WildWord;
string word;
int dp[101][101];

// Wildword의 인덱스가 index1
// 비교 단어의 인덱스가 index2
int Waca(int index1, int index2) {
	// Base case.
	// 1. index1이 먼저 끝나면.
	if (index1 == WildWord.size()) {
		if (index2 == word.size()) return 1;
		else return 0;
	}

	// 2. index2가 먼저 끝나면
	if (index2 == word.size()) {
		// index1의 나머지를 본다.
		for (int i = index1; i < WildWord.size(); i++)
			if (WildWord[i] != '*') return 0;
		return 1;
	}

	// 두 문자열 비교해서 리턴.
	if (WildWord[index1] != word[index2]) {
		if (WildWord[index1] == '*' || WildWord[index1] == '?');
		else return 0;
	}

	int& ret = dp[index1][index2];
	if (ret != -1) return ret;

	// 두 문자열을 비교한다.
	ret = Waca(index1 + 1, index2 + 1);

	// WildWord[index1]이 *이라면,
	// 분기가 나뉘게 된다.
	if (WildWord[index1] == '*') {
		ret += Waca(index1, index2 + 1);
		ret += Waca(index1 + 1, index2);
	}
	// 1. 그냥 index2를 ++해주면서 비교한다.
	// Waca(index1, index2+1);
	
	// 2. 하나의 문자로 취급. index1을 늘려서 탈출한다.

	return ret;
}

int main() {
	cin >> C;
	for (int t = 0; t < C; t++) {

		cin >> WildWord;
		cin >> N;
		vector<string> ret;

		for (int i = 0; i < N; i++) {
			cin >> word;

			memset(dp, -1, sizeof(dp));

			if (Waca(0, 0)) {
				ret.push_back(word);
			}
		}

		sort(ret.begin(), ret.end());

		for (auto& e : ret) cout << e << "\n";
	}
}
