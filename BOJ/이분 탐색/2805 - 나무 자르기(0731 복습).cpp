#include <cstdio>
#include <algorithm>

int N, M, height[1000000];

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		scanf("%d", height + i);
	}

	// 높이의 최댓값을 구해야 한다.
	// 잘라서 나온 게 적어도 M 이상이어야 한다.
	long long lo = 0, hi = 2000000000;
	
	while (lo + 1 < hi) {
		long long mid = (lo + hi) / 2;
		
		long long ret = 0;
		// mid로 설정했을 때, 나무를 잘라본다.
		for (int i = 0; i < N; i++) {
			if (height[i] - mid > 0)
				ret += height[i] - mid;
		}

		// M보다 자른 높이들의 합이 낮다면,
		// hi를 낮춰야 한다.
		if (ret < M) hi = mid; 
		// 여기서 등호를 빼는 이유는, 
		// 설정 가능한 '최대'를 구하기 때문에
		// ret == M이라면 lo를 mid로 만들어서 최댓값으로 움직여야 한다.
		// 즉, lo = 가능한 최대, hi = 불가능한 최소.

		else lo = mid;

	}

	printf("%lld\n", lo);
}