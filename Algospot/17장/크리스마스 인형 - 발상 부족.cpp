#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

int T, N, K, tmp;

long long pSum[100002] = { 0 };

// 0607. 2번 문제 한 번에 봤을 때 잘 이해가 안 감.
// 그냥 앞에서부터 보면서, 중복된 수가 나타나면 ++하고 초기화하는 식으로 그리디로 풀면 왜 안됨?
// - 수정 : 뭐야 그렇게 푸니까 되잖아.

// 풀이 1. DP로 풀기.
int MaxBuy(int k) {
	std::vector<int> ret(N+1, 0);

	// 마지막에 나온 수를 저장한다.
	// prev[pSum[i]] = . 이런 식으로.
	std::vector<int> prev(k, -1);

	for (int i = 0; i <= N; i++) {
		// 안 사는 경우. ret[i] = ret[i-1]. 그냥 그대로 이전으로 넘겨야 한다.
		if (i > 0) ret[i] = ret[i - 1];
		else ret[i] = 0;

		// pSum[i]이 언제 마지막으로 나타났는지 알아낸 후
		int loc = prev[pSum[i]];
		// 나타났다면, 걔에다가 1을 더한다.
		if (loc != -1) {
			ret[i] = std::max(ret[i], ret[loc] + 1);
		}
		
		// 갱신한다. 마지막에 나온 위치가 i라는 의미에서 prev 배열.
		prev[pSum[i]] = i;
	}

	return ret.back();
}

int main() {
	scanf("%d", &T);

	for (int t = 0; t < T; t++) {
		scanf("%d %d", &N, &K);

		for (int i = 0; i < N; i++) {
			scanf("%d", &tmp);
			pSum[i + 1] = (pSum[i] + tmp) % K;
		}

		// 부분 문제 1. 0 ~ K-1 카운트해서 조합.
		std::vector<long long> cnt(K, 0);
		std::vector<long long> cnt2(K, 0);
		for (int i = 0; i <= N; i++) {
			cnt[pSum[i]]++;
		}

		long long ans1 = 0;

		for (int i = 0; i < K; i++) {
			ans1 += ((cnt[i] * (cnt[i] - 1)) / 2) % 20091101;
			ans1 %= 20091101;
		}
		printf("%lld ", ans1 % 20091101);


		// 부분 문제 2. 여러 개 골라서.

		// 풀이 2. Greedy하게 풀기.
		long long ans2 = 0;
		for (int i = 0; i <= N; i++) {
			// 이미 존재하면 ++해버려
			if (cnt2[pSum[i]] != 0) {
				ans2++;
				std::fill(cnt2.begin(), cnt2.end(), 0);
			}
			cnt2[pSum[i]]++;
		}
		
		printf("%lld\n", ans2);
	}

}