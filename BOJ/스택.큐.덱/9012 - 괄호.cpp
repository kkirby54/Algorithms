#include <cstdio>
#include <algorithm>

int T;
char str[50];

int main() {
	scanf("%d", &T);

	for (int t = 0; t < T; t++) {
		scanf("%s", str);

		int count = 0;
		bool isPossible = true;

		for (int i = 0; str[i]; i++) {
			if (str[i] == '(') count++;
			else {
				count--;
				if (count < 0) {
					isPossible = false;
					break;
				}
			}
		}
		if (count != 0 || !isPossible) {
			printf("NO\n");
		}
		else printf("YES\n");

	}

}