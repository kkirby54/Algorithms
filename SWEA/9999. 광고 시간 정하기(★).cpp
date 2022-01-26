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

		// pSum[i + 1]����, i��°������ ��ũ Ÿ���� ���� ���� �ִ�.
		// ���� pSum[i+1] - pSum[i]�ϸ� �� ��Ȯ�� i��°�� ��ũ Ÿ���� ��.
		for (int i = 0; i < N; i++) {
			int start = s[i];
			
			int endIdx = upper_bound(e + i, e + N, start + L) - e;
			int end = e[endIdx];

			// �� ū�� ���ٸ�,
			if (endIdx == N) {
				ret = max(ret, pSum[N] - pSum[i]);
			}
			else {
				// |-----|            |-----------|
				// ���⼭ �׷���
				// endIdx������ ���Եȴٰ�.
				// endIdx - 1���� ������ �ϰ�,
				// (start + L) - s[endIdx] �ϸ� ��.

				ret = max(ret,
					pSum[endIdx] - pSum[i] + max(0, (start + L - s[endIdx])));
			}

		}

		printf("#%d %d\n", tc, ret);
	}
}