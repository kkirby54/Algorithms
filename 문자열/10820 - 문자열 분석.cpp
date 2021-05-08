#include <cstdio>

int main() {
	char str[101];

	while (scanf("%[^\n]s", str) != EOF) {
		int cnt[4] = { 0 };

		for (int i = 0; str[i]; i++) {
			if (str[i] == ' ') {
				cnt[3]++;
			}
			else if ('0' <= str[i] && str[i] <= '9') cnt[2]++;
			else if ('a' <= str[i] && str[i] <= 'z') cnt[0]++;
			else cnt[1]++;
		}

		for (int i = 0; i < 4; i++) {
			printf("%d ", cnt[i]);
		}
		puts("");
		
		getchar();
	}

}