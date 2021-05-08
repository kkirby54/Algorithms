#include <cstdio>

int main() {
	char str[101];
	int cnt = 0;
	scanf("%s", str);

	for (int i = 0; str[i]; i++) cnt++;
	printf("%d", cnt);

}