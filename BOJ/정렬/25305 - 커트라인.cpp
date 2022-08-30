#include <cstdio>
#include <algorithm>
#include <functional>
int N, K;
int arr[1000];

int main() {
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}

	std::sort(arr, arr + N, std::greater<int>());

	printf("%d\n", arr[K - 1]);

}