#include <cstdio>

int N, M;
int arr[10000];

int lo, hi, sum;
int cnt;

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}

	while (lo < N-1) {
		if (sum == M) cnt++;

		if (hi <= N-1 &&
			sum + arr[hi] <= M) sum += arr[hi++];
		else {
			sum -= arr[lo++];
		}
	}

	printf("%d", cnt);
}