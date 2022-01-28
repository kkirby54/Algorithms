#include <cstdio>
#include <algorithm>

int T, N, K, W[200000], S[200000];

bool isPossible(int val) {
	int cnt = 0;
	int blockNum = 0;

	// val보다 작거나 같으면, cnt를 올린다.
	for (int i = 0; i < N; i++) {
		if (W[i] <= val) {
			cnt++;
		}
		else cnt = 0;

		if (S[blockNum] == cnt) {
			cnt = 0;
			if (++blockNum == K) return true;

		}
	}

	return false;
}

int main() {
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d %d", &N, &K);

		// Wear level이 적혀있음.
		for (int i = 0; i < N; i++) {
			scanf("%d", W + i);
		}
		// K개의 덩어리
		for (int i = 0; i < K; i++) {
			scanf("%d", S + i);
		}

		int lo = 0, hi = 200001;

		while (lo + 1 < hi) {
			int mid = (lo + hi) / 2;
			
			// 되면, val을 줄여
			if (isPossible(mid))
				hi = mid;
			else lo = mid;
		}
		
		printf("#%d %d\n", t, hi);
	}
 }
