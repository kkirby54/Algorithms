#include <cstdio>
#include <algorithm>

int main() {
	int N, arr[1000];
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}
	std::sort(arr, arr + N);

	int ret = arr[0];
	int sum = arr[0];

	for (int i = 1; i < N; i++) {
		sum += arr[i];
		ret += sum;
	}
	printf("%d", ret);

}