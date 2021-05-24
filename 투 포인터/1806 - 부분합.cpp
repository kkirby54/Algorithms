#include <cstdio>
#include <algorithm>

const int INF = 1000000;

int N, S;
int arr[100000];

int lo, hi, sum = 0;
int min_length = INF;

int main() {
	scanf("%d %d", &N, &S);
	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}

	while (lo < N){

		if (hi < N && sum < S) 
			sum += arr[hi++];
		else 
			sum -= arr[lo++];

		if (sum >= S) min_length = std::min(min_length, hi - lo);
	}

	printf("%d", min_length == INF ? 0 : min_length);
}