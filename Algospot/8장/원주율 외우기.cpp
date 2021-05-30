#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

const int INF = 987654321;

int C;
string nums;
int dp[10005];

// nums[a,b]의 점수 return 함수
int classify(int a, int b) {
	// a부터 b까지의 string 빼옴
	string N = nums.substr(a, b - a + 1);

	int len = b - a + 1;
	// 다 같은 거니까
	if (N == string(N.size(), N[0])) return 1;

	// 3. 번갈아가는 경우
	// [0] [2] [4]
	// [1] [3]

	bool alternate = true;
	for (int i = 2; i < len; i++) {
		if (N[i] != N[i % 2]) {
			alternate = false;
			break;
		}
	}

	bool isPossible = true;
	// 2. 단조 증가/감소
	for (int i = 1; i < len; i++) {
		if (N[i] - N[i - 1] != 1) {
			isPossible = false;
			break;
		}
	}

	if (isPossible) return 2;

	isPossible = true;
	for (int i = 1; i < len; i++) {
		if (N[i] - N[i - 1] != -1) {
			isPossible = false;
			break;
		}
	}
	if (isPossible) return 2;

	if (alternate) return 4;

	isPossible = true;
	// 4. 등차를 이룰 떄
	int d = N[1] - N[0];
	for (int i = 2; i < len; i++) {
		if (N[i] - N[i - 1] != d) {
			isPossible = false; break;
		}
	}
	if (isPossible) return 5;

	return 10;
}


// start부터 시작한..
// 최대 길이.
int PI(int start) {
	if (start >= nums.size()) return 0;

	int& ret = dp[start];
	if (ret != -1) return ret;

	ret = 987654321;

	// 3, 4, 5중에 하나니까
	
	for (int L = 3; L <= 5; L++) {
		if (start + L <= nums.size())
			ret = std::min(ret, PI(start + L) + classify(start, start + L - 1));
	}

	return ret;
}

int main() {
	cin >> C;

	for (int t = 0; t < C; t++) {
		cin >> nums;

		fill(dp, dp + 10005, -1);

		printf("%d\n", PI(0));
	}
}