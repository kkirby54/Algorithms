#include <cstdio>
#include <algorithm>

int main() {
	int N, M;
	scanf("%d %d", &N, &M);

	if (N == 1) printf("1");
	else if (N == 2) {
		printf("%d", std::min(4, (M + 1) / 2));
	}
	else {
		if (M <= 6) {
			printf("%d", std::min(4, M));
		}
		else {
			printf("%d",M - 2);
		}

	}

}