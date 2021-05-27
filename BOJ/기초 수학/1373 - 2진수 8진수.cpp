#include <cstdio>
#include <cstring>

char str[1000001];
char ret[1000001];

int main() {
	scanf("%s", str);

	int length = strlen(str);
	int k = 0;
	int tmp;

	for (int i = length - 1; i >= 0; i--) {

		// i-2, i-1, i를 본다.
		int j = i - 3;
		int digit = 1;
		tmp = 0;

		while (i >= 0 && i != j) {
			tmp += (str[i] - '0') * digit;
			
			i--;
			digit *= 2;
		}
		i++;

		ret[k++] = tmp + '0';
	}

	for (int i = k-1; i >= 0; i--)
		printf("%c", ret[i]);

}