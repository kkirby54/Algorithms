#include <cstdio>
#include <algorithm>
#include <cmath>

int main() {
	int N, arr[9];
	int ret = 0;

	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}
	
	std::sort(arr, arr + N);

	do {
		int tmp = 0;

		for (int i = 0; i < N-1; i++) {
			tmp += abs(arr[i] - arr[i + 1]);
		}
		ret = std::max(ret, tmp);

	} while (std::next_permutation(arr, arr + N));

	printf("%d", ret);

}