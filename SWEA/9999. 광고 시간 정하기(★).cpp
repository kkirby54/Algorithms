#include <cstdio>
#include <algorithm>
using namespace std;

int TC, L, N, s[100000], e[100005];

int main() {
	// freopen("input.txt", "r", stdin);

	scanf("%d", &TC);
	for (int tc = 1; tc <= TC; tc++) {
		scanf("%d %d", &L, &N);
		int last = 0;
		int pSum[100001] = { 0 };
		for (int i = 0; i < N; i++) {
			scanf("%d %d", s + i, e + i);
			int tmpTime = e[i] - s[i];
			pSum[i + 1] = pSum[i] + tmpTime;
			last = max(last, e[i]);
		}
		int ret = 0;

		// pSum[i + 1]에는, i번째까지의 피크 타임의 합이 적혀 있다.
		// 따라서 pSum[i+1] - pSum[i]하면 딱 정확히 i번째의 피크 타임의 합.
		for (int i = 0; i < N; i++) {
			int start = s[i];
			
			int endIdx = upper_bound(e + i, e + N, start + L) - e;
			int end = e[endIdx];

			// 더 큰게 없다면,
			if (endIdx == N) {
				ret = max(ret, pSum[N] - pSum[i]);
			}
			else {
				// |-----|            |-----------|
				// 여기서 그러면
				// endIdx까지가 포함된다고.
				// endIdx - 1까지 포함을 하고,
				// (start + L) - s[endIdx] 하면 됨.

				ret = max(ret,
					pSum[endIdx] - pSum[i] + max(0, (start + L - s[endIdx])));
			}

		}

		printf("#%d %d\n", tc, ret);
	}
}