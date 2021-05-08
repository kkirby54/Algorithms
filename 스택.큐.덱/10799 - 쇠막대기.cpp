#include <cstdio>
#include <algorithm>

int T;
char str[100005];

int main() {
	scanf("%s", str);

	int count = 0;
	int ret = 0;

	for (int i = 0; str[i]; i++) {
		if (str[i] == '(') count++;
		else {
			count--;
			// 레이저
			if (str[i - 1] == '(') ret += count;
			else ret++;
		}
	}
	printf("%d", ret);

}