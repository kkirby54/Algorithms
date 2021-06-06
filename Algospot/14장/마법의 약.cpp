#include <cstdio>
#include <algorithm>

int C, N, R[1001], P[1001];

int gcd(int p, int q) {
	if (q == 0) return p;
	return gcd(q, p % q);
}

int main() {
	scanf("%d", &C);
	for (int t = 0; t < C; t++) {
		scanf("%d", &N);

		for (int i = 0; i < N; i++)
			scanf("%d", R + i);

		for (int i = 0; i < N; i++) {
			scanf("%d", P + i);

		}

		// R들의 최대공약수를 구해보자.
		int G = R[0];
		for (int i = 1; i < N; i++) {
			G = gcd(G, R[i]);
		}

		// 이제 그 만큼을 나눠버린다.
		for (int i = 0; i < N; i++)
			R[i] /= G;

		int MaxProp = 0;
		for (int i = 0; i < N; i++) {
			// P[i] / R[i]를 해서 제일 큰 걸 찾는다.
			if (P[i] <= R[i]) {
				MaxProp = std::max(MaxProp, 1);
			}
			// P[i] > R[i]라면. 이제 나눠본다
			else {
				int a = ((P[i] + R[i] - 1) / R[i]);

				MaxProp = std::max(MaxProp, a);
			}

		}
	
		for (int i = 0; i < N; i++) {
			R[i] *= MaxProp;
			printf("%d ", R[i] - P[i]);
		}
		puts("");
	}

}