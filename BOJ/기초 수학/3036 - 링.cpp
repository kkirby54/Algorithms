#include <cstdio>
#include <algorithm>
#include <vector>

int N;
int arr[100];

int gcd(int p, int q) {
	if (q == 0) return p;
	return gcd(q, p % q);
}

int main() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
		if (i != 0) {
			int divisor = gcd(arr[0], arr[i]);

			printf("%d/%d\n", arr[0] / divisor, arr[i] / divisor);


		}
	}

}