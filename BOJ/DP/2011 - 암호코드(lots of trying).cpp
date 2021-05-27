#include <cstdio>
#include <cstring>
#include <algorithm>

const int MOD = 1000000;

char str[5005];

int length, dp[5005];
bool isPossible = true;

int password(int curr) {
	if (curr < 0) return 1;

	int& ret = dp[curr];
	if (ret != -1) return ret;

	ret = 0;

	// 안 되는 경우..
	// 1. 0으로 시작할 때
	// 2. 0 이전이 1이나 2가 아닐 때.
	if (str[curr] == '0') {
		if (curr == 0) {
			isPossible = false;
			return 0;
		}
		if (str[curr - 1] != '1' && str[curr - 1] != '2') {
			isPossible = false;
			return 0;
		}
	}

	// password(curr - 1)이 되는 경우.
	// 1~9일 때.
	if (str[curr] != '0') {
		ret += password(curr - 1);
		ret %= MOD;
	}

	// password(curr-2)가 되는 경우
	// 10 ~ 26일 때.
	if (curr - 1 >= 0) {
		int curr_val = str[curr] - '0' + (str[curr - 1] - '0') * 10;

		if (10 <= curr_val && curr_val <= 26) {
			ret += password(curr - 2);
			ret %= MOD;
		}
	}


	return ret;
}


int main() {
	scanf("%s", str);
	length = strlen(str);

	std::fill(dp, dp + length + 1, -1);
	
	int val = password(length - 1);
	if (isPossible) {
		printf("%d", val);
	}
	else printf("0");
	
}