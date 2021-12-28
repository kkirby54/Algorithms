#include <cstdio>
#include <cstring>

int need[10] = { 6, 2, 5, 5, 4, 5, 6, 3, 7, 6 };
int T, N;
int dp[101][101][2];

// remain개를 써서 K자리 수를 만들기가 가능?
bool isPossible(int remain, int K, bool isFirst) {
	if (K < 0) return 0;
	if (remain == 0) {
		return K == 0;
	}

	int& ret = dp[remain][K][isFirst];
	if (ret != -1) return ret;

	ret = 0;
	for (int i = 0; i < 10; i++) {
		if (i == 0 && isFirst) continue;
		if (remain - need[i] < 0) continue;

		if (isPossible(remain - need[i], K - 1, false)) {
			ret = 1;
			break;
		}
	}
	return ret;
}

// remain개 써서, K자리를 써서 구할 수 있는 경우의 수.
int match(int remain, int K, bool isFirst) {
	if (K < 0) return 0;
	int& ret = dp[remain][K][isFirst];
	if (ret != -1) return ret;

	if (remain == 0) {
		if (K == 0) return 1;
		return 0;
	}

	ret = 0;
	for (int i = 0; i < 10; i++) {
		if (i == 0 && isFirst) continue;

		if (remain - need[i] >= 0)
			ret += match(remain - need[i], K - 1, false);
	}

	return ret;
}

int ret[100];
// K자리 중에서.
void skip(int remain, int K, bool isFirst, int loc, int p) {
	if (K == 0) return;

	int pivot = 0;
	for (int i = 0; i < 10; i++) {
		if (i == 0 && isFirst) continue;

		// 15를 3개로 표현한다고 하자.
		// 그럼 일단 1.. => 이거의 개수가 나온다.
		if (remain - need[i] < 0) continue;
		if (pivot + match(remain - need[i], K - 1, false) > loc) {
			ret[p] = i;
			skip(remain - need[i], K - 1, false, loc, p + 1);
			return;
		}
		pivot += match(remain - need[i], K - 1, false);
	}

}

void findMax(int remain) {
	if (remain <= 0) return;
	if (remain % 2 == 1) {
		printf("7");
		findMax(remain - 3);
	}
	else {
		while (remain) {
			printf("1");
			remain -= 2;
		}
	}

}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		memset(dp, -1, sizeof(dp));
		// N개를 써서, 가장 작은 수, 가장 큰 수 만들어야 함.
		// 표현 가능한 최소 자리,
		// 표현 가능한 최대 자리를 구한다.
		int minV = 0, maxV = 0;
		for (int k = 1; k < 100; k++) {
			if (isPossible(N, k, 1)) {
				if (!minV) minV = k;
				maxV = k;
			}
		}

		// 최소 minV자리,
		// 최대 maxV자리로 만들기 가능.

		memset(dp, -1, sizeof(dp));

		skip(N, minV, true, 0, 0);
		for (int i = 0; i < minV; i++)
			printf("%d", ret[i]);
		printf(" ");

		findMax(N);
		puts("");

	}

}