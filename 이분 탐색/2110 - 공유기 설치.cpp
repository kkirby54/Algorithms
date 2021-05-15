#include <cstdio>
#include <algorithm>

int N, C;
int arr[200000];

int main() {
	scanf("%d %d", &N, &C);

	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}

	std::sort(arr, arr + N);

	long long s = 0, e = 1000000000;
	while (s + 1 < e) {
		long long mid = (s + e) / 2;
		//printf("%lld, %lld 시작합니다\n", s, e);

		// mid 간격 이상으로 설치한다고 하자.

		// 0번 마을 무조건 놓고
		// 쭉 돌면서, 거리를 저장하는 변수 하나.
		// 그게 mid이상이 되면, 빼기
		int dist = 0;
		int ret = 1;

		for (int i = 0; i < N - 1; i++) {
			dist += arr[i + 1] - arr[i];

			if (dist >= mid) {
				//printf("%d에 하나 놓자\n", i+1);
				dist = 0;
				ret++;
			}
		}

		if (ret >= C) s = mid;
		else e = mid;

	}
	printf("%lld", s);

}