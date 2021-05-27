#include <cstdio>
#include <algorithm>

int N, M, tmp, arr[500000];

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}

	std::sort(arr, arr + N);

	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		scanf("%d", &tmp);

		int s = 0, e = N;
		bool isPossible = false;
		while (s + 1 < e) {
			int mid = (s + e) / 2;

			// mid번째와 비교한다.
			if (arr[mid] == tmp) {
				isPossible = true;
				break;
			}

			if (arr[mid] > tmp) {
				e = mid;
			}
			else s = mid;

		}
		if (isPossible || arr[s] == tmp) printf("1 ");
		else printf("0 ");

	}

}