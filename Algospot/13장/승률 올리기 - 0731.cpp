#include <cstdio>
#include <algorithm>

int T, N, M;

// 연승을 X번 했을 때, 승률
long long getWinrate(long long X) {
	return (M + X)*100 / (N + X);
}

int main() {
	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		scanf("%d %d", &N, &M);

		// N번 중 M번 승리함.
		long long winrate = (long long)M * 100 / N;

		long long lo = 0, hi = 2000000000;

		// winrate가 1 증가하는 구간은?
		// 이전 문제들과 달리 실수가 아니라 정수로 표현됐기 때문에
		// lo + 1 < hi와 같이 표현하는 게 가능해진다.
		while (lo + 1 < hi) {
			long long mid = (lo + hi) / 2;
			
			// mid만큼 해본다.
			if (getWinrate(mid) == winrate) {
				lo = mid;
			}
			else hi = mid;
		}
		if (hi == 2000000000) printf("-1\n");
		else printf("%lld\n", hi);

	}


}