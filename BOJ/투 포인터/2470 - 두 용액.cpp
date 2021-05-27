#include <cstdio>
#include <cmath>
#include <algorithm>

int N, X, arr[100000];

int curr = 2000000001;
std::pair<int, int> ret;

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}
	std::sort(arr, arr + N);

	int s = 0, e = N - 1;

	while (s < e) {
		// arr[s] + arr[e]와 curr을 비교.
		if (abs(arr[s] + arr[e]) < curr) {
			curr = abs(arr[s] + arr[e]);
			ret = std::make_pair(arr[s], arr[e]);
		}
		if (arr[s] + arr[e] < 0) s++;
		else e--;

	}

	printf("%d %d", ret.first, ret.second);

} 