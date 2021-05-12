#include <cstdio>

typedef long long LL;

LL GCD(LL a, LL b) {
	while (1) {
		LL r = a % b;
		if (!r) break;

		a = b;
		b = r;
	}

	return b;
}

int main() {
	LL A, B, k;
	scanf("%lld %lld", &A, &B);

	k = GCD(A, B);

	for (LL i = 0; i < k; i++)
		printf("1");
}