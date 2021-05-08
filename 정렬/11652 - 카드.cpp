#include <cstdio>
#include <algorithm>

int N;
long long arr[100000];

int main() {
	scanf("%d", &N);

	long long ret = 0;
	int curr_max = 0;
	int tmp;

	for (int i = 0; i < N; i++) {
		scanf("%lld", arr + i);
	}
	std::sort(arr, arr + N);

	for (int i = 0; i < N; i++) {
		tmp = 1;
		while (arr[i] == arr[i + 1]) {
			tmp++;
			i++;
		}
		if (curr_max < tmp) {
			curr_max = tmp;
			ret = arr[i];
		}
	}

	printf("%lld\n", ret);
}