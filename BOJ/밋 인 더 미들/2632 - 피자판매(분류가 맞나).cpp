#include <cstdio>
#include <algorithm>

int G, M, N;
int Marr[1000], Narr[1000];
long long ret;
int cnt[2000005] = { 0 };

int main() {
	scanf("%d", &G);
	scanf("%d %d", &M, &N);

	for (int i = 0; i < M; i++) {
		scanf("%d", Marr + i);
	}
	for (int i = 0; i < N; i++) {
		scanf("%d", Narr + i);
	}

	cnt[0] = 1;

	// M배열 돌기
	for (int i = 0; i < M; i++) {
		// M-1개의 가짓수.
		int sum = 0;

		for (int j = i; j < i + (M - 1); j++) {
			// Marr[i]부터.. Marr[i + (M-1)]까지.
			// 즉. 0이라하면
			// 0 ~ 4

			// 1이라 하면
			// 1 ~ 5인데 j % M 해주면
			// 0

			// sum에다가 쌓아간다
			// j = i이면 sum = Marr[j]
			// j = i + 1 이면 sum = sum + Marr[j]
			sum += Marr[j % M];

			// 마지막 case는 따로 처리(모든 조각 합)
			if (i == 0 && j == i + (M - 2)) {
				++(cnt[sum + Marr[(j + 1) % M]]);
			}

			++(cnt[sum]);
		}
	}

	ret += cnt[G];


	// 이제 N배열을 돌면서,
	// 같은 짓을 한다.
	for (int i = 0; i < N; i++) {
		int sum = 0;
		for (int j = i; j < i + (N - 1); j++) {
			sum += Narr[j % N];

			// 목표 피자보다 sum이 작으면 안됨.
			if (G < sum) continue;

			// G-sum이 몇 개였는지 확인하고 결과에 +
			if (cnt[G - sum]) {
				ret += cnt[G - sum];
			}

			if (i == 0 && j == i + (N - 2)) {
				sum += Narr[(j + 1) % N];
				ret += cnt[G - sum];
			}

		}

	}
	printf("%lld", ret);

}