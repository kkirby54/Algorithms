#include <cstdio>

int GCD(int a, int b) {
	while (1) {
		int r = a % b;
		if (!r) break;

		a = b;
		b = r;
	}

	return b;
}

int main() {
	int A, B;
	scanf("%d %d", &A, &B);

	int gcd = GCD(A, B);

	printf("%d\n%d", gcd, A * B / gcd);

}