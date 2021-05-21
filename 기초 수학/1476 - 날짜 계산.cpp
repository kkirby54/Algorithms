#include <cstdio>

int E, S, M;

int main() {
	scanf("%d %d %d", &E, &S, &M);

	int standard = S;

	int X;
	if (E == 15) E = 0;
	if (M == 19) M = 0;

	for (int i = 0; ;  i++) {
		X = standard + 28 * i;

		if (X % 15 == E && X % 19 == M) {
			break;
		}
	}

	printf("%d", X);
}