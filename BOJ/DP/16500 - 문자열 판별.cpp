#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

string S;
string A[101];
int N, Slen;
int dp[101];

int solve(int Spos) {
	if (Spos == Slen) return 1;

	int& ret = dp[Spos];
	if (ret != -1) return ret;
	ret = 0;

	// A 전체를 다 돌아야 한다.
	for (int i = 0; i < N; i++) {
		// 첫 문자가 같다면, 그리고 범위가 옳다면
		if (A[i][0] == S[Spos] &&
			Slen >= Spos + A[i].size()) {
			// 거기서 또 A[i]의 문자열 개수만큼 본다.
			int len = A[i].size();
			bool isPossible = true;

			for (int j = 0; j < len; j++) {
				if (A[i][j] != S[Spos + j]) {
					isPossible = false;
					break;
				}
			}
			// 가능하면 쓰고 넘긴다.
			if (isPossible) {
				ret += solve(Spos + len);
			}
		}
	}
	
	return ret;
}

int main() {
	cin >> S;
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> A[i];

	memset(dp, -1, sizeof(dp));
	Slen = S.size();
	// A에 포함된 문자열 사용해서,
	// S를 만들어야 한다.
	int ret = solve(0) > 0 ? 1 : 0;
	cout << ret;
}