#include <cstdio>
#include <algorithm>

int arr[5000001];
int main() {
	int N, K;
	scanf("%d %d", &N, &K);

	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}

	std::sort(arr, arr + N);
	printf("%d", arr[K-1]);

}