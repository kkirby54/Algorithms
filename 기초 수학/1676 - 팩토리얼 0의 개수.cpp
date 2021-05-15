#include <cstdio>

int main() {
	int N;
	int cnt = 0;
	scanf("%d", &N);

	for (int i = 2; i <= N; i++) {
		int tmp = i;

		while (tmp % 5 == 0) {
			cnt++;
			tmp /= 5;
		}
	}

	printf("%d", cnt);

}