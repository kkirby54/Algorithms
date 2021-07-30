#include <cstdio>
#include <algorithm>

using namespace std;

int N;
int arr[100000];

long long fence(int left, int right) {
	if (left == right) return (long long) arr[left] * arr[left];

	int mid = (left + right) / 2;
	long long ret = max(fence(left, mid), fence(mid + 1, right));

	// 관통하는 max.
	int lo = mid, hi = mid + 1;
	int height = min(arr[lo], arr[hi]);
	long long width = (long long)arr[lo] + arr[hi];
	ret = max(ret, (long long) height * width);

	while (left < lo || hi < right) {
		if (lo == left) {
			hi++;
			width += arr[hi];
			height = min(height, arr[hi]);
		}
		else if (hi == right) {
			lo--;
			width += arr[lo];
			height = min(height, arr[lo]);
		}
		// 양쪽 다 확인한다.
		else {
			if (arr[lo - 1] > arr[hi + 1]) {
				lo--;
				width += arr[lo];
				height = min(height, arr[lo]);
			}
			else {
				hi++;
				width += arr[hi];
				height = min(height, arr[hi]);
			}
		}

		ret = max(ret, (long long)width * height);
	}

	return ret;
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%d", arr + i);

	printf("%lld\n", fence(0, N - 1));
}