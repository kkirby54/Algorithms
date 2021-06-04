#include <cstdio>
#include <algorithm>
#include <cstring>

const int INF = 2000000000;
int C, N, M;
double win_rate;

// b번의 게임 중 a번 이겼을 때 승률.
int ratio(long long a, long long b) {
	return (a * 100) / b;
}

// 승률은 wins / total.
long long neededGames(long long total, long long wins) {
	if (ratio(wins + INF, total + INF) - win_rate < 1) return -1;

	long long lo = 0, hi = INF;

	while (lo + 1 < hi) {
		long long mid = (lo + hi) / 2;

		// mid번 연승했다고 했을 때의 승률
		if (ratio(wins + mid, total + mid) - win_rate < 1) {
			lo = mid;
		}
		else hi = mid;
	}

	return hi;
}

int main() {
	scanf("%d", &C);

	for (int t = 0; t < C; t++) {
		scanf("%d %d", &N, &M);

		// 총 N개의 게임 중 M번 이긴 상황.
		win_rate = ratio(M, N);
		// win_rate + 1이 되려면?
		printf("%lld\n", neededGames(N, M));
	}

}