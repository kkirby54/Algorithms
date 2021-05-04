#include <cstdio>
#include <algorithm>

int N, dp[1000001];

int make_one(int curr) {
	// 종료 조건
	if (curr == 1) return 0;

	int& ret = dp[curr];
	if (ret) return ret;

	// 실제 계산
	ret = make_one(curr - 1) + 1;
	if (curr % 3 == 0) ret = std::min(ret, make_one(curr / 3) + 1);
	if (curr % 2 == 0) ret = std::min(ret, make_one(curr / 2) + 1);

	return ret;
}

int main() {
	scanf("%d", &N);

	printf("%d", make_one(N));

}