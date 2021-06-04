#include <cstdio>
#include <cstring>
#include <algorithm>

int T;
double N, M, P;

// amount원을 duration 동안 rates%로, 한 달에 monthlyPay만큼 갚을 때 잔액
double balance(double amount, int duration, double rates, double monthlyPay) {
	double ret = amount;

	for (int i = 0; i < duration; i++) {
		ret = (ret * (1 + rates / 12 / 100));
		ret -= monthlyPay;
	}

	return ret;
}

// amount원을 duration동안 rates%. 그럼 한 달에 얼마 갚아야?
double payment(double amount, double duration, double rates) {

	double lo = 0, hi = amount * (1 + rates / 12 / 100);

	for (int itr = 0; itr < 100; itr++) {
		double mid = (lo + hi) / 2;

		// mid 만큼 갚았을 때..
		// 0보다 크면 더 갚아야돼. lo를 옮기기
		if (balance(amount, duration, rates, mid) > 0)
			lo = mid;
		else hi = mid;
	}

	return (hi + lo) / 2;
}

int main() {
	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		scanf("%lf %lf %lf", &N, &M, &P);

		printf("%.10lf\n", payment(N, M, P));

	}


}