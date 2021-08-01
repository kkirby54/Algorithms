#include <cstdio>
#include <algorithm>

int C, N, R[200], P[200];

int gcd(int p, int q) {
	if (q == 0) return p;
	return gcd(q, p % q);
}

int main() {
	scanf("%d", &C);
	for (int t = 0; t < C; t++) {
		scanf("%d", &N);

		for (int i = 0; i < N; i++) scanf("%d", R + i);
		for (int i = 0; i < N; i++) scanf("%d", P + i);

		// R들의 최대공약수를 구해본다.
		// 그러고 나서 최대공약수로 나눠버리면,
		// 이 재료들의 비율이 된다.
		int G = R[0];
		for (int i = 1; i < N; i++) G = gcd(G, R[i]);
		for (int i = 0; i < N; i++) R[i] /= G;

		// 이제 후보지들을 돈다.
		// 그러면서 곱해야할 최대치를 찾는다.
		int Mul = 1;
		for (int i = 0; i < N; i++) {
			// P[i] / R[i]를 넘는 최소의 정수.
			Mul = std::max(Mul, ((P[i] - 1) / R[i]) + 1);
		}

		//printf("최대 %d번 곱해야 함\n", Mul);
		for (int i = 0; i < N; i++) {
			printf("%d ", (R[i] * Mul - P[i]));
		}
		puts("");

	}


}