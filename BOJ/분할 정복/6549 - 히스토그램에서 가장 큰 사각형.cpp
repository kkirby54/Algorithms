#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int N;
int arr[100000];

// [left, right]의 최대값 리턴
long long fence(int left, int right) {
	if (left == right) return arr[left];

	int mid = (left + right) / 2;
	long long ret = max(fence(left, mid), fence(mid + 1, right));

	// 관통하는 max.
	int lo = mid, hi = mid + 1;
	int width = hi - lo + 1;
	int height = min(arr[lo], arr[hi]);
	ret = max(ret, (long long)height * width);

	// 모든 구간을 훑는다.
	while (left < lo || hi < right) {
		// arr[lo-1] vs arr[hi+1] 중에서,
		// 무조건 높이가 높은 쪽으로 이동한다.
		// 또는 맨 끝까지 도달한다면? 그 때는 높이를 -1로 한다.
		if (lo == left) {
			hi++;
			height = min(height, arr[hi]);
		}
		else if (hi == right) {
			lo--;
			height = min(height, arr[lo]);
		}
		else {
			if (arr[lo - 1] > arr[hi + 1]) {
				lo--;
				height = min(height, arr[lo]);
			}
			else {
				hi++;
				height = min(height, arr[hi]);
			}
		}

		ret = max(ret, (long long)height * (++width));
	}

	return ret;
}

int main() {
	while (1) {
		scanf("%d", &N);
		if (!N) return 0;
		for (int i = 0; i < N; i++) scanf("%d", arr + i);

		printf("%lld\n", fence(0, N - 1));

	}

}