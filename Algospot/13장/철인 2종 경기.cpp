#include <cstdio>
#include <algorithm>
#include <cstring>

int T, N;
double R[21], K[21];

// i번째 선수가 거리 run일 때 걸리는 시간
double time(int i, double run) {
	return run / R[i] + (T - run) / K[i];
}

// run일 때 others - cheater를 반환한다.
double subtract(double run) {
	double cheater = time(N - 1, run);
	double others = time(0, run);

	for (int i = 1; i < N - 1; i++) {
		// 2등을 골라야 하니까.
		others = std::min(others, time(i, run));
	}

	return others - cheater;
}

// others - cheater를 최대로 만들어야 함.
// 지금 처리하는 값은 r임.
double Duathlon(double lo, double hi) {

	for (int itr = 0; itr < 100; itr++) {
		double aab = (2 * lo + hi) / 3;
		double abb = (2 * hi + lo) / 3;

		// lo > hi인 경우에는..
		if (subtract(aab) > subtract(abb)) {
			hi = abb;
		}
		else lo = aab;
	}
	return (lo + hi) / 2;
}

int main() {
	scanf("%d %d", &T, &N);
	for (int i = 0; i < N; i++) {
		// i번째 선수의 R속력, K속력 입력
		scanf("%lf %lf", R + i, K + i);
	}

	bool isPossible = false;
	// 되나 안되나 봐바
	for (int r = 0; r <= 100; r++) {
		if (subtract(r) > 0) {
			isPossible = true;
			break;
		}
	}
	if (!isPossible) printf("The cheater cannot win.");
	else printf("%lf\n", Duathlon(0, 101));
}