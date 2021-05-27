#include <cstdio>

int main() {
	int N;
	int ret = 1;
	scanf("%d", &N);

	for (int i = 2; i <= N; i++)
		ret *= i;
	printf("%d", ret);
}