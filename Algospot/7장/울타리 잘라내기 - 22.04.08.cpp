#include <cstdio>
#include <cstring>
#include <algorithm>

int C, N, H[20005];

// [start, end]까지 최대를 구한다.
int fence(int start, int end) {
	if (start == end) return H[start];
	if (start > end) return 0;

	int mid = (start + end) / 2;

	// 뚫고 들어가는 max를 구하자.
	int lo = mid;
	int hi = mid + 1;
	int minHeight = std::min(H[lo], H[hi]);
	int maxVal = 2 * minHeight;

	while (lo >= start && hi <= end) {
		int p = (start <= lo - 1) ? H[lo - 1] : -1;
		int q = (hi + 1 <= end) ? H[hi + 1] : -1;


		if (p == q == -1) break;
		
		if (p >= q) {
			lo--;
			minHeight = std::min(minHeight, p);
		}
		else if (p < q) {
			hi++;
			minHeight = std::min(minHeight, q);
		}

		// 실제 값 갱신
		maxVal = std::max(maxVal, (hi - lo + 1) * minHeight);
	}

	int ret = std::max(fence(start, mid), fence(mid + 1, end));
	ret = std::max(ret, maxVal);

	return ret;
}

int main() {
	scanf("%d", &C);

	while (C--) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%d", H + i);
		}

		int ans = fence(0, N - 1);
		printf("%d\n", ans);
	}

}