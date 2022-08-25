#include <cstdio>

int main() {
	int pieces[] = { 1, 1, 2, 2, 2, 8 };

	for (int i = 0; i < 6; i++) {
		int tmp;
		scanf("%d", &tmp);

		printf("%d ", pieces[i] - tmp);
	}

}