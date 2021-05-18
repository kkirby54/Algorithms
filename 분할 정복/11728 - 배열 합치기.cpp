#include <cstdio>
#include <algorithm>

int N, M, Arr[2000000];

int main() {
	scanf("%d %d", &N, &M);

	for (int i = 0; i < N + M; i++) {
		scanf("%d", Arr + i);
	}
	std::sort(Arr, Arr + N+M);
	for (int i = 0; i < N + M; i++) {
		printf("%d ", Arr[i]);
	}


}