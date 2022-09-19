#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <set>
using namespace std;
typedef pair<int, int> P;

string S, T;
queue<string> Q;
set<string> visited;

int main() {
	cin >> S >> T;
	Q.push(T);
	visited.insert(T);

	if (S.size() > T.size()) {
		cout << 0;
		return 0;
	}

	while (!Q.empty()) {
		string curr = Q.front();
		Q.pop();

		if (curr == S) {
			cout << 1;
			return 0;
		}
		else if (curr.empty()) continue;

		// A »©±â.
		if (curr.at(curr.size() - 1) == 'A') {
			string next = curr.substr(0, curr.size() - 1);
			Q.push(next);
		}
		// B »©°í reverse
		else {
			curr.pop_back();
			reverse(curr.begin(), curr.end());
			Q.push(curr);
		}

	}

	cout << 0;
}

//int N;
//int d, p;
//P DP[10000];
//
//int main() {
//	scanf("%d", &N);
//	for (int i = 0; i < N; i++) {
//		scanf("%d %d", &p, &d);
//		DP[i] = P(-d, -p);
//	}
//
//	sort(DP, DP + N);
//	int day = 1;
//	int ret = 0;
//
//	for (int i = 0; i < N; i++) {
//		printf("%d %d\n", DP[i].first, DP[i].second);
//
//	}
//
//
//	printf("%d", -ret);
//
//}