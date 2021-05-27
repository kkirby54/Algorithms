#include <cstdio>
#include <algorithm>


int N, M, arr[500000], tmp;

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}

	std::sort(arr, arr + N);

	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		scanf("%d", &tmp);

		int pos1 = std::lower_bound(arr, arr + N, tmp) - arr;
		int pos2 = std::lower_bound(arr, arr + N, tmp + 1) - arr;
		printf("%d ", pos2 - pos1);
	}

}