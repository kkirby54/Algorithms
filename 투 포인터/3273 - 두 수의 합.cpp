#include <cstdio>
#include <algorithm>

int N, X, arr[100000];

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}
	std::sort(arr, arr + N);

	scanf("%d", &X);

	int s = 0, e = N - 1, result = 0;

	while (s < e) {
		if (arr[s] + arr[e] == X) result++;
		// 둘의 합이 X보다 크다면, e를 --
		if (arr[s] + arr[e] > X) e--;
		// 둘의 합이 X보다 작거나 같, s를 ++
		else if (arr[s] + arr[e] <= X) s++;
	}

	printf("%d", result);

}