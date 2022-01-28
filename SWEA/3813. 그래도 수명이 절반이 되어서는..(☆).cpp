#include <cstdio>
#include <algorithm>

int T, N, K, W[200000], S[200000];

bool isPossible(int val) {
	int cnt = 0;
	int blockNum = 0;

	// val���� �۰ų� ������, cnt�� �ø���.
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

		// Wear level�� ��������.
		for (int i = 0; i < N; i++) {
			scanf("%d", W + i);
		}
		// K���� ���
		for (int i = 0; i < K; i++) {
			scanf("%d", S + i);
		}

		int lo = 0, hi = 200001;

		while (lo + 1 < hi) {
			int mid = (lo + hi) / 2;
			
			// �Ǹ�, val�� �ٿ�
			if (isPossible(mid))
				hi = mid;
			else lo = mid;
		}
		
		printf("#%d %d\n", t, hi);
	}
 }
