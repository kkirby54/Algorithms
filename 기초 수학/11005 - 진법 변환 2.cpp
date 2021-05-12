#include <cstdio>
#include <cstring>

int main() {
	char str[35];
	int N, B, k = 0;

	scanf("%d %d", &N, &B);

	while (N) {
		str[k++] = (N % B) >= 10 ? (N % B) + 'A' - 10 : (N % B) + '0';
		N /= B;
	}

	for (int i = k - 1; i >= 0; i--) {
		printf("%c", str[i]);
	}

}