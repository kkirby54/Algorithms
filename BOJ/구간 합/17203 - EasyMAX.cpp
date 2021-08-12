#include <cstdio>
#include <cmath>
#include <algorithm>

int main() {
	int N, Q, s, e;
	int pSum[1001] = { 0 };
	int arr[1000];
	scanf("%d %d", &N, &Q);

	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
		if (i != 0)
			pSum[i] = pSum[i - 1] + abs(arr[i] - arr[i - 1]);
	}

	for (int i = 0; i < Q; i++) {
		scanf("%d %d", &s, &e);
		s--; e--;
		printf("%d\n", pSum[e] - pSum[s]);
	}

}