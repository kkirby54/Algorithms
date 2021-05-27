#include <cstdio>
#include <cstring>

int main() {
	char str[35];
	int B, length;
	int ret = 0, digit = 1;
	scanf("%s %d", str, &B);

	length = strlen(str);
	for (int i = length - 1; i >= 0; i-- ) {
		if ('0' <= str[i] && str[i] <= '9')
			ret += (str[i] - '0') * digit;
		else ret += (str[i] - 'A' + 10) * digit;
		digit *= B;
	}
	printf("%d", ret);

}