#include <cstdio>
#include <algorithm>

int N, C;
int arr[200000];

// 거리를 최소 X 띄우고 설치한다고 했을 때,
// 설치 가능한 공유기의 수를 리턴한다.
int getCnt(int X) {
	int sum = 1; // 일단 첫번째 집.
	int prev = arr[0]; // 이전에 설치한 집의 위치 저장.
	for (int i = 1; i < N; i++) {
		int curr = arr[i];
		
		// 현재 위치 - 마지막으로 공유기를 놓은 위치 >= X라면, 여기에 공유기를 설치한다.
		if (curr - prev >= X) {
			prev = curr;
			sum++;
		}
	}
	return sum;
}

int main() {
	scanf("%d %d", &N, &C);
	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}
	std::sort(arr, arr + N);

	// C개의 공유기를 N개의 집에 설치해야 한다.
	// 집의 좌표는 arr[].
	
	// 거리를 mid로 둔다.
	int lo = 0, hi = 1000000000;

	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;

		// C개보다 더 많이 설치하게 된다면,
		// 거리를 늘려야 함.
		if (getCnt(mid) >= C) {
			lo = mid;
		}
		else hi = mid;

	}
	printf("%d\n", lo);
}