#include <cstdio>
#include <algorithm>

int N;
int arr[1000000];

int main() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}
	std::sort(arr, arr + N);
	for (int i = 0; i < N; i++) {
		printf("%d\n", arr[i]);
	}

}