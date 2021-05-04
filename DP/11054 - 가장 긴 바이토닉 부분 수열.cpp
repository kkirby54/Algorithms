#include <cstdio>
#include <cstring>
#include <algorithm>

int N;
int arr[1000];

int LIS[1000];
int LDS[1000];

// 항상 커야함.

int main() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);

		LIS[i] = 1;
		for (int j = 0; j < i; j++) {
			if (arr[i] > arr[j]) {
				LIS[i] = std::max(LIS[i], LIS[j] + 1);
			}
		}
	}
	
	for (int i = N - 1; i >= 0; i--) {
		LDS[i] = 1;
		for (int j = N - 1; j > i; j--) {
			if (arr[i] > arr[j]) {
				LDS[i] = std::max(LDS[i], LDS[j] + 1);
			}
		}
	}


	int Mx = 0;

	for (int i = 0; i < N; i++) {
		Mx = std::max(Mx, LIS[i] + LDS[i]);
	}

	printf("%d", Mx - 1);

}