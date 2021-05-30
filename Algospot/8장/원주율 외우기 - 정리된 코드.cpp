#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

int dp[10005];
char nums[10005];
int C, len;

// [a, b]의 점수 return
int get_score(int a, int b) {
	int length = b - a + 1;

	// 1. 다 같을 경우.
	bool isSame = true;
	for (int i = 1; i < length; i++) {
		if (nums[a + i] != nums[a]) {
			isSame = false; break;
		}
	}

	if (isSame) return 1;

	// 4. 번갈아 가며 나타날 때.
	bool isAlternate = true;
	for (int i = 2; i < length; i++) {
		if (nums[a + i] != nums[a + i % 2]) {
			isAlternate = false; break;
		}
	}

	// 등차 수열 확인.
	int d = nums[a + 1] - nums[a];
	bool isProgressive = true;
	for (int i = 2; i < length; i++) {
		if (nums[a + i] - nums[a + i - 1] != d) {
			isProgressive = false;
			break;
		}
	}

	// 2. 등차면서 d = 1, -1 -> 단조 증가 or 감소
	if (isProgressive && abs(d) == 1) return 2;

	// 4. 번갈아 나타나는 경우
	if (isAlternate) return 4;
	if (isProgressive) return 5;

	return 10;
}


// start부터 시작한 최소 점수.
int PI(int start) {
	if (start >= len) return 0;

	int& ret = dp[start];
	if (ret != -1) return ret;

	ret = 987654321;

	// 3개, 4개, 5개 케이스
	for (int L = 3; L <= 5; L++) {
		if (start + L <= len)
			ret = std::min(ret, PI(start + L) + get_score(start, start + L - 1));
	}

	return ret;
}

int main() {
	scanf("%d", &C);
	for (int t = 0; t < C; t++) {
		scanf("%s", nums);
		
		memset(dp, -1, sizeof(dp));
		len = strlen(nums);

		printf("%d\n", PI(0));

	}

}